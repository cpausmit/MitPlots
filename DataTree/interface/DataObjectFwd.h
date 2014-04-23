#ifndef MITANA_DATATREE_DATAOBJECTFWD_H
#define MITANA_DATATREE_DATAOBJECTFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class DataObject;
  typedef Collection<DataObject>        DataObjectCol;
  typedef Array<DataObject>             DataObjectArr;
  typedef ObjArray<DataObject>          DataObjectOArr;
}
#endif
