// $Id:$

#ifndef MITANA_DATATREE_EVENTHEADERFWD_H
#define MITANA_DATATREE_EVENTHEADERFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class EventHeader;
  typedef Collection<EventHeader>       EventHeaderCol;
  typedef Array<EventHeader>            EventHeaderArr;
  typedef ObjArray<EventHeader>         EventHeaderOArr;
}
#endif
