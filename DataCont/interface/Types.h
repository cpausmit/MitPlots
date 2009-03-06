//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.2 2009/03/03 18:01:34 bendavid Exp $
//
// Types
//
// Here we define additional types.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_TYPES_H
#define MITANA_DATACONT_TYPES_H
 
#include <Rtypes.h>
#include "MitCommon/DataFormats/interface/Types.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"

namespace mithep
{
  typedef FastArrayBasic<Double_t>         FArrDouble;
  typedef FastArrayBasic<Double32_t,kTRUE> FArrDouble32;
  typedef FastArrayBasic<Int_t>            FArrInt;
  typedef FastArrayBasic<UInt_t>           FArrUInt;
}
#endif
