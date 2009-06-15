// $Id:$

#ifndef MITANA_DATATREE_CALOMETFWD_H
#define MITANA_DATATREE_CALOMETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CaloMet;
  typedef Collection<CaloMet>           CaloMetCol;
  typedef Array<CaloMet>                CaloMetArr;
  typedef ObjArray<CaloMet>             CaloMetOArr;
}
#endif
