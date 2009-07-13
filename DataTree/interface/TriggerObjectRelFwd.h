// $Id: TriggerObjectFwd.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTRELFWD_H
#define MITANA_DATATREE_TRIGGEROBJECTRELFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TriggerObjectRel;
  typedef Collection<TriggerObjectRel>  TriggerObjectRelCol;
  typedef Array<TriggerObjectRel>       TriggerObjectRelArr;
  typedef ObjArray<TriggerObjectRel>    TriggerObjectRelOArr;
}
#endif
