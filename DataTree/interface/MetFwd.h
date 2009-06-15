// $Id:$

#ifndef MITANA_DATATREE_METFWD_H
#define MITANA_DATATREE_METFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Met;
  typedef Collection<Met>               MetCol;
  typedef Array<Met>                    MetArr;
  typedef ObjArray<Met>                 MetOArr;
}
#endif
