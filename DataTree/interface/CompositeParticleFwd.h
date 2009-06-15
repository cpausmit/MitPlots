// $Id:$

#ifndef MITANA_DATATREE_COMPOSITEPARTICLEFWD_H
#define MITANA_DATATREE_COMPOSITEPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CompositeParticle;
  typedef Collection<CompositeParticle> CompositeParticleCol;
  typedef Array<CompositeParticle>      CompositeParticleArr;
  typedef ObjArray<CompositeParticle>   CompositeParticleOArr;
}
#endif
