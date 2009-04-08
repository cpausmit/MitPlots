//--------------------------------------------------------------------------------------------------
// $Id: PFTau.h,v 1.3 2009/03/22 19:55:45 loizides Exp $
//
// PFTau
//
// This class holds information about reconstructed tau based on PFCandidates.
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
      PFTau() :   fLeadPFCandSignD0Sig(0), fHCalTotalEOverP(0), fHCalMaxEOverP(0),
                  fHCal3x3EOverP(0), fIsoChargedHadronPtSum(0), fIsoGammaEtSum(0),
                  fMaxHCalPFClusterEt(0), fEMFraction(0), fECalStripSumEOverP(0),
                  fBremRecoveryEOverP(0), fElectronPreIDOutput(0), fCaloCompatibility(0), 
                  fSegmentCompatibility(0), fElectronPreIDDecision(kFALSE), 
                  fMuonDecision(kFALSE) {}
                  
      PFTau(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Tau(px,py,pz,e),
                  fLeadPFCandSignD0Sig(0), fHCalTotalEOverP(0), fHCalMaxEOverP(0),
                  fHCal3x3EOverP(0), fIsoChargedHadronPtSum(0), fIsoGammaEtSum(0),
                  fMaxHCalPFClusterEt(0), fEMFraction(0), fECalStripSumEOverP(0),
                  fBremRecoveryEOverP(0), fElectronPreIDOutput(0), fCaloCompatibility(0), 
                  fSegmentCompatibility(0), fElectronPreIDDecision(kFALSE),
                  fMuonDecision(kFALSE) {}

      void               AddIsoPFCand(const PFCandidate *p)  { fIsoPFCands.Add(p);                 }
      void               AddSignalPFCand(const PFCandidate *p)      
                            { ClearCharge(); fSignalPFCands.Add(p); }
      Double_t           BremRecoveryEOverP()          const { return fBremRecoveryEOverP;         }
      Double_t           CaloCompatibility()           const { return fCaloCompatibility;          }
      Double_t           ECalStripSumEOverP()          const { return fECalStripSumEOverP;         }
      Double_t           EMFraction()                  const { return fEMFraction;                 }
      const Track       *ElectronTrack()               const { return fElectronTrack.Obj();        }
      Bool_t             ElectronPreIDDecision()       const { return fElectronPreIDDecision;      }
      Double_t           ElectronPreIDOutput()         const { return fElectronPreIDOutput;        }
      Double_t           HCal3x3EOverP()               const { return fHCal3x3EOverP;              }
      Double_t           HCalMaxEOverP()               const { return fHCalMaxEOverP;              }
      Double_t           HCalTotalEOverP()             const { return fHCalTotalEOverP;            }
      Double_t           IsoChargedHadronPtSum()       const { return fIsoChargedHadronPtSum;      }
      Double_t           IsoGammaEtSum()               const { return fIsoGammaEtSum;              }
      const PFCandidate *IsoPFCand(UInt_t i)           const { return fIsoPFCands.At(i);           }
      const PFCandidate *LeadChargedHadronPFCand()     const { return fLeadChargedHadPFCand.Obj(); }
      const PFCandidate *LeadNeutralHadronPFCand()     const { return fLeadNeutralPFCand.Obj();    }
      const PFCandidate *LeadPFCand()                  const { return fLeadPFCand.Obj();           }
      Double_t           LeadPFCandSignD0Sig()         const { return fLeadPFCandSignD0Sig;        }
      Double_t           MaxHCalPFClusterEt()          const { return fMaxHCalPFClusterEt;         }
      Bool_t             MuonDecision()                const { return fMuonDecision;               }
      UInt_t             NIsoPFCandS()                 const { return fIsoPFCands.Entries();       }
      UInt_t             NSignalPFCands()              const { return fSignalPFCands.Entries();    }
      EObjType           ObjType()                     const { return kPFTau;                      }
      Double_t           SegmentCompatibility()        const { return fSegmentCompatibility;       }
      void               SetBremRecoveryEOverP(Double_t x)   { fBremRecoveryEOverP = x;            }
      void               SetCaloCompatibility(Double_t x)    { fCaloCompatibility = x;             }
      void               SetECalStripSumEOverP(Double_t x)   { fECalStripSumEOverP = x;            }
      void               SetEMFraction(Double_t x)           { fEMFraction = x;                    }
      void               SetElectronPreIDDecision(Bool_t b)  { fElectronPreIDDecision = b;         }
      void               SetElectronPreIDOutput(Double_t x)  { fElectronPreIDOutput = x;           }
      void               SetElectronTrack(const Track *t)    { fElectronTrack = t;                 }
      void               SetHCal3x3EOverP(Double_t x)        { fHCal3x3EOverP = x;                 }
      void               SetHCalMaxEOverP(Double_t x)        { fHCalMaxEOverP = x;                 }
      void               SetHCalTotalEOverP(Double_t x)      { fHCalTotalEOverP = x;               }
      void               SetIsoChargedHadronPtSum(Double_t x){ fIsoChargedHadronPtSum = x;         }
      void               SetIsoGammaEtSum(Double_t x)        { fIsoGammaEtSum = x;                 }
      void               SetLeadChargedHadronPFCand(const PFCandidate *p) 
                                                                    { fLeadChargedHadPFCand = p;   }
      void               SetLeadNeutralPFCand(const PFCandidate *p) { fLeadNeutralPFCand = p;      }
      void               SetLeadPFCand(const PFCandidate *p)        { fLeadPFCand = p;             }
      void               SetLeadPFCandSignD0Sig(Double_t x)         { fLeadPFCandSignD0Sig = x;    }
      void               SetMaxHCalPFClusterEt(Double_t x)          { fMaxHCalPFClusterEt = x;     }
      void               SetMuonDecision(Bool_t b)                  { fMuonDecision = b;           }
      void               SetPFJet(const PFJet *j)                   { fPFJet = j;                  }
      void               SetSegmentCompatibility(Double_t x)        { fSegmentCompatibility = x;   }
      const PFCandidate *SignalPFCand(UInt_t i)         const { return fSignalPFCands.At(i);       }
      const PFJet       *SourcePFJet()                  const { return fPFJet.Obj();               }
      const Jet         *SourceJet()                    const { return SourcePFJet();              }

    protected:
      Double_t           GetCharge()                    const;

      Double32_t         fLeadPFCandSignD0Sig;   //[0,0,14]signed lead track D0 significance
      Double32_t         fHCalTotalEOverP;       //[0,0,14]total hcal e / lead ch had pfcand mom
      Double32_t         fHCalMaxEOverP;         //[0,0,14]max hcal e / lead ch had pfcand. mom
      Double32_t         fHCal3x3EOverP;         //[0,0,14]3x3 hcal e / lead ch hadron pfcand. mom
      Double32_t         fIsoChargedHadronPtSum; //[0,0,14]sum pt of sel. ch had pfcands in iso cone
      Double32_t         fIsoGammaEtSum;         //[0,0,14]sum et of sel. photon pfcands in iso cone
      Double32_t         fMaxHCalPFClusterEt;    //[0,0,14]et of largest et hcal pfcluster
      Double32_t         fEMFraction;            //[0,0,14]em energy fraction
      Double32_t         fECalStripSumEOverP;    //[0,0,14]simple brem recovery e / lead ch had mom
      Double32_t         fBremRecoveryEOverP;    //[0,0,14]brem recovery E / lead charged hadron P
      Double32_t         fElectronPreIDOutput;   //[0,0,14]pfel pre id bdt output to be an el
      Double32_t         fCaloCompatibility;     //[0,0,14]calo comp. for this tau to be a muon
      Double32_t         fSegmentCompatibility;  //[0,0,14]segment comp. for this tau to be a muon
      Bool_t             fElectronPreIDDecision; //pf electron pre id decision
      Bool_t             fMuonDecision;          //pf muon id decision
      Ref<PFCandidate>   fLeadPFCand;            //leading signal pf candidate (charged or neutral)
      Ref<PFCandidate>   fLeadChargedHadPFCand;  //leading charged hadron signal pf candidate
      Ref<PFCandidate>   fLeadNeutralPFCand;     //leading neutral signal pf candidate
      Ref<PFJet>         fPFJet;                 //original reconstructed pf jet
      Ref<Track>         fElectronTrack;         //track corresponding to possible matching el cand.
      RefArray<PFCandidate> fSignalPFCands;      //selected pf candidates in signal cone
      RefArray<PFCandidate> fIsoPFCands;         //selected pf candidates in isolation annulus

    ClassDef(PFTau, 1) // PFTau class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::PFTau::GetCharge() const
{
  // Get charge from signal candidates.

  Double_t sumq = 0;
  for (UInt_t i=0; i<fSignalPFCands.Entries(); ++i) {
    sumq += fSignalPFCands.At(i)->Charge();
  }
  return sumq;
}
#endif
