// $Id: PileupEnergyDensityFwd.h,v 1.1 2009/06/15 15:00:11 loizides Exp $

#ifndef MITANA_DATATREE_PILEUPENERGYDENSITYFWD_H
#define MITANA_DATATREE_PILEUPENERGYDENSITYFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PileupEnergyDensity;
  typedef Collection<PileupEnergyDensity>          PileupEnergyDensityCol;
  typedef Array<PileupEnergyDensity>               PileupEnergyDensityArr;
  typedef ObjArray<PileupEnergyDensity>            PileupEnergyDensityOArr;
}
#endif
