//--------------------------------------------------------------------------------------------------
// $Id: Particle.h,v 1.23 2008/12/01 17:30:48 loizides Exp $
//
// Particle
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PARTICLE_H
#define MITANA_DATATREE_PARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() {}
      ~Particle() {}
     
      Double_t                  AbsEta()                  const { return TMath::Abs(Eta()); }
      virtual Double_t 		Charge()                  const = 0;
      Int_t                     Compare(const TObject *o) const;   
      virtual Double_t		E()                       const { return Mom().E();     }
      virtual Double_t		Et()                      const;
      virtual Double_t		Eta()                     const { return Mom().Eta();   }
      Bool_t                    IsSortable()              const { return kTRUE;         }
      virtual Double_t		Mass()                    const { return TMath::Sqrt(Mom().M2());  }
      virtual Double_t		Mt()                      const { return TMath::Sqrt(Mom().Mt2()); }
      virtual FourVector	Mom()                     const = 0;
      EObjType                  ObjType()                 const { return kParticle;                }
      virtual Double_t		Phi()                     const { return Mom().Phi();              }
      Double_t                  PhiDeg()                  const { return Phi() * 180 /TMath::Pi(); }
      virtual Double_t		Pt()                      const { return Mom().Pt();    }
      virtual Double_t		Px()                      const { return Mom().Px();    }
      virtual Double_t		Py()                      const { return Mom().Py();    }
      virtual Double_t		Pz()                      const { return Mom().Pz();    }
      virtual Double_t		P()                       const { return Mom().P();     }
      virtual Double_t          Theta()                   const { return Mom().Theta(); }
      void                      Print(Option_t *opt="")   const;
     
    ClassDef(Particle, 1) // Generic particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Particle::Compare(const TObject *o) const
{
  // Default compare function for sorting according to transverse momentum. 
  // Returns -1 if this object is smaller than given object, 0 if objects are 
  // equal and 1 if this is larger than given object.

  const mithep::Particle *p = dynamic_cast<const mithep::Particle *>(o);
  if (!p)
    return 1;

  Double_t mypt = Pt();
  Double_t pt   = p->Pt();
  if (mypt>pt)
    return -1;
  else if (pt>mypt)
    return +1;
  return 0;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Particle::Et() const
{
  // Return transverse energy.

  return Mom().E()*Mom().Pt()/Mom().P(); 
}
#endif
