#ifndef MITANA_DATATREE_DCASIGFWD_H
#define MITANA_DATATREE_DCASIGFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class DCASig;
  typedef Collection<DCASig>            DCASigCol;
  typedef Array<DCASig>                 DCASigArr;
  typedef ObjArray<DCASig>              DCASigOArr;
}
#endif

