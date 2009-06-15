// $Id:$

#ifndef MITANA_DATATREE_STABLEPARTICLEFWD_H
#define MITANA_DATATREE_STABLEPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class StableParticle;
  typedef Collection<StableParticle>    StableParticleCol;
  typedef Array<StableParticle>         StableParticleArr;
  typedef ObjArray<StableParticle>      StableParticleOArr;
}
#endif
