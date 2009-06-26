//--------------------------------------------------------------------------------------------------
// $Id: GenericParticle.h,v 1.6 2009/06/19 07:41:34 loizides Exp $
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
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class GenericParticle : public Particle
  {
    public:
      GenericParticle(): fQ(0), fObjId(kGenericParticle), fObjType(kGenericParticle) {} 
      GenericParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t c, 
                      Int_t id=kGenericParticle, EObjType type=kGenericParticle) : 
        fMom(FourVector(px,py,pz,e)), fQ(c), fObjId(id), fObjType(type) {}
      GenericParticle(Double_t px, Double_t py, Double_t pz, Double_t e,                     
                      Int_t id=kGenericParticle, EObjType type=kGenericParticle) : 
        fMom(FourVector(px,py,pz,e)), fQ(0), fObjId(id), fObjType(type) {}
      GenericParticle(const FourVector &m, Double_t c, 
                      Int_t id=kGenericParticle, EObjType type=kGenericParticle) : 
        fMom(m), fQ(c), fObjId(id), fObjType(type) {}
      GenericParticle(const FourVectorM &m, Double_t c, 
                      Int_t id=kGenericParticle, EObjType type=kGenericParticle) : 
        fMom(m), fQ(c), fObjId(id), fObjType(type) {}
      GenericParticle(const Particle &p) :
        fMom(p.Mom()), fQ(p.Charge()), fObjId(p.ObjId()), fObjType(p.ObjType()) {}
      GenericParticle(const Track &t, Double_t mass=0) :
        fMom(t.Mom4(mass)), fQ(t.Charge()), fObjId(t.ObjId()), fObjType(t.ObjType()) {}
     
      void               Print(Option_t *opt="")   const;
      Int_t              ObjId()                   const { return fObjId;           }
      EObjType           ObjType()		   const { return fObjType;	    }
      void		 SetCharge(Double_t c)           { fQ = c; ClearCharge();   }
      void		 SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void               SetObjId(Int_t id)              { fObjId = id;             }
      void               SetObjType(EObjType t)          { fObjType = t;            }
     
    protected:
      Double_t 		 GetCharge()               const { return fQ;		    }
      Double_t           GetMass()                 const { return fMom.M();         }
      void               GetMom()                  const;

      FourVectorM        fMom;     //momentum vector
      Double_t           fQ;	   //charge value
      Int_t              fObjId;   //object id
      EObjType           fObjType; //object type

    ClassDef(GenericParticle, 2) // Generic particle class
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
