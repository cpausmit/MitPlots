// $Id:$

#ifndef MITANA_DATATREE_BEAMSPOTFWD_H
#define MITANA_DATATREE_BEAMSPOTFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class BeamSpot;
  typedef Collection<BeamSpot>          BeamSpotCol;
  typedef Array<BeamSpot>               BeamSpotArr;
  typedef ObjArray<BeamSpot>            BeamSpotOArr;
}
#endif
