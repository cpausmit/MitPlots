// $Id:$

#ifndef MITANA_DATATREE_TRACKFWD_H
#define MITANA_DATATREE_TRACKFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Track;
  typedef Collection<Track>             TrackCol;
  typedef Array<Track>                  TrackArr;
  typedef ObjArray<Track>               TrackOArr;
}
#endif
