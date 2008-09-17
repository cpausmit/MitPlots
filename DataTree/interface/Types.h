//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.18 2008/09/10 03:33:27 loizides Exp $
//
// Types
//
// Here we define additional types.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TYPES_H
#define MITANA_DATATREE_TYPES_H
 
#include <Rtypes.h>
#include "MitCommon/DataFormats/interface/Types.h"
#include "MitAna/DataTree/interface/BitMask.h"

namespace mithep
{
  typedef BitMask<1>  BitMask8;
  typedef BitMask<2>  BitMask16;
  typedef BitMask<4>  BitMask32;
  typedef BitMask<5>  BitMask40;
  typedef BitMask<6>  BitMask48;
  typedef BitMask<7>  BitMask56;
  typedef BitMask<8>  BitMask64;
  typedef BitMask<32> BitMask256;
}
#endif
