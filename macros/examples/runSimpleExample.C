// $Id: runSimpleExample.C,v 1.2 2008/06/03 07:21:28 paus Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif

//--------------------------------------------------------------------------------------------------
void runSimpleExample(const char *files = "mit-gen_000.root")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  // set up the modules
  ParticleExampleMod *mod = new ParticleExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(mod);
  ana->AddFile(files);
  ana->SetOutputName("mit-gen-hist.root");

  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
