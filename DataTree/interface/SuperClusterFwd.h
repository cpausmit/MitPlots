// $Id:$

#ifndef MITANA_DATATREE_SUPERCLUSTERFWD_H
#define MITANA_DATATREE_SUPERCLUSTERFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class SuperCluster;
  typedef Collection<SuperCluster>      SuperClusterCol;
  typedef Array<SuperCluster>           SuperClusterArr;
  typedef ObjArray<SuperCluster>        SuperClusterOArr;
}
#endif
