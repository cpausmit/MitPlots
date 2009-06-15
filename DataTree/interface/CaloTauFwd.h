// $Id:$

#ifndef MITANA_DATATREE_CALOTAUFWD_H
#define MITANA_DATATREE_CALOTAUFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CaloTau;
  typedef Collection<CaloTau>           CaloTauCol;
  typedef Array<CaloTau>                CaloTauArr;
  typedef ObjArray<CaloTau>             CaloTauOArr;
}
#endif
