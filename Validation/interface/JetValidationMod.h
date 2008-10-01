//--------------------------------------------------------------------------------------------------
// $Id:  $
//
// JetValidationMod
//
// This Module makes histograms for various Jet related quantities including
// Pt, Eta, JetResponse, Number of Reconstructed Jets for efficiency studies
// ...etc
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_VALIDATION_JETVALIDATIONMOD_H
#define MITANA_VALIDATION_JETVALIDATIONMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;
class TH3D;

namespace mithep 
{
  class JetValidationMod : public BaseMod
  {
    public:
      JetValidationMod(const char *name="JetValidationMod", 
                     const char *title="Example analysis module with all branches");
      ~JetValidationMod() {}

    protected:
      bool                     fPrintDebug;
      TString                  fIC5GenJetName;      
      TString                  fSC5GenJetName;      
      TString                  fIC5JetName;         
      TString                  fSC5JetName;         

      JetCol                  *fIC5Jets;              //!Jet branch
      JetCol                  *fSC5Jets;              //!Jet branch
      GenJetCol               *fIC5GenJets;           //!GenJet branch
      GenJetCol               *fSC5GenJets;           //!GenJet branch

      TH1D                    *fIC5GenJetRecoJetDeltaR;
      TH1D                    *fIC5GenJetRecoJetDeltaEta;
      TH1D                    *fIC5GenJetRecoJetDeltaPhi;
      TH2D                    *fIC5JetResponseVsGenJetPtInBarrel;
      TH2D                    *fIC5JetResponseVsGenJetPtInEndcap;
      TH2D                    *fIC5JetResponseVsGenJetPtForward;
      TH2D                    *fIC5JetResponseVsCaloJetEta;
      TH1D                    *fIC5CentralGenJetRecoJetDeltaR;
      TH1D                    *fIC5ForwardGenJetRecoJetDeltaR;
      TH1D                    *fIC5NMatchedCaloJetsVsGenJetPt;
      TH1D                    *fIC5NMatchedCaloJetsVsGenJetEta;
      TH1D                    *fIC5NMatchedCaloJetsVsGenJetEta_Pt20To30;
      TH1D                    *fIC5NMatchedCaloJetsVsGenJetEta_Pt30To40;
      TH1D                    *fIC5NMatchedCaloJetsVsGenJetEta_Pt60To80;
      TH1D                    *fIC5NGenJetsVsGenJetPt;
      TH1D                    *fIC5NGenJetsVsGenJetEta;
      TH1D                    *fIC5NGenJetsVsGenJetEta_Pt20To30;
      TH1D                    *fIC5NGenJetsVsGenJetEta_Pt30To40;
      TH1D                    *fIC5NGenJetsVsGenJetEta_Pt60To80;
      TH1D                    *fIC5CaloJetsPt;
      TH1D                    *fIC5CaloJetsEta;
      TH1D                    *fIC5NUnmatchedCaloJetsVsCorrectedCaloJetPt;
      TH1D                    *fIC5NUnmatchedCalojetsVsCorrectedCaloJetEta;
      TH2D                    *fIC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt;
      TH1D                    *fIC5NCaloJets;
      TH1D                    *fSC5GenJetRecoJetDeltaR;
      TH1D                    *fSC5GenJetRecoJetDeltaEta;
      TH1D                    *fSC5GenJetRecoJetDeltaPhi;
      TH2D                    *fSC5JetResponseVsGenJetPtInBarrel;
      TH2D                    *fSC5JetResponseVsGenJetPtInEndcap;
      TH2D                    *fSC5JetResponseVsGenJetPtForward;
      TH2D                    *fSC5JetResponseVsCaloJetEta;
      TH1D                    *fSC5CentralGenJetRecoJetDeltaR;
      TH1D                    *fSC5ForwardGenJetRecoJetDeltaR;
      TH1D                    *fSC5NMatchedCaloJetsVsGenJetPt;
      TH1D                    *fSC5NMatchedCaloJetsVsGenJetEta;
      TH1D                    *fSC5NMatchedCaloJetsVsGenJetEta_Pt20To30;
      TH1D                    *fSC5NMatchedCaloJetsVsGenJetEta_Pt30To40;
      TH1D                    *fSC5NMatchedCaloJetsVsGenJetEta_Pt60To80;
      TH1D                    *fSC5NGenJetsVsGenJetPt;
      TH1D                    *fSC5NGenJetsVsGenJetEta;
      TH1D                    *fSC5CaloJetsPt;
      TH1D                    *fSC5CaloJetsEta;
      TH1D                    *fSC5NGenJetsVsGenJetEta_Pt20To30;
      TH1D                    *fSC5NGenJetsVsGenJetEta_Pt30To40;
      TH1D                    *fSC5NGenJetsVsGenJetEta_Pt60To80;
      TH1D                    *fSC5NUnmatchedCaloJetsVsCorrectedCaloJetPt;
      TH1D                    *fSC5NUnmatchedCalojetsVsCorrectedCaloJetEta;
      TH2D                    *fSC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt;
      TH1D                    *fSC5NCaloJets;

      int                      fNEventsProcessed;

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();      

      ClassDef(JetValidationMod,1) // TAM example analysis module
  };
}
#endif
