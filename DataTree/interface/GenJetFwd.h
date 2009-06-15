// $Id:$

#ifndef MITANA_DATATREE_GENJETFWD_H
#define MITANA_DATATREE_GENJETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class GenJet;
  typedef Collection<GenJet>            GenJetCol;
  typedef Array<GenJet>                 GenJetArr;
  typedef ObjArray<GenJet>              GenJetOArr;
}
#endif
