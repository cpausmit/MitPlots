// $Id:$

#ifndef MITANA_DATATREE_PARTICLEFWD_H
#define MITANA_DATATREE_PARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class Particle;
  typedef Collection<Particle>          ParticleCol;
  typedef ObjArray<Particle>            ParticleOArr;
}
#endif
