//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.17 2008/09/05 01:21:45 loizides Exp $
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
#include <Math/GenVector/LorentzVector.h>
#include <Math/Point3Dfwd.h>
#include <Math/SMatrix.h>
#include "MitCommon/DataFormats/interface/Types.h"
#include "MitAna/DataTree/interface/BitMask.h"

namespace mithep
{
  //typedef BitMask<4> BitMask32;
  //typedef BitMask<8> BitMask64;
  typedef BitMask<32> BitMask256;
}
#endif
