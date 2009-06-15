// $Id:$

#ifndef MITANA_DATATREE_MUONFWD_H
#define MITANA_DATATREE_MUONFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Muon;
  typedef Collection<Muon>              MuonCol;
  typedef Array<Muon>                   MuonArr;
  typedef ObjArray<Muon>                MuonOArr;
}
#endif
