//--------------------------------------------------------------------------------------------------
// $Id: HwwEvtSelMod.h,v 1.1 2008/09/30 19:24:21 sixie Exp $
//
// HwwEvtSelMod
//
// A Module for Selecting H->WW events
// and produces some distributions.
//
//
// Authors: Si Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_HWWEVTSELMOD_H
#define MITANA_PHYSICSMOD_HWWEVTSELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class HwwEvtSelMod : public BaseMod
  {
    public:
    HwwEvtSelMod(const char *name="HwwEvtSelMod", 
		 const char *title="Example analysis module with all branches");
      ~HwwEvtSelMod() {}
      void         SetLoadGenParticles(bool b)           { fLoadGenParticles = b;         }        
      void         SetPrintDebug(bool b)                 { fPrintDebug = b;               }   
      void         SetPlotType(TString type)             { fPlotType = type;              }   
      void         SetCleanJetsName (TString s)          { fCleanJetsName = s;            }   
      void         SetJetName (TString s)                { fJetName = s;                  }   

    protected:
      bool                     fPrintDebug;
      TString                  fPlotType;              //Type of histograms to make
      TString                  fMCPartName;            //name of particle collection
      TString                  fMetName;               //name of met collection
      TString                  fTrackName;          
      TString                  fJetName;          
      TString                  fCleanJetsName; //name of clean central jets collection
      bool                     fLoadGenParticles;     //bool to determine if we want gen info
      MCParticleCol           *fParticles;            //!GenParticle branch
      MetCol                  *fMet;                  //!Missing Et
      TrackCol		      *fTracks;               //!Track branch      
      JetCol                  *fJets;                 //!Jet branch
  
      TH1D                    *fGoodMuonPtHist;       //!Muon pt histogram
      TH1D                    *fGoodMuonEtaHist;      //!Muon eta histogram
      TH1D                    *fGoodElectronPtHist;   //!Electron pt histogram
      TH1D                    *fGoodElectronEtaHist;  //!Electron eta histogram
      TH1D                    *fJetPtHist;	      //!Electron pt histogram
      TH1D                    *fJetEtaHist;           //!Electron eta histogram

      TH1D                    *fMetPtHist;	      //!Electron pt histogram
      TH1D                    *fMetPhiHist;           //!Electron phi histogram
      TH1D                    *fNCentralJets;         //!Number of Central Jets
      TH1D                    *fNForwardJets;         //!Number of Forward Jets
      TH1D                    *fNCentralJetsPlusOneTrack;
      TH1D                    *fNCentralJetsTrackSumPt;
      TH1D                    *fVBFJetPt;             //!Pt of Selected VBF Jets      
      TH1D                    *fVBFJetEta;            //!Eta of Selected VBF Jets
      TH1D                    *fDeltaEtaVBFJets;      //!Gap in Eta between the selected VBF Jets
      TH1D                    *fDeltaPhiLeptons;      //!DeltaPhi between the leptons
      TH1D                    *fDeltaEtaLeptons;      //!DeltaEta between the leptons
      TH1D                    *fDileptonMass;         //!Dilepton Mass
      TH1D                    *fLeptonPtMax;          //!Max Pt of either Lepton
      TH1D                    *fLeptonPtMin;          //!Min Pt of either Lepton
      TH1D                    *fLeptonEta;   
      TH1D                    *fLepton1Pt_afterCuts;  //!Max Pt of either Lepton
      TH1D                    *fLepton2Pt_afterCuts;  //!Min Pt of either Lepton
      TH1D                    *fMetPtAfterSelectionHist;
      TH1D                    *fMetPhiAfterSelectionHist;
      TH1D                    *fMetSignificanceAfterCuts;
      TH1D                    *fSumEtAfterCuts;
      TH1D                    *fMinDeltaPhiLeptonMet; //!Min DeltaPhi between Lepton and Met
      TH1D                    *fMtLepton1;            //!Transverse Mass of Lepton1 and Met
      TH1D                    *fMtLepton2;            //!Transverse Mass of Lepton1 and Met
      TH1D                    *fMtHiggs;
      TH1D                    *fpTTot;                //!pT total
      TH1D                    *fLeptonPtPlusMet;
      TH1D                    *fHWWSelection;
      TH1D                    *fHWWToEESelection;
      TH1D                    *fHWWToMuMuSelection;
      TH1D                    *fHWWToEMuSelection;

      int                      fNEventsProcessed;
      int                      fNEventsPassedSkim;
      int                      fNEventsPassedLeptonSelection;
      int                      fNEventsPassedKinematicPreselection;
      int                      fNEventsInsideAcceptance;

      void         Begin();
      void         Process();
      void         SlaveBegin();
      void         SlaveTerminate();
      void         Terminate();      

      ClassDef(HwwEvtSelMod,1) // TAM example analysis module
  };
}
#endif
