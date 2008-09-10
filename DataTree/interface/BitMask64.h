//--------------------------------------------------------------------------------------------------
// $Id: BitMask64.h,v 1.1 2008/07/31 13:28:41 bendavid Exp $
//
// BitMask64
//
// Helper class for using ULong64_t as a bitmask
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BITMASK64_H
#define MITANA_DATATREE_BITMASK64_H
 
#include "Rtypes.h"

namespace mithep 
{
  class BitMask64
  {
    public:
      BitMask64() : fBitMask(0) {}
      BitMask64(ULong64_t bits) : fBitMask(bits) {}
      virtual ~BitMask64() {}

      ULong64_t Bits() const { return fBitMask; }
      void      Clear() { fBitMask = 0; }
      void      ClearBit(UInt_t n) { fBitMask &= SingleBitInverted(n); }
      UInt_t    NBitsSet(UInt_t first=0, UInt_t last=63) const;
      void      SetBit(UInt_t n) { fBitMask |= SingleBit(n); }
      void      SetBits(ULong64_t bits) { fBitMask = bits; }
      Bool_t    TestBit(UInt_t n) const { return (fBitMask & SingleBit(n)); }
      
    protected:
      ULong64_t SingleBit(UInt_t n) const { return (1 << (n)); }
      ULong64_t SingleBitInverted(UInt_t n) const { return ~SingleBit(n); }
    
      ULong64_t fBitMask; //the actual bitmask
                
    ClassDef(BitMask64, 1)
  };
}
#endif
