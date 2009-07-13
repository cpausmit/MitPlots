// $Id: TriggerObjectFwd.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTFWD_H
#define MITANA_DATATREE_TRIGGEROBJECTFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TriggerObject;
  typedef Collection<TriggerObject>     TriggerObjectCol;
  typedef Array<TriggerObject>          TriggerObjectArr;
  typedef ObjArray<TriggerObject>       TriggerObjectOArr;
}
#endif
