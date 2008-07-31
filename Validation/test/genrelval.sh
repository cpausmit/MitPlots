#!/bin/bash
# $Id: genrelval.sh,v 1.4 2008/07/25 12:41:41 loizides Exp $
#
# genrelval.sh: Release validation script for generated particles
#
# $Id: genrelval.sh,v 1.4 2008/07/25 12:41:41 loizides Exp $
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
    echo '
process Gen =
{
    # request 2 events for validation purpose
    untracked PSet maxEvents = { untracked int32 input = 5 }

    include "FWCore/MessageService/data/MessageLogger.cfi"
    include "Configuration/StandardSequences/data/SimulationRandomNumberGeneratorSeeds.cff"
    include "SimGeneral/HepPDTESSource/data/pythiapdt.cfi"

    # verbose parameter set for pythia
    source = PythiaSource
    {
        untracked int32  pythiaPylistVerbosity = 1
        untracked bool   pythiaHepMCVerbosity  = false
        untracked int32  maxEventsToPrint      = 5
        untracked double filterEfficiency      = 1.

        PSet PythiaParameters = {
            vstring parameterSets = {
            }
        }
    }

    # load generator sequence (VtxSmeared is needed inside, missing dependence)
    include "Configuration/StandardSequences/data/VtxSmearedBetafuncEarlyCollision.cff"
    include "Configuration/StandardSequences/data/Generator.cff"

    # define the object service
    service = ObjectService { }

    # define the tree service
    service = TreeService {
        untracked vstring fileNames   = { "mit-gen" }
    }

    # customize the MIT filler
    module MitTreeFiller = FillMitTree {
        untracked bool defactive = false
        untracked PSet MCParticles = {
            untracked bool active = true
            untracked bool simActive = false
        }
    }

    # standard path of action of the module
    path p0 = { pgen, MitTreeFiller }

    # also make Edm output for the events we generate
    include "Configuration/EventContent/data/EventContent.cff"
    module FEVT = PoolOutputModule
    {
        using FEVTSIMEventContent
        untracked string fileName = "edm-gen.root"
    }

    # output path for the Edm file
    endpath outpath = { FEVT }

    # schedule the various path
    schedule = { p0, outpath }
}
'
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

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(mod);
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
write_cfg > relval.cfg
cmsRun relval.cfg >pythia_raw.txt 2>/dev/null
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
