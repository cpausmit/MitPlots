// $Id:$

#ifndef MITANA_DATATREE_BASICCLUSTERFWD_H
#define MITANA_DATATREE_BASICCLUSTERFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class BasicCluster;
  typedef Collection<BasicCluster>      BasicClusterCol;
  typedef Array<BasicCluster>           BasicClusterArr;
  typedef ObjArray<BasicCluster>        BasicClusterOArr;
}
#endif
