#!/bin/bash
# $Id: genrelval.sh,v 1.6 2008/11/21 20:12:26 loizides Exp $
#
# genrelval.sh: Release validation script for generated particles
#
# $Id: genrelval.sh,v 1.6 2008/11/21 20:12:26 loizides Exp $
#_____________________________________________________________________________________________
#
# Variables to configure:
#

# Assume there is already a CMSSW environment
# and that our code is compiled.

# Set the directory where the generated sample and logfiles
# will be placed.
export MY_BASE_DIR=/tmp/relval.`date +%s`

#
# end variables to configure.
#_____________________________________________________________________________________________
##############################################################################################
##############################################################################################

function write_cfg {
cat <<EOF
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

process.load('Configuration.StandardSequences.SimulationRandomNumberGeneratorSeeds_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')

   
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(25)
)

process.source = cms.Source("PythiaSource",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency      = cms.untracked.double(1.0),
    pythiaHepMCVerbosity  = cms.untracked.bool(False),
    comEnergy             = cms.untracked.double(10000.0),    
    maxEventsToPrint      = cms.untracked.int32(-1),

    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring()
    )
)                           
    
# load generator sequence (VtxSmeared is needed inside, missing dependence)
process.load('Configuration.StandardSequences.VtxSmearedBetafuncEarlyCollision_cff')
process.load('Configuration.StandardSequences.Generator_cff')

# include the MIT services and standard filler
process.ObjectService = cms.Service("ObjectService")

process.TreeService = cms.Service("TreeService",
    fileNames = cms.untracked.vstring("mit-gen")
)

process.MitTreeFiller = cms.EDAnalyzer("FillMitTree",
    fillers = cms.untracked.vstring('MetaInfos',
                                    'MCParticles',
                                    'MCEventInfo'), 

    MetaInfos = cms.untracked.PSet(
        hltActive  = cms.untracked.bool(False),
        fillerType = cms.untracked.string('FillerMetaInfos')
    ),

    MCParticles = cms.untracked.PSet(
        simActive  = cms.untracked.bool(False),
        fillerType = cms.untracked.string('FillerMCParticles')
    )
)
 
process.p0 = cms.Path( process.pgen * process.MitTreeFiller)

# also make Edm output for the events we generate
process.load('Configuration.EventContent.EventContent_cff')

process.FEVT = cms.OutputModule("PoolOutputModule",
    process.FEVTSIMEventContent,
    fileName = cms.untracked.string('edm-gen.root'),        
)
   
process.end = cms.EndPath( process.FEVT )
EOF
}


function write_macro {
    echo '
//--------------------------------------------------------------------------------------------------
void runGenRelVal(const char *files = "mit-gen_000.root")
{
  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
  gSystem->Load("$CMSSW_BASE/lib/slc4_ia32_gcc345/libMitAnaValidation.so");

  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 0;

  // set up the modules
  GenRelValMod *mod = new GenRelValMod;
  mod->SetWrite(1);
  mod->SetPrint(0);

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(mod);
  ana->SetUseHLT(0);
  ana->AddFile(files);

  // run the analysis after successful initialisation
  ana->Run(0);
}
'
}

##############################################################################################
##############################################################################################
#
# Generate sample and fill tree
mkdir -p $MY_BASE_DIR/prod
cd $MY_BASE_DIR/prod
write_cfg > relval.py
cmsRun relval.py >pythia_raw.txt 2>/dev/null
if (( $? )) ; then 
    echo "Problem generating sample:" >&2
    echo '' >&2
    cat pythia_raw.txt >&2
    echo "Output left in $MY_BASE_DIR" >&2
    exit 1
fi

# Parse pythia output into something easier to compare with tree.
# The following outputs: index, pdgcode, px, py, pz, E
# with a particular spacing similar to pylist.
PYFILE=$MY_BASE_DIR/prod/pythia_parsed.txt
cat pythia_raw.txt | \
    perl -ne 'if ($_ =~ /^(\s{4}\d{1})\s.{18}(.{5})(.{5})(.{36})/ or 
                  $_ =~ /^(\s{3}\d{2})\s.{18}(.{5})(.{5})(.{36})/ or 
                  $_ =~ /^(\s{2}\d{3})\s.{18}(.{5})(.{5})(.{36})/ or 
                  $_ =~ /^(\s{1}\d{4})\s.{18}(.{5})(.{5})(.{36})/) 
                { print "$1$2$3$4\n" ; }' > $PYFILE


# write+run the validation macro:
cd $MY_BASE_DIR/prod

write_macro > ./runGenRelVal.C

rec=`root -l -n -q ./runGenRelVal.C 2>&1`
if (( $? )) ; then 
    echo "Problem executing runGenRelVal.C:" >&2
    echo ''  >&2
    echo $rec >&2
    echo "Output left in $MY_BASE_DIR" >&2
    exit 1
fi

# do the diff of pythia output and mit tree contents obtained from macro:
diff $PYFILE macro_output.txt > diff_report.txt

# check if things are ok
if (( $? )) ; then 
    echo "Pythia output disagrees with GenParticles branch contents:" >&2
    cat diff_report.txt >&2
    echo "Output left in $MY_BASE_DIR" >&2
    exit 1
fi

# Cleanup
rm -rf $MY_BASE_DIR
exit 0
