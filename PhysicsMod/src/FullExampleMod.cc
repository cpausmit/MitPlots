#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/TrackCol.h"

using namespace mithep;

ClassImp(mithep::FullExampleMod)

//--------------------------------------------------------------------------------------------------
FullExampleMod::FullExampleMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fMCPartName(Names::gkMCPartBrn),
  fTrackName(Names::gkTrackBrn),
  fMuonName(Names::gkMuonBrn),
  fElectronName(Names::gkElectronBrn),
  fMuonsFromBranch(kTRUE),
  fElectronsFromBranch(kTRUE),
  fMCPtHist(0),
  fMCEtaHist(0),
  fTrackPtHist(0),
  fTrackEtaHist(0),
  fMuonPtHist(0),
  fMuonEtaHist(0),
  fElectronPtHist(0),
  fElectronEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void FullExampleMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void FullExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and
  // fill the histograms.

  auto* particles = GetObject<MCParticleCol>(fMCPartName);

  for (UInt_t i=0; i<particles->GetEntries(); ++i) {
    const MCParticle *p = particles->At(i);
    fMCPtHist->Fill(p->Pt());
    fMCEtaHist->Fill(p->Eta());
  }

  auto* tracks = GetObject<TrackCol>(fTrackName);
  
  for (UInt_t i=0; i<tracks->GetEntries(); ++i) {
    const Track *p = tracks->At(i);
    fTrackPtHist->Fill(p->Pt());
    fTrackEtaHist->Fill(p->Eta());
  }

  auto* muons = GetObject<MuonCol>(fMuonName);

  for (UInt_t i=0; i<muons->GetEntries(); ++i) {
    const Muon *p = muons->At(i);
    fMuonPtHist->Fill(p->Pt());
    fMuonEtaHist->Fill(p->Eta());
  }

  auto* electrons = GetObject<ElectronCol>(fElectronName);
  
  for (UInt_t i=0; i<electrons->GetEntries(); ++i) {
    const Electron *p = electrons->At(i);
    fElectronPtHist->Fill(p->Pt());
    fElectronEtaHist->Fill(p->Eta());
  }
}

//--------------------------------------------------------------------------------------------------
void FullExampleMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  AddTH1(fMCPtHist,"hMCPtHist",";p_{t} [GeV];#",100,0.,250.);
  AddTH1(fMCEtaHist,"hMCEtaHist",";#eta;#",160,-8.,8.);
  AddTH1(fTrackPtHist,"hTrackPtHist",";p_{t} [GeV];#",100,0.,250.);
  AddTH1(fTrackEtaHist,"hTrackEtaHist",";#eta;#",160,-8.,8.);
  AddTH1(fMuonPtHist,"hMuonPtHist",";p_{t} [GeV];#",100,0.,250.);
  AddTH1(fMuonEtaHist,"hMuonEtaHist",";#eta;#",160,-8.,8.);
  AddTH1(fElectronPtHist,"hElectronPtHist",";p_{t} [GeV];#",100,0.,250.);
  AddTH1(fElectronEtaHist,"hElectronEtaHist",";#eta;#",160,-8.,8.);
}

//--------------------------------------------------------------------------------------------------
void FullExampleMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.
}

//--------------------------------------------------------------------------------------------------
void FullExampleMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
