// $Id:$

#ifndef MITANA_DATATREE_PFJETFWD_H
#define MITANA_DATATREE_PFJETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PFJet;
  typedef Collection<PFJet>             PFJetCol;
  typedef Array<PFJet>                  PFJetArr;
  typedef ObjArray<PFJet>               PFJetOArr;
}
#endif
