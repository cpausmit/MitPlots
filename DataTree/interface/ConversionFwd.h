// $Id:$

#ifndef MITANA_DATATREE_CONVERSIONFWD_H
#define MITANA_DATATREE_CONVERSIONFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Conversion;
  typedef Collection<Conversion>        ConversionCol;
  typedef Array<Conversion>             ConversionArr;
  typedef ObjArray<Conversion>          ConversionOArr;
}
#endif
