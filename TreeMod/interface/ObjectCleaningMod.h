//--------------------------------------------------------------------------------------------------
// $Id: FullExampleMod.h,v 1.4 2008/07/02 16:34:06 loizides Exp $
//
// ObjectCleaningMod
//
// This Module performs cleaning of objects including, removal of
// duplicate objects, applying object ID cuts, correction of MET
// The output will be collections of objects deemed as "good" and
// exported to other modules.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef TREEMOD_OBJECTCLEANINGMOD_H
#define TREEMOD_OBJECTCLEANINGMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class ObjectCleaningMod : public BaseMod
  {
    public:
      ObjectCleaningMod(const char *name="ObjectCleaningMod", 
                     const char *title="Example analysis module with all branches");
      ~ObjectCleaningMod() {}

    protected:
      TString                  fMCPartName;               //name of gen particle collection
      TString                  fTrackName;                //name of track collection
      TString                  fBarrelBasicClusterName;   //name of basic Cluster collection
      TString                  fBarrelSuperClusterName;   //name of Super Cluster collection
      TString                  fMuonName;                 //name of muon collection
      TString                  fElectronName;             //name of electron collection
      TString                  fJetName;                  //name of jet collection
      TString                  fMetName;                  //name of met collection
      string                   fGoodElectronsName ;        
      string                   fGoodMuonsName ;        
      string                   fGoodCentralJetsName;        
      string                   fGoodForwardJetsName ;        
      string                   fMuonCorrectedMetName ;        
      string                   fGenLeptonsName;
      MCParticleCol           *fParticles;                //!GenParticle branch
      TrackCol		      *fTracks;	                  //!Track branch
      BasicClusterCol         *fBarrelBasicClusters;      //!Basic Cluster branch
      SuperClusterCol         *fBarrelSuperClusters;      //!Super Cluster branch
      MuonCol		      *fMuons;                    //!Muon branch
      ElectronCol	      *fElectrons;                //!Electron branch

      MetCol                  *fMet;                      //!Missing Et
      JetCol                  *fJets;                     //!Jet branch

      TH1D                    *fGenPtHist;                //!GenParticle pt histogram
      TH1D                    *fGenEtaHist;               //!GenParticle eta histogram
      TH1D                    *fGenPhiHist;               //!GenParticle eta histogram
      TH1D                    *fGenElectronPt;
      TH1D                    *fGenElectronEta;
      TH1D                    *fGenElectronPhi;
      TH1D                    *fGenMuonPt;
      TH1D                    *fGenMuonEta;
      TH1D                    *fGenMuonPhi;
      TH1D                    *fGenTauPt;
      TH1D                    *fGenTauEta;
      TH1D                    *fGenTauPhi;

      TH1D                    *fTrackPtHist;              //!Track pt histogram
      TH1D                    *fTrackThetaHist;           //!Track theta histogram
      TH1D                    *fTrackPhiHist;             //!Track eta histogram
  
      TH1D                    *fAllMuonPtHist;            //!Muon pt histogram
      TH1D                    *fAllMuonEtaHist;           //!Muon eta histogram

      //Histograms for Muon Object ID variables   
      TH1D                    *fAllMuonChi2;
      TH1D                    *fAllMuonNHits;
      TH1D                    *fAllMuonBestTrackD0;
      TH1D                    *fAllMuonIsoR03SumPt;
      TH1D                    *fAllMuonIsoR03EmEt;      
      TH1D                    *fAllMuonIsoR03HadEt;
      TH1D                    *fAllMuonIsoR03EmAndHadEt;
      TH1D                    *fAllMuonIsoR03HoEt;
      TH1D                    *fAllMuonIsoR03NTracks;
      TH1D                    *fAllMuonIsoR03NJets;
      TH1D                    *fAllMuonIsoR05SumPt;
      TH1D                    *fAllMuonIsoR05EmEt;      
      TH1D                    *fAllMuonIsoR05HadEt;
      TH1D                    *fAllMuonIsoR05HoEt;
      TH1D                    *fAllMuonIsoR05NTracks;
      TH1D                    *fAllMuonIsoR05NJets;
      TH1D                    *fAllMuonEmEnergy;
      TH1D                    *fAllMuonHadEnergy;
      TH1D                    *fAllMuonHoEnergy;
      TH1D                    *fAllMuonEmS9Energy;
      TH1D                    *fAllMuonHadS9Energy;
      TH1D                    *fAllMuonHoS9Energy;
      //Histrograms for Muon Object ID variables for matched real muons
      TH1D                    *fRealMuonPtHist;           //!Muon pt histogram
      TH1D                    *fRealMuonEtaHist;          //!Muon eta histogram     
      TH1D                    *fRealMuonChi2;
      TH1D                    *fRealMuonNHits;
      TH1D                    *fRealMuonBestTrackD0;
      TH1D                    *fRealMuonIsoR03SumPt;
      TH1D                    *fRealMuonIsoR03EmEt;      
      TH1D                    *fRealMuonIsoR03HadEt;
      TH1D                    *fRealMuonIsoR03EmAndHadEt;
      TH1D                    *fRealMuonIsoR03HoEt;
      TH1D                    *fRealMuonIsoR03NTracks;
      TH1D                    *fRealMuonIsoR03NJets;
      TH1D                    *fRealMuonIsoR05SumPt;
      TH1D                    *fRealMuonIsoR05EmEt;      
      TH1D                    *fRealMuonIsoR05HadEt;
      TH1D                    *fRealMuonIsoR05HoEt;
      TH1D                    *fRealMuonIsoR05NTracks;
      TH1D                    *fRealMuonIsoR05NJets;
      TH1D                    *fRealMuonEmEnergy;
      TH1D                    *fRealMuonHadEnergy;
      TH1D                    *fRealMuonHoEnergy;
      TH1D                    *fRealMuonEmS9Energy;
      TH1D                    *fRealMuonHadS9Energy;
      TH1D                    *fRealMuonHoS9Energy;
      //Histrograms for Muon Object ID variables for matched fake muons
      TH1D                    *fFakeMuonPtHist;           //!Muon pt histogram
      TH1D                    *fFakeMuonEtaHist;          //!Muon eta histogram      
      TH1D                    *fFakeMuonChi2;
      TH1D                    *fFakeMuonNHits;
      TH1D                    *fFakeMuonBestTrackD0;
      TH1D                    *fFakeMuonIsoR03SumPt;
      TH1D                    *fFakeMuonIsoR03EmEt;      
      TH1D                    *fFakeMuonIsoR03HadEt;
      TH1D                    *fFakeMuonIsoR03EmAndHadEt;
      TH1D                    *fFakeMuonIsoR03HoEt;
      TH1D                    *fFakeMuonIsoR03NTracks;
      TH1D                    *fFakeMuonIsoR03NJets;
      TH1D                    *fFakeMuonIsoR05SumPt;
      TH1D                    *fFakeMuonIsoR05EmEt;      
      TH1D                    *fFakeMuonIsoR05HadEt;
      TH1D                    *fFakeMuonIsoR05HoEt;
      TH1D                    *fFakeMuonIsoR05NTracks;
      TH1D                    *fFakeMuonIsoR05NJets;
      TH1D                    *fFakeMuonEmEnergy;
      TH1D                    *fFakeMuonHadEnergy;
      TH1D                    *fFakeMuonHoEnergy;
      TH1D                    *fFakeMuonEmS9Energy;
      TH1D                    *fFakeMuonHadS9Energy;
      TH1D                    *fFakeMuonHoS9Energy;
      //Histrograms for Good Muons
      TH1D                    *fGoodMuonPtHist;           //!Muon pt histogram
      TH1D                    *fGoodMuonEtaHist;          //!Muon eta histogram
      TH1D                    *fMuonSelection;
      TH1D                    *fRealMuonSelection;
      TH1D                    *fFakeMuonSelection;

      //Electrons
      TH1D                    *fAllElectronPtHist;        //!Electron pt histogram
      TH1D                    *fAllElectronEtaHist;       //!Electron eta histogram      
      //Histograms for Muon Object ID variables   
      TH1D                    *fAllElectronESuperClOverP;
      TH1D                    *fAllElectronESeedClOverPout;
      TH1D                    *fAllElectronDeltaEtaSuperClTrackAtVtx;
      TH1D                    *fAllElectronDeltaEtaSeedClTrackAtCalo;
      TH1D                    *fAllElectronDeltaPhiSuperClTrackAtVtx;
      TH1D                    *fAllElectronDeltaPhiSeedClTrackAtCalo;
      TH1D                    *fAllElectronEPInv;
      TH1D                    *fAllElectronCutClass;
      TH1D                    *fAllElectronHadronicOverEm;
      TH1D                    *fAllElectronE33OverE55;
      TH1D                    *fAllElectronIsEnergyScaleCorrected;
      TH1D                    *fAllElectronIsMomentumCorrected;
      TH1D                    *fAllElectronNumberOfClusters;
      TH1D                    *fAllElectronClassification;
      TH1D                    *fAllElectronE33;
      TH1D                    *fAllElectronE55;
      TH1D                    *fAllElectronCovEtaEta;
      TH1D                    *fAllElectronCovEtaPhi;
      TH1D                    *fAllElectronCovPhiPhi;
      TH1D                    *fAllElectronLat;
      TH1D                    *fAllElectronZernike20;
      TH1D                    *fAllElectronZernike42;
      TH1D                    *fAllElectronCaloIso;
      TH1D                    *fAllElectronTrackIso;
      TH1D                    *fAllElectronComputedEcalIso;
      TH1D                    *fAllElectronComputedTrackIso;
      TH1D                    *fAllElectronTrackChi2;
      TH1D                    *fAllElectronTrackNHits;
      TH1D                    *fAllElectronPOutOverPIn;
      TH1D                    *fAllElectronSuperClEOverTrueE;
      TH1D                    *fAllElectronPOverTrueP;
     
      //Histrograms for Electron Object ID variables for matched real electrons
      TH1D                    *fRealElectronPtHist;
      TH1D                    *fRealElectronEtaHist;
      TH1D                    *fRealElectronESuperClOverP;
      TH1D                    *fRealElectronESeedClOverPout;
      TH1D                    *fRealElectronDeltaEtaSuperClTrackAtVtx;
      TH1D                    *fRealElectronDeltaEtaSeedClTrackAtCalo;
      TH1D                    *fRealElectronDeltaPhiSuperClTrackAtVtx;
      TH1D                    *fRealElectronDeltaPhiSeedClTrackAtCalo;
      TH1D                    *fRealElectronEPInv;
      TH1D                    *fRealElectronCutClass;
      TH1D                    *fRealElectronHadronicOverEm;
      TH1D                    *fRealElectronE33OverE55;
      TH1D                    *fRealElectronIsEnergyScaleCorrected;
      TH1D                    *fRealElectronIsMomentumCorrected;
      TH1D                    *fRealElectronNumberOfClusters;
      TH1D                    *fRealElectronClassification;
      TH1D                    *fRealElectronE33;
      TH1D                    *fRealElectronE55;
      TH1D                    *fRealElectronCovEtaEta;
      TH1D                    *fRealElectronCovEtaPhi;
      TH1D                    *fRealElectronCovPhiPhi;
      TH1D                    *fRealElectronLat;
      TH1D                    *fRealElectronZernike20;
      TH1D                    *fRealElectronZernike42;
      TH1D                    *fRealElectronCaloIso;
      TH1D                    *fRealElectronTrackIso;
      TH1D                    *fRealElectronComputedEcalIso;
      TH1D                    *fRealElectronComputedTrackIso;
      TH1D                    *fRealElectronTrackChi2;
      TH1D                    *fRealElectronTrackNHits;
      TH1D                    *fRealElectronPOutOverPIn;
      TH1D                    *fRealElectronSuperClEOverTrueE;
      TH1D                    *fRealElectronPOverTrueP;
      //Histrograms for Electron Object ID variables for matched fake electrons
      TH1D                    *fFakeElectronPtHist;
      TH1D                    *fFakeElectronEtaHist;
      TH1D                    *fFakeElectronESuperClOverP;
      TH1D                    *fFakeElectronESeedClOverPout;
      TH1D                    *fFakeElectronDeltaEtaSuperClTrackAtVtx;
      TH1D                    *fFakeElectronDeltaEtaSeedClTrackAtCalo;
      TH1D                    *fFakeElectronDeltaPhiSuperClTrackAtVtx;
      TH1D                    *fFakeElectronDeltaPhiSeedClTrackAtCalo;
      TH1D                    *fFakeElectronEPInv;
      TH1D                    *fFakeElectronCutClass;
      TH1D                    *fFakeElectronHadronicOverEm;
      TH1D                    *fFakeElectronE33OverE55;
      TH1D                    *fFakeElectronIsEnergyScaleCorrected;
      TH1D                    *fFakeElectronIsMomentumCorrected;
      TH1D                    *fFakeElectronNumberOfClusters;
      TH1D                    *fFakeElectronClassification;
      TH1D                    *fFakeElectronE33;
      TH1D                    *fFakeElectronE55;
      TH1D                    *fFakeElectronCovEtaEta;
      TH1D                    *fFakeElectronCovEtaPhi;
      TH1D                    *fFakeElectronCovPhiPhi;
      TH1D                    *fFakeElectronLat;
      TH1D                    *fFakeElectronZernike20;
      TH1D                    *fFakeElectronZernike42;
      TH1D                    *fFakeElectronCaloIso;
      TH1D                    *fFakeElectronTrackIso;
      TH1D                    *fFakeElectronComputedEcalIso;
      TH1D                    *fFakeElectronComputedTrackIso;
      TH1D                    *fFakeElectronTrackChi2;
      TH1D                    *fFakeElectronTrackNHits;
      TH1D                    *fFakeElectronPOutOverPIn;
      TH1D                    *fFakeElectronSuperClEOverTrueE;
      TH1D                    *fFakeElectronPOverTrueP;

      TH1D                    *fElectronSelection;
      TH1D                    *fRealElectronSelection;
      TH1D                    *fFakeElectronSelection;
      //Histrograms for Good Electrons
      TH1D                    *fGoodElectronPtHist;	       //!Electron pt histogram
      TH1D                    *fGoodElectronEtaHist;           //!Electron eta histogram
      TH1D                    *fGoodElectronClassification;

      //Jets
      //Jet Object ID histograms
      TH1D                    *fAllJetPtHist;	               //!Electron pt histogram
      TH1D                    *fAllJetEtaHist;                 //!Electron eta histogramAll
      TH2D                    *fAllJetPtEta2DHist;
      TH1D                    *fAllJetMaxEInEmTowers;
      TH1D                    *fAllJetMaxEInHadTowers;
      TH1D                    *fAllJetEnergyFractionH;
      TH1D                    *fAllJetEnergyFractionEm;
      TH1D                    *fAllJetHadEnergyInHB;
      TH1D                    *fAllJetHadEnergyInHO;
      TH1D                    *fAllJetHadEnergyInHE;
      TH1D                    *fAllJetHadEnergyInHF;
      TH1D                    *fAllJetEmEnergyInEB;
      TH1D                    *fAllJetEmEnergyInEE;
      TH1D                    *fAllJetEmEnergyInHF;
      TH1D                    *fAllJetTowersArea;
      TH1D                    *fAllJetN;
      TH1D                    *fAllJetN60;
      TH1D                    *fAllJetN90;
      TH1D                    *fAllJetIsFake;
      TH1D                    *fCentralJetSelection;
      //Jet Object ID histograms for Good Jets
      TH1D                    *fGoodCentralJetPtHist;	       //!Electron pt histogram
      TH1D                    *fGoodCentralJetEtaHist;         //!Electron eta histogram      
      TH2D                    *fGoodCentralJetPtEta2DHist;	   
      TH1D                    *fGoodCentralJetMaxEInEmTowers;
      TH1D                    *fGoodCentralJetMaxEInHadTowers;
      TH1D                    *fGoodCentralJetEnergyFractionH;
      TH1D                    *fGoodCentralJetEnergyFractionEm;
      TH1D                    *fGoodCentralJetHadEnergyInHB;
      TH1D                    *fGoodCentralJetHadEnergyInHO;
      TH1D                    *fGoodCentralJetHadEnergyInHE;
      TH1D                    *fGoodCentralJetHadEnergyInHF;
      TH1D                    *fGoodCentralJetEmEnergyInEB;
      TH1D                    *fGoodCentralJetEmEnergyInEE;
      TH1D                    *fGoodCentralJetEmEnergyInHF;
      TH1D                    *fGoodCentralJetTowersArea;
      TH1D                    *fGoodCentralJetN;
      TH1D                    *fGoodCentralJetN60;
      TH1D                    *fGoodCentralJetN90;
      //Jet Object ID histograms for matched fake Jets
      TH1D                    *fFakeJetPtHist;	               //!Electron pt histogram
      TH1D                    *fFakeJetEtaHist;                //!Electron eta histogram      
      TH2D                    *fFakeJetPtEta2DHist;
      TH1D                    *fFakeJetMaxEInEmTowers;
      TH1D                    *fFakeJetMaxEInHadTowers;
      TH1D                    *fFakeJetEnergyFractionH;
      TH1D                    *fFakeJetEnergyFractionEm;
      TH1D                    *fFakeJetHadEnergyInHB;
      TH1D                    *fFakeJetHadEnergyInHO;
      TH1D                    *fFakeJetHadEnergyInHE;
      TH1D                    *fFakeJetHadEnergyInHF;
      TH1D                    *fFakeJetEmEnergyInEB;
      TH1D                    *fFakeJetEmEnergyInEE;
      TH1D                    *fFakeJetEmEnergyInHF;
      TH1D                    *fFakeJetTowersArea;
      TH1D                    *fFakeJetN;
      TH1D                    *fFakeJetN60;
      TH1D                    *fFakeJetN90;
      TH1D                    *fFakeJetSelection;
      //Jet Object ID histograms for matched real Jets
      TH1D                    *fRealJetPtHist;	               //!Electron pt histogram
      TH1D                    *fRealJetEtaHist;                //!Electron eta histogram      
      TH2D                    *fRealJetPtEta2DHist;
      TH1D                    *fRealJetMaxEInEmTowers;
      TH1D                    *fRealJetMaxEInHadTowers;
      TH1D                    *fRealJetEnergyFractionH;
      TH1D                    *fRealJetEnergyFractionEm;
      TH1D                    *fRealJetHadEnergyInHB;
      TH1D                    *fRealJetHadEnergyInHO;
      TH1D                    *fRealJetHadEnergyInHE;
      TH1D                    *fRealJetHadEnergyInHF;
      TH1D                    *fRealJetEmEnergyInEB;
      TH1D                    *fRealJetEmEnergyInEE;
      TH1D                    *fRealJetEmEnergyInHF;
      TH1D                    *fRealJetTowersArea;
      TH1D                    *fRealJetN;
      TH1D                    *fRealJetN60;
      TH1D                    *fRealJetN90;
      TH1D                    *fRealJetSelection;

      //MET Histograms
      TH1D                    *fMetRawPtHist;	               //!Electron pt histogram
      TH1D                    *fMetRawPhiHist;                 //!Electron phi histogram
      TH1D                    *fMetMuonCorrectedPtHist;	       //!Electron pt histogram
      TH1D                    *fMetMuonCorrectedPhiHist;       //!Electron phi histogram
      int                      fNEventsProcessed;              // Number of events processed

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      ClassDef(ObjectCleaningMod,1) // TAM example analysis module
  };
}
#endif
