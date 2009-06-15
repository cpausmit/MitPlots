// $Id:$

#ifndef MITANA_DATATREE_PFMETFWD_H
#define MITANA_DATATREE_PFMETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PFMet;
  typedef Collection<PFMet>             PFMetCol;
  typedef Array<PFMet>                  PFMetArr;
  typedef ObjArray<PFMet>               PFMetOArr;
}
#endif
