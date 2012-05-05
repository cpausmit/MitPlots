// $Id: PSClusterFwd.h,v 1.1 2009/06/15 15:00:11 loizides Exp $

#ifndef MITANA_DATATREE_PSCLUSTERFWD_H
#define MITANA_DATATREE_PSCLUSTERFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PsCluster;
  typedef Collection<PsCluster>      PsClusterCol;
  typedef Array<PsCluster>           PsClusterArr;
  typedef ObjArray<PsCluster>        PsClusterOArr;
}
#endif
