//--------------------------------------------------------------------------------------------------
// $Id: GenJet.h,v 1.5 2009/03/03 17:04:09 loizides Exp $
//
// GenJet
//
// This class holds information about reconstructed jets at generation level.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_GENJET_H
#define MITANA_DATATREE_GENJET_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class GenJet : public Particle
  {
    public:
      GenJet() : fHadEnergy(0), fEmEnergy(0), fInvisibleEnergy(0), 
                 fAuxiliaryEnergy(0), fMatchedMCFlavor(0) {}

      Double_t          AuxiliaryEnergy()             const { return fAuxiliaryEnergy;           }
      Double_t          Charge()                      const { return 0;                          }
      Double_t          EmEnergy()                    const { return fEmEnergy;                  } 
      Double_t          HadEnergy()                   const { return fHadEnergy;                 } 
      Double_t          InvisibleEnergy()             const { return fInvisibleEnergy;           }
      Int_t             MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      EObjType          ObjType()                     const { return kGenJet;                    }
      void              SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m);
      void              SetHadEnergy(Double_t val)          { fHadEnergy        = val;           } 
      void              SetEmEnergy(Double_t val)           { fEmEnergy         = val;           }
      void              SetInvisibleEnergy(Double_t val)    { fInvisibleEnergy  = val;           }
      void              SetAuxiliaryEnergy(Double_t val)    { fAuxiliaryEnergy  = val;           }
      void              SetMatchedMCFlavor(Int_t flavor)    { fMatchedMCFlavor  = flavor;        }

    protected:
      void              GetMom()                      const;

      Vect4M            fMom;                    //four momentum of jet
      Double32_t        fHadEnergy; 	         //[0,0,14]hadronic energy
      Double32_t        fEmEnergy; 	         //[0,0,14]electromagnetic
      Double32_t        fInvisibleEnergy; 	 //[0,0,14]invisible energy (mu, nu)
      Double32_t        fAuxiliaryEnergy; 	 //[0,0,14]anything else (eg. undecayed sigmas)
      Int_t             fMatchedMCFlavor;        //pdg of the matched quark flavor

    ClassDef(GenJet, 1) // Jet class at generation level
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenJet::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M()); 
}

inline void mithep::GenJet::SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m)
{ 
  // Set momentum vector.

  fMom.Set(pt, eta, phi, m);
  ClearMom();
}

#endif
