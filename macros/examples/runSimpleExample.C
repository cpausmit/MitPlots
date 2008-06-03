// $Id: runSimpleExample.C,v 1.1 2008/05/27 19:59:54 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif

//--------------------------------------------------------------------------------------------------
void runSimpleExample(const char *files = "mit-gen_000.root", const char *tname = "MitTree")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  ParticleExampleMod *mod = new ParticleExampleMod;

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetTreeName(tname);
  ana->SetSuperModule(mod);
  ana->AddFile(files);
  ana->SetOutputName("mit-gen-hist.root");

  // run the analysis after successful initialisation
  if (ana->Init()) {
    ana->Run();
    ana->Terminate();
  } else {
    ::Error("runAna", "Could not initialize analysis.");
  }

  // cleanup ( someone is really worried here :-) )
  delete ana;
  delete mod;
}
