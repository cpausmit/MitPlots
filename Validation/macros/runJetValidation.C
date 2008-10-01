// $Id:  $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitHiggs/FakeRateMods/interface/JetValidationMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void runJetValidation()
{
  //run the jet Validation Module.
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  // set up the modules 
  JetValidationMod *eventSelectionMod = new JetValidationMod;
  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(eventSelectionMod);
  TString files      = TString("castor:/castor/cern.ch/user/s/sixie/OAKSamples/relval212QCDpt50_80-id6/*.root");
  ana->AddFile(files);
  ana->SetOutputName("mit-JetValidation-hist.root");

  // run the analysis after successful initialisation
  ana->Run(! gROOT->IsBatch());
}
