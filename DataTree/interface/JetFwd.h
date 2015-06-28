#ifndef MITANA_DATATREE_JETFWD_H
#define MITANA_DATATREE_JETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Jet;
  typedef Collection<Jet>               JetCol;
  typedef Array<Jet>                    JetArr;
  typedef ObjArray<Jet>                 JetOArr;
}
#endif
