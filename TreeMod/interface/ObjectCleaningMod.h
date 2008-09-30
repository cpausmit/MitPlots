//--------------------------------------------------------------------------------------------------
// $Id: ObjectCleaningMod.h,v 1.4 2008/09/10 03:33:28 loizides Exp $
//
// ObjectCleaningMod
//
// This Module performs cleaning of objects including, removal of
// duplicate objects, removal of good muons from the good electrons,
// removal of good isolated electrons from good jets
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_OBJECTCLEANINGMOD_H
#define MITANA_TREEMOD_OBJECTCLEANINGMOD_H

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

      void         SetPrintDebug(bool b)   { fPrintDebug = b;     }   

    protected:
      bool                     fPrintDebug;      
      TString                  fMCPartName;               //name of gen particle collection
      TString                  fMuonName;                 //name of muon collection
      TString                  fElectronName;             //name of electron collection
      TString                  fJetName;                  //name of jet collection
      TString                  fSCJetName;                //name of siscone jet collection
      TString                  fMetName;                  //name of met collection
      TString                  fGoodElectronsName ;        
      TString                  fGoodMuonsName ;        
      TString                  fGoodCentralJetsName;        
      TString                  fGoodForwardJetsName ;   
      TString                  fGoodCentralSCJetsName;        
      TString                  fGoodForwardSCJetsName ;  
      TString                  fMuonCorrectedMetName ;      
      TString                  fGoodMetName ;      
      TString                  fGenLeptonsName;
      MCParticleCol           *fParticles;                //!GenParticle branch
      MuonCol		      *fMuons;                    //!Muon branch
      ElectronCol	      *fElectrons;                //!Electron branch
      MetCol                  *fMet;                      //!Missing Et
      JetCol                  *fJets;                     //!IC5 Jet branch
      JetCol                  *fSCJets;                   //!SC5 Jet branch

      //Histrograms for Muons
      TH1D                    *fAllMuonPtHist;            //!Muon pt histogram
      TH1D                    *fAllMuonEtaHist;           //!Muon eta histogram
      TH1D                    *fGoodMuonPtHist;           //!Muon pt histogram
      TH1D                    *fGoodMuonEtaHist;          //!Muon eta histogram
      TH1D                    *fMuonSelection;

      //Histrograms for Electrons
      TH1D                    *fAllElectronPtHist;        //!Electron pt histogram
      TH1D                    *fAllElectronEtaHist;       //!Electron eta histogram      
      TH1D                    *fElectronSelection;
      TH1D                    *fGoodElectronPtHist;	      
      TH1D                    *fGoodElectronEtaHist;      
      TH1D                    *fGoodElectronClassification;

      //Jet Object ID histograms
      TH1D                    *fCentralJetSelection;
      TH1D                    *fAllJetPtHist;	               
      TH1D                    *fAllJetEtaHist;                 
      TH1D                    *fGoodCentralJetPtHist;	       
      TH1D                    *fGoodCentralJetEtaHist;         

      //MET Histograms
      TH1D                    *fMetPtHist;	               
      TH1D                    *fMetPhiHist;                 

      int                      fNEventsProcessed;              // Number of events processed

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();
      void               SetGoodElectronsName(TString s) { fGoodElectronsName = s; }        
      void               SetGoodMuonsName(TString s)     { fGoodMuonsName = s; }        
      void               SetGoodCentralJetsName(TString s) { fGoodCentralJetsName = s; } 
      void               SetGoodForwardJetsName(TString s) { fGoodForwardJetsName = s; }  
      void               SetMuonCorrectedMetName(TString s) { fMuonCorrectedMetName = s; }        
    
      ClassDef(ObjectCleaningMod,1) // TAM example analysis module
  };
}
#endif
