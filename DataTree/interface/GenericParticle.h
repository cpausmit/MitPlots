//--------------------------------------------------------------------------------------------------
// $Id: GenericParticle.h,v 1.3 2009/04/09 11:24:45 loizides Exp $
//
// GenericParticle
//
// General particle class to be filled and used at analysis time.
// It provides an abstract interface to kinematical quantities computed by derived classes.
//
// Authors: G.Ceballos, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_GENERICPARTICLE_H
#define MITANA_DATATREE_GENERICPARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class GenericParticle : public Particle
  {
    public:
      GenericParticle(): fQ(0), fObjType(kGenericParticle) {}
    GenericParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t c, 
                    EObjType type=kGenericParticle) : 
        fMom(FourVector(px,py,pz,e)), fQ(c), fObjType(type) {}
    GenericParticle(Double_t px, Double_t py, Double_t pz, Double_t e,                     
                    EObjType type=kGenericParticle) : 
      fMom(FourVector(px,py,pz,e)), fQ(0), fObjType(type) {}
    GenericParticle(const FourVector &m, Double_t c, EObjType type=kGenericParticle) : 
        fMom(m), fQ(c), fObjType(type) {}
    GenericParticle(const FourVectorM &m, Double_t c, EObjType type=kGenericParticle) : 
        fMom(m), fQ(c), fObjType(type) {}
     
      void               Print(Option_t *opt="")   const;
      EObjType           RecoObjType()		   const { return fObjType;	   }
      void		 SetCharge(Double_t c)  	 { fQ = c; ClearCharge();  }
      void		 SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void               SetRecoObjType(EObjType t)      { fObjType = t;           }
     
    protected:
      Double_t 		 GetCharge()		   const { return fQ;		   }
      Double_t           GetMass()                 const { return fMom.M();        }
      void               GetMom()                  const;

      FourVectorM        fMom;     //momentum vector
      Double_t           fQ;	   //charge value
      EObjType           fObjType; //object type

    ClassDef(GenericParticle, 1) // Generic particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenericParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fMom.SetXYZT(px, py, pz, e);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenericParticle::GetMom() const
{
  // Get momentum values.

  fCachedMom = fMom;
}
#endif
