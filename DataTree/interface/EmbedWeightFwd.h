#ifndef MITANA_DATATREE_EMBEDWEIGHTFWD_H
#define MITANA_DATATREE_EMBEDWEIGHTFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class EmbedWeight;
  typedef Collection<EmbedWeight>       EmbedWeightCol;
  typedef Array<EmbedWeight>            EmbedWeightArr;
  typedef ObjArray<EmbedWeight>         EmbedWeightOArr;
}
#endif
