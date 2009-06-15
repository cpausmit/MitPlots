// $Id:$

#ifndef MITANA_DATATREE_DAUGHTERDATAFWD_H
#define MITANA_DATATREE_DAUGHTERDATAFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class DaughterData;
  typedef Collection<DaughterData>        DaughterDataCol;
  typedef ObjArray<DaughterData>          DaughterDataOArr;
}
#endif
