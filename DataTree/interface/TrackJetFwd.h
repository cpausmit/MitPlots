// $Id: TrackJetFwd.h,v 1.1 2009/06/15 15:00:13 loizides Exp $

#ifndef MITANA_DATATREE_TRACKJETFWD_H
#define MITANA_DATATREE_TRACKJETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TrackJet;
  typedef Collection<TrackJet>             TrackJetCol;
  typedef Array<TrackJet>                  TrackJetArr;
  typedef ObjArray<TrackJet>               TrackJetOArr;
}
#endif
