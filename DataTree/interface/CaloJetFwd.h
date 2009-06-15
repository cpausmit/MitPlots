// $Id:$

#ifndef MITANA_DATATREE_CALOJETFWD_H
#define MITANA_DATATREE_CALOJETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CaloJet;
  typedef Collection<CaloJet>           CaloJetCol;
  typedef Array<CaloJet>                CaloJetArr;
  typedef ObjArray<CaloJet>             CaloJetOArr;
}
#endif
