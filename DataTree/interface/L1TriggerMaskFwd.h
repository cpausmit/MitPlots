// $Id: TriggerMaskFwd.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_L1TRIGGERMASKFWD_H
#define MITANA_DATATREE_L1TRIGGERMASKFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class L1TriggerMask;
  typedef Collection<L1TriggerMask>       L1TriggerMaskCol;
  typedef Array<L1TriggerMask>            L1TriggerMaskArr;
  typedef ObjArray<L1TriggerMask>         L1TriggerMaskOArr;
}
#endif
