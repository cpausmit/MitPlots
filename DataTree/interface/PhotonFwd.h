#ifndef MITANA_DATATREE_PHOTONFWD_H
#define MITANA_DATATREE_PHOTONFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Photon;
  typedef Collection<Photon>            PhotonCol;
  typedef Array<Photon>                 PhotonArr;
  typedef ObjArray<Photon>              PhotonOArr;
}
#endif
