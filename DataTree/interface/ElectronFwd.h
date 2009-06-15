// $Id:$

#ifndef MITANA_DATATREE_ELECTRONFWD_H
#define MITANA_DATATREE_ELECTRONFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Electron;
  typedef Collection<Electron>          ElectronCol;
  typedef Array<Electron>               ElectronArr;
  typedef ObjArray<Electron>            ElectronOArr;
}
#endif
