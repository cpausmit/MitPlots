// $Id:$

#ifndef MITANA_DATATREE_CHARGEDPARTICLEFWD_H
#define MITANA_DATATREE_CHARGEDPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class ChargedParticle;
  typedef Collection<ChargedParticle>   ChargedParticleCol;
  typedef Array<ChargedParticle>        ChargedParticleArr;
  typedef ObjArray<ChargedParticle>     ChargedParticleOArr;
}
#endif
