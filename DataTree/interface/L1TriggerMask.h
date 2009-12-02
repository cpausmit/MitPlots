//--------------------------------------------------------------------------------------------------
// $Id: L1TriggerMask.h,v 1.2 2009/11/26 21:42:56 loizides Exp $
//
// L1TriggerMask
//
// A class to hold the L1 trigger mask.
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
      L1TriggerMask() : fBx(0) {}
      L1TriggerMask(const BitMask128 &mask) : fMask(mask), fBx(0) {} 

      Bool_t                At(UInt_t n)            const { return fMask.TestBit(n); }
      Char_t                Bx()                    const { return fBx;              }
      const BitMask128     &Get()                   const { return fMask;            }
      EObjType              ObjType()               const { return kL1TriggerMask;   }      
      void                  Print(Option_t *opt="") const { fMask.Print(opt);        }
      void                  SetBits(const BitMask128 &m)  { fMask.SetBits(m);        }
      void                  SetBx(Char_t bx)              { fBx = bx;                }
      UInt_t                Size()                  const { return fMask.Size();     }
      Bool_t                TestBit(UInt_t n)       const { return fMask.TestBit(n); }

    protected:
      BitMask128            fMask; //trigger mask
      Char_t                fBx;   //bunch crossing (-2,-1,0,1,2)

    ClassDef(L1TriggerMask, 3) // L1 trigger mask 
  };
}
#endif
