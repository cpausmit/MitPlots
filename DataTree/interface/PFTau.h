//--------------------------------------------------------------------------------------------------
// $Id: PFTau.h,v 1.10 2012/03/26 15:26:35 mhchan Exp $
//
// PFTau
//
// This class holds information about reconstructed tau based on PFCandidates.
//
// Authors: J.Bendavid, C.Paus
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
		  fMuonDecision(kFALSE), 
		  fDiscriminationAgainstElectron(0), 
		  fDiscriminationAgainstMuon(0),
		  fDiscriminationByLooseElectronRejection(0),
		  fDiscriminationByMediumElectronRejection(0), 
		  fDiscriminationByTightElectronRejection(0),
                  fDiscriminationByMVAElectronRejection(0),
		  fDiscriminationByLooseMuonRejection(0),
                  fDiscriminationByMediumMuonRejection(0),
		  fDiscriminationByTightMuonRejection(0),
		  fDiscriminationByDecayModeFinding(0),
		  fDiscriminationByVLooseIsolation(0), fDiscriminationByLooseIsolation(0),
                  fDiscriminationByMediumIsolation(0), fDiscriminationByTightIsolation(0), 
		  fDiscriminationByVLooseCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByLooseCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByMediumCombinedIsolationDBSumPtCorr(0),
                  fDiscriminationByTightCombinedIsolationDBSumPtCorr(0),
                  fDiscriminationByRawCombinedIsolationDBSumPtCorr(0) {}
                  
      PFTau(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Tau(px,py,pz,e),
                  fLeadPFCandSignD0Sig(0), fHCalTotalEOverP(0), fHCalMaxEOverP(0),
                  fHCal3x3EOverP(0), fIsoChargedHadronPtSum(0), fIsoGammaEtSum(0),
                  fMaxHCalPFClusterEt(0), fEMFraction(0), fECalStripSumEOverP(0),
                  fBremRecoveryEOverP(0), fElectronPreIDOutput(0), fCaloCompatibility(0), 
                  fSegmentCompatibility(0), fElectronPreIDDecision(kFALSE),
		  fMuonDecision(kFALSE),
		  fDiscriminationAgainstElectron(0), 
		  fDiscriminationAgainstMuon(0),
		  fDiscriminationByLooseElectronRejection(0),
		  fDiscriminationByMediumElectronRejection(0), 
		  fDiscriminationByTightElectronRejection(0),
		  fDiscriminationByMVAElectronRejection(0),
		  fDiscriminationByLooseMuonRejection(0),
		  fDiscriminationByMediumMuonRejection(0),
		  fDiscriminationByTightMuonRejection(0),
		  fDiscriminationByDecayModeFinding(0),
		  fDiscriminationByVLooseIsolation(0), fDiscriminationByLooseIsolation(0),
		  fDiscriminationByMediumIsolation(0), fDiscriminationByTightIsolation(0),
		  fDiscriminationByVLooseCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByLooseCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByMediumCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByTightCombinedIsolationDBSumPtCorr(0),
		  fDiscriminationByRawCombinedIsolationDBSumPtCorr(0) {}

      void               AddIsoPFCand(const PFCandidate *p)  { fIsoPFCands.Add(p);                 }
      void               AddSignalPFCand(const PFCandidate *p)      
                            { ClearCharge(); fSignalPFCands.Add(p); }
      void               AddSignalPFChargedHadrCand(const PFCandidate *p) { fSignalPFChargedHadrCands.Add(p); }
      void               AddSignalPFNeutrHadrCand(const PFCandidate *p)   { fSignalPFNeutrHadrCands.Add(p); }
      void               AddSignalPFGammaCand(const PFCandidate *p)       { fSignalPFGammaCands.Add(p); }
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
      UInt_t             NSignalPFChargedHadrCands()   const { return fSignalPFChargedHadrCands.Entries(); }
      UInt_t             NSignalPFNeutrHadrCands()     const { return fSignalPFNeutrHadrCands.Entries(); }
      UInt_t             NSignalPFGammaCands()         const { return fSignalPFGammaCands.Entries(); }
      EObjType           ObjType()                     const { return kPFTau;                      }
      Double_t           SegmentCompatibility()        const { return fSegmentCompatibility;       }
      Double_t DiscriminationAgainstElectron()         const {return fDiscriminationAgainstElectron;}
      Double_t DiscriminationAgainstMuon()             const {return fDiscriminationAgainstMuon;}
      Double_t DiscriminationByLooseElectronRejection()  const {return fDiscriminationByLooseElectronRejection;}
      Double_t DiscriminationByMediumElectronRejection() const {return fDiscriminationByMediumElectronRejection;}
      Double_t DiscriminationByTightElectronRejection()  const {return fDiscriminationByTightElectronRejection;}
      Double_t DiscriminationByMVAElectronRejection()  const {return fDiscriminationByMVAElectronRejection;}
      Double_t DiscriminationByLooseMuonRejection()    const {return fDiscriminationByLooseMuonRejection;}
      Double_t DiscriminationByMediumMuonRejection()   const {return fDiscriminationByMediumMuonRejection;}
      Double_t DiscriminationByTightMuonRejection()    const {return fDiscriminationByTightMuonRejection;}
      Double_t DiscriminationByDecayModeFinding()      const {return fDiscriminationByDecayModeFinding;}
      Double_t DiscriminationByVLooseIsolation()       const {return fDiscriminationByVLooseIsolation;}
      Double_t DiscriminationByLooseIsolation()        const {return fDiscriminationByLooseIsolation;}
      Double_t DiscriminationByMediumIsolation()       const {return fDiscriminationByMediumIsolation;}
      Double_t DiscriminationByTightIsolation()        const {return fDiscriminationByTightIsolation;}
      Double_t DiscriminationByVLooseCombinedIsolationDBSumPtCorr() const {return fDiscriminationByVLooseCombinedIsolationDBSumPtCorr;}
      Double_t DiscriminationByLooseCombinedIsolationDBSumPtCorr()  const {return fDiscriminationByLooseCombinedIsolationDBSumPtCorr;}
      Double_t DiscriminationByMediumCombinedIsolationDBSumPtCorr() const {return fDiscriminationByMediumCombinedIsolationDBSumPtCorr;}
      Double_t DiscriminationByTightCombinedIsolationDBSumPtCorr() const {return fDiscriminationByTightCombinedIsolationDBSumPtCorr;}
      Double_t DiscriminationByRawCombinedIsolationDBSumPtCorr() const {return fDiscriminationByRawCombinedIsolationDBSumPtCorr;}
      
      void               SetCharge(Char_t x)                 { fCharge = x; ClearCharge();         }
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
      const PFCandidate *SignalPFChargedHadrCand(UInt_t i) const { return fSignalPFChargedHadrCands.At(i); }
      const PFCandidate *SignalPFNeutrHadrCand(UInt_t i)   const { return fSignalPFNeutrHadrCands.At(i); }
      const PFCandidate *SignalPFGammaCand(UInt_t i)       const { return fSignalPFGammaCands.At(i); }
      const PFJet       *SourcePFJet()                  const { return fPFJet.Obj();               }
      const Jet         *SourceJet()                    const { return SourcePFJet();              }

      void SetDiscriminationAgainstElectron(Double_t x)    {fDiscriminationAgainstElectron = x;}
      void SetDiscriminationAgainstMuon(Double_t x)        {fDiscriminationAgainstMuon = x;}
      void SetDiscriminationByLooseElectronRejection(Double_t x) {fDiscriminationByLooseElectronRejection = x;}
      void SetDiscriminationByMediumElectronRejection(Double_t x) {fDiscriminationByMediumElectronRejection = x;}
      void SetDiscriminationByTightElectronRejection(Double_t x) {fDiscriminationByTightElectronRejection = x;}
      void SetDiscriminationByMVAElectronRejection(Double_t x) {fDiscriminationByMVAElectronRejection = x;}
      void SetDiscriminationByLooseMuonRejection(Double_t x) {fDiscriminationByLooseMuonRejection = x;}
      void SetDiscriminationByMediumMuonRejection(Double_t x) {fDiscriminationByMediumMuonRejection = x;}
      void SetDiscriminationByTightMuonRejection(Double_t x) {fDiscriminationByTightMuonRejection = x;}
      void SetDiscriminationByDecayModeFinding(Double_t x) {fDiscriminationByDecayModeFinding = x;}
      void SetDiscriminationByVLooseIsolation(Double_t x)   {fDiscriminationByVLooseIsolation = x;}
      void SetDiscriminationByLooseIsolation(Double_t x)   {fDiscriminationByLooseIsolation = x;}
      void SetDiscriminationByMediumIsolation(Double_t x)  {fDiscriminationByMediumIsolation = x;}
      void SetDiscriminationByTightIsolation(Double_t x)   {fDiscriminationByTightIsolation = x;}
      void SetDiscriminationByVLooseCombinedIsolationDBSumPtCorr(Double_t x) {fDiscriminationByVLooseCombinedIsolationDBSumPtCorr = x;}
      void SetDiscriminationByLooseCombinedIsolationDBSumPtCorr(Double_t x)  {fDiscriminationByLooseCombinedIsolationDBSumPtCorr = x; }
      void SetDiscriminationByMediumCombinedIsolationDBSumPtCorr(Double_t x) {fDiscriminationByMediumCombinedIsolationDBSumPtCorr = x;}
      void SetDiscriminationByTightCombinedIsolationDBSumPtCorr(Double_t x)  {fDiscriminationByTightCombinedIsolationDBSumPtCorr = x; }
      void SetDiscriminationByRawCombinedIsolationDBSumPtCorr(Double_t x) {fDiscriminationByRawCombinedIsolationDBSumPtCorr = x;}

      // Some structural tools
      void                  Mark()                         const;
			    
    protected:		    
      Double_t              GetCharge()                    const;
      Char_t                fCharge;                //stored charge
      Double32_t            fLeadPFCandSignD0Sig;   //[0,0,14]signed lead track D0 significance
      Double32_t            fHCalTotalEOverP;       //[0,0,14]total hcal e / lead ch had pfcand mom
      Double32_t            fHCalMaxEOverP;         //[0,0,14]max hcal e / lead ch had pfcand. mom
      Double32_t            fHCal3x3EOverP;         //[0,0,14]3x3 hcal e / lead ch hadron pfcand. mom
      Double32_t            fIsoChargedHadronPtSum; //[0,0,14]sum pt of sel. ch had pfcands in iso cone
      Double32_t            fIsoGammaEtSum;         //[0,0,14]sum et of sel. photon pfcands in iso cone
      Double32_t            fMaxHCalPFClusterEt;    //[0,0,14]et of largest et hcal pfcluster
      Double32_t            fEMFraction;            //[0,0,14]em energy fraction
      Double32_t            fECalStripSumEOverP;    //[0,0,14]simple brem recovery e / lead ch had mom
      Double32_t            fBremRecoveryEOverP;    //[0,0,14]brem recovery E / lead charged hadron P
      Double32_t            fElectronPreIDOutput;   //[0,0,14]pfel pre id bdt output to be an el
      Double32_t            fCaloCompatibility;     //[0,0,14]calo comp. for this tau to be a muon
      Double32_t            fSegmentCompatibility;  //[0,0,14]segment comp. for this tau to be a muon
      Bool_t                fElectronPreIDDecision; //pf electron pre id decision
      Bool_t                fMuonDecision;          //pf muon id decision
      Double32_t            fDiscriminationAgainstElectron;    
      Double32_t            fDiscriminationAgainstMuon;        
      Double32_t            fDiscriminationByLooseElectronRejection; 
      Double32_t            fDiscriminationByMediumElectronRejection; 
      Double32_t            fDiscriminationByTightElectronRejection; 
      Double32_t            fDiscriminationByMVAElectronRejection; 
      Double32_t            fDiscriminationByLooseMuonRejection; 
      Double32_t            fDiscriminationByMediumMuonRejection; 
      Double32_t            fDiscriminationByTightMuonRejection; 
      Double32_t            fDiscriminationByDecayModeFinding; 
      Double32_t            fDiscriminationByVLooseIsolation;  
      Double32_t            fDiscriminationByLooseIsolation;   
      Double32_t            fDiscriminationByMediumIsolation;  
      Double32_t            fDiscriminationByTightIsolation;   
      Double32_t            fDiscriminationByVLooseCombinedIsolationDBSumPtCorr; 
      Double32_t            fDiscriminationByLooseCombinedIsolationDBSumPtCorr;  
      Double32_t            fDiscriminationByMediumCombinedIsolationDBSumPtCorr; 
      Double32_t            fDiscriminationByTightCombinedIsolationDBSumPtCorr;  
      Double32_t            fDiscriminationByRawCombinedIsolationDBSumPtCorr;
      
      Ref<PFCandidate>      fLeadPFCand;               //leading sig pf cand (charged or neutral)
      Ref<PFCandidate>      fLeadChargedHadPFCand;     //leading charged hadron signal pf cand
      Ref<PFCandidate>      fLeadNeutralPFCand;        //leading neutral signal pf cand
      Ref<PFJet>            fPFJet;                    //original reconstructed pf jet
      Ref<Track>            fElectronTrack;            //track corresp. to pot. matching el cand
      RefArray<PFCandidate> fSignalPFCands;            //selected pf candidates in signal cone
      RefArray<PFCandidate> fSignalPFChargedHadrCands; //signal pf charged hadron candidates
      RefArray<PFCandidate> fSignalPFNeutrHadrCands;   //signal pf neutral hadron candidates
      RefArray<PFCandidate> fSignalPFGammaCands;       //signal pf gamma candidates
      RefArray<PFCandidate> fIsoPFCands;               //selected pf candidates in isolation annulus

    ClassDef(PFTau, 5) // PFTau class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::PFTau::Mark() const
{
  // mark myself
  mithep::DataObject::Mark();
  // mark my dependencies if they are there
  if (fLeadPFCand          .IsValid())
    fLeadPFCand          .Obj()->Mark();
  if (fLeadChargedHadPFCand.IsValid())
    fLeadChargedHadPFCand.Obj()->Mark();
  if (fLeadNeutralPFCand   .IsValid())
    fLeadNeutralPFCand   .Obj()->Mark();
  if (fPFJet               .IsValid())
    fPFJet               .Obj()->Mark();
  if (fElectronTrack       .IsValid())
    fElectronTrack       .Obj()->Mark();
  for (UInt_t i=0; i<fSignalPFCands           .Entries(); i++)
    fSignalPFCands           .At(i)->Mark();
  for (UInt_t i=0; i<fSignalPFChargedHadrCands.Entries(); i++)
    fSignalPFChargedHadrCands.At(i)->Mark();
  for (UInt_t i=0; i<fSignalPFNeutrHadrCands  .Entries(); i++)
    fSignalPFNeutrHadrCands  .At(i)->Mark();
  for (UInt_t i=0; i<fSignalPFGammaCands      .Entries(); i++)
    fSignalPFGammaCands      .At(i)->Mark();
  for (UInt_t i=0; i<fIsoPFCands              .Entries(); i++)
    fIsoPFCands              .At(i)->Mark();
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::PFTau::GetCharge() const
{
  return fCharge;
}
#endif
