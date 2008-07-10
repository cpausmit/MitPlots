#!/bin/bash
# $Id:$
#
# genrelval.sh: Release validation script for generated particles
#

#_____________________________________________________________________________________________
#
# Variables to configure:
#

# Assume there is already a CMSSW environment
# and that our code is compiled.

# Top directory for validation module:
export MOD=$CMSSW_BASE/src/MitRelVal

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
    untracked PSet maxEvents = { untracked int32 input = 3 }

    include "FWCore/MessageService/data/MessageLogger.cfi"
    include "Configuration/StandardSequences/data/SimulationRandomNumberGeneratorSeeds.cff"
    include "SimGeneral/HepPDTESSource/data/pythiapdt.cfi"

    # verbose parameter set for pythia
    source = PythiaSource
    {
        untracked int32  pythiaPylistVerbosity = 1
        untracked bool   pythiaHepMCVerbosity  = false
        untracked int32  maxEventsToPrint      = 3
        untracked double filterEfficiency      = 1.

        PSet PythiaParameters = {
            vstring parameterSets = {
            }
        }
    }

    # load generator sequence (VtxSmeared is needed inside, missing dependence)
    include "Configuration/StandardSequences/data/VtxSmearedBetafuncEarlyCollision.cff"
    include "Configuration/StandardSequences/data/Generator.cff"

    # define the tree service
    service = TreeService {
        untracked vstring fileNames   = { "mit-gen" }
    }

    # customize the MIT filler
    module MitTreeFiller = FillMitTree {
        untracked bool defactive = false
    	untracked PSet GenParts = {
		untracked bool active = true
		untracked string mitName = "GenParticles"
		untracked string edmName = "source"
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

function write_module {

    echo '
#include "MitRelVal/Mods/interface/RelVal.h"
#include "MitAna/DataTree/interface/Names.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace mithep;

ClassImp(mithep::RelVal)

//__________________________________________________________________________________________________
RelVal::RelVal(const char *name, const char *title) :
  TAModule    (name,title),
  fParticles  (0),
  fGenPartName(Names::gkGenPartBrn)
{}

//__________________________________________________________________________________________________

void RelVal::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here, we typically
  // initialize histograms and other analysis objects and request branches. For this module, we
  // request a branch of the MitTree and open a text file for writing.

  // Request the branches
  ReqBranch(fGenPartName,fParticles);

  // Open file for writing
  ofile = new std::ofstream("macro_output.txt");
  if (ofile->bad())
    std::cout<<"Problem opening output file\n";
}

//__________________________________________________________________________________________________
void RelVal::Process()
{
  // Process entries of the tree. For this module, we just load the branch and fill the histograms.

  LoadBranch(fGenPartName);
  std::cout<<"in a new event\n";
  for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
    const GenParticle *p = fParticles->At(i);
    int I     = i+1;                                         // Particle index (starts at 1)
    int KF    = p->GetPdgId();                               // Pdg code
    double p_x = p->Px(); if (fabs(p_x)<0.0005) p_x = 0.;    // Momenta.  We only compare the
    double p_y = p->Py(); if (fabs(p_y)<0.0005) p_y = 0.;    //  first 3 digits after the
    double p_z = p->Pz(); if (fabs(p_z)<0.0005) p_z = 0.;    //  decimal.
    double E   = p->E();  if (fabs(E  )<0.0005) E   = 0.;    // Energy
    char buf[254];
    sprintf(buf,"%5i%5i%9.3f%9.3f%9.3f%9.3f\n",I,KF,p_x,p_y,p_z,E);
    *ofile<<buf;
  }
}

//__________________________________________________________________________________________________
void RelVal::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this module, we close
  // the text file.

  ofile->close();
}
'

}

function write_buildfile {

    echo '
<use name=MitAna/TAM>
<use name=MitAna/DataTree>
<use name=MitAna/DataUtil>
<use name=root>
<export>
   <lib name=MitRelVal>
   <use name=MitAna/TAM>
   <use name=MitAna/DataTree>
   <use name=MitAna/DataUtil>
   <use name=root>
</export>
'

}

function write_macro {

    echo '
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitRelVal/Mods/interface/RelVal.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif

//--------------------------------------------------------------------------------------------------
void runRelVal(const char *files = "$MY_BASE_DIR/prod/mit-gen_000.root")
{
  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
  gSystem->Load("$CMSSW_BASE/lib/slc4_ia32_gcc345/libMitRelValMods.so");

  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  // set up the modules
  RelVal *mod = new RelVal;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(mod);
  ana->AddFile(files);

  // run the analysis after successful initialisation
  ana->Run(! gROOT->IsBatch());
}
'
}

function write_include_file {

    echo '
//--------------------------------------------------------------------------------------------------
// RelVal
//
// This is an analysis module which is used to validate mit tree.
//--------------------------------------------------------------------------------------------------

#ifndef MITRELVAL_RELVAL_H
#define MITRELVAL_RELVAL_H

#include "MitAna/TAM/interface/TAModule.h"
#include "MitAna/DataTree/interface/Collections.h"

#include <stdio.h>
#include <iostream>
#include <fstream>

namespace mithep
{
  class RelVal : public TAModule
  {
    public:
      RelVal(const char *name  = "RelVal",
             const char *title = "Analysis Module for release validation");
      ~RelVal() {}
      void             Process       ();
      void             SlaveBegin    ();
      void             SlaveTerminate();

    protected:
      GenParticleCol  *fParticles;    //! point to particle branch
      TString          fGenPartName;  // name of particle collection
      std::ofstream *ofile;

      ClassDef(RelVal,1)
  };
}
#endif
'
}

function write_linkdef {

    echo '
#ifndef RELVALMODS_LINKDEF_H
#define RELVALMODS_LINKDEF_H
#include "MitRelVal/Mods/interface/RelVal.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::RelVal+;
#endif
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

exit 1;

# Make directory structure for validation module.
if [ -d $MOD ] ; then
    echo "$MOD already exists." >&2
    bak=$MOD.bak.`date +%s`
    echo "It is likely the last executed relval ended in error." >&2
    echo "Moving $MOD to $bak" >&2
    mv $MOD $bak
fi
mkdir -p $MOD/Mods/src
mkdir -p $MOD/Mods/interface
mkdir -p $MOD/macros

# Write validation module
write_module       > $MOD/Mods/src/RelVal.cc
write_buildfile    > $MOD/Mods/BuildFile
write_linkdef      > $MOD/Mods/src/MitRelValModsLinkDef.h
write_include_file > $MOD/Mods/interface/RelVal.h
write_macro        > $MOD/macros/runRelVal.C

# build:
cd $CMSSW_BASE/src
rec=`scramv1 b $MOD 2>&1`
if (( $? )) ; then 
    echo "Problem compiling RelVal module:" >&2
    echo ''  >&2
    echo $rec >&2
    exit 1
fi

# run the validation macro:
cd $MY_BASE_DIR/prod
rec=`root -l -n -q $MOD/macros/runRelVal.C 2>&1`
if (( $? )) ; then 
    echo "Problem executing runRelVal.C:" >&2
    echo ''  >&2
    echo $rec >&2
    exit 1
fi

# do the diff of pythia output and mit tree contents obtained from macro:
diff $PYFILE macro_output.txt > diff_report.txt

# check if things are ok
if (( $? )) ; then 
    echo "Pythia output disagrees with mit tree contents:" >&2
    cat diff_report.txt >&2
    exit 1
fi

exit 0
# Cleanup
rm -rf $MOD
rm -rf $MY_BASE_DIR
exit 0
