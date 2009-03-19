//--------------------------------------------------------------------------------------------------
// $Id: PFTau.h,v 1.2 2009/03/12 15:55:38 bendavid Exp $
//
// PFTau
//
// This class holds information about reconstructed tau based on PF Cands
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PFTAU_H
#define MITANA_DATATREE_PFTAU_H
 
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PFCandidate.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/PFJet.h"

namespace mithep 
{
  class PFTau : public Tau
  {
    public:
      PFTau() :   fLeadPFCandSignedD0Significance(0), fHCalTotalEOverP(0), fHCalMaxEOverP(0),
                  fHCal3x3EOverP(0), fIsoChargedHadronPtSum(0), fIsoGammaEtSum(0),
                  fMaxHCalPFClusterEt(0), fEMFraction(0), fECalStripSumEOverP(0),
                  fBremRecoveryEOverP(0), fElectronPreIDOutput(0), fElectronPreIDDecision(kFALSE),
                  fCaloCompatibility(0), fSegmentCompatibility(0), fMuonDecision(kFALSE) {}
                  
      PFTau(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Tau(px,py,pz,e),
                  fLeadPFCandSignedD0Significance(0), fHCalTotalEOverP(0), fHCalMaxEOverP(0),
                  fHCal3x3EOverP(0), fIsoChargedHadronPtSum(0), fIsoGammaEtSum(0),
                  fMaxHCalPFClusterEt(0), fEMFraction(0), fECalStripSumEOverP(0),
                  fBremRecoveryEOverP(0), fElectronPreIDOutput(0), fElectronPreIDDecision(kFALSE),
                  fCaloCompatibility(0), fSegmentCompatibility(0), fMuonDecision(kFALSE) {}

      void                AddIsoPFCand(const PFCandidate *p)       { fIsoPFCands.Add(p);                 }
      void                AddSignalPFCand(const PFCandidate *p)    { fSignalPFCands.Add(p);              }
      void                SetPFJet(const PFJet *j)                 { fPFJet = j;                         }
      void                SetLeadPFCand(const PFCandidate *p)      { fLeadPFCand = p;                    }   
      void                SetLeadChargedHadronPFCand(const PFCandidate *p) { fLeadChargedHadronPFCand = p; }
      void                SetLeadNeutralPFCand(const PFCandidate *p) { fLeadNeutralPFCand = p;           }
      void                SetElectronTrack(const Track *t)         { fElectronTrack = t;                 }
                   
      const PFCandidate  *LeadPFCand()                       const { return fLeadPFCand.Obj();           }
      const PFCandidate  *LeadChargedHadronPFCand()          const { return fLeadChargedHadronPFCand.Obj(); }
      const PFCandidate  *LeadNeutralHadronPFCand()          const { return fLeadChargedHadronPFCand.Obj(); }
      const Track        *ElectronTrack()                    const { return fElectronTrack.Obj();        }
      const PFJet        *SourcePFJet()                      const { return fPFJet.Obj();                }
      const Jet          *SourceJet()                        const { return SourcePFJet();               }
 
      UInt_t              NIsoPFCandS()                      const { return fIsoPFCands.GetEntries();    }
      UInt_t              NSignalPFCands()                   const { return fSignalPFCands.GetEntries(); }
      const PFCandidate  *SignalPFCand(UInt_t i)             const { return fSignalPFCands.At(i);        }
      const PFCandidate  *IsoPFCand(UInt_t i)                const { return fIsoPFCands.At(i);           }
                       
      EObjType            ObjType()                          const { return kPFTau;                      }  
      

      Double_t            LeadPFCandSignedD0Significance()   const { return fLeadPFCandSignedD0Significance; }
      Double_t            HCalTotalEOverP()                  const { return fHCalTotalEOverP; }
      Double_t            HCalMaxEOverP()                    const { return fHCalMaxEOverP; }
      Double_t            HCal3x3EOverP()                    const { return fHCal3x3EOverP; }
      Double_t            IsoChargedHadronPtSum()            const { return fIsoChargedHadronPtSum; }
      Double_t            IsoGammaEtSum()                    const { return fIsoGammaEtSum; }
      Double_t            MaxHCalPFClusterEt()               const { return fMaxHCalPFClusterEt; }
      Double_t            EMFraction()                       const { return fEMFraction; }
      Double_t            ECalStripSumEOverP()               const { return fECalStripSumEOverP; }
      Double_t            BremRecoveryEOverP()               const { return fBremRecoveryEOverP; }
      Double_t            ElectronPreIDOutput()              const { return fElectronPreIDOutput; }
      Double_t            CaloCompatibility()                const { return fCaloCompatibility; }
      Double_t            SegmentCompatibility()             const { return fSegmentCompatibility; }
      Bool_t              ElectronPreIDDecision()            const { return fElectronPreIDDecision; }
      Bool_t              MuonDecision()                     const { return fMuonDecision; }
      
      void                SetLeadPFCandSignedD0Significance(Double_t x)   { fLeadPFCandSignedD0Significance = x; }
      void                SetHCalTotalEOverP(Double_t x)                  { fHCalTotalEOverP = x; }
      void                SetHCalMaxEOverP(Double_t x)                    { fHCalMaxEOverP = x; }
      void                SetHCal3x3EOverP(Double_t x)                    { fHCal3x3EOverP = x; }
      void                SetIsoChargedHadronPtSum(Double_t x)            { fIsoChargedHadronPtSum = x; }
      void                SetIsoGammaEtSum(Double_t x)                    { fIsoGammaEtSum = x; }
      void                SetMaxHCalPFClusterEt(Double_t x)               { fMaxHCalPFClusterEt = x; }
      void                SetEMFraction(Double_t x)                       { fEMFraction = x; }
      void                SetECalStripSumEOverP(Double_t x)               { fECalStripSumEOverP = x; }
      void                SetBremRecoveryEOverP(Double_t x)               { fBremRecoveryEOverP = x; }
      void                SetElectronPreIDOutput(Double_t x)              { fElectronPreIDOutput = x; }
      void                SetCaloCompatibility(Double_t x)                { fCaloCompatibility = x; }
      void                SetSegmentCompatibility(Double_t x)             { fSegmentCompatibility = x; }
      void                SetElectronPreIDDecision(Bool_t b)              { fElectronPreIDDecision = b; }
      void                SetMuonDecision(Bool_t b)                       { fMuonDecision = b; }

    protected:

      Double32_t              fLeadPFCandSignedD0Significance;  //signed lead track D0 significance
      Double32_t              fHCalTotalEOverP; //total hcal Energy / lead charged hadron pf candidate P
      Double32_t              fHCalMaxEOverP; //max hcal cluster Energy / lead charged hadron pf candidate P
      Double32_t              fHCal3x3EOverP; //sum hcal cluster Energy in 3x3 tower region / lead charged hadron pf candidate P
      Double32_t              fIsoChargedHadronPtSum;  //sum pt of selected charged hadron PFCands in isolation annulus
      Double32_t              fIsoGammaEtSum;      //sum et of selected photon PFCands in isolation annulus
      Double32_t              fMaxHCalPFClusterEt; //Et of largest Et HCal PFCluster
      Double32_t              fEMFraction;        //EM energy fraction
      Double32_t              fECalStripSumEOverP; //simple brem recovery E / lead charged hadron P
      Double32_t              fBremRecoveryEOverP; //brem recovery E / lead charged hadron P
      Double32_t              fElectronPreIDOutput; //pf electron pre id bdt output for this to be an electron
      Bool_t                  fElectronPreIDDecision; //pf electron pre id decision
      Double32_t              fCaloCompatibility;  //calo compatibility for this tau to be a muon
      Double32_t              fSegmentCompatibility; //segment compatibility for this tau to be a muon
      Bool_t                  fMuonDecision;        //pf muon id decision
      Ref<PFCandidate>        fLeadPFCand;        //leading signal pf candidate (could be charged or neutral)
      Ref<PFCandidate>        fLeadChargedHadronPFCand; //leading charged hadron signal pf candidate
      Ref<PFCandidate>        fLeadNeutralPFCand; //leading neutral signal pf candidate
      Ref<PFJet>              fPFJet;           //original reconstructed pf jet
      Ref<Track>              fElectronTrack;   //track corresponding to possible matching electron candidate
      RefArray<PFCandidate>   fSignalPFCands; //selected pf candidates in signal cone
      RefArray<PFCandidate>   fIsoPFCands;         //selected pf candidates in isolation annulus

    ClassDef(PFTau, 1) // PFTau class
  };
}
#endif
