//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.14 2008/07/25 11:32:45 bendavid Exp $
//
// BitMask32
//
// Helper class for using UInt_t as a bitmask
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_BITMASK32_H
#define DATATREE_BITMASK32_H
 
#include "Rtypes.h"

namespace mithep 
{
  class BitMask32
  {
    public:
      BitMask32() : fBitMask(0) {}
      BitMask32(UInt_t bits) : fBitMask(bits) {}
      virtual ~BitMask32() {}

      UInt_t  Bits() const { return fBitMask; }
      void    Clear() { fBitMask = 0; }
      void    ClearBit(UInt_t n) { fBitMask &= SingleBitInverted(n); }
      UInt_t  NBitsSet(UInt_t first=0, UInt_t last=31) const;
      void    SetBit(UInt_t n) { fBitMask |= SingleBit(n); }
      void    SetBits(UInt_t bits) { fBitMask = bits; }
      Bool_t  TestBit(UInt_t n) const { return (fBitMask & SingleBit(n)); }
      
    protected:
      UInt_t  SingleBit(UInt_t n) const { return (1 << (n)); }
      UInt_t  SingleBitInverted(UInt_t n) const { return ~SingleBit(n); }
    
      UInt_t  fBitMask; //the actual bitmask
    
    ClassDef(BitMask32, 1)
  };
}
#endif
