// $Id: HLTExampleMod.cc,v 1.6 2008/07/25 11:34:46 bendavid Exp $

#include "MitAna/TreeMod/interface/HLTExampleMod.h"
#include <TH1D.h>

using namespace mithep;

ClassImp(mithep::HLTExampleMod)

//--------------------------------------------------------------------------------------------------
HLTExampleMod::HLTExampleMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPtHist(0),
  fEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void HLTExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load
  // the branch and fill the histograms.

  const TriggerObjectCol *objs = GetHLTObjects(fObjsName);

  
  if (!objs) // this can only happen if HLTMod::SetAbortIfNotAccepted(kFALSE) was called
    return;

  Int_t ents=objs->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     const TriggerObject* to = objs->At(i);
     fPtHist->Fill(to->Pt());
     fEtaHist->Fill(to->Eta());
  }
}

//--------------------------------------------------------------------------------------------------
void HLTExampleMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual
  // analysis. Here, we typically initialize histograms and 
  // other analysis objects and request branches. For this module,
  // we request a branch of the MitTree.

  fPtHist  = new TH1D("hPtHist",";p_{t};#",250,0.,500.);
  AddOutput(fPtHist);
  fEtaHist = new TH1D("hEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fEtaHist);
}
