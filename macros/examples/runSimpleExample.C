// $Id: runSimpleExample.C,v 1.11 2009/04/06 13:41:26 loizides Exp $

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runSimpleExample(
   const char *files = "/castor/cern.ch/user/p/paus/filler/009/s8-zmm-id11/s8-zmm-id11_000_1.root", 
   Bool_t useHlt=1
  )
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  SimpleExampleMod *smod = new SimpleExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(smod);
  ana->AddFile(files);
  ana->SetUseHLT(useHlt);
  if (gROOT->IsBatch()) 
    ana->SetOutputName("mit-example-hist.root");
  
  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
