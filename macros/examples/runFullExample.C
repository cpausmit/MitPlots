// $Id: runFullExample.C,v 1.2 2008/06/09 11:47:03 paus Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/FullExampleMod.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif

//--------------------------------------------------------------------------------------------------
void runFullExample(const char *files = "mit-full_000.root")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  // set up the modules
  FullExampleMod *mod = new FullExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetUseHLT(false);
  ana->SetSuperModule(mod);
  ana->AddFile(files);
  ana->SetOutputName("mit-full-hist.root");

  // run the analysis after successful initialisation
  ana->Run(! gROOT->IsBatch());
}
