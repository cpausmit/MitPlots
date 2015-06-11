#ifndef MITANA_DATATREE_BASEVERTEXFWD_H
#define MITANA_DATATREE_BASEVERTEXFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class BaseVertex;
  typedef Collection<BaseVertex>        BaseVertexCol;
  typedef Array<BaseVertex>             BaseVertexArr;
  typedef ObjArray<BaseVertex>          BaseVertexOArr;
}
#endif
