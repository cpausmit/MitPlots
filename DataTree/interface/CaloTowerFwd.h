// $Id:$

#ifndef MITANA_DATATREE_CALOTOWERFWD_H
#define MITANA_DATATREE_CALOTOWERFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CaloTower;
  typedef Collection<CaloTower>         CaloTowerCol;
  typedef Array<CaloTower>              CaloTowerArr; 
  typedef ObjArray<CaloTower>           CaloTowerOArr; 
}
#endif
