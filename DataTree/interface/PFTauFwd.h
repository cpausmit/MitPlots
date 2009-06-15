// $Id:$

#ifndef MITANA_DATATREE_PFTAUFWD_H
#define MITANA_DATATREE_PFTAUFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PFTau;
  typedef Collection<PFTau>             PFTauCol;
  typedef Array<PFTau>                  PFTauArr;
  typedef ObjArray<PFTau>               PFTauOArr;
}
#endif
