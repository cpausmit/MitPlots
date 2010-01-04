// $Id: runHLTExample.C,v 1.5 2009/09/29 19:18:22 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/HLTMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runHLTExample(const char *trigger="HLT_Jet80", 
                   const char *files = "mit-full_000.root",
                   Int_t nEvs = 0)
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  HLTMod *hltmod = new HLTMod;
  hltmod->SetPrintTable(kTRUE);
  hltmod->AddTrigger(trigger);
  hltmod->SetTrigObjsName("myhltobjs");

  HLTExampleMod *hltexmod = new HLTExampleMod;
  hltexmod->SetTrigObjsName("myhltobjs");
  hltmod->Add(hltexmod);
  
  // set up analysis
  Analysis *ana = new Analysis;
  if (0) {
    hltmod->SetBitsName("HLTBits_E29");
    ana->SetHLTTreeName("HLT_E29");
    ana->SetHLTObjsName("HLTObjects_E29");
  }
  if (nEvs)
    ana->SetProcessNEvents(nEvs);
  ana->SetSuperModule(hltmod);
  ana->AddFile(files);
  if (gROOT->IsBatch())
    ana->SetOutputName("mit-hlt-hist.root");

  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());

  cout << "HLTMod: Accepted " << hltmod->GetNAccepted() 
       << " of " << hltmod->GetNEvents() << " events" << endl;
}
