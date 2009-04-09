//--------------------------------------------------------------------------------------------------
// $Id: GenericParticle.h,v 1.31 2009/04/06 09:50:49 loizides Exp $
//
// GenericParticle
//
// General GenericParticle class. It provides an abstract interface to kinematical quantities
// computed by derived classes.
//
// Authors: C.Loizides
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
      GenericParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t c) : 
        fMom(FourVector(px,py,pz,e)), fQ(c), fObjType(kGenericParticle) {}
      GenericParticle(FourVector &m, Double_t c) : fMom(m), fQ(c), fObjType(kGenericParticle) {}
     
      EObjType           ObjType()		   const { return fObjType;	   }
      void               Print(Option_t *opt="")   const;

      void		 SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		 SetCharge(Double_t c)  	 { fQ = c;		   }
      void               SetObjType(EObjType t)          { fObjType = t;           }
     
    protected:
      Double_t 		 GetCharge()		   const { return fQ;		   }
      Double_t           GetMass()                 const { return fMom.M();        }
      void               GetMom()                  const;

      FourVectorM        fMom;     //momentum vector
      Double_t           fQ;	   //charge value
      EObjType           fObjType; //object type

    ClassDef(GenericParticle, 1) // Generic GenericParticle class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenericParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fMom.SetXYZT(px, py, pz, e);
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenericParticle::GetMom() const
{
  // Get momentum values

  fCachedMom = fMom;
}
#endif
