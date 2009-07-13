//--------------------------------------------------------------------------------------------------
// $Id: TriggerObjectBase.h,v 1.2 2009/07/13 10:38:46 loizides Exp $
//
// TriggerObjectBase
//
// This class holds the HLT trigger object information, ie mainly the kinematics and type of 
// trigger, as known at tree filling time.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECTBASE_H
#define MITANA_DATATREE_TRIGGEROBJECTBASE_H

#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class TriggerObjectBase : public Particle
  {
    public:
      TriggerObjectBase() : fId(0), fType(0), fTagInd(-1) {}
      TriggerObjectBase(Int_t id, Char_t type, const FourVectorM32 &mom) : 
        fId(id), fMom(mom), fType(type), fTagInd(-1) {}
      TriggerObjectBase(Int_t id, Char_t type, 
                        Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        fId(id), fMom(pt,eta,phi,mass), fType(type), fTagInd(-1) {}

      Bool_t                HasType()           const { return fType!=0;           }
      Int_t                 Id()                const { return fId;                }
      Bool_t                IsHLT()             const { return fType>0;            }
      Bool_t                IsL1()              const { return fType<0;            }
      EObjType              ObjType()           const { return kTriggerObjectBase; }      
      Short_t               TagInd()            const { return fTagInd;            }
      Int_t                 Type()              const { return fType;              }
      void                  SetTagInd(Short_t i)      { fTagInd = i;               }
      void                  SetType(Char_t t)         { fType = t;                 }
   
    protected:
      void                  GetMom()        const;

      Int_t                 fId;          //id or physics type (similar to pdgId)
      Vect4M                fMom;         //object momentum
      Char_t                fType;        //trigger type
      Short_t               fTagInd;      //tag name index of original input tag

    ClassDef(TriggerObjectBase, 2) // Trigger object base class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::TriggerObjectBase::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M()); 
}
#endif
