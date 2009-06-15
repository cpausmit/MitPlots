// $Id:$

#ifndef MITANA_DATATREE_TAUFWD_H
#define MITANA_DATATREE_TAUFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Tau;
  typedef Collection<Tau>               TauCol;
  typedef Array<Tau>                    TauArr;
  typedef ObjArray<Tau>                 TauOArr;
}
#endif
