// $Id: ObjectCleaningMod.cc,v 1.3 2008/09/04 21:36:21 loizides Exp $

#include "MitAna/TreeMod/interface/ObjectCleaningMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"


using namespace mithep;
using namespace mitcommon;

ClassImp(mithep::ObjectCleaningMod)

//--------------------------------------------------------------------------------------------------
ObjectCleaningMod::ObjectCleaningMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fMCPartName(Names::gkMCPartBrn),
  fTrackName(Names::gkTrackBrn),
  fBarrelBasicClusterName(Names::gkBarrelBasicClusterBrn),
  fBarrelSuperClusterName(Names::gkBarrelSuperClusterBrn),
  fEndcapBasicClusterName(Names::gkEndcapBasicClusterBrn),
  fEndcapSuperClusterName(Names::gkEndcapSuperClusterBrn),  
  fCaloTowerName(Names::gkCaloTowerBrn),
  fMuonName(Names::gkMuonBrn),
  fElectronName(Names::gkElectronBrn),
  fJetName(Names::gkCaloJetBrn),
  fMetName(Names::gkCaloMetBrn),
  fParticles(0),
  fTracks(0),
  fMuons(0),
  fElectrons(0),
  fGenPtHist(0),
  fGenEtaHist(0),
  fTrackPtHist(0),
  fTrackThetaHist(0), 
  fAllMuonPtHist(0),
  fAllMuonEtaHist(0),
  fGoodMuonPtHist(0),
  fGoodMuonEtaHist(0),
  fAllElectronPtHist(0),
  fAllElectronEtaHist(0),
  fAllJetPtHist(0),
  fAllJetEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
                  fGoodElectronsName = "GoodElectrons" ;        
                 fGoodMuonsName = "GoodMuons" ;        
                  fGoodCentralJetsName = "GoodCentralJets";        
                  fGoodForwardJetsName = "GoodForwardJets" ;        
                  fMuonCorrectedMetName = "MET" ; 
                  fGenLeptonsName = "GenLeptons";
}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and
  //output debug info or not  
  bool printDebug = false; 
  bool debug = false; 

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || printDebug)
    cerr << endl << "Process Event " << fNEventsProcessed << endl;

  //Get Generator Level information for matching
  ObjArray<MCParticle> *GenLeptons = new ObjArray<MCParticle>;
  LoadBranch(fMCPartName);

  for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
    MCParticle* p = fParticles->At(i);
    fGenPtHist->Fill(p->Pt());
    fGenEtaHist->Fill(p->Eta());
    fGenPhiHist->Fill(p->Phi());

    if (p->IsGenerated() && 
	(abs(p->PdgId()) >= 11 && abs(p->PdgId()) <= 16) 
	&& p->Status() == 3 //pick 3 because we want primary interaction leptons only
      ) 
      GenLeptons->Add(p);
    
  }
     
  if (printDebug) cerr << "Check Generator Leptons Finding" << endl;
  for (UInt_t i=0; i<GenLeptons->GetEntries(); ++i) {
    if (GenLeptons->At(i)->AbsPdgId() == 11) {
      fGenElectronPt->Fill(GenLeptons->At(i)->Pt());
      fGenElectronEta->Fill(GenLeptons->At(i)->Eta());
      fGenElectronPhi->Fill(GenLeptons->At(i)->Phi());
    }
    if (GenLeptons->At(i)->AbsPdgId() == 13) {
      fGenMuonPt->Fill(GenLeptons->At(i)->Pt());
      fGenMuonEta->Fill(GenLeptons->At(i)->Eta());
      fGenMuonPhi->Fill(GenLeptons->At(i)->Phi());      
    }
    if (GenLeptons->At(i)->AbsPdgId() == 15) {
      fGenTauPt->Fill(GenLeptons->At(i)->Pt());
      fGenTauEta->Fill(GenLeptons->At(i)->Eta());
      fGenTauPhi->Fill(GenLeptons->At(i)->Phi());      
    } 
    if (printDebug) {
      cout << i << " " << GenLeptons->At(i)->PdgId() << " " << GenLeptons->At(i)->Status() 
           << " " << GenLeptons->At(i)->Pt() << " " << GenLeptons->At(i)->Eta() << " " 
           << GenLeptons->At(i)->Phi() << endl;
    }
  }    
  
  //Load Tracking Information
  LoadBranch(fTrackName);
  for (UInt_t i=0; i<fTracks->GetEntries(); ++i) {
    Track* p = fTracks->At(i);
    fTrackPtHist->Fill(p->Pt());
    fTrackThetaHist->Fill(p->Theta());
    fTrackPhiHist->Fill(p->Phi());    
  }

  //Get the Basic Clusters
  LoadBranch(fBarrelBasicClusterName);
  LoadBranch(fEndcapBasicClusterName);  
  //Get the Super Clusters
  LoadBranch(fBarrelSuperClusterName);
  LoadBranch(fEndcapSuperClusterName);
  //Get the CaloTowers
  LoadBranch(fCaloTowerName); 
  
  //Muons
  ObjArray<Muon> *GoodMuons = new ObjArray<Muon>; 
  vector<bool> GoodMuonsIsFake;   
  LoadBranch(fMuonName);
  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    Muon *mu = fMuons->At(i);
    fAllMuonPtHist->Fill(mu->Pt());
    fAllMuonEtaHist->Fill(mu->Eta());
    
    //do matching to gen particle to find if it's a fake
    bool isFake = true;
    bool isFromTau = false;
    for (UInt_t j = 0; j<GenLeptons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GenLeptons->At(j)->Mom(),mu->Mom());    
      if (deltaR < 0.15) {
        if (abs(GenLeptons->At(j)->PdgId()) == 13) {
          isFake = false;
          if (printDebug) 
            cout << "Matched: " 
                 << mu->Pt() << " " << mu->Eta() << " " << mu->Phi() << endl
                 << GenLeptons->At(j)->PdgId() << " " << GenLeptons->At(j)->Pt() << " " 
                 << GenLeptons->At(j)->Eta() << " " << GenLeptons->At(j)->Phi() << endl;
          //debug = true;
        }
        if (abs(GenLeptons->At(j)->PdgId()) == 15) {
          isFromTau = true;	 
        }	 
      }
    }
    
    //Fill Muon ID histograms     
    fAllMuonChi2->Fill(mu->Trk()->Chi2());
    fAllMuonNHits->Fill(mu->Trk()->NHits());
    fAllMuonBestTrackD0->Fill(abs(mu->BestTrk()->D0()));     
    fAllMuonIsoR03SumPt->Fill(mu->IsoR03SumPt());
    fAllMuonIsoR03EmEt->Fill(mu->IsoR03EmEt());
    fAllMuonIsoR03HadEt->Fill(mu->IsoR03HadEt());
    fAllMuonIsoR03EmAndHadEt->Fill(mu->IsoR03EmEt() + mu->IsoR03HadEt());
    fAllMuonIsoR03HoEt->Fill(mu->IsoR03HoEt());
    fAllMuonIsoR03NTracks->Fill(mu->IsoR03NTracks());
    fAllMuonIsoR03NJets->Fill(mu->IsoR03NJets());
    fAllMuonIsoR05SumPt->Fill(mu->IsoR05SumPt());
    fAllMuonIsoR05EmEt->Fill(mu->IsoR05EmEt());
    fAllMuonIsoR05HadEt->Fill(mu->IsoR05HadEt());
    fAllMuonIsoR05HoEt->Fill(mu->IsoR05HoEt());
    fAllMuonIsoR05NTracks->Fill(mu->IsoR05NTracks());
    fAllMuonIsoR05NJets->Fill(mu->IsoR05NJets());
    fAllMuonEmEnergy->Fill(mu->EmEnergy());
    fAllMuonHadEnergy->Fill(mu->HadEnergy());
    fAllMuonHoEnergy->Fill(mu->HoEnergy());
    fAllMuonEmS9Energy->Fill(mu->EmS9Energy());
    fAllMuonHadS9Energy->Fill(mu->HadS9Energy());
    fAllMuonHoS9Energy->Fill(mu->HoS9Energy());
    if (!isFake) {
      fRealMuonPtHist->Fill(mu->Pt());
      fRealMuonEtaHist->Fill(mu->Eta());
      fRealMuonChi2->Fill(mu->Trk()->Chi2());
      fRealMuonNHits->Fill(mu->Trk()->NHits());
      fRealMuonBestTrackD0->Fill(abs(mu->BestTrk()->D0()));     
      fRealMuonIsoR03SumPt->Fill(mu->IsoR03SumPt());
      fRealMuonIsoR03EmEt->Fill(mu->IsoR03EmEt());
      fRealMuonIsoR03HadEt->Fill(mu->IsoR03HadEt());
      fRealMuonIsoR03EmAndHadEt->Fill(mu->IsoR03EmEt() + mu->IsoR03HadEt());
      fRealMuonIsoR03HoEt->Fill(mu->IsoR03HoEt());
      fRealMuonIsoR03NTracks->Fill(mu->IsoR03NTracks());
      fRealMuonIsoR03NJets->Fill(mu->IsoR03NJets());
      fRealMuonIsoR05SumPt->Fill(mu->IsoR05SumPt());
      fRealMuonIsoR05EmEt->Fill(mu->IsoR05EmEt());
      fRealMuonIsoR05HadEt->Fill(mu->IsoR05HadEt());
      fRealMuonIsoR05HoEt->Fill(mu->IsoR05HoEt());
      fRealMuonIsoR05NTracks->Fill(mu->IsoR05NTracks());
      fRealMuonIsoR05NJets->Fill(mu->IsoR05NJets());
      fRealMuonEmEnergy->Fill(mu->EmEnergy());
      fRealMuonHadEnergy->Fill(mu->HadEnergy());
      fRealMuonHoEnergy->Fill(mu->HoEnergy());
      fRealMuonEmS9Energy->Fill(mu->EmS9Energy());
      fRealMuonHadS9Energy->Fill(mu->HadS9Energy());
      fRealMuonHoS9Energy->Fill(mu->HoS9Energy());
    } else {
      fFakeMuonPtHist->Fill(mu->Pt());
      fFakeMuonEtaHist->Fill(mu->Eta());
      fFakeMuonChi2->Fill(mu->Trk()->Chi2());
      fFakeMuonNHits->Fill(mu->Trk()->NHits());
      fFakeMuonBestTrackD0->Fill(abs(mu->BestTrk()->D0()));     
      fFakeMuonIsoR03SumPt->Fill(mu->IsoR03SumPt());
      fFakeMuonIsoR03EmEt->Fill(mu->IsoR03EmEt());
      fFakeMuonIsoR03HadEt->Fill(mu->IsoR03HadEt());
      fFakeMuonIsoR03EmAndHadEt->Fill(mu->IsoR03EmEt() + mu->IsoR03HadEt());
      fFakeMuonIsoR03HoEt->Fill(mu->IsoR03HoEt());
      fFakeMuonIsoR03NTracks->Fill(mu->IsoR03NTracks());
      fFakeMuonIsoR03NJets->Fill(mu->IsoR03NJets());
      fFakeMuonIsoR05SumPt->Fill(mu->IsoR05SumPt());
      fFakeMuonIsoR05EmEt->Fill(mu->IsoR05EmEt());
      fFakeMuonIsoR05HadEt->Fill(mu->IsoR05HadEt());
      fFakeMuonIsoR05HoEt->Fill(mu->IsoR05HoEt());
      fFakeMuonIsoR05NTracks->Fill(mu->IsoR05NTracks());
      fFakeMuonIsoR05NJets->Fill(mu->IsoR05NJets());
      fFakeMuonEmEnergy->Fill(mu->EmEnergy());
      fFakeMuonHadEnergy->Fill(mu->HadEnergy());
      fFakeMuonHoEnergy->Fill(mu->HoEnergy());
      fFakeMuonEmS9Energy->Fill(mu->EmS9Energy());
      fFakeMuonHadS9Energy->Fill(mu->HadS9Energy());
      fFakeMuonHoS9Energy->Fill(mu->HoS9Energy());
    }    
    
    //Define the ID Cuts
    const int nCuts = 4;
    double cutValue[nCuts] = {0.1, 3.0, 3.0, 1.5};
    bool passCut[nCuts] = {false, false, false,};
    
    double muonD0 = -0.05;
    //if (mu->GlobalTrk() != NULL)
    muonD0 = mu->BestTrk()->D0();
    if(muonD0 < cutValue[0] //&& mu->GlobalTrk() != NULL
      ) 
      passCut[0] = true;
    if(mu->IsoR03SumPt() < cutValue[1]) passCut[1] = true;
    if(mu->IsoR03EmEt() + 
       mu->IsoR03HadEt() < cutValue[2]) passCut[2] = true;
    
    if(mu->Pt() > 1.5)
      passCut[3] = true;

    // Final decision
    bool allCuts = true;
    for(int c=0; c<nCuts; c++) {
      allCuts = allCuts & passCut[c];
    }
    
    //make muon ID selection histograms
    fMuonSelection->Fill(-1);
    if (!isFake)
      fRealMuonSelection->Fill(-1);
    else 
      fFakeMuonSelection->Fill(-1);
    
    //Fill the rest of the muon selection histograms
    for (int k=0;k<3;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
        pass = (pass && passCut[p]);
      
      if (pass) {
        fMuonSelection->Fill(k);
        if (!isFake)
          fRealMuonSelection->Fill(k);
        else 
          fFakeMuonSelection->Fill(k);
      }
    } 
    
    //Fill histogram for the Good Muons
    if ( allCuts
         && abs(mu->Eta()) < 2.5  //$$ mu->Pt() > 5.0 	  
      ) {     
      fGoodMuonPtHist->Fill(mu->Pt());
      fGoodMuonEtaHist->Fill(mu->Eta());       
      GoodMuons->Add(mu);
      GoodMuonsIsFake.push_back(isFake);
    }                    
  }
  
  
  //Get Electrons
  LoadBranch(fElectronName);
  
  //we have to use a vector first and then fill the ObjArray with the vector 
  //contents because ObJArray does not allow removal of duplicates.
  vector<Electron*> GoodElectronsVector;
  vector<bool> GoodElectronIsFake;
  
  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {
    Electron *e = fElectrons->At(i);
    
    fAllElectronPtHist->Fill(e->Pt());
    fAllElectronEtaHist->Fill(e->Eta());
    
    //do matching to gen particle to find if it's a fake
    bool isFake = true;
    bool isFromTau = false;
    for (UInt_t j = 0; j<GenLeptons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GenLeptons->At(j)->Mom(),e->Mom());
      if (deltaR < 0.15) {
        if (abs(GenLeptons->At(j)->PdgId()) == 11) {
          isFake = false;
          if (printDebug) 
            cout << "Matched: " 
                 << e->Pt() << " " << e->Eta() << " " << e->Phi() << endl
                 << GenLeptons->At(j)->PdgId() << " " << GenLeptons->At(j)->Pt() 
                 << " " << GenLeptons->At(j)->Eta() << " " << GenLeptons->At(j)->Phi() << endl;
          //debug = true;
        }
        if (abs(GenLeptons->At(j)->PdgId()) == 15) {
          isFromTau = true;	 
        }	 
      }
    }       
    
    double electronepInv = fabs(1./e->SCluster()->Energy()- 1./e->E());
    
    
    //electron isolation calculation
    double computedEcalIso;    
    if (fabs(e->Eta()) < 1.479) {
      computedEcalIso = IsolationTools::EcalIsolation(e->SCluster(),0.3,0.0,fBarrelBasicClusters);
    } else {
      computedEcalIso = IsolationTools::EcalIsolation(e->SCluster(),0.3,0.0,fEndcapBasicClusters);
    } 
    double computedTrackIso =  IsolationTools::TrackIsolation(e->Trk(),0.2, 0.02,1.5,0.1,fTracks);    

    if (printDebug) {
      cout << "Check Iso Calculation:" << endl;
      cout << "e->ComputeTrackIso: " << computedTrackIso << endl;
      cout << "e->TrackIso: " << e->TrackIsolation() << endl;
      cout << "diff: " << computedTrackIso - e->TrackIsolation() << endl;
      cout << "e->ComputeEcalIso: " << computedEcalIso << endl;
      cout << "e->EcalIso: " << e->CaloIsolation() << endl;
      cout << "diff: " << computedEcalIso - e->CaloIsolation() << endl;
    }
        
    //Fill electron ID histograms
    fAllElectronESuperClOverP->Fill(e->ESuperClusterOverP());
    fAllElectronESeedClOverPout->Fill(e->ESeedClusterOverPout());
    fAllElectronDeltaEtaSuperClTrackAtVtx->Fill(abs(e->DeltaEtaSuperClusterTrackAtVtx()));
    fAllElectronDeltaEtaSeedClTrackAtCalo->Fill(abs(e->DeltaEtaSeedClusterTrackAtCalo()));
    fAllElectronDeltaPhiSuperClTrackAtVtx->Fill(abs(e->DeltaPhiSuperClusterTrackAtVtx()));
    fAllElectronDeltaPhiSeedClTrackAtCalo->Fill(abs(e->DeltaPhiSeedClusterTrackAtCalo()));
    fAllElectronEPInv->Fill(electronepInv);     
    fAllElectronHadronicOverEm->Fill(e->HadronicOverEm());
    fAllElectronE33OverE55->Fill(e->E33()/e->E55());
    fAllElectronIsEnergyScaleCorrected->Fill(e->IsEnergyScaleCorrected());
    fAllElectronIsMomentumCorrected->Fill(e->IsMomentumCorrected());
    fAllElectronNumberOfClusters->Fill(e->NumberOfClusters());
    fAllElectronClassification->Fill(e->Classification());
    fAllElectronE33->Fill(e->E33());
    fAllElectronE55->Fill(e->E55());
    fAllElectronCovEtaEta->Fill(e->CovEtaEta()*10000);
    fAllElectronCovEtaPhi->Fill(abs(e->CovEtaPhi()*10000));
    fAllElectronCovPhiPhi->Fill(e->CovPhiPhi()*1000);
    fAllElectronCaloIso->Fill(e->CaloIsolation());
    fAllElectronTrackIso->Fill(e->TrackIsolation());
    fAllElectronComputedEcalIso->Fill(computedEcalIso);
    fAllElectronComputedTrackIso->Fill(computedTrackIso);
    fAllElectronTrackChi2->Fill(e->Trk()->Chi2());
    fAllElectronTrackNHits->Fill(e->Trk()->NHits());
    if (!isFake) {       
      fRealElectronPtHist->Fill(e->Pt());
      fRealElectronEtaHist->Fill(e->Eta());
      fRealElectronESuperClOverP->Fill(e->ESuperClusterOverP());
      fRealElectronESeedClOverPout->Fill(e->ESeedClusterOverPout());
      fRealElectronDeltaEtaSuperClTrackAtVtx->Fill(abs(e->DeltaEtaSuperClusterTrackAtVtx()));
      fRealElectronDeltaEtaSeedClTrackAtCalo->Fill(abs(e->DeltaEtaSeedClusterTrackAtCalo()));
      fRealElectronDeltaPhiSuperClTrackAtVtx->Fill(abs(e->DeltaPhiSuperClusterTrackAtVtx()));
      fRealElectronDeltaPhiSeedClTrackAtCalo->Fill(abs(e->DeltaPhiSeedClusterTrackAtCalo()));
      fRealElectronEPInv->Fill(electronepInv);
      fRealElectronHadronicOverEm->Fill(e->HadronicOverEm());
      fRealElectronE33OverE55->Fill(e->E33()/e->E55());
      fRealElectronIsEnergyScaleCorrected->Fill(e->IsEnergyScaleCorrected());
      fRealElectronIsMomentumCorrected->Fill(e->IsMomentumCorrected());
      fRealElectronNumberOfClusters->Fill(e->NumberOfClusters());
      fRealElectronClassification->Fill(e->Classification());
      fRealElectronE33->Fill(e->E33());
      fRealElectronE55->Fill(e->E55());
      fRealElectronCovEtaEta->Fill(e->CovEtaEta()*10000);
      fRealElectronCovEtaPhi->Fill(abs(e->CovEtaPhi()*10000));
      fRealElectronCovPhiPhi->Fill(e->CovPhiPhi()*1000);
      fRealElectronCaloIso->Fill(e->CaloIsolation());
      fRealElectronTrackIso->Fill(e->TrackIsolation()); 
      fRealElectronComputedEcalIso->Fill(computedEcalIso);
      fRealElectronComputedTrackIso->Fill(computedTrackIso);
      fRealElectronTrackChi2->Fill(e->Trk()->Chi2());
      fRealElectronTrackNHits->Fill(e->Trk()->NHits());
    } else {
      fFakeElectronPtHist->Fill(e->Pt());
      fFakeElectronEtaHist->Fill(e->Eta());
      fFakeElectronESuperClOverP->Fill(e->ESuperClusterOverP());
      fFakeElectronESeedClOverPout->Fill(e->ESeedClusterOverPout());
      fFakeElectronDeltaEtaSuperClTrackAtVtx->Fill(abs(e->DeltaEtaSuperClusterTrackAtVtx()));
      fFakeElectronDeltaEtaSeedClTrackAtCalo->Fill(abs(e->DeltaEtaSeedClusterTrackAtCalo()));
      fFakeElectronDeltaPhiSuperClTrackAtVtx->Fill(abs(e->DeltaPhiSuperClusterTrackAtVtx()));
      fFakeElectronDeltaPhiSeedClTrackAtCalo->Fill(abs(e->DeltaPhiSeedClusterTrackAtCalo()));
      fFakeElectronEPInv->Fill(electronepInv);
      fFakeElectronHadronicOverEm->Fill(e->HadronicOverEm());
      fFakeElectronE33OverE55->Fill(e->E33()/e->E55());
      fFakeElectronIsEnergyScaleCorrected->Fill(e->IsEnergyScaleCorrected());
      fFakeElectronIsMomentumCorrected->Fill(e->IsMomentumCorrected());
      fFakeElectronNumberOfClusters->Fill(e->NumberOfClusters());
      fFakeElectronClassification->Fill(e->Classification());
      fFakeElectronE33->Fill(e->E33());
      fFakeElectronE55->Fill(e->E55());
      fFakeElectronCovEtaEta->Fill(e->CovEtaEta()*10000);
      fFakeElectronCovEtaPhi->Fill(abs(e->CovEtaPhi()*10000));
      fFakeElectronCovPhiPhi->Fill(e->CovPhiPhi()*1000);
      fFakeElectronCaloIso->Fill(e->CaloIsolation());
      fFakeElectronTrackIso->Fill(e->TrackIsolation());
      fFakeElectronComputedEcalIso->Fill(computedEcalIso);
      fFakeElectronComputedTrackIso->Fill(computedTrackIso);
      fFakeElectronTrackChi2->Fill(e->Trk()->Chi2());
      fFakeElectronTrackNHits->Fill(e->Trk()->NHits());
    }
    
    //cuts depend on electron classification
    int cutClass = -1;
    if	 (e->Classification() ==   0) cutClass = 0;
    else if(e->Classification() ==  10) cutClass = 1;
    else if(e->Classification() ==  20) cutClass = 2;
    else if(e->Classification() ==  30) cutClass = 3;
    else if(e->Classification() ==  31) cutClass = 3;
    else if(e->Classification() ==  32) cutClass = 3;
    else if(e->Classification() ==  33) cutClass = 3;
    else if(e->Classification() ==  34) cutClass = 3;
    else if(e->Classification() == 100) cutClass = 4;
    else if(e->Classification() == 110) cutClass = 5;
    else if(e->Classification() == 120) cutClass = 6;
    else if(e->Classification() == 130) cutClass = 7;
    else if(e->Classification() == 131) cutClass = 7;
    else if(e->Classification() == 132) cutClass = 7;
    else if(e->Classification() == 133) cutClass = 7;
    else if(e->Classification() == 134) cutClass = 7;
    else if(e->Classification() ==  40) cutClass = 8;
    else {
      cout << "Error, electron.classification not defined: " << e->Classification() << endl;       
    }

    fAllElectronCutClass->Fill(cutClass);
    
    if (!isFake) 
      fRealElectronCutClass->Fill(cutClass);
    else
      fFakeElectronCutClass->Fill(cutClass);
    
    //cerr << "3" << endl;
    
    //values of cuts[classification]
    //double EoverPInMax[]     = { 1.3,   1.2,   1.3,   999.,  999.,  999.,  999.,  999.  }; // 0
    //double EoverPInMin[]     = { 0.9,   0.9,   0.9,   0.6,   0.9,   0.9,   0.9,   0.7   }; // 1
    double deltaEtaIn[]	     = { 0.004, 0.006, 0.005, 0.007, 0.007, 0.008, 0.007, 0.008 }; // 2
    double deltaPhiIn[]	     = { 0.04,  0.07,  0.04,  0.08,  0.06,  0.07,  0.06,  0.07  }; // 3
    double HoverE[] 	     = { 0.06,  0.05,  0.06,  0.14,  0.1,   0.1,   0.1,   0.12  }; // 4
    double E9overE25[]	     = { 0.7,   0.75,  0.8,   0.,    0.85,  0.75,  0.8,   0.    }; // 5
    double EoverPOutMax[]    = { 2.5,   999.,  999.,  999.,  2.,    999.,  999.,  999.  }; // 6
    double EoverPOutMin[]    = { 0.6,   1.8,   1.,    0.75,  0.6,   1.5,   1.,    0.8   }; // 7
    double deltaPhiOut[]     = { 0.011, 999.,  999.,  999.,  0.02,  999.,  999.,  999.  }; // 8
    double invEMinusInvP[]   = { 0.06,  0.06,  0.06,  0.06,  0.06,  0.06,  0.06,  0.06  }; // 9
    //double sigmaEtaEtaMax[]  = { 0.011, 0.011, 0.011, 0.011, 0.022, 0.022, 0.022, 0.3   }; // 10
    //double sigmaEtaEtaMin[]  = { 0.00,  0.00, 0.00,   0.00,  0.00,  0.00,  0.00,  0.    }; // 11
    //double sigmaPhiPhiMax[]  = { 0.015, 999.,  999.,  999.,  0.02,  999.,  999.,  999.  }; // 12
    //double sigmaPhiPhiMin[]  = { 0.00,  0.,    0.,    0.,    0.,    0.,    0.,    0.    }; // 13
    
    const int nCuts = 16;
    bool passCut[nCuts] = {false, false, false, false, false, 
                           false, false, false, false, false,
                           false, false, false, false, false,
                           false};
    
    //if(e->ESuperClusterOverP() < EoverPInMax[cutClass])
 		      passCut[0] = true;
    //if(e->ESuperClusterOverP() > EoverPInMin[cutClass]) 		
      passCut[1] = true;
    if(fabs(e->DeltaEtaSuperClusterTrackAtVtx()) < deltaEtaIn[cutClass])      passCut[2] = true;
    if(fabs(e->DeltaPhiSuperClusterTrackAtVtx()) < deltaPhiIn[cutClass])      passCut[3] = true;
    if(e->HadronicOverEm() < HoverE[cutClass])                                passCut[4] = true;
    if(e->E33()/e->E55() > E9overE25[cutClass]) 
      passCut[5] = true;
    //comment out these two for now because this variable 
    //seems to be incorrect in CMSSW 2_0_8                              
    if(e->ESeedClusterOverPout() < EoverPOutMax[cutClass])                    passCut[6] = true;
    if(e->ESeedClusterOverPout() > EoverPOutMin[cutClass])                    passCut[7] = true;
    if(fabs(e->DeltaPhiSeedClusterTrackAtCalo()) < deltaPhiOut[cutClass])     passCut[8] = true;
    if(electronepInv < invEMinusInvP[cutClass])                               passCut[9] = true;
    //if(e->CovEtaEta() < sigmaEtaEtaMax[cutClass])  			 
     passCut[10] = true;
    //if(e->CovEtaEta() > sigmaEtaEtaMin[cutClass])  			   
   passCut[11] = true;
    //if(e->CovPhiPhi() < sigmaPhiPhiMax[cutClass])  			   
   passCut[12] = true;
    //if(e->CovPhiPhi() > sigmaPhiPhiMin[cutClass])  			   
   passCut[13] = true;
    if(e->TrackIsolation() < 5.0)                                             passCut[14] = true;
    if(e->CaloIsolation() < 5.0)                                              passCut[15] = true; 
    
    // Final decision
    bool allCuts = true;  
    for(int c=0; c<nCuts; c++) {
      allCuts = allCuts & passCut[c];
    }
    
    //make electron ID selection histogram
    fElectronSelection->Fill(-1);
    if (!isFake)
      fRealElectronSelection->Fill(-1);
    else 
      fFakeElectronSelection->Fill(-1);
    
    for (int k=0;k<16;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
        pass = (pass && passCut[p]);      
      if (pass) {
        fElectronSelection->Fill(k);	
        if (!isFake)
          fRealElectronSelection->Fill(k);
        else 
          fFakeElectronSelection->Fill(k);
      }
    }
    
    //Check whether it overlaps with a good muon.
    bool isMuonOverlap = false;
    for (UInt_t j=0; j<GoodMuons->GetEntries();j++) {
      double deltaR = MathUtils::DeltaR(GoodMuons->At(j)->Mom(), e->Mom());     
      if (deltaR < 0.1) {
        isMuonOverlap = true;
        break;	 
      }
    }
    
    //Check whether it overlaps with another electron candidate
    bool isElectronOverlap = false;
    for (UInt_t j=0; j<GoodElectronsVector.size(); j++) {      
      double deltaR = MathUtils::DeltaR(GoodElectronsVector[j]->Mom(), e->Mom());

      if (deltaR < 0.1) {
        isElectronOverlap = true;        
        
        //if there's an overlap and the new one being considered has E/P closer to 1.0 
        //then replace the overlapping one with this new one because it's better.
        //Once we get super cluster info, we should make sure the superclusters match 
        //before declaring it is a duplicate
        //can have one SC matched to many tracks. or one track matched to many SC's. 
        //we should cover all the cases. see SUSYAnalyzer...
        if (abs(GoodElectronsVector[j]->ESuperClusterOverP() - 1) > 
            abs(e->ESuperClusterOverP() - 1)) {	   
          GoodElectronsVector[j] = e;
        }        
        break;
      }
    }
    

    //Debug information
    if (e->Trk()->Pt() > 2000) {
      cout << "!!!!!!!!!!!!!!! Track Pt: " << e->Trk()->Pt() << endl;
      debug = true;
    }

    //These are Good Electrons
    bool imposeElectronID = false;
    if ( (!imposeElectronID || allCuts)
//          && abs(e->Eta()) < 2.5
          && !isMuonOverlap && !isElectronOverlap    
               
      ) {       
      fGoodElectronPtHist->Fill(e->Pt());
      fGoodElectronEtaHist->Fill(e->Eta());  
      fGoodElectronClassification->Fill(e->Classification());
      
      GoodElectronsVector.push_back(fElectrons->At(i));   
      GoodElectronIsFake.push_back(isFake);
      //debug = isFake && !isFromTau;	
    }     
  }   
  
  //fill the electron ObjArray with the contents of the vector
  ObjArray<Electron> *GoodElectrons = new ObjArray<Electron>;
  for (UInt_t j=0; j<GoodElectronsVector.size(); j++) 
    GoodElectrons->Add(GoodElectronsVector[j]);
  
  
  //Get Jet info
  ObjArray<Jet> GoodJets; 
  ObjArray<Jet> *GoodCentralJets = new ObjArray<Jet>; 
  ObjArray<Jet> *GoodForwardJets = new ObjArray<Jet>; 
  LoadBranch(fJetName);
  for (UInt_t i=0; i<fJets->GetEntries(); ++i) {
    Jet *jet = fJets->At(i);
     //cout << "Jet " << i << endl;
     //cout << jet->Pt() << " " << jet->Eta() << endl;
        
    bool isElectronOverlap = false;
    bool isFromGenLepton = false;
     
    //Check for overlap with an electron
    for (UInt_t j=0; j<GoodElectrons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GoodElectrons->At(j)->Mom(),jet->Mom());  
      if (deltaR < 0.1) {
	isElectronOverlap = true;	 	 	
	break;	 	 
      }      
    }
    if (isElectronOverlap) continue; //skip this jet if it was an overlap
    
    
    fAllJetPtHist->Fill(jet->Pt());
    fAllJetEtaHist->Fill(jet->Eta());
    fAllJetPtEta2DHist->Fill(jet->Pt(), jet->Eta());
    
    //check whether a jet is actually from a lepton
    for (UInt_t j=0; j<GenLeptons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GenLeptons->At(j)->Mom(),jet->Mom());
      if (deltaR < 0.1) {
	isFromGenLepton = true;	
	//debug = true;
	if (abs(GenLeptons->At(j)->PdgId()) == 15) {
	  // isFromTau = true;	 
	}
	if (printDebug) cout << "Fake Jet Found" << endl;
	break; 	 	   	  	   
      }
    }
    
    const int nCuts = 4;
    double cutValue[nCuts]  = {1.0, 20., 2.5, 0.2};
    bool passCut[nCuts] = {false, false, false, false};
    
    passCut[0] = (!isElectronOverlap); //This is supposed to check e/ph overlap
    if(jet->Et() // /jet.scaleFactor() 
       > cutValue[1])    passCut[1] = true;
    if(fabs(jet->Eta()) < cutValue[2])    passCut[2] = true;
    
    //Si: We don't make this cut for now, since we don't have alpha saved
    //if(//jet.alpha() > cutValue[3] ||
    //	jet.Pt()/jet.scaleFactor() > 20.) 
    passCut[3] = true; 
    
    // Final decision
    bool passAllCentralJetCuts = true;
    bool passAllForwardJetCuts = true;
    for(int i=0; i<nCuts; i++) {
      passAllCentralJetCuts = passAllCentralJetCuts & passCut[i];
      passAllForwardJetCuts = passAllForwardJetCuts & ((i==2)?(!passCut[i]):passCut[i]);       
    }
    
    //make electron ID selection histogram
    fCentralJetSelection->Fill(-1);
    if (!isFromGenLepton)
      fRealJetSelection->Fill(-1);
    else 
      fFakeJetSelection->Fill(-1);
    
    for (int k=0;k<nCuts;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
	pass = (pass && passCut[p]);
      
      if (pass) {
	fCentralJetSelection->Fill(k);	
	if (!isFromGenLepton)
	  fRealJetSelection->Fill(k);
	else 
	  fFakeJetSelection->Fill(k);
      }
    } 
    
    
    //Fill All Jet Histograms     
    fAllJetMaxEInEmTowers->Fill(jet->MaxEInEmTowers());
    fAllJetMaxEInHadTowers->Fill(jet->MaxEInHadTowers());
    fAllJetEnergyFractionH->Fill(jet->EnergyFractionH());
    fAllJetEnergyFractionEm->Fill(jet->EnergyFractionEm());
    fAllJetHadEnergyInHB->Fill(jet->HadEnergyInHB());
    fAllJetHadEnergyInHO->Fill(jet->HadEnergyInHO());
    fAllJetHadEnergyInHE->Fill(jet->HadEnergyInHE());
    fAllJetHadEnergyInHF->Fill(jet->HadEnergyInHF());
    fAllJetEmEnergyInEB->Fill(jet->EmEnergyInEB());
    fAllJetEmEnergyInEE->Fill(jet->EmEnergyInEE());
    fAllJetEmEnergyInHF->Fill(jet->EmEnergyInHF());
    fAllJetTowersArea->Fill(jet->TowersArea());
    fAllJetN->Fill(jet->N());
    fAllJetN60->Fill(jet->N60());
    fAllJetN90->Fill(jet->N90());
    //For Fake Jets
    if (isFromGenLepton) {
      fFakeJetPtHist->Fill(jet->Pt());
      fFakeJetEtaHist->Fill(jet->Eta());
      fFakeJetPtEta2DHist->Fill(jet->Pt(), jet->Eta());
      fAllJetIsFake->Fill(1);
      fFakeJetMaxEInEmTowers->Fill(jet->MaxEInEmTowers());
      fFakeJetMaxEInHadTowers->Fill(jet->MaxEInHadTowers());
      fFakeJetEnergyFractionH->Fill(jet->EnergyFractionH());
      fFakeJetEnergyFractionEm->Fill(jet->EnergyFractionEm());
      fFakeJetHadEnergyInHB->Fill(jet->HadEnergyInHB());
      fFakeJetHadEnergyInHO->Fill(jet->HadEnergyInHO());
      fFakeJetHadEnergyInHE->Fill(jet->HadEnergyInHE());
      fFakeJetHadEnergyInHF->Fill(jet->HadEnergyInHF());
      fFakeJetEmEnergyInEB->Fill(jet->EmEnergyInEB());
      fFakeJetEmEnergyInEE->Fill(jet->EmEnergyInEE());
      fFakeJetEmEnergyInHF->Fill(jet->EmEnergyInHF());
      fFakeJetTowersArea->Fill(jet->TowersArea());
      fFakeJetN->Fill(jet->N());
      fFakeJetN60->Fill(jet->N60());
      fFakeJetN90->Fill(jet->N90());
    } else { //real Jet
      fRealJetPtHist->Fill(jet->Pt());
      fRealJetEtaHist->Fill(jet->Eta());
      fRealJetPtEta2DHist->Fill(jet->Pt(), jet->Eta());
      fAllJetIsFake->Fill(0);
      fRealJetMaxEInEmTowers->Fill(jet->MaxEInEmTowers());
      fRealJetMaxEInHadTowers->Fill(jet->MaxEInHadTowers());
      fRealJetEnergyFractionH->Fill(jet->EnergyFractionH());
      fRealJetEnergyFractionEm->Fill(jet->EnergyFractionEm());
      fRealJetHadEnergyInHB->Fill(jet->HadEnergyInHB());
      fRealJetHadEnergyInHO->Fill(jet->HadEnergyInHO());
      fRealJetHadEnergyInHE->Fill(jet->HadEnergyInHE());
      fRealJetHadEnergyInHF->Fill(jet->HadEnergyInHF());
      fRealJetEmEnergyInEB->Fill(jet->EmEnergyInEB());
      fRealJetEmEnergyInEE->Fill(jet->EmEnergyInEE());
      fRealJetEmEnergyInHF->Fill(jet->EmEnergyInHF());
      fRealJetTowersArea->Fill(jet->TowersArea());
      fRealJetN->Fill(jet->N());
      fRealJetN60->Fill(jet->N60());
      fRealJetN90->Fill(jet->N90());
    }
    
    
    //Save Good Jets
    if (passAllCentralJetCuts) {
      //GoodJets.push_back(jet);
      GoodCentralJets->Add(jet);
      
      fGoodCentralJetPtHist->Fill(jet->Pt());
      fGoodCentralJetEtaHist->Fill(jet->Eta());
      fGoodCentralJetPtEta2DHist->Fill(jet->Pt(), jet->Eta());
      //debug = isFromGenLepton;
      
      fGoodCentralJetMaxEInEmTowers->Fill(jet->MaxEInEmTowers());
      fGoodCentralJetMaxEInHadTowers->Fill(jet->MaxEInHadTowers());
      fGoodCentralJetEnergyFractionH->Fill(jet->EnergyFractionH());
      fGoodCentralJetEnergyFractionEm->Fill(jet->EnergyFractionEm());
      fGoodCentralJetHadEnergyInHB->Fill(jet->HadEnergyInHB());
      fGoodCentralJetHadEnergyInHO->Fill(jet->HadEnergyInHO());
      fGoodCentralJetHadEnergyInHE->Fill(jet->HadEnergyInHE());
      fGoodCentralJetHadEnergyInHF->Fill(jet->HadEnergyInHF());
      fGoodCentralJetEmEnergyInEB->Fill(jet->EmEnergyInEB());
      fGoodCentralJetEmEnergyInEE->Fill(jet->EmEnergyInEE());
      fGoodCentralJetEmEnergyInHF->Fill(jet->EmEnergyInHF());
      fGoodCentralJetTowersArea->Fill(jet->TowersArea());
      fGoodCentralJetN->Fill(jet->N());
      fGoodCentralJetN60->Fill(jet->N60());
      fGoodCentralJetN90->Fill(jet->N90());
    }
    
    if(passAllForwardJetCuts)
      GoodForwardJets->Add(jet);
    
  } //for all jets
  
  //we should sort the jets in Pt
  //We don't sort them for now because ObjArray can't do it yet
  // for(UInt_t i=0; i < GoodCentralJets->GetEntries(); i++)
  //      for(UInt_t j=i+1; j < GoodCentralJets->GetEntries(); j++)
  //        if(GoodCentralJets[i]->Et() < GoodCentralJets[j]->Et()) {
  // 	 //swap i and j
  // 	 Jet* tempjet = GoodCentralJets[i];
  // 	 GoodCentralJets[i] = GoodCentralJets[j];
  // 	 GoodCentralJets[j] = tempjet;	 	 	 
  //        }  
  //check
  
  if (printDebug) {
    cout << "Check Jet Sort\n";
    for(UInt_t i=0; i<GoodCentralJets->GetEntries(); i++)
      cout << GoodCentralJets->At(i)->Et() << " " << GoodCentralJets->At(i)->Eta() << " " 
           << GoodCentralJets->At(i)->Phi() << endl;
  }
  
   //Get MET
   LoadBranch(fMetName);
   
   Met *met = fMet->At(0); //define the met
   fMetRawPtHist->Fill(met->Pt());
   fMetRawPhiHist->Fill(met->Phi());
      
   if (debug && printDebug) {
     cout << "Correct MET for muons" << endl;
     cout << "Original MET: " << met->Px() << " " << met->Py() << endl;
   }

   double met_px = met->Px();
   double met_py = met->Py();
   for (UInt_t j=0; j < GoodMuons->GetEntries() ; j++) {
     if (debug && printDebug) cout << "Muon " << j << " " << GoodMuons->At(j)->Px() << " " 
                                   <<GoodMuons->At(j)->Py() << endl;
     met_px = met_px - GoodMuons->At(j)->Px();
     met_py = met_py - GoodMuons->At(j)->Py();
   }
   if (debug && printDebug) cout << "Final MET: " << met_px << " " << met_py << endl;
   
   Met *muonCorrectedMet = new Met (met_px, met_py);
   fMetMuonCorrectedPtHist->Fill(muonCorrectedMet->Pt());
   fMetMuonCorrectedPhiHist->Fill(muonCorrectedMet->Phi());
   
   //Save Objects for Other Modules to use
   AddObjThisEvt(GoodElectrons, fGoodElectronsName.c_str());
   AddObjThisEvt(GoodMuons, fGoodMuonsName.c_str());
   AddObjThisEvt(GoodCentralJets, fGoodCentralJetsName.c_str());
   AddObjThisEvt(GoodForwardJets, fGoodForwardJetsName.c_str());
   AddObjThisEvt(muonCorrectedMet, fMuonCorrectedMetName.c_str());
   AddObjThisEvt(GenLeptons,fGenLeptonsName.c_str());

   //Final Summary Debug Output   
   if ( 
       printDebug &&
       debug )
     
     {
       cout << "Event Dump: " << fNEventsProcessed << endl;
       
       //print out event content to text
       cout << "Electrons" << endl;
       for (UInt_t i = 0; i < GoodElectrons->GetEntries(); i++) {
	 cout << i << " " << GoodElectrons->At(i)->Pt() << " " << GoodElectrons->At(i)->Eta() 
              << " " << GoodElectrons->At(i)->Phi() << " " 
              << GoodElectrons->At(i)->ESuperClusterOverP() << endl;    
       }   
       
       cout << "Muons" << endl;
       for (UInt_t i = 0; i < GoodMuons->GetEntries(); i++) {
	 cout << i << " " << GoodMuons->At(i)->Pt() << " " << GoodMuons->At(i)->Eta() 
              << " " << GoodMuons->At(i)->Phi() << endl;    
       }
       
       cout << "Central Jets" << endl;
       for (UInt_t i = 0; i < GoodCentralJets->GetEntries(); i++) {
	 cout << i << " " << GoodCentralJets->At(i)->Pt() << " " 
              << GoodCentralJets->At(i)->Eta() << " " << GoodCentralJets->At(i)->Phi() << endl;    
       }
       
       cout << "CorrectedMET" << endl;	  
       cout << muonCorrectedMet->Pt() << " " << muonCorrectedMet->Eta() << " " 
            << muonCorrectedMet->Phi() << endl;    	  
       
       
       //print out Generator BLock       
       LoadBranch(fMCPartName);
       cout << "Generator Block" << endl;
       for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
	 MCParticle* p = fParticles->At(i); 	 
         cout << i << " " << p->PdgId() << " " << p->Status() << " " << p->Pt() 
              << " " << p->Eta() << " " << p->Phi() << endl;	    	 
       }
       
     }
}


//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMCPartName,                fParticles);
  ReqBranch(fTrackName,                 fTracks);
  ReqBranch(fBarrelBasicClusterName,    fBarrelBasicClusters);
  ReqBranch(fBarrelSuperClusterName,    fBarrelSuperClusters);
  ReqBranch(fMuonName,                  fMuons);
  ReqBranch(fElectronName,              fElectrons);
  ReqBranch(fJetName,                   fJets);
  ReqBranch(fMetName,                   fMet);

  fGenPtHist                       = new TH1D("hGenPtHist",";p_{t};#",200,0.,200.);
  fGenEtaHist                      = new TH1D("hGenEtaHist",";#eta;#",160,-8.,8.);
  fGenPhiHist                      = new TH1D("hGenPhiHist",";#phi;#",200,-3.2,3.2);
  fGenElectronPt                   = new TH1D("hGenElectronPt",";p_{t};#",250,0.,1000);
  fGenElectronEta                  = new TH1D("hGenElectronEta",";#eta;#",160,-8.,8.);
  fGenElectronPhi                  = new TH1D("hGenElectronPhi",";#phi;#",200,-3.2,3.2);
  fGenMuonPt                       = new TH1D("hGenMuonPt",";p_{t};#",200,0.,200.);
  fGenMuonEta                      = new TH1D("hGenMuonEta",";#eta;#",160,-8.,8.);
  fGenMuonPhi                      = new TH1D("hGenMuonPhi",";#phi;#",200,-3.2,3.2);
  fGenTauPt                        = new TH1D("hGenTauPt",";p_{t};#",200,0.,200.);
  fGenTauEta                       = new TH1D("hGenTauEta",";#eta;#",160,-8.,8.);
  fGenTauPhi                       = new TH1D("hGenTauPhi",";#phi;#",200,-3.2,3.2);
  AddOutput(fGenPtHist);
  AddOutput(fGenEtaHist); 
  AddOutput(fGenPhiHist); 
  AddOutput(fGenElectronPt);
  AddOutput(fGenElectronEta); 
  AddOutput(fGenElectronPhi); 
  AddOutput(fGenMuonPt);
  AddOutput(fGenMuonEta); 
  AddOutput(fGenMuonPhi); 
  AddOutput(fGenTauPt);
  AddOutput(fGenTauEta); 
  AddOutput(fGenTauPhi); 


  fTrackPtHist                     = new TH1D("hTrackPtHist",";p_{t};#",100,0.,25.);
  fTrackThetaHist                  = new TH1D("hTrackThetaHist",";#theta;#",100,-5.0,5.0);
  fTrackPhiHist                    = new TH1D("hTrackPhiHist",";p_{t};#",100,-3.5,3.5);
  AddOutput(fTrackPhiHist);
  AddOutput(fTrackPtHist);  
  AddOutput(fTrackThetaHist);
   

  //Muon Plots
  fAllMuonPtHist                   = new TH1D("hAllMuonPtHist",";p_{t};#",200,0.,200.);
  fAllMuonEtaHist                  = new TH1D("hAllMuonEtaHist",";#eta;#",100,-5.,5.);
  fAllMuonChi2                     = new TH1D("hAllMuonChi2",";Chi2;#",51,0,50);
  fAllMuonNHits                    = new TH1D("hAllMuonNHits",";NHits;#",71,0,70);
  fAllMuonBestTrackD0              = new TH1D("hAllMuonBestTrackD0",";BestTrackD0;#",100,0,0.1);
  fAllMuonIsoR03SumPt              = new TH1D("hAllMuonIsoR03SumPt",";IsoR03SumPt;#",100,0,10);
  fAllMuonIsoR03EmEt               = new TH1D("hAllMuonIsoR03EmEt", ";IsoR03EmEt;#",100,0,10);
  fAllMuonIsoR03HadEt              = new TH1D("hAllMuonIsoR03HadEt", ";IsoR03HadEt;#",100,0,10); 
  fAllMuonIsoR03EmAndHadEt         = new TH1D("hAllMuonIsoR03EmAndHadEt", 
                                              ";IsoR03EmAndHadEt;#",100,0,10);
  fAllMuonIsoR03HoEt               = new TH1D("hAllMuonIsoR03HoEt",  ";IsoR03HoEt;#",100,0,10);
  fAllMuonIsoR03NTracks            = new TH1D("hAllMuonIsoR03NTracks", ";IsoR03NTracks;#",50,0,50);
  fAllMuonIsoR03NJets              = new TH1D("hAllMuonIsoR03NJets",  ";IsoR03NJets;#",10,0,10);
  fAllMuonIsoR05SumPt              = new TH1D("hAllMuonIsoR05SumPt", ";IsoR05SumPt;#",100,0,10);
  fAllMuonIsoR05EmEt               = new TH1D("hAllMuonIsoR05EmEt", ";IsoR05EmEt;#",100,0,10);
  fAllMuonIsoR05HadEt              = new TH1D("hAllMuonIsoR05HadEt",  ";IsoR05HadEt;#",100,0,10);
  fAllMuonIsoR05HoEt               = new TH1D("hAllMuonIsoR05HoEt",  ";IsoR05HoEt;#",100,0,10);
  fAllMuonIsoR05NTracks            = new TH1D("hAllMuonIsoR05NTracks",";IsoR05NTracks;#",50,0,50);
  fAllMuonIsoR05NJets              = new TH1D("hAllMuonIsoR05NJets",  ";IsoR05NJets;#",10,0,10);
  fAllMuonEmEnergy                 = new TH1D("hAllMuonEmEnergy",";EmEnergy;#",100,0,10);
  fAllMuonHadEnergy                = new TH1D("hAllMuonHadEnergy",";HadEnergy;#",100,0,30);
  fAllMuonHoEnergy                 = new TH1D("hAllMuonHoEnergy",";HoEnergy;#",100,0,10);
  fAllMuonEmS9Energy               = new TH1D("hAllMuonEmS9Energy",";EmS9Energy;#",100,0,10);
  fAllMuonHadS9Energy              = new TH1D("hAllMuonHadS9Energy",";HadS9Energy;#",100,0,30);
  fAllMuonHoS9Energy               = new TH1D("hAllMuonHoS9Energy",";HoS9Energy;#",100,0,10);
  fRealMuonPtHist                  = new TH1D("hRealMuonPtHist",";p_{t};#",200,0.,200.);
  fRealMuonEtaHist                 = new TH1D("hRealMuonEtaHist",";#eta;#",100,-5.,5.);
  fRealMuonChi2                    = new TH1D("hRealMuonChi2",";Chi2;#",51,0,50);
  fRealMuonNHits                   = new TH1D("hRealMuonNHits",";NHits;#",71,0,70);
  fRealMuonBestTrackD0             = new TH1D("hRealMuonBestTrackD0",";BestTrackD0;#",100,0,0.1);
  fRealMuonIsoR03SumPt             = new TH1D("hRealMuonIsoR03SumPt",";IsoR03SumPt;#",100,0,10);
  fRealMuonIsoR03EmEt              = new TH1D("hRealMuonIsoR03EmEt",";IsoR03EmEt;#",100,0,10);
  fRealMuonIsoR03HadEt             = new TH1D("hRealMuonIsoR03HadEt",";IsoR03HadEt;#",100,0,10);
  fRealMuonIsoR03EmAndHadEt        = new TH1D("hRealMuonIsoR03EmAndHadEt",
                                              ";IsoR03EmAndHadEt;#",100,0,10);
  fRealMuonIsoR03HoEt              = new TH1D("hRealMuonIsoR03HoEt",";IsoR03HoEt;#",100,0,10);
  fRealMuonIsoR03NTracks           = new TH1D("hRealMuonIsoR03NTracks",";IsoR03NTracks;#",50,0,50);
  fRealMuonIsoR03NJets             = new TH1D("hRealMuonIsoR03NJets", ";IsoR03NJets;#",10,0,10);
  fRealMuonIsoR05SumPt             = new TH1D("hRealMuonIsoR05SumPt", ";IsoR05SumPt;#",100,0,10);
  fRealMuonIsoR05EmEt              = new TH1D("hRealMuonIsoR05EmEt", ";IsoR05EmEt;#",100,0,10);
  fRealMuonIsoR05HadEt             = new TH1D("hRealMuonIsoR05HadEt", ";IsoR05HadEt;#",100,0,10);
  fRealMuonIsoR05HoEt              = new TH1D("hRealMuonIsoR05HoEt", ";IsoR05HoEt;#",100,0,10);
  fRealMuonIsoR05NTracks           = new TH1D("hRealMuonIsoR05NTracks",";IsoR05NTracks;#",50,0,50);
  fRealMuonIsoR05NJets             = new TH1D("hRealMuonIsoR05NJets",";IsoR05NJets;#",10,0,10);
  fRealMuonEmEnergy                = new TH1D("hRealMuonEmEnergy",";EmEnergy;#",100,0,10);
  fRealMuonHadEnergy               = new TH1D("hRealMuonHadEnergy",";HadEnergy;#",100,0,30);
  fRealMuonHoEnergy                = new TH1D("hRealMuonHoEnergy",";HoEnergy;#",100,0,10);
  fRealMuonEmS9Energy              = new TH1D("hRealMuonEmS9Energy",";EmS9Energy;#",100,0,10);
  fRealMuonHadS9Energy             = new TH1D("hRealMuonHadS9Energy",";HadS9Energy;#",100,0,30);
  fRealMuonHoS9Energy              = new TH1D("hRealMuonHoS9Energy",";HoS9Energy;#",100,0,10);
  fFakeMuonPtHist                  = new TH1D("hFakeMuonPtHist",";p_{t};#",200,0.,200.);
  fFakeMuonEtaHist                 = new TH1D("hFakeMuonEtaHist",";#eta;#",100,-5.,5.);
  fFakeMuonChi2                    = new TH1D("hFakeMuonChi2",";Chi2;#",51,0,50);
  fFakeMuonNHits                   = new TH1D("hFakeMuonNHits", ";NHits;#",71,0,70);
  fFakeMuonBestTrackD0             = new TH1D("hFakeMuonBestTrackD0",";BestTrackD0;#",100,0,0.1);
  fFakeMuonIsoR03SumPt             = new TH1D("hFakeMuonIsoR03SumPt",";IsoR03SumPt;#",100,0,10);
  fFakeMuonIsoR03EmEt              = new TH1D("hFakeMuonIsoR03EmEt",";IsoR03EmEt;#",100,0,10);
  fFakeMuonIsoR03HadEt             = new TH1D("hFakeMuonIsoR03HadEt",";IsoR03HadEt;#",100,0,10);
  fFakeMuonIsoR03EmAndHadEt        = new TH1D("hFakeMuonIsoR03EmAndHadEt",
                                              ";IsoR03EmAndHadEt;#",100,0,10);
  fFakeMuonIsoR03HoEt              = new TH1D("hFakeMuonIsoR03HoEt",";IsoR03HoEt;#",100,0,10);
  fFakeMuonIsoR03NTracks           = new TH1D("hFakeMuonIsoR03NTracks",";IsoR03NTracks;#",50,0,50);
  fFakeMuonIsoR03NJets             = new TH1D("hFakeMuonIsoR03NJets",";IsoR03NJets;#",10,0,10);
  fFakeMuonIsoR05SumPt             = new TH1D("hFakeMuonIsoR05SumPt",";IsoR05SumPt;#",100,0,10);
  fFakeMuonIsoR05EmEt              = new TH1D("hFakeMuonIsoR05EmEt",";IsoR05EmEt;#",100,0,10);
  fFakeMuonIsoR05HadEt             = new TH1D("hFakeMuonIsoR05HadEt",";IsoR05HadEt;#",100,0,10);
  fFakeMuonIsoR05HoEt              = new TH1D("hFakeMuonIsoR05HoEt",";IsoR05HoEt;#",100,0,10);
  fFakeMuonIsoR05NTracks           = new TH1D("hFakeMuonIsoR05NTracks",";IsoR05NTracks;#",50,0,50);
  fFakeMuonIsoR05NJets             = new TH1D("hFakeMuonIsoR05NJets",";IsoR05NJets;#",10,0,10);
  fFakeMuonEmEnergy                = new TH1D("hFakeMuonEmEnergy",";EmEnergy;#",100,0,10);
  fFakeMuonHadEnergy               = new TH1D("hFakeMuonHadEnergy",";HadEnergy;#",100,0,30);
  fFakeMuonHoEnergy                = new TH1D("hFakeMuonHoEnergy",";HoEnergy;#",100,0,10);
  fFakeMuonEmS9Energy              = new TH1D("hFakeMuonEmS9Energy",";EmS9Energy;#",100,0,10);
  fFakeMuonHadS9Energy             = new TH1D("hFakeMuonHadS9Energy",";HadS9Energy;#",100,0,30);
  fFakeMuonHoS9Energy              = new TH1D("hFakeMuonHoS9Energy",";HoS9Energy;#",100,0,10); 
  fGoodMuonPtHist                  = new TH1D("hGoodMuonPtHist",";p_{t};#",200,0.,200.);
  fGoodMuonEtaHist                 = new TH1D("hGoodMuonEtaHist",";#eta;#",21,-5.,5.);
  fMuonSelection                   = new TH1D("hMuonSelection", ";MuonSelection;#",4,-1.5,2.5 ) ;  
  fRealMuonSelection               = new TH1D("hRealMuonSelection",
                                              ";RealMuonSelection;#",4,-1.5,2.5 ) ;    
  fFakeMuonSelection               = new TH1D("hFakeMuonSelection", 
                                             ";FakeMuonSelection;#",4,-1.5,2.5 ) ;  
  AddOutput(fAllMuonPtHist);
  AddOutput(fAllMuonEtaHist);
  AddOutput(fAllMuonChi2);
  AddOutput(fAllMuonNHits);
  AddOutput(fAllMuonBestTrackD0);
  AddOutput(fAllMuonIsoR03SumPt);
  AddOutput(fAllMuonIsoR03EmEt);
  AddOutput(fAllMuonIsoR03HadEt);
  AddOutput(fAllMuonIsoR03EmAndHadEt);
  AddOutput(fAllMuonIsoR03HoEt);
  AddOutput(fAllMuonIsoR03NTracks);
  AddOutput(fAllMuonIsoR03NJets);
  AddOutput(fAllMuonIsoR05SumPt);
  AddOutput(fAllMuonIsoR05EmEt);
  AddOutput(fAllMuonIsoR05HadEt);
  AddOutput(fAllMuonIsoR05HoEt);
  AddOutput(fAllMuonIsoR05NTracks);
  AddOutput(fAllMuonIsoR05NJets);
  AddOutput(fAllMuonEmEnergy);
  AddOutput(fAllMuonHadEnergy);
  AddOutput(fAllMuonHoEnergy);
  AddOutput(fAllMuonEmS9Energy);
  AddOutput(fAllMuonHadS9Energy);
  AddOutput(fAllMuonHoS9Energy);
  AddOutput(fRealMuonPtHist);
  AddOutput(fRealMuonEtaHist);
  AddOutput(fRealMuonChi2);
  AddOutput(fRealMuonNHits);
  AddOutput(fRealMuonBestTrackD0);
  AddOutput(fRealMuonIsoR03SumPt);
  AddOutput(fRealMuonIsoR03EmEt);
  AddOutput(fRealMuonIsoR03HadEt);
  AddOutput(fRealMuonIsoR03EmAndHadEt);
  AddOutput(fRealMuonIsoR03HoEt);
  AddOutput(fRealMuonIsoR03NTracks);
  AddOutput(fRealMuonIsoR03NJets);
  AddOutput(fRealMuonIsoR05SumPt);
  AddOutput(fRealMuonIsoR05EmEt);
  AddOutput(fRealMuonIsoR05HadEt);
  AddOutput(fRealMuonIsoR05HoEt);
  AddOutput(fRealMuonIsoR05NTracks);
  AddOutput(fRealMuonIsoR05NJets);
  AddOutput(fRealMuonEmEnergy);
  AddOutput(fRealMuonHadEnergy);
  AddOutput(fRealMuonHoEnergy);
  AddOutput(fRealMuonEmS9Energy);
  AddOutput(fRealMuonHadS9Energy);
  AddOutput(fRealMuonHoS9Energy);
  AddOutput(fFakeMuonPtHist);
  AddOutput(fFakeMuonEtaHist);
  AddOutput(fFakeMuonChi2);
  AddOutput(fFakeMuonNHits);
  AddOutput(fFakeMuonBestTrackD0);
  AddOutput(fFakeMuonIsoR03SumPt);
  AddOutput(fFakeMuonIsoR03EmEt);
  AddOutput(fFakeMuonIsoR03HadEt);
  AddOutput(fFakeMuonIsoR03EmAndHadEt);
  AddOutput(fFakeMuonIsoR03HoEt);
  AddOutput(fFakeMuonIsoR03NTracks);
  AddOutput(fFakeMuonIsoR03NJets);
  AddOutput(fFakeMuonIsoR05SumPt);
  AddOutput(fFakeMuonIsoR05EmEt);
  AddOutput(fFakeMuonIsoR05HadEt);
  AddOutput(fFakeMuonIsoR05HoEt);
  AddOutput(fFakeMuonIsoR05NTracks);
  AddOutput(fFakeMuonIsoR05NJets);
  AddOutput(fFakeMuonEmEnergy);
  AddOutput(fFakeMuonHadEnergy);
  AddOutput(fFakeMuonHoEnergy);
  AddOutput(fFakeMuonEmS9Energy);
  AddOutput(fFakeMuonHadS9Energy);
  AddOutput(fFakeMuonHoS9Energy);
  AddOutput(fGoodMuonPtHist);
  AddOutput(fGoodMuonEtaHist);
  AddOutput(fMuonSelection);
  AddOutput(fRealMuonSelection);
  AddOutput(fFakeMuonSelection);

  //Electron Plots
  fAllElectronPtHist                     = new TH1D("hAllElectronPtHist",";p_{t};#",100,0.,200.);  
  fAllElectronEtaHist                    = new TH1D("hAllElectronEtaHist",";#eta;#",100,-5.,5.);
  fAllElectronESuperClOverP              = new TH1D("hAllElectronESuperClOverP",
                                                   ";ESuperClOverP;#",100,0,5.0 ) ; 
  fAllElectronESeedClOverPout            = new TH1D("hAllElectronESeedClOverPout",
                                                    ";ESeedClOverPout;#",90,0,3.0 ) ; 
  fAllElectronDeltaEtaSuperClTrackAtVtx  = new TH1D("hAllElectronDeltaEtaSuperClTrackAtVtx",
                                                   ";DeltaEtaSuperClTrackAtVtx;#",200,0,0.02 ) ; 
  fAllElectronDeltaEtaSeedClTrackAtCalo  = new TH1D("hAllElectronDeltaEtaSeedClTrackAtCalo",
                                                    ";DeltaEtaSeedClTrackAtCalo;#",200,0,0.04 ) ; 
  fAllElectronDeltaPhiSuperClTrackAtVtx  = new TH1D("hAllElectronDeltaPhiSuperClTrackAtVtx",
                                                    ";DeltaPhiSuperClTrackAtVtx;#",200,0,-.1 ) ; 
  fAllElectronDeltaPhiSeedClTrackAtCalo  = new TH1D("hAllElectronDeltaPhiSeedClTrackAtCalo",
                                                    ";DeltaPhiSeedClTrackAtCalo;#",200,0,0.4 ) ; 
  fAllElectronEPInv                      = new TH1D("hAllElectronEPInv",
                                                    ";AllElectronEPInv;#",100,0,0.1);
  fAllElectronCutClass                   = new TH1D("hAllElectronCutClass",
                                                 ";AllElectronCutClass;#",10,-0.5,9.5);
  fAllElectronHadronicOverEm             = new TH1D("hAllElectronHadronicOverEm",
                                                 ";HadronicOverEm;#",150,-0.00001,0.14999 ) ; 
  fAllElectronE33OverE55                 = new TH1D("hAllElectronE33OverE55",
                                                 ";AllElectronE33OverE55;#",110,0,1.1);
  fAllElectronIsEnergyScaleCorrected     = new TH1D("hAllElectronIsEnergyScaleCorrected",
                                                    ";IsEnergyScaleCorrected;#",3,-1,1 ) ; 
  fAllElectronIsMomentumCorrected        = new TH1D("hAllElectronIsMomentumCorrected",
                                                    ";IsMomentumCorrected;#",3,-1,1 ) ; 
  fAllElectronNumberOfClusters           = new TH1D("hAllElectronNumberOfClusters",
                                                    ";NumberOfClusters;#",11,0,10 ) ; 
  fAllElectronClassification             = new TH1D("hAllElectronClassification",
                                                    ";Classification;#",51,0,50 ) ; 
  fAllElectronE33                        = new TH1D("hAllElectronE33",";E33;#",50,0,200 ) ; 
  fAllElectronE55                        = new TH1D("hAllElectronE55",";E55;#",50,0,200 ) ; 
  fAllElectronCovEtaEta                  = new TH1D("hAllElectronCovEtaEta",
                                                    ";CovEtaEta * 10^4;#",200,0,2.0 ) ; 
  fAllElectronCovEtaPhi                  = new TH1D("hAllElectronCovEtaPhi",
                                                    ";CovEtaPhi * 10^4;#",100,0,1.0 ) ; 
  fAllElectronCovPhiPhi                  = new TH1D("hAllElectronCovPhiPhi",
                                                    ";CovPhiPhi * 10^3;#",200,0,2.0 ) ; 
  fAllElectronLat                        = new TH1D("hAllElectronLat",";Lat;#",20,0,10 ) ; 
  fAllElectronZernike20                  = new TH1D("hAllElectronZernike20",
                                                    ";Zernike20;#",20,0,10 ) ; 
  fAllElectronZernike42                  = new TH1D("hAllElectronZernike42",
                                                    ";Zernike42;#",20,0,10 ) ; 
  fAllElectronCaloIso                    = new TH1D("hAllElectronCaloIso",
                                                    ";CaloIso;#",100,0,10 ) ; 
  fAllElectronTrackIso                   = new TH1D("hAllElectronTrackIso",
                                                    ";TrackIso;#",100,0,10 ) ; 
  fAllElectronComputedEcalIso            = new TH1D("hAllElectronComputedEcalIso",
                                                    ";ComputedEcalIso;#",100,0,10 ) ; 
  fAllElectronComputedTrackIso           = new TH1D("hAllElectronComputedTrackIso",
                                                    ";ComputedTrackIso;#",100,0,10 ) ; 
  fAllElectronTrackChi2                  = new TH1D("hAllElectronTrackChi2",
                                                    ";TrackChi2;#",100,0,100 ) ; 
  fAllElectronTrackNHits                 = new TH1D("hAllElectronTrackNHits",
                                                    ";TrackNHits;#",100,0,100 ) ; 
  fAllElectronPOutOverPIn                = new TH1D("hAllElectronPOutOverPIn",
                                                    ";POutOverPIn;#",100,0,1 ) ; 
  fAllElectronSuperClEOverTrueE          = new TH1D("hAllElectronSuperClEOverTrueE",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
  fAllElectronPOverTrueP                 = new TH1D("hAllElectronPOverTrueP",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
 

  fRealElectronPtHist                    = new TH1D("hRealElectronPtHist",";p_{t};#",100,0.,200.);

  fRealElectronEtaHist                   = new TH1D("hRealElectronEtaHist",";#eta;#",100,-5.,5.);
  fRealElectronESuperClOverP             = new TH1D("hRealElectronESuperClOverP",
                                                    ";ESuperClOverP;#",100,0,5.0 ) ; 
  fRealElectronESeedClOverPout           = new TH1D("hRealElectronESeedClOverPout",
                                                    ";ESeedClOverPout;#",90,0,3.0 ) ; 

  fRealElectronDeltaEtaSuperClTrackAtVtx = new TH1D("hRealElectronDeltaEtaSuperClTrackAtVtx",
                                                    ";DeltaEtaSuperClTrackAtVtx;#",200,0,0.02 ) ; 
  fRealElectronDeltaEtaSeedClTrackAtCalo = new TH1D("hRealElectronDeltaEtaSeedClTrackAtCalo",
                                                    ";DeltaEtaSeedClTrackAtCalo;#",200,0,0.04 ) ; 
  fRealElectronDeltaPhiSuperClTrackAtVtx = new TH1D("hRealElectronDeltaPhiSuperClTrackAtVtx",
                                                    ";DeltaPhiSuperClTrackAtVtx;#",200,0,-.1 ) ; 
  fRealElectronDeltaPhiSeedClTrackAtCalo = new TH1D("hRealElectronDeltaPhiSeedClTrackAtCalo",
                                                    ";DeltaPhiSeedClTrackAtCalo;#",200,0,0.4 ) ; 

  fRealElectronEPInv                     = new TH1D("hRealElectronEPInv",
                                                    ";RealElectronEPInv;#",100,0,0.1);
  fRealElectronCutClass                  = new TH1D("hRealElectronCutClass",
                                                    ";RealElectronCutClass;#",10,-0.5,9.5);
  fRealElectronHadronicOverEm            = new TH1D("hRealElectronHadronicOverEm",
                                                    ";HadronicOverEm;#",150,-0.00001,0.14999 ) ; 
  fRealElectronE33OverE55                = new TH1D("hRealElectronE33OverE55",
                                                    ";RealElectronE33OverE55;#",110,0,1.1);
  fRealElectronIsEnergyScaleCorrected    = new TH1D("hRealElectronIsEnergyScaleCorrected",
                                                    ";IsEnergyScaleCorrected;#",3,-1,1 ) ; 
  fRealElectronIsMomentumCorrected       = new TH1D("hRealElectronIsMomentumCorrected",
                                                    ";IsMomentumCorrected;#",3,-1,1 ) ; 
  fRealElectronNumberOfClusters          = new TH1D("hRealElectronNumberOfClusters",
                                                    ";NumberOfClusters;#",11,0,10 ) ; 
  fRealElectronClassification            = new TH1D("hRealElectronClassification",
                                                    ";Classification;#",51,0,50 ) ; 
  fRealElectronE33                       = new TH1D("hRealElectronE33",";E33;#",50,0,200 ) ; 
  fRealElectronE55                       = new TH1D("hRealElectronE55",";E55;#",50,0,200 ) ; 
  fRealElectronCovEtaEta                 = new TH1D("hRealElectronCovEtaEta",
                                                    ";CovEtaEta * 10^4;#",200,0,2.0 ) ; 
  fRealElectronCovEtaPhi                 = new TH1D("hRealElectronCovEtaPhi",
                                                    ";CovEtaPhi * 10^4;#",100,0,1.0 ) ; 
  fRealElectronCovPhiPhi                 = new TH1D("hRealElectronCovPhiPhi",
                                                    ";CovPhiPhi * 10^3;#",200,0,2.0 ) ; 
  fRealElectronLat                       = new TH1D("hRealElectronLat",";Lat;#",20,0,10 ) ; 
  fRealElectronZernike20                 = new TH1D("hRealElectronZernike20",
                                                    ";Zernike20;#",20,0,10 ) ; 
  fRealElectronZernike42                 = new TH1D("hRealElectronZernike42",
                                                    ";Zernike42;#",20,0,10 ) ; 
  fRealElectronCaloIso                   = new TH1D("hRealElectronCaloIso",
                                                    ";CaloIso;#",100,0,10 ) ; 
  fRealElectronTrackIso                  = new TH1D("hRealElectronTrackIso",
                                                    ";TrackIso;#",100,0,10 ) ; 
  fRealElectronComputedEcalIso           = new TH1D("hRealElectronComputedEcalIso",
                                                    ";ComputedEcalIso;#",100,0,10 ) ; 
  fRealElectronComputedTrackIso          = new TH1D("hRealElectronComputedTrackIso",
                                                    ";ComputedTrackIso;#",100,0,10 ) ; 
  fRealElectronTrackChi2                  = new TH1D("hRealElectronTrackChi2",
                                                    ";TrackChi2;#",100,0,100 ) ; 
  fRealElectronTrackNHits                 = new TH1D("hRealElectronTrackNHits",
                                                    ";TrackNHits;#",100,0,100 ) ; 
  fRealElectronPOutOverPIn                = new TH1D("hRealElectronPOutOverPIn",
                                                    ";POutOverPIn;#",100,0,1 ) ; 
  fRealElectronSuperClEOverTrueE          = new TH1D("hRealElectronSuperClEOverTrueE",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
  fRealElectronPOverTrueP                 = new TH1D("hRealElectronPOverTrueP",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
  fFakeElectronPtHist                    = new TH1D("hFakeElectronPtHist",";p_{t};#",100,0.,200.);
  fFakeElectronEtaHist                   = new TH1D("hFakeElectronEtaHist",";#eta;#",100,-5.,5.);
  
  fFakeElectronESuperClOverP             = new TH1D("hFakeElectronESuperClOverP",
                                                    ";ESuperClOverP;#",100,0,5.0 ) ; 
  fFakeElectronESeedClOverPout           = new TH1D("hFakeElectronESeedClOverPout",
                                                    ";ESeedClOverPout;#",90,0,3.0 ) ; 
   
  fFakeElectronDeltaEtaSuperClTrackAtVtx = new TH1D("hFakeElectronDeltaEtaSuperClTrackAtVtx",
                                                    ";DeltaEtaSuperClTrackAtVtx;#",200,0,0.02 ) ; 
  fFakeElectronDeltaEtaSeedClTrackAtCalo = new TH1D("hFakeElectronDeltaEtaSeedClTrackAtCalo",
                                                    ";DeltaEtaSeedClTrackAtCalo;#",200,0,0.04 ) ; 
  fFakeElectronDeltaPhiSuperClTrackAtVtx = new TH1D("hFakeElectronDeltaPhiSuperClTrackAtVtx",
                                                    ";DeltaPhiSuperClTrackAtVtx;#",200,0,-.1 ) ; 
  fFakeElectronDeltaPhiSeedClTrackAtCalo = new TH1D("hFakeElectronDeltaPhiSeedClTrackAtCalo",
                                                    ";DeltaPhiSeedClTrackAtCalo;#",200,0,0.4 ) ; 

  fFakeElectronEPInv                     = new TH1D("hFakeElectronEPInv",
                                                    ";FakeElectronEPInv;#",100,0,0.1);
  fFakeElectronCutClass                  = new TH1D("hFakeElectronCutClass",
                                                    ";FakeElectronCutClass;#",10,-0.5,9.5);
  fFakeElectronHadronicOverEm            = new TH1D("hFakeElectronHadronicOverEm",
                                                    ";HadronicOverEm;#",150,-0.00001,0.14999 ) ; 
  fFakeElectronE33OverE55                = new TH1D("hFakeElectronE33OverE55",
                                                    ";FakeElectronE33OverE55;#",110,0,1.1);
  fFakeElectronIsEnergyScaleCorrected    = new TH1D("hFakeElectronIsEnergyScaleCorrected",
                                                    ";IsEnergyScaleCorrected;#",3,-1,1 ) ; 
  fFakeElectronIsMomentumCorrected       = new TH1D("hFakeElectronIsMomentumCorrected",
                                                    ";IsMomentumCorrected;#",3,-1,1 ) ; 
  fFakeElectronNumberOfClusters          = new TH1D("hFakeElectronNumberOfClusters",
                                                    ";NumberOfClusters;#",11,0,10 ) ; 
  fFakeElectronClassification            = new TH1D("hFakeElectronClassification",
                                                       ";Classification;#",51,0,50 ) ; 
  fFakeElectronE33                       = new TH1D("hFakeElectronE33",";E33;#",50,0,200 ) ; 
  fFakeElectronE55                       = new TH1D("hFakeElectronE55",";E55;#",50,0,200 ) ; 
  fFakeElectronCovEtaEta                 = new TH1D("hFakeElectronCovEtaEta",
                                                    ";CovEtaEta * 10^4;#",200,0,2.0 ) ; 
  fFakeElectronCovEtaPhi                 = new TH1D("hFakeElectronCovEtaPhi",
                                                    ";CovEtaPhi * 10^4;#",100,0,1.0 ) ; 
  fFakeElectronCovPhiPhi                 = new TH1D("hFakeElectronCovPhiPhi",
                                                    ";CovPhiPhi * 10^3;#",200,0,2.0 ) ; 
  fFakeElectronLat                       = new TH1D("hFakeElectronLat",";Lat;#",20,0,10 ) ; 
  fFakeElectronZernike20                 = new TH1D("hFakeElectronZernike20",
                                                    ";Zernike20;#",20,0,10 ) ; 
  fFakeElectronZernike42                 = new TH1D("hFakeElectronZernike42",
                                                    ";Zernike42;#",20,0,10 ) ; 
  fFakeElectronCaloIso                   = new TH1D("hFakeElectronCaloIso",
                                                    ";CaloIso;#",100,0,10 ) ; 
  fFakeElectronTrackIso                  = new TH1D("hFakeElectronTrackIso",
                                                    ";TrackIso;#",100,0,10 ) ; 
  fFakeElectronComputedEcalIso           = new TH1D("hFakeElectronComputedEcalIso",
                                                    ";ComputedEcalIso;#",100,0,10 ) ; 
  fFakeElectronComputedTrackIso          = new TH1D("hFakeElectronComputedTrackIso",
                                                    ";ComputedTrackIso;#",100,0,10 ) ; 
  fFakeElectronTrackChi2                  = new TH1D("hFakeElectronTrackChi2",
                                                    ";TrackChi2;#",100,0,100 ) ; 
  fFakeElectronTrackNHits                 = new TH1D("hFakeElectronTrackNHits",
                                                    ";TrackNHits;#",100,0,100 ) ; 
  fFakeElectronPOutOverPIn                = new TH1D("hFakeElectronPOutOverPIn",
                                                    ";POutOverPIn;#",100,0,1 ) ; 
  fFakeElectronSuperClEOverTrueE          = new TH1D("hFakeElectronSuperClEOverTrueE",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
  fFakeElectronPOverTrueP                 = new TH1D("hFakeElectronPOverTrueP",
                                                    ";POutOverPIn;#",150,0,1.5 ) ; 
  fElectronSelection                     = new TH1D("hElectronSelection",
                                                    ";ElectronSelection;#",18,-1.5,16.5 ) ; 
  fRealElectronSelection                 = new TH1D("hRealElectronSelection",
                                                    ";RealElectronSelection;#",18,-1.5,16.5 ) ; 
  fFakeElectronSelection                 = new TH1D("hFakeElectronSelection",
                                                    ";FakeElectronSelection;#",18,-1.5,16.5 ) ; 
  fGoodElectronPtHist                    = new TH1D("hGoodElectronPtHist",";p_{t};#",25,0.,200.);
  fGoodElectronEtaHist                   = new TH1D("hGoodElectronEtaHist",";#eta;#",21,-5.,5.);
  fGoodElectronClassification            = new TH1D("hGoodElectronClassification",
                                                    ";Good Electron Classification;#",51,0,50 ) ; 
  


  AddOutput(fAllElectronPtHist);
  AddOutput(fAllElectronEtaHist);
  AddOutput(fAllElectronESuperClOverP);
  AddOutput(fAllElectronESeedClOverPout);
  AddOutput(fAllElectronDeltaEtaSuperClTrackAtVtx);
  AddOutput(fAllElectronDeltaEtaSeedClTrackAtCalo);
  AddOutput(fAllElectronDeltaPhiSuperClTrackAtVtx);
  AddOutput(fAllElectronDeltaPhiSeedClTrackAtCalo);
  AddOutput(fAllElectronEPInv);
  AddOutput(fAllElectronCutClass);
  AddOutput(fAllElectronHadronicOverEm);
  AddOutput(fAllElectronE33OverE55);
  AddOutput(fAllElectronIsEnergyScaleCorrected);
  AddOutput(fAllElectronIsMomentumCorrected);
  AddOutput(fAllElectronNumberOfClusters);
  AddOutput(fAllElectronClassification);
  AddOutput(fAllElectronE33);
  AddOutput(fAllElectronE55);
  AddOutput(fAllElectronCovEtaEta);
  AddOutput(fAllElectronCovEtaPhi);
  AddOutput(fAllElectronCovPhiPhi);
  AddOutput(fAllElectronLat);
  AddOutput(fAllElectronZernike20);
  AddOutput(fAllElectronZernike42);
  AddOutput(fAllElectronCaloIso);
  AddOutput(fAllElectronTrackIso);
  AddOutput(fAllElectronComputedEcalIso);
  AddOutput(fAllElectronComputedTrackIso);
  AddOutput(fAllElectronTrackChi2);
  AddOutput(fAllElectronTrackNHits);
  AddOutput(fAllElectronPOutOverPIn);
  AddOutput(fAllElectronSuperClEOverTrueE);
  AddOutput(fAllElectronPOverTrueP);

  AddOutput(fRealElectronPtHist);
  AddOutput(fRealElectronEtaHist);
  AddOutput(fRealElectronESuperClOverP);
  AddOutput(fRealElectronESeedClOverPout);
  AddOutput(fRealElectronDeltaEtaSuperClTrackAtVtx);
  AddOutput(fRealElectronDeltaEtaSeedClTrackAtCalo);
  AddOutput(fRealElectronDeltaPhiSuperClTrackAtVtx);
  AddOutput(fRealElectronDeltaPhiSeedClTrackAtCalo);
  AddOutput(fRealElectronEPInv);
  AddOutput(fRealElectronCutClass);
  AddOutput(fRealElectronHadronicOverEm);
  AddOutput(fRealElectronE33OverE55);
  AddOutput(fRealElectronIsEnergyScaleCorrected);
  AddOutput(fRealElectronIsMomentumCorrected);
  AddOutput(fRealElectronNumberOfClusters);
  AddOutput(fRealElectronClassification);
  AddOutput(fRealElectronE33);
  AddOutput(fRealElectronE55);
  AddOutput(fRealElectronCovEtaEta);
  AddOutput(fRealElectronCovEtaPhi);
  AddOutput(fRealElectronCovPhiPhi);
  AddOutput(fRealElectronLat);
  AddOutput(fRealElectronZernike20);
  AddOutput(fRealElectronZernike42);
  AddOutput(fRealElectronCaloIso);
  AddOutput(fRealElectronTrackIso);
  AddOutput(fRealElectronComputedEcalIso);
  AddOutput(fRealElectronComputedTrackIso);
  AddOutput(fRealElectronTrackChi2);
  AddOutput(fRealElectronTrackNHits);
  AddOutput(fRealElectronPOutOverPIn);
  AddOutput(fRealElectronSuperClEOverTrueE);
  AddOutput(fRealElectronPOverTrueP);

  AddOutput(fFakeElectronPtHist);
  AddOutput(fFakeElectronEtaHist);
  AddOutput(fFakeElectronESuperClOverP);
  AddOutput(fFakeElectronESeedClOverPout);
  AddOutput(fFakeElectronDeltaEtaSuperClTrackAtVtx);
  AddOutput(fFakeElectronDeltaEtaSeedClTrackAtCalo);
  AddOutput(fFakeElectronDeltaPhiSuperClTrackAtVtx);
  AddOutput(fFakeElectronDeltaPhiSeedClTrackAtCalo);
  AddOutput(fFakeElectronEPInv);
  AddOutput(fFakeElectronCutClass);
  AddOutput(fFakeElectronHadronicOverEm);
  AddOutput(fFakeElectronE33OverE55);
  AddOutput(fFakeElectronIsEnergyScaleCorrected);
  AddOutput(fFakeElectronIsMomentumCorrected);
  AddOutput(fFakeElectronNumberOfClusters);
  AddOutput(fFakeElectronClassification);
  AddOutput(fFakeElectronE33);
  AddOutput(fFakeElectronE55);
  AddOutput(fFakeElectronCovEtaEta);
  AddOutput(fFakeElectronCovEtaPhi);
  AddOutput(fFakeElectronCovPhiPhi);
  AddOutput(fFakeElectronLat);
  AddOutput(fFakeElectronZernike20);
  AddOutput(fFakeElectronZernike42);
  AddOutput(fFakeElectronCaloIso);
  AddOutput(fFakeElectronTrackIso);
  AddOutput(fFakeElectronComputedEcalIso);
  AddOutput(fFakeElectronComputedTrackIso);
  AddOutput(fFakeElectronTrackChi2);
  AddOutput(fFakeElectronTrackNHits);
  AddOutput(fFakeElectronPOutOverPIn);
  AddOutput(fFakeElectronSuperClEOverTrueE);
  AddOutput(fFakeElectronPOverTrueP);
  AddOutput(fElectronSelection);
  AddOutput(fRealElectronSelection);
  AddOutput(fFakeElectronSelection);
  AddOutput(fGoodElectronPtHist);
  AddOutput(fGoodElectronEtaHist);
  AddOutput(fGoodElectronClassification);

  //Jet Plots
  fAllJetPtHist                   = new TH1D("hAllJetPtHist",";All Jet p_{t};#",100,0.,200.);
  fAllJetEtaHist                  = new TH1D("hAllJetEtaHist",";All Jet #eta;#",160,-8.,8.);
  fAllJetPtEta2DHist              = new TH2D("hAllJetPtEta2DHist",
                                             ";All Jet p_{t} vs #eta;#",25,0,100,32,-8.,8.);  
  fAllJetMaxEInEmTowers           = new TH1D("hAllJetMaxEInEmTowers",";;#",110,-100,1000 ) ; 
  fAllJetMaxEInHadTowers          = new TH1D("hAllJetMaxEInHadTowers",";;#",100,0,1000 ) ; 
  fAllJetEnergyFractionH          = new TH1D("hAllJetEnergyFractionH",";;#",100,0,2 ) ; 
  fAllJetEnergyFractionEm         = new TH1D("hAllJetEnergyFractionEm",";;#",0,0,1 ) ; 
  fAllJetHadEnergyInHB            = new TH1D("hAllJetHadEnergyInHB",";;#",100,0,100 ) ; 
  fAllJetHadEnergyInHO            = new TH1D("hAllJetHadEnergyInHO",";;#",100,0,10 ) ; 
  fAllJetHadEnergyInHE            = new TH1D("hAllJetHadEnergyInHE",";;#",100,0,1000 ) ; 
  fAllJetHadEnergyInHF            = new TH1D("hAllJetHadEnergyInHF",";;#",100,0,2000 ) ; 
  fAllJetEmEnergyInEB             = new TH1D("hAllJetEmEnergyInEB",";;#",100,0,200 ) ; 
  fAllJetEmEnergyInEE             = new TH1D("hAllJetEmEnergyInEE",";;#",100,0,500 ) ; 
  fAllJetEmEnergyInHF             = new TH1D("hAllJetEmEnergyInHF",";;#",110,-100,1000 ) ; 
  fAllJetTowersArea               = new TH1D("hAllJetTowersArea",";;#",100,0,1 ) ; 
  fAllJetN                        = new TH1D("hAllJetN",";;#",80,0,40 ) ; 
  fAllJetN60                      = new TH1D("hAllJetN60",";;#",13,0,12 ) ; 
  fAllJetN90                      = new TH1D("hAllJetN90",";;#",31,0,30 ) ; 
  fAllJetIsFake                   = new TH1D("hAllJetIsFake",";;#",3,-0.5,1.5) ; 
  fCentralJetSelection            = new TH1D("hCentralJetSelection",
                                             ";CentralJetSelection;#",5,-1.5,3.5 ) ; 
  fGoodCentralJetPtHist           = new TH1D("hGoodCentralJetPtHist",
                                             ";Good Jet p_{t};#",100,0.,200.);  
  fGoodCentralJetEtaHist          = new TH1D("hGoodCentralJetEtaHist",
                                             ";Good Jet #eta;#",160,-8.,8.);
  fGoodCentralJetPtEta2DHist      = new TH2D("hGoodCentralJetPtEta2DHist",
                                             ";Good Jet p_{t} vs #eta;#",25,0,100,32,-8.,8.);
  fGoodCentralJetMaxEInEmTowers   = new TH1D("hGoodCentralJetMaxEInEmTowers",
                                             ";;#",110,-100,1000 ) ; 
  fGoodCentralJetMaxEInHadTowers  = new TH1D("hGoodCentralJetMaxEInHadTowers",";;#",100,0,1000 ) ; 
  fGoodCentralJetEnergyFractionH  = new TH1D("hGoodCentralJetEnergyFractionH",";;#",100,0,2 ) ; 
  fGoodCentralJetEnergyFractionEm = new TH1D("hGoodCentralJetEnergyFractionEm",
                                             ";;#",3,-0.5,1.5 ) ; 
  fGoodCentralJetHadEnergyInHB    = new TH1D("hGoodCentralJetHadEnergyInHB",";;#",100,0,100 ) ; 
  fGoodCentralJetHadEnergyInHO    = new TH1D("hGoodCentralJetHadEnergyInHO",";;#",100,0,10 ) ; 
  fGoodCentralJetHadEnergyInHE    = new TH1D("hGoodCentralJetHadEnergyInHE",";;#",100,0,1000 ) ; 
  fGoodCentralJetHadEnergyInHF    = new TH1D("hGoodCentralJetHadEnergyInHF",";;#",100,0,2000 ) ; 
  fGoodCentralJetEmEnergyInEB     = new TH1D("hGoodCentralJetEmEnergyInEB",";;#",100,0,200 ) ; 
  fGoodCentralJetEmEnergyInEE     = new TH1D("hGoodCentralJetEmEnergyInEE",";;#",100,0,500 ) ; 
  fGoodCentralJetEmEnergyInHF     = new TH1D("hGoodCentralJetEmEnergyInHF",";;#",110,-100,1000 ) ; 
  fGoodCentralJetTowersArea       = new TH1D("hGoodCentralJetTowersArea",";;#",100,0,1 ) ; 
  fGoodCentralJetN                = new TH1D("hGoodCentralJetN",";;#",80,0,40 ) ; 
  fGoodCentralJetN60              = new TH1D("hGoodCentralJetN60",";;#",13,0,12 ) ; 
  fGoodCentralJetN90              = new TH1D("hGoodCentralJetN90",";;#",31,0,30 ) ; 
  fRealJetPtHist                  = new TH1D("hRealJetPtHist",";Real Jet p_{t};#",100,0.,200.);
  fRealJetEtaHist                 = new TH1D("hRealJetEtaHist",";Real Jet #eta;#",160,-8.,8.);
  fRealJetPtEta2DHist             = new TH2D("hRealJetPtEta2DHist",
                                             ";Real Jet p_{t} vs #eta;#",25,0,100,32,-8.,8.);
  fRealJetMaxEInEmTowers          = new TH1D("hRealJetMaxEInEmTowers",";;#",110,-100,1000 ) ; 
  fRealJetMaxEInHadTowers         = new TH1D("hRealJetMaxEInHadTowers",";;#",100,0,1000 ) ; 
  fRealJetEnergyFractionH         = new TH1D("hRealJetEnergyFractionH",";;#",100,0,2 ) ; 
  fRealJetEnergyFractionEm        = new TH1D("hRealJetEnergyFractionEm",";;#",3,-0.5,1.5 ) ; 
  fRealJetHadEnergyInHB           = new TH1D("hRealJetHadEnergyInHB",";;#",100,0,100 ) ; 
  fRealJetHadEnergyInHO           = new TH1D("hRealJetHadEnergyInHO",";;#",100,0,10 ) ; 
  fRealJetHadEnergyInHE           = new TH1D("hRealJetHadEnergyInHE",";;#",100,0,1000 ) ; 
  fRealJetHadEnergyInHF           = new TH1D("hRealJetHadEnergyInHF",";;#",100,0,2000 ) ; 
  fRealJetEmEnergyInEB            = new TH1D("hRealJetEmEnergyInEB",";;#",100,0,200 ) ; 
  fRealJetEmEnergyInEE            = new TH1D("hRealJetEmEnergyInEE",";;#",100,0,500 ) ; 
  fRealJetEmEnergyInHF            = new TH1D("hRealJetEmEnergyInHF",";;#",110,-100,1000 ) ; 
  fRealJetTowersArea              = new TH1D("hRealJetTowersArea",";;#",100,0,1 ) ; 
  fRealJetN                       = new TH1D("hRealJetN",";;#",80,0,40 ) ; 
  fRealJetN60                     = new TH1D("hRealJetN60",";;#",13,0,12 ) ; 
  fRealJetN90                     = new TH1D("hRealJetN90",";;#",31,0,30 ) ; 
  fRealJetSelection               = new TH1D("hRealJetSelection",
                                             ";RealJetSelection;#",5,-1.5,3.5 ) ; 
  fFakeJetPtHist                  = new TH1D("hFakeJetPtHist",";Fake Jet p_{t};#",100,0.,200.);
  fFakeJetEtaHist                 = new TH1D("hFakeJetEtaHist",";Fake Jet #eta;#",160,-8.,8.);
  fFakeJetPtEta2DHist             = new TH2D("hFakeJetPtEta2DHist",
                                             ";Fake Jet p_{t} vs #eta;#",25,0,100,32,-8.,8.);
  fFakeJetMaxEInEmTowers          = new TH1D("hFakeJetMaxEInEmTowers",";;#",110,-100,1000 ) ; 
  fFakeJetMaxEInHadTowers         = new TH1D("hFakeJetMaxEInHadTowers",";;#",100,0,1000 ) ; 
  fFakeJetEnergyFractionH         = new TH1D("hFakeJetEnergyFractionH",";;#",100,0,2 ) ; 
  fFakeJetEnergyFractionEm        = new TH1D("hFakeJetEnergyFractionEm",";;#",3,-0.5,1.5 ) ; 
  fFakeJetHadEnergyInHB           = new TH1D("hFakeJetHadEnergyInHB",";;#",100,0,100 ) ; 
  fFakeJetHadEnergyInHO           = new TH1D("hFakeJetHadEnergyInHO",";;#",100,0,10 ) ; 
  fFakeJetHadEnergyInHE           = new TH1D("hFakeJetHadEnergyInHE",";;#",100,0,1000 ) ; 
  fFakeJetHadEnergyInHF           = new TH1D("hFakeJetHadEnergyInHF",";;#",100,0,2000 ) ; 
  fFakeJetEmEnergyInEB            = new TH1D("hFakeJetEmEnergyInEB",";;#",100,0,200 ) ; 
  fFakeJetEmEnergyInEE            = new TH1D("hFakeJetEmEnergyInEE",";;#",100,0,500 ) ; 
  fFakeJetEmEnergyInHF            = new TH1D("hFakeJetEmEnergyInHF",";;#",110,-100,1000 ) ; 
  fFakeJetTowersArea              = new TH1D("hFakeJetTowersArea",";;#",100,0,1 ) ; 
  fFakeJetN                       = new TH1D("hFakeJetN",";;#",80,0,40 ) ; 
  fFakeJetN60                     = new TH1D("hFakeJetN60",";;#",13,0,12 ) ; 
  fFakeJetN90                     = new TH1D("hFakeJetN90",";;#",31,0,30 ) ; 
  fFakeJetSelection               = new TH1D("hFakeJetSelection",
                                             ";FakeJetSelection;#",5,-1.5,3.5 ) ; 

  AddOutput(fAllJetPtHist);
  AddOutput(fAllJetEtaHist);
  AddOutput(fAllJetPtEta2DHist);
  AddOutput(fAllJetMaxEInEmTowers);
  AddOutput(fAllJetMaxEInHadTowers);
  AddOutput(fAllJetEnergyFractionH);
  AddOutput(fAllJetEnergyFractionEm);
  AddOutput(fAllJetHadEnergyInHB);
  AddOutput(fAllJetHadEnergyInHO);
  AddOutput(fAllJetHadEnergyInHE);
  AddOutput(fAllJetHadEnergyInHF);
  AddOutput(fAllJetEmEnergyInEB);
  AddOutput(fAllJetEmEnergyInEE);
  AddOutput(fAllJetEmEnergyInHF);
  AddOutput(fAllJetTowersArea);
  AddOutput(fAllJetN);
  AddOutput(fAllJetN60);
  AddOutput(fAllJetN90); 
  AddOutput(fAllJetIsFake);
  AddOutput(fCentralJetSelection);
  AddOutput(fGoodCentralJetPtHist);
  AddOutput(fGoodCentralJetEtaHist);
  AddOutput(fGoodCentralJetPtEta2DHist);
  AddOutput(fGoodCentralJetMaxEInEmTowers);
  AddOutput(fGoodCentralJetMaxEInHadTowers);
  AddOutput(fGoodCentralJetEnergyFractionH);
  AddOutput(fGoodCentralJetEnergyFractionEm);
  AddOutput(fGoodCentralJetHadEnergyInHB);
  AddOutput(fGoodCentralJetHadEnergyInHO);
  AddOutput(fGoodCentralJetHadEnergyInHE);
  AddOutput(fGoodCentralJetHadEnergyInHF);
  AddOutput(fGoodCentralJetEmEnergyInEB);
  AddOutput(fGoodCentralJetEmEnergyInEE);
  AddOutput(fGoodCentralJetEmEnergyInHF);
  AddOutput(fGoodCentralJetTowersArea);
  AddOutput(fGoodCentralJetN);
  AddOutput(fGoodCentralJetN60);
  AddOutput(fGoodCentralJetN90);
  AddOutput(fRealJetPtHist);
  AddOutput(fRealJetEtaHist);
  AddOutput(fRealJetPtEta2DHist);
  AddOutput(fRealJetMaxEInEmTowers);
  AddOutput(fRealJetMaxEInHadTowers);
  AddOutput(fRealJetEnergyFractionH);
  AddOutput(fRealJetEnergyFractionEm);
  AddOutput(fRealJetHadEnergyInHB);
  AddOutput(fRealJetHadEnergyInHO);
  AddOutput(fRealJetHadEnergyInHE);
  AddOutput(fRealJetHadEnergyInHF);
  AddOutput(fRealJetEmEnergyInEB);
  AddOutput(fRealJetEmEnergyInEE);
  AddOutput(fRealJetEmEnergyInHF);
  AddOutput(fRealJetTowersArea);
  AddOutput(fRealJetN);
  AddOutput(fRealJetN60);
  AddOutput(fRealJetN90);  
  AddOutput(fRealJetSelection);
  AddOutput(fFakeJetPtHist);
  AddOutput(fFakeJetEtaHist);
  AddOutput(fFakeJetPtEta2DHist);
  AddOutput(fFakeJetMaxEInEmTowers);
  AddOutput(fFakeJetMaxEInHadTowers);
  AddOutput(fFakeJetEnergyFractionH);
  AddOutput(fFakeJetEnergyFractionEm);
  AddOutput(fFakeJetHadEnergyInHB);
  AddOutput(fFakeJetHadEnergyInHO);
  AddOutput(fFakeJetHadEnergyInHE);
  AddOutput(fFakeJetHadEnergyInHF);
  AddOutput(fFakeJetEmEnergyInEB);
  AddOutput(fFakeJetEmEnergyInEE);
  AddOutput(fFakeJetEmEnergyInHF);
  AddOutput(fFakeJetTowersArea);
  AddOutput(fFakeJetN);
  AddOutput(fFakeJetN60);
  AddOutput(fFakeJetN90);
  AddOutput(fFakeJetSelection);
  
  //MET Plots
  fMetRawPtHist                = new TH1D("hMetRawPtHist",";p_{t};#",30,0.,300.);
  fMetRawPhiHist               = new TH1D("hMetRawPhiHist",";#phi;#",28,-3.5,3.5);
  fMetMuonCorrectedPtHist      = new TH1D("hMetMuonCorrectedPtHist",";p_{t};#",30,0.,300.);
  fMetMuonCorrectedPhiHist     = new TH1D("hMetMuonCorrectedPhiHist",";#phi;#",28,-3.5,3.5);
  AddOutput(fMetRawPtHist);
  AddOutput(fMetRawPhiHist);
  AddOutput(fMetMuonCorrectedPtHist);
  AddOutput(fMetMuonCorrectedPhiHist);

}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
