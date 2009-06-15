// $Id:$

#ifndef MITANA_DATATREE_COMPOUNDPARTICLEFWD_H
#define MITANA_DATATREE_COMPOUNDPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class CompoundParticle;
  typedef Collection<CompoundParticle> CompoundParticleCol;
  typedef Array<CompoundParticle>      CompoundParticleArr;
  typedef ObjArray<CompoundParticle>   CompoundParticleOArr;
}
#endif
