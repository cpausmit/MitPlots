// $Id: runSimpleExample.C,v 1.6 2008/09/28 02:42:49 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/SimpleExampleMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runSimpleExample(const char *files = "mit-gen_000.root")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  SimpleExampleMod *smod = new SimpleExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(smod);
  ana->AddFile(files);
  if (gROOT->IsBatch()) 
    ana->SetOutputName("mit-example-hist.root");
  
  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
