//--------------------------------------------------------------------------------------------------
// $Id: BitMask32.h,v 1.2 2008/08/29 01:52:21 loizides Exp $
//
// BitMask
//
// Helper class implementing a Nx8 bit bitmask.
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_BITMASK_H
#define DATATREE_BITMASK_H
 
#include <Rtypes.h>

namespace mithep
{
  template<UInt_t N>
  class BitMask
  {
    public:
      BitMask() { Clear(); }
      BitMask(const Char_t *bits) { SetBits(bits); }
      virtual ~BitMask() {}

      const Char_t *Bits()                const { return fBitMask; }
      void          Clear()                     { memset(fBitMask,0,N); }
      void          ClearBit(UInt_t n)          { SetBit(n,0); }
      UInt_t        NBitsSet(UInt_t first=0, UInt_t last=N*8) const;
      void          SetBit(UInt_t n, Bool_t b=1);
      void          SetBits(const Char_t *bits) { strncpy(fBitMask,bits,N); }
      Bool_t        TestBit(UInt_t n)     const;
      
    protected:
      Char_t        fBitMask[N]; //the actual bitmask
    
    ClassDefT(BitMask, 1)
  };
}

//--------------------------------------------------------------------------------------------------
template<UInt_t N>
inline void mithep::BitMask<N>::SetBit(UInt_t n, Bool_t b)
{
  // Set nth bit to given value.

  if(n>=N*8) return;

  UInt_t loc = n/8;
  UChar_t bit = n%8;
  if (b)
    fBitMask[loc] |= (1<<bit);
  else
    fBitMask[loc] &= (0xFF ^ (1<<bit));
}

//--------------------------------------------------------------------------------------------------
template<UInt_t N>
UInt_t mithep::BitMask<N>::NBitsSet(UInt_t first, UInt_t last) const
{
  // Count number of bits which are set.

  UInt_t numBits = 0;
  for (UInt_t i=first; i<=last; i++)
    numBits += TestBit(i);
    
  return numBits;
}

//--------------------------------------------------------------------------------------------------
template<UInt_t N>
inline Bool_t mithep::BitMask<N>::TestBit(UInt_t n) const
{
  // Return true if nth bit is set.

  if(n>=N*8) return 0;

  UInt_t loc = n/8;
  UChar_t bit = n%8;
  Char_t val = fBitMask[loc];
  Bool_t result = (val & (1<<bit)) != 0;
  return result;
}
#endif
