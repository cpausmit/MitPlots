// $Id: runAna.C 4148 2007-06-21 12:22:37Z loizides $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif


//________________________________________________________________________
void runSimpleExample(const char *files, const char *tname="MitTree")
{
  using namespace mithep;
  gDebugMask = Debug::kAnalysis;
  gDebugLevel = 1; 

  ParticleExampleMod *mod = new ParticleExampleMod;
  //mod->

  // set up top-level analysis class
  Analysis *ana = new Analysis;
  ana->SetTreeName(tname);
  ana->SetSuperModule(mod);
  ana->AddFile(files);
  ana->SetOutputName("ana_testoutput.root"); 

  if(ana->Init()) {
    ana->Run();
    ana->Terminate();
  } else {
    ::Error("runAna", "Could not initialize analysis.");
  } 

  delete ana;
  delete mod;
}
