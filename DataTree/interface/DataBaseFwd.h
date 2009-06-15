// $Id:$

#ifndef MITANA_DATATREE_DATABASEFWD_H
#define MITANA_DATATREE_DATABASEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class DataBase;
  typedef Collection<DataBase>          DataBaseCol;
  typedef Array<DataBase>               DataBaseArr;
  typedef ObjArray<DataBase>            DataBaseOArr;
}
#endif
