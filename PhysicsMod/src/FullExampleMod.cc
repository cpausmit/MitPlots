// $Id: FullExampleMod.cc,v 1.4 2008/07/25 11:34:46 bendavid Exp $

#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::FullExampleMod)

//--------------------------------------------------------------------------------------------------
FullExampleMod::FullExampleMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fMCPartName(Names::gkMCPartBrn),
  fTrackName(Names::gkTrackBrn),
  fMuonName(Names::gkMuonBrn),
  fElectronName(Names::gkElectronBrn),
  fParticles(0),
  fTracks(0),
  fMuons(0),
  fElectrons(0),
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

  LoadBranch(fMCPartName);
  for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
    MCParticle* p = fParticles->At(i);
    fMCPtHist->Fill(p->Pt());
    fMCEtaHist->Fill(p->Eta());
  }
  
  LoadBranch(fTrackName);
  for (UInt_t i=0; i<fTracks->GetEntries(); ++i) {
    Track* p = fTracks->At(i);
    fTrackPtHist->Fill(p->Pt());
  }
  
  LoadBranch(fMuonName);
  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    Muon *p = fMuons->At(i);
    fMuonPtHist->Fill(p->Pt());
    fMuonEtaHist->Fill(p->Eta());
  }
  
  LoadBranch(fElectronName);
  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {
    Electron *p = fElectrons->At(i);
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

  ReqBranch(fMCPartName,   fParticles);
  ReqBranch(fTrackName,    fTracks);
  ReqBranch(fMuonName,     fMuons);
  ReqBranch(fElectronName, fElectrons);

  fMCPtHist           = new TH1D("hMCPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fMCPtHist);
  fMCEtaHist          = new TH1D("hMCEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fMCEtaHist);
  fTrackPtHist         = new TH1D("hTrackPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fTrackPtHist);
  fTrackEtaHist      = new TH1D("hTrakEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fTrackEtaHist);
  fMuonPtHist          = new TH1D("hMuonPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fMuonPtHist);
  fMuonEtaHist         = new TH1D("hMuonEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fMuonEtaHist);
  fElectronPtHist      = new TH1D("hElectronPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fElectronPtHist);
  fElectronEtaHist      = new TH1D("hElectronEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fElectronEtaHist);
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
