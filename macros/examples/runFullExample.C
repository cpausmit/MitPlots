// $Id: runFullExample.C,v 1.5 2009/03/23 09:07:48 loizides Exp $

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
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
  ana->Run(!gROOT->IsBatch());
}
