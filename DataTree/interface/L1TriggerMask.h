//--------------------------------------------------------------------------------------------------
// $Id: L1TriggerMask.h,v 1.1 2009/03/08 12:10:42 loizides Exp $
//
// L1TriggerMask
//
// A class to hold the l1 trigger mask.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_L1TRIGGERMASK_H
#define MITANA_DATATREE_L1TRIGGERMASK_H

#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class L1TriggerMask : public DataBase
  {
    public:
      L1TriggerMask()                                      {}
      L1TriggerMask(const BitMask64 &mask) : fMask(mask)   {} 

      Bool_t                At(UInt_t n)            const { return fMask.TestBit(n); }
      const BitMask64      &Get()                   const { return fMask;            }
      EObjType              ObjType()               const { return kL1TriggerMask;   }      
      void                  Print(Option_t *opt="") const { fMask.Print(opt);        }
      void                  SetBits(const BitMask64 &m)   { fMask.SetBits(m);        }
      UInt_t                Size()                  const { return fMask.Size();     }
      Bool_t                TestBit(UInt_t n)       const { return fMask.TestBit(n); }

    protected:
      BitMask64             fMask; //trigger mask

    ClassDef(L1TriggerMask, 1) // L1 trigger mask 
  };
}
#endif
