#include "MitAna/PhysicsMod/interface/PlotKineMod.h"

ClassImp(mithep::PlotKineMod)

//--------------------------------------------------------------------------------------------------
mithep::PlotKineMod::PlotKineMod(const char *name, const char *title) : 
  BaseMod(name, title)
{
  SetFillHist(kTRUE);
}

//--------------------------------------------------------------------------------------------------
void
mithep::PlotKineMod::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  auto* collection = GetObject<mithep::ParticleCol>(fColName);
  if (!collection) {
    SendError(kAbortModule, "Process", "Could not load data!");
    return;
  }

  if (!GetFillHist())
    return;
    
  UInt_t ents = collection->GetEntries();
  fMultHist->Fill(ents);

  double leadPt = -1.;
  double leadEta = 0.;
  for(UInt_t iO = 0; iO != ents; ++iO) {
    auto& part = *collection->At(iO);
    Double_t pt = part.Pt();
    if (pt < fPtMin) 
      continue;
    if (pt > fPtMax)
      continue;
    Double_t eta = part.Eta();
    if (eta < fEtaMin)
      continue;
    if (eta > fEtaMax)
      continue;
    Double_t absEta = part.AbsEta();
    if (absEta < fAbsEtaMin)
      continue;
    if (absEta > fAbsEtaMax)
      continue;

    fPtHist->Fill(pt);
    fEtaHist->Fill(eta);
    fPhiHist->Fill(part.Phi());

    if (pt > leadPt) {
      leadPt = pt;
      leadEta = eta;
    }
  }

  if (leadPt >= 0.) {
    fLeadPtHist->Fill(leadPt);
    fLeadEtaHist->Fill(leadEta);
  }
}

//--------------------------------------------------------------------------------------------------
void
mithep::PlotKineMod::SlaveBegin()
{
  if (!GetFillHist())
    return;

  Int_t ptbins = (Int_t)((fPtMax - fPtMin) / 2.5);
  AddTH1(fPtHist, "hPt", ";p_{T} (GeV);", ptbins, fPtMin, fPtMax);
  AddTH1(fLeadPtHist, "hLeadPt", ";p_{T} (GeV);", ptbins, fPtMin, fPtMax);

  Int_t etabins = (Int_t)((fEtaMax - fEtaMin) / 0.1);
  AddTH1(fEtaHist, "hEta", ";#eta;", etabins, fEtaMin, fEtaMax);
  AddTH1(fLeadEtaHist, "hLeadEta", ";#eta;", etabins, fEtaMin, fEtaMax);

  AddTH1(fPhiHist, "hPhi", "#phi;", 40, -3.1416, 3.1416);

  AddTH1(fMultHist, "hMultiplicity", ";Number of objects in " + fColName + ";", 10, 0., 10.);
  fMultHist->SetBit(TH1::kCanRebin);
}
