//--------------------------------------------------------------------------------------------------
// Types
//
// Here we define additional types.
//
// Authors: C.Loizides, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_TYPES_H
#define MITANA_DATACONT_TYPES_H
 
#include <Rtypes.h>
#include "MitCommon/DataFormats/interface/Types.h"
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"
#include "MitAna/DataCont/interface/NamedFastArrayBasic.h"
#include "MitAna/DataCont/interface/FastArray.h"

namespace mithep
{
  typedef BitMaskT<UChar_t>                BitMask8;
  typedef BitMaskT<UShort_t>               BitMask16;
  typedef BitMaskT<UInt_t>                 BitMask32;
  typedef BitMask<5>                       BitMask40;
  typedef BitMask<6>                       BitMask48;
  typedef BitMask<7>                       BitMask56;
  typedef BitMaskT<ULong64_t>              BitMask64;
  typedef BitMask<16>                      BitMask128;
  typedef BitMask<32>                      BitMask256;
  typedef BitMask<128>                     BitMask1024;

  typedef FastArrayBasic<Double_t>         FArrDouble;
  typedef FastArrayBasic<Double32_t,kTRUE> FArrDouble32;
  typedef FastArrayBasic<Int_t>            FArrInt;
  typedef FastArrayBasic<UInt_t>           FArrUInt;
  typedef FastArrayBasic<Short_t>          FArrShort;
  typedef FastArrayBasic<UShort_t>         FArrUShort;
  typedef FastArrayBasic<Char_t>           FArrChar;
  typedef FastArrayBasic<UChar_t>          FArrUChar;
  typedef FastArrayBasic<Bool_t>           FArrBool;

  typedef NamedFastArrayBasic<Double_t>         NFArrDouble;
  typedef NamedFastArrayBasic<Double32_t,kTRUE> NFArrDouble32;
  typedef NamedFastArrayBasic<Int_t>            NFArrInt;
  typedef NamedFastArrayBasic<UInt_t>           NFArrUInt;
  typedef NamedFastArrayBasic<Short_t>          NFArrShort;
  typedef NamedFastArrayBasic<UShort_t>         NFArrUShort;
  typedef NamedFastArrayBasic<Char_t>           NFArrChar;
  typedef NamedFastArrayBasic<UChar_t>          NFArrUChar;
  typedef NamedFastArrayBasic<Bool_t>           NFArrBool;

  typedef FastArray<TObjString>            FArrObjString;
}
#endif
