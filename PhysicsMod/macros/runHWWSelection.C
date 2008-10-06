// $Id: runHWWSelection.C,v 1.2 2008/10/05 14:22:12 sixie Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/ObjectValidationMod.h"
#include "MitHiggs/HwwMods/interface/HwwEvtSelMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runHWWSelection()
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  // HWW signal
  TString files1      = TString("/server/04d/sixie/OAKSamples/003/mitPrivateH165WW_2l-id9/mitPrivateH165WW_2l-id9_*.root");
  //runHWWAnalysisChain(files1, TString("mit-HWWSelection-003-hist_HWWSignal.root"), TString("Sequential"), TString("CleanIC5Jets"));

  // WW bkg
  TString files2      = TString("/server/04d/sixie/OAKSamples/003/mitPrivateWW_2l-id9/mitPrivateWW_2l-id9_000.root");
  //runHWWAnalysisChain(files2, TString("mit-HWWSelection-003-hist_WWBkg.root"), TString("N-1"), TString("CleanIC5Jets"));

  // WZ bkg
  TString files3      = TString("/server/04d/sixie/OAKSamples/003/mitPrivateWZ_3l-id9/mitPrivateWZ_3l-id9_*.root");
//  runHWWAnalysisChain(files3, TString("mit-HWWSelection-003-hist_WZBkg.root"), TString("N-1"), TString("CleanIC5Jets"));
  // ZZ Background
  TString files4      = TString("/server/04d/sixie/OAKSamples/003/mitPrivateZZ_4l-id9/mitPrivateZZ_4l-id9_*.root");
//  runHWWAnalysisChain(files4, TString("mit-HWWSelection-003-hist_ZZBkg.root"), TString("N-1"), TString("CleanIC5Jets"));
  // ttbar Background
  TString files5      = TString("castor:/castor/cern.ch/user/p/paus/filler/003/s8-ttbar-id6/s8-ttbar-id6_000_*.root");
  runHWWAnalysisChain(files5, TString("mit-HWWSelection-003-hist_ttbarBkg.root"), TString("N-1"), TString("CleanIC5Jets"));

  return;
}

void runHWWAnalysisChain(TString inputfiles, TString outputfileName, TString PlotType, TString CleanJetsName) {

  HwwEvtPreSelMod *preSelectionMod = new HwwEvtPreSelMod;
  //Object ID and Cleaning Sequence;
  MuonIDMod *muonID = new MuonIDMod;  
  ElectronIDMod *electronID = new ElectronIDMod;
  JetIDMod *IC5JetID = new JetIDMod; //default names are IC5
  JetIDMod *SC5JetID = new JetIDMod;
  SC5JetID->SetJetName(TString("SisCone5Jets")); //for SC5 I have to set the names
  SC5JetID->SetGoodJetsName(TString("GoodSC5Jets"));
  ElectronCleaningMod *electronCleaning = new ElectronCleaningMod;
  JetCleaningMod *IC5JetCleaning = new JetCleaningMod; //default names are ok for IC5
  JetCleaningMod *SC5JetCleaning = new JetCleaningMod; //for SC5 need to set names
  SC5JetCleaning->SetGoodJetsName(TString("GoodSC5Jets"));
  SC5JetCleaning->SetCleanJetsName(TString("CleanSC5Jets"));
  //Chain them together
  //Event Selection modules
  HwwEvtSelMod *eventSelectionMod = new HwwEvtSelMod;
  eventSelectionMod->SetLoadGenParticles(true);
  eventSelectionMod->SetCleanJetsName(CleanJetsName);
  eventSelectionMod->SetPlotType(PlotType);
  //chain modules together
  preSelectionMod->Add(muonID);
  muonID->Add(electronID);
  electronID->Add(IC5JetID);
  IC5JetID->Add(SC5JetID);
  SC5JetID->Add(electronCleaning);
  electronCleaning->Add(IC5JetCleaning);
  IC5JetCleaning->Add(SC5JetCleaning);
  SC5JetCleaning->Add(eventSelectionMod);
  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetUseHLT(false);
  ana->SetKeepHierachy(kFALSE);
  //ana->SetSuperModule(preSelectionMod);  
  ana->SetSuperModule(muonID);  
  ana->AddFile(inputfiles);
  ana->SetOutputName(outputfileName.Data());
  // run the analysis after successful initialisation
  ana->Run(! gROOT->IsBatch());  

  return;

}

void runHWWFakeElectronAnalysisChain(TString inputfiles, TString outputfileName, TString PlotType, TString CleanJetsName) {

  HwwFakeElectronBkgPreSelMod *preSelectionMod = new HwwFakeElectronBkgPreSelMod;
  //Object ID and Cleaning Sequence;
  MuonIDMod *muonID = new MuonIDMod;  
  ElectronIDMod *electronID = new ElectronIDMod;
  JetIDMod *IC5JetID = new JetIDMod; //default names are IC5
  JetIDMod *SC5JetID = new JetIDMod;
  SC5JetID->SetJetName(TString("SisCone5Jets")); //for SC5 I have to set the names
  SC5JetID->SetGoodJetsName(TString("GoodSC5Jets"));
  ElectronCleaningMod *electronCleaning = new ElectronCleaningMod;
  JetCleaningMod *IC5JetCleaning = new JetCleaningMod; //default names are ok for IC5
  JetCleaningMod *SC5JetCleaning = new JetCleaningMod; //for SC5 need to set names
  SC5JetCleaning->SetGoodJetsName(TString("GoodSC5Jets"));
  SC5JetCleaning->SetCleanJetsName(TString("CleanSC5Jets"));
  //Chain them together
  //Event Selection modules
  HwwFakeElectronBkgSelMod *eventSelectionMod = new HwwFakeElectronBkgSelMod;
  eventSelectionMod->SetFakeRateInputFile(TString("/server/02a/sixie/CMSSW_2_1_8/src/MitElectronFakes/macros/electronFakeRate_from_qcd_50-80.root"));
  eventSelectionMod->SetCleanJetsName(CleanJetsName);
  eventSelectionMod->SetPlotType(PlotType);
  //chain modules together
  preSelectionMod->Add(muonID);
  muonID->Add(electronID);
  electronID->Add(IC5JetID);
  IC5JetID->Add(SC5JetID);
  SC5JetID->Add(electronCleaning);
  electronCleaning->Add(IC5JetCleaning);
  IC5JetCleaning->Add(SC5JetCleaning);
  SC5JetCleaning->Add(eventSelectionMod);
  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetUseHLT(false);
  ana->SetKeepHierachy(kFALSE);
  ana->SetSuperModule(preSelectionMod);  
  ana->AddFile(inputfiles);
  ana->SetOutputName(outputfileName.Data());
  // run the analysis after successful initialisation
  ana->Run(! gROOT->IsBatch());  

  return;

}
