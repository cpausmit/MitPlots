//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.5 2009/02/18 15:38:55 loizides Exp $
//
// TriggerMask
//
// A class to hold the trigger mask.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERMASK_H
#define MITANA_DATATREE_TRIGGERMASK_H

#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class TriggerMask : public DataBase
  {
    public:
      TriggerMask()                                       {}
      TriggerMask(const BitMask256 &mask) : fMask(mask)   {} 

      Bool_t                At(UInt_t n)            const { return fMask.TestBit(n); }
      const BitMask256     &Get()                   const { return fMask;            }
      EObjType              ObjType()               const { return kTriggerMask;     }      
      void                  Print(Option_t *opt="") const { fMask.Print(opt);        }
      void                  SetBits(const BitMask256 &m)  { fMask.SetBits(m);        }
      UInt_t                Size()                  const { return fMask.Size();     }
      Bool_t                TestBit(UInt_t n)       const { return fMask.TestBit(n); }

    protected:
      BitMask256            fMask; //trigger mask

    ClassDef(TriggerMask, 1) // Trigger mask 
  };
}
#endif
