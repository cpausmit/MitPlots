// $Id:$

#ifndef MITANA_DATATREE_STABLEDATAFWD_H
#define MITANA_DATATREE_STABLEDATAFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class StableData;
  typedef Collection<StableData>        StableDataCol;
  typedef Array<StableData>             StableDataArr;
  typedef ObjArray<StableData>          StableDataOArr;
}
#endif
