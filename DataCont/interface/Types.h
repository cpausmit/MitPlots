//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.22 2009/03/02 12:36:04 loizides Exp $
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
  typedef FastArrayBasic<Double_t>    FArrDouble;
  typedef FastArrayBasic<Double32_t>  FArrDouble32;
  typedef FastArrayBasic<Int_t>       FArrInt;
  typedef FastArrayBasic<UInt_t>      FArrUInt;
}
#endif
