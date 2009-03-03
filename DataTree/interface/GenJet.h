//--------------------------------------------------------------------------------------------------
// $Id: GenJet.h,v 1.4 2009/02/18 15:38:54 loizides Exp $
//
// GenJet
//
// This class holds information about reconstructed jets at generation level.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_GENJET_H
#define MITANA_DATATREE_GENJET_H
 
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class GenJet : public Particle
  {
    public:
      GenJet() : fHadEnergy(0), fEmEnergy(0), fInvisibleEnergy(0), 
                 fAuxiliaryEnergy(0), fMatchedMCFlavor(0) {}
      GenJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fMom(FourVector(px,py,pz,e)), 
        fHadEnergy(0), fEmEnergy(0), fInvisibleEnergy(0),
        fAuxiliaryEnergy(0), fMatchedMCFlavor(0)  {}

      Double_t          AuxiliaryEnergy()             const { return fAuxiliaryEnergy;           }
      Double_t          Charge()                      const { return 0;                          }
      Double_t          EmEnergy()                    const { return fEmEnergy;                  } 
      Double_t          HadEnergy()                   const { return fHadEnergy;                 } 
      Double_t          InvisibleEnergy()             const { return fInvisibleEnergy;           }
      Int_t             MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      EObjType          ObjType()                     const { return kGenJet;                    }
      void              SetHadEnergy(Double_t val)          { fHadEnergy        = val;           } 
      void              SetEmEnergy(Double_t val)           { fEmEnergy         = val;           }
      void              SetInvisibleEnergy(Double_t val)    { fInvisibleEnergy  = val;           }
      void              SetAuxiliaryEnergy(Double_t val)    { fAuxiliaryEnergy  = val;           }
      void              SetMatchedMCFlavor(Int_t flavor)    { fMatchedMCFlavor  = flavor;        }

    protected:
      void              GetMom()                      const;

      FourVectorM32     fMom;                    //four momentum of jet
      Double32_t        fHadEnergy; 	         //hadronic energy
      Double32_t        fEmEnergy; 	         //electromagnetic
      Double32_t        fInvisibleEnergy; 	 //invisible energy (mu, nu)
      Double32_t        fAuxiliaryEnergy; 	 //anything else (eg. undecayed sigmas)
      Int_t             fMatchedMCFlavor;        //pdg of the quark flavor that the jet matched to

    ClassDef(GenJet, 1) // Jet class at generation level
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenJet::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M()); 
}
#endif
