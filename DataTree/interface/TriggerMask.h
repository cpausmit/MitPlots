//--------------------------------------------------------------------------------------------------
// $Id: TriggerMask.h,v 1.1 2009/03/08 12:10:42 loizides Exp $
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
#include "MitAna/DataCont/interface/CacheFlag.h"

namespace mithep 
{
  class TriggerMask : public DataBase
  {
    public:
      TriggerMask() : fFilledLargeMask(kFALSE)                    {}
      TriggerMask(const BitMask1024 &mask) : fMasknew(mask), fFilledLargeMask(kTRUE) {} 

      Bool_t                At(UInt_t n)            const { return TestBit(n); }
      const BitMask1024    &Get()                   const;
      EObjType              ObjType()               const { return kTriggerMask;     }      
      void                  Print(Option_t *opt="") const { Get().Print(opt);        }
      void                  SetBits(const BitMask1024 &m)  { fFilledLargeMask=kTRUE; fMasknew.SetBits(m); }
      UInt_t                Size()                  const { return fFilledLargeMask ? fMasknew.Size() : fMask.Size();  }
      UInt_t                MaxSize()               const { return fMasknew.Size(); }
      Bool_t                TestBit(UInt_t n)       const { return fFilledLargeMask ? fMasknew.TestBit(n) : fMask.TestBit(n); }

    protected:
      BitMask256    fMask; //trigger mask
      mutable BitMask1024 fMasknew; //larger trigger mask
      Bool_t      fFilledLargeMask; //bool switch, was large mask filled originally

    ClassDef(TriggerMask, 2) // Trigger mask 
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::BitMask1024 &mithep::TriggerMask::Get() const
{
  //printf("get bitmask, fUseLargeMask = %i, fFilledLargeMask = %i\n",fUseLargeMask.IsValid(),fFilledLargeMask);
  
  // Return bitmask, filling new bitmask from old one if necessary
  if (fFilledLargeMask) return fMasknew;
  
  fMasknew.Clear();
  for (UInt_t i=0; i<fMask.Size(); ++i) {
    fMasknew.SetBit(i,fMask.TestBit(i));
  }
  
  return fMasknew;
  
}
#endif
