// $Id: runHLTExample.C,v 1.7 2010/03/30 12:10:08 bendavid Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/HLTMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runHLTExample(const char *trigger="HLT_Mu15_v1",
                   //const char *files = "XX-MITDATASET-XX_000.root",
                   const char *files = "/castor/cern.ch/user/p/paus/filefi/020/p11-h160ww2l-gf-v1g1-pu/342631BD-F250-E011-9C32-00A0D1EE8B54.root",
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
    hltmod->SetBitsName("HLTBits");
    ana->SetHLTTreeName("HLT");
    ana->SetHLTObjsName("HLTObjects");
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
