// $Id:$

#ifndef MITANA_DATATREE_VERTEXFWD_H
#define MITANA_DATATREE_VERTEXFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Vertex;
  typedef Collection<Vertex>            VertexCol;
  typedef Array<Vertex>                 VertexArr;
  typedef ObjArray<Vertex>              VertexOArr;
}
#endif
