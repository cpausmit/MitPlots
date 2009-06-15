// $Id:$

#ifndef MITANA_DATATREE_TRIGGEROBJECTFWD_H
#define MITANA_DATATREE_TRIGGEROBJECTFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TriggerObjectRel;
  class TriggerObjectBase;
  class TriggerObject;
  typedef Collection<TriggerObjectRel>  TriggerObjectRelCol;
  typedef Collection<TriggerObjectBase> TriggerObjectBaseCol;
  typedef Collection<TriggerObject>     TriggerObjectCol;
  typedef Array<TriggerObjectRel>       TriggerObjectRelArr;
  typedef Array<TriggerObjectBase>      TriggerObjectBaseArr;
  typedef Array<TriggerObject>          TriggerObjectArr;
  typedef ObjArray<TriggerObjectRel>    TriggerObjectRelOArr;
  typedef ObjArray<TriggerObjectBase>   TriggerObjectBaseOArr;
  typedef ObjArray<TriggerObject>       TriggerObjectOArr;
}
#endif
