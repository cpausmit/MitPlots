// $Id: TriggerObjectFwd.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTBASEFWD_H
#define MITANA_DATATREE_TRIGGEROBJECTBASEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TriggerObjectBase;
  typedef Collection<TriggerObjectBase> TriggerObjectBaseCol;
  typedef Array<TriggerObjectBase>      TriggerObjectBaseArr;
  typedef ObjArray<TriggerObjectBase>   TriggerObjectBaseOArr;
}
#endif
