// $Id:$

#ifndef MITANA_DATATREE_TRIGGERMASKFWD_H
#define MITANA_DATATREE_TRIGGERMASKFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TriggerMask;
  typedef Collection<TriggerMask>       TriggerMaskCol;
  typedef Array<TriggerMask>            TriggerMaskArr;
  typedef ObjArray<TriggerMask>         TriggerMaskOArr;
}
#endif
