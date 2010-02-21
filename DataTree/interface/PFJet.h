//--------------------------------------------------------------------------------------------------
// $Id: PFJet.h,v 1.5 2009/09/09 03:38:26 bendavid Exp $
//
// PFJet
//
// This class holds information about reconstructed jet based on pf candidates.
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
                fNeutralEmEnergy(0), fMuonEnergy(0), fChargedMultiplicity(0),
                fNeutralMultiplicity(0), fMuonMultiplicity(0) {}
      PFJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                Jet(px,py,pz,e),
                fChargedHadronEnergy(0), fNeutralHadronEnergy(0), fChargedEmEnergy(0),
                fNeutralEmEnergy(0), fMuonEnergy(0), fChargedMultiplicity(0),
                fNeutralMultiplicity(0), fMuonMultiplicity(0) {}

      void                  AddPFCand(const PFCandidate *p)       { fPFCands.Add(p); ClearCharge();}
      Double_t              ChargedEmEnergy()               const { return fChargedEmEnergy;       }
      Double_t              ChargedHadronEnergy()           const { return fChargedHadronEnergy;   }
      Double_t              MuonEnergy()                    const { return fMuonEnergy;            }
      UInt_t                ChargedMultiplicity()           const { return fChargedMultiplicity;   }
      Bool_t                HasPFCand(const PFCandidate *p) const { return fPFCands.HasObject(p);  }
      Jet                  *MakeCopy()                      const { return new PFJet(*this);       }
      UInt_t                NConstituents()                 const { return NPFCands();             }
      Double_t              NeutralEmEnergy()               const { return fNeutralEmEnergy;       }
      Double_t              NeutralHadronEnergy()           const { return fNeutralHadronEnergy;   }
      UInt_t                NeutralMultiplicity()           const { return fNeutralMultiplicity;   }
      UInt_t                NPFCands()                      const { return fPFCands.Entries();     }
      UInt_t                MuonMultiplicity()              const { return fMuonMultiplicity;      }
      EObjType              ObjType()                       const { return kPFJet;                 } 
      const PFCandidate    *PFCand(UInt_t i)                const { return fPFCands.At(i);         }
      void                  SetChargedEmEnergy(Double_t e)        { fChargedEmEnergy     = e;      }
      void                  SetChargedHadronEnergy(Double_t e)    { fChargedHadronEnergy = e;      }
      void                  SetChargedMuEnergy(Double_t e)        { fMuonEnergy          = e;      }
      void                  SetChargedMultiplicity(UInt_t n)      { fChargedMultiplicity = n;      }
      void                  SetMuonMultiplicity(UInt_t n)         { fMuonMultiplicity    = n;      }
      void                  SetNeutralEmEnergy(Double_t e)        { fNeutralEmEnergy     = e;      }
      void                  SetNeutralHadronEnergy(Double_t e)    { fNeutralHadronEnergy = e;      }
      void                  SetNeutralMultiplicity(UInt_t n)      { fNeutralMultiplicity = n;      }

    protected:
      Double_t              GetCharge()                     const;

      Double32_t            fChargedHadronEnergy;  //[0,0,14]charged hadron energy
      Double32_t            fNeutralHadronEnergy;  //[0,0,14]neutral hadron energy
      Double32_t            fChargedEmEnergy;      //[0,0,14]charged em energy
      Double32_t            fNeutralEmEnergy;      //[0,0,14]neutral em energy
      Double32_t            fMuonEnergy;           //[0,0,14]muon energy
      UInt_t                fChargedMultiplicity;  //number of charged constituents
      UInt_t                fNeutralMultiplicity;  //number of neutral constituents
      UInt_t                fMuonMultiplicity;     //number of muon constituents
      RefArray<PFCandidate> fPFCands;              //pf candidates in the jet

    ClassDef(PFJet, 1) // PFJet class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::PFJet::GetCharge() const 
{
  // Return sum of charge of constituent PFCandidates.

  Double_t charge = 0;
  for (UInt_t i=0; i<NPFCands(); ++i)
    charge += PFCand(i)->Charge();
  
  return charge;
}
#endif
