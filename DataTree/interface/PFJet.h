//--------------------------------------------------------------------------------------------------
// $Id: GenJet.h,v 1.5 2009/03/03 17:04:09 loizides Exp $
//
// PFJet
//
// This class holds information about reconstructed jet based on pf candidates
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PFJET_H
#define MITANA_DATATREE_PFJET_H
 
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/PFCandidate.h"

namespace mithep 
{
  class PFJet : public Jet
  {
    public:
      PFJet() : fChargedHadronEnergy(0), fNeutralHadronEnergy(0), fChargedEmEnergy(0),
                fChargedMuEnergy(0), fNeutralEmEnergy(0), fChargedMultiplicity(0),
                fNeutralMultiplicity(0), fMuonMultiplicity(0) {}
      PFJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                Jet(px,py,pz,e),
                fChargedHadronEnergy(0), fNeutralHadronEnergy(0), fChargedEmEnergy(0),
                fChargedMuEnergy(0), fNeutralEmEnergy(0), fChargedMultiplicity(0),
                fNeutralMultiplicity(0), fMuonMultiplicity(0) {}

      void              AddPFCand(const PFCandidate *p)     { fPFCands.Add(p);                   }
      Bool_t            HasPFCand(const PFCandidate *p) const { return fPFCands.HasObject(p);    }
      UInt_t            NPFCands()                    const { return fPFCands.GetEntries();      }
      const PFCandidate *PFCand(UInt_t i)              const { return fPFCands.At(i);            }
      UInt_t            NConstituents()               const { return NPFCands();                 }

      Double_t          ChargedHadronEnergy()         const { return fChargedHadronEnergy;       }
      Double_t          NeutralHadronEnergy()         const { return fNeutralHadronEnergy;       }
      Double_t          ChargedEmEnergy()             const { return fChargedEmEnergy;           }
      Double_t          ChargedMuEnergy()             const { return fChargedMuEnergy;           }
      Double_t          NeutralEmEnergy()             const { return fNeutralEmEnergy;           }
      UInt_t            ChargedMultiplicity()         const { return fChargedMultiplicity;       }
      UInt_t            NeutralMultiplicity()         const { return fNeutralMultiplicity;       }
      UInt_t            MuonMultiplicity()            const { return fMuonMultiplicity;          }
      void              SetChargedHadronEnergy(Double_t e)  { fChargedHadronEnergy = e;          }
      void              SetNeutralHadronEnergy(Double_t e)  { fNeutralHadronEnergy = e;          }
      void              SetChargedEmEnergy(Double_t e)      { fChargedEmEnergy = e;              }
      void              SetChargedMuEnergy(Double_t e)      { fChargedMuEnergy = e;              }
      void              SetNeutralEmEnergy(Double_t e)      { fNeutralEmEnergy = e;              }
      void              SetChargedMultiplicity(UInt_t n)    { fChargedMultiplicity = n;          }
      void              SetNeutralMultiplicity(UInt_t n)    { fNeutralMultiplicity = n;          }
      void              SetMuonMultiplicity(UInt_t n)       { fMuonMultiplicity = n;             }

    protected:

      Double32_t            fChargedHadronEnergy;
      Double32_t            fNeutralHadronEnergy;
      Double32_t            fChargedEmEnergy;
      Double32_t            fChargedMuEnergy;
      Double32_t            fNeutralEmEnergy;
      UInt_t                fChargedMultiplicity;
      UInt_t                fNeutralMultiplicity;
      UInt_t                fMuonMultiplicity;
      RefArray<PFCandidate> fPFCands;              //pf candidates in the jet

    ClassDef(PFJet, 1) // PFJet class
  };
}
#endif
