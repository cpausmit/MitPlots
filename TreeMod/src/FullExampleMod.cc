// $Id: FullExample.cc,v 1.3 2008/06/11 23:37:20 paus Exp $

#include "MitAna/TreeMod/interface/FullExampleMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::FullExampleMod)

//__________________________________________________________________________________________________
FullExampleMod::FullExampleMod(const char *name, const char *title)
  : TAModule(name,title),
    fParticles(0),
    fTracks(0),
    fMuons(0),
    fElectrons(0),
    fGenPartName(Names::gkGenPartBrn),
    fTrackName(Names::gkTrackBrn),
    fMuonName(Names::gkMuonBrn),
    fElectronName(Names::gkElectronBrn),
    fGenPtHist(0),
    fGenEtaHist(0),
    fTrackPtHist(0),
    fMuonPtHist(0),
    fMuonEtaHist(0),
    fMuonTrackPtHist(0),
    fMuonTrackPtErrHist(0),
    fElectronPtHist(0)
{
  // Constructor.
}

//__________________________________________________________________________________________________
void FullExampleMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//__________________________________________________________________________________________________
void FullExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load the branch and
  // fill the histograms.

  LoadBranch(fGenPartName);
  for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
    GenParticle* p = fParticles->At(i);
    fGenPtHist->Fill(p->Pt());
    fGenEtaHist->Fill(p->Eta());
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
    fMuonTrackPtHist->Fill(p->GetTrack()->Pt());
    fMuonTrackPtErrHist->Fill(p->GetTrack()->PtErr());
  }
  
  
  LoadBranch(fElectronName);
  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {
    Electron *p = fElectrons->At(i);
    fElectronPtHist->Fill(p->Pt());
  }

}

//__________________________________________________________________________________________________
void FullExampleMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fGenPartName,  fParticles);
  ReqBranch(fTrackName,    fTracks);
  ReqBranch(fMuonName,     fMuons);
  ReqBranch(fElectronName, fElectrons);

  fGenPtHist           = new TH1D("hGenPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fGenPtHist);
  fGenEtaHist          = new TH1D("hGenEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fGenEtaHist);
  
  fTrackPtHist         = new TH1D("hTrackPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fTrackPtHist);
  
  fMuonPtHist          = new TH1D("hMuonPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fMuonPtHist);
  fMuonEtaHist         = new TH1D("hMuonEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fMuonEtaHist);
  
  fMuonTrackPtHist     = new TH1D("hMuonTrackPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fMuonTrackPtHist);
  fMuonTrackPtErrHist  = new TH1D("hMuonTrackPtErrHist",";p_{t};#",100,0.,25.);
  AddOutput(fMuonTrackPtErrHist);
  
  fElectronPtHist      = new TH1D("hElectronPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fElectronPtHist);
}

//__________________________________________________________________________________________________
void FullExampleMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.
}

//__________________________________________________________________________________________________
void FullExampleMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
