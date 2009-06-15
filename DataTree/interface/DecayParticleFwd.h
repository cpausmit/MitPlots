// $Id:$

#ifndef MITANA_DATATREE_DECAYPARTICLEFWD_H
#define MITANA_DATATREE_DECAYPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class DecayParticle;
  typedef Collection<DecayParticle>     DecayParticleCol;
  typedef Array<DecayParticle>          DecayParticleArr;
  typedef ObjArray<DecayParticle>       DecayParticleOArr;
}
#endif
