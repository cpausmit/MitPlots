//--------------------------------------------------------------------------------------------------
// $Id: Particle.h,v 1.33 2009/07/13 11:00:30 loizides Exp $
//
// Particle
//
// General particle class. It provides an abstract interface to kinematical quantities
// computed by derived classes.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PARTICLE_H
#define MITANA_DATATREE_PARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataCont/interface/CacheFlag.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() : fIsFakeable(0) {}
     
      Double_t                  AbsEta()                  const { return TMath::Abs(Eta());        }
      Double_t 		        Charge()                  const;
      Int_t                     Compare(const TObject *o) const;   
      Double_t		        E()                       const { return Mom().E();                }
      Double_t		        Et()                      const;
      Double_t		        Eta()                     const { return Mom().Eta();              }
      Bool_t                    IsSortable()              const { return kTRUE;                    }
      Double_t		        Mass()                    const { return Mom().M();                }
      Double_t		        Mt()                      const { return Mom().Mt();               }
      const FourVectorM        &Mom()                     const;
      EObjType                  ObjType()                 const { return kParticle;                }
      Double_t		        Phi()                     const { return Mom().Phi();              }
      Double_t                  PhiDeg()                  const { return Phi() * 180 /TMath::Pi(); }
      void                      Print(Option_t *opt="")   const;
      Double_t		        Pt()                      const { return Mom().Pt();               }
      Double_t		        Px()                      const { return Mom().Px();               }
      Double_t		        Py()                      const { return Mom().Py();               }
      Double_t		        Pz()                      const { return Mom().Pz();               }
      Double_t		        P()                       const { return Mom().P();                }
      Double_t		        Rapidity()                const { return Mom().Rapidity();         }
      Double_t                  Theta()                   const { return Mom().Theta();            }
      Double_t		        TMass()                   const;
      Bool_t                    IsFakeable()              const { return fIsFakeable;              }
      void		        SetIsFakeable(Bool_t b)         { fIsFakeable = b;                 }
     
    protected:
      void                      ClearCharge()             const { fCacheQFlag.ClearCache();   }
      void                      ClearMom()                const { fCacheMomFlag.ClearCache(); }
      virtual Double_t          GetCharge()               const { return 0; }
      virtual Double_t          GetMass()                 const { return 0; }
      virtual void              GetMom()                  const = 0; 

      mutable CacheFlag         fCacheMomFlag; //||cache validity flag for momentum
      mutable CacheFlag         fCacheQFlag;   //||cache validity flag for charge
      mutable FourVectorM       fCachedMom;    //!cached momentum vector (filled by derived classes)
      mutable Double_t          fCachedQ;      //!chached charge value (filled by derived classes)
      Bool_t                    fIsFakeable;   //set to true if the lepton is a fakeable object

    ClassDef(Particle, 1) // Generic particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Particle::Charge() const
{
  // Return cached charge value.

  if (!fCacheQFlag.IsValid()) {
    fCachedQ = GetCharge();
    fCacheQFlag.SetValid();
  }

  return fCachedQ;
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

  return E()*Pt()/P(); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::FourVectorM &mithep::Particle::Mom() const
{
  // Return cached momentum value.

  if (!fCacheMomFlag.IsValid()) {
    GetMom();
    fCacheMomFlag.SetValid();
  }

  return fCachedMom;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Particle::TMass() const
{
  // Return transverse mass.

  return Mass()*Pt()/P();
}
#endif
