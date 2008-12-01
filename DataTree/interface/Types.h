//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.20 2008/09/27 06:12:59 loizides Exp $
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
#include "MitAna/DataCont/interface/Vector.h"

namespace mithep
{
  typedef BitMask<1>  BitMask8;
  typedef BitMask<2>  BitMask16;
  typedef BitMask<4>  BitMask32;
  typedef BitMask<5>  BitMask40;
  typedef BitMask<6>  BitMask48;
  typedef BitMask<7>  BitMask56;
  typedef BitMask<8>  BitMask64;
  typedef BitMask<16> BitMask128;
  typedef BitMask<32> BitMask256;

  typedef Collection<std::string>     StringCol;
  typedef mithep::Vector<std::string> StringVec;
}
#endif
