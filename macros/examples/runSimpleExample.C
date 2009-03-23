// $Id: runSimpleExample.C,v 1.9 2009/03/16 07:45:32 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runSimpleExample(const char *files = "mit-gen_000.root", Bool_t useHlt=0)
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  SimpleExampleMod *smod = new SimpleExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(smod);
  ana->AddFile(files);
  ana->SetUseHLT(useHLT);
  if (gROOT->IsBatch()) 
    ana->SetOutputName("mit-example-hist.root");
  
  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
