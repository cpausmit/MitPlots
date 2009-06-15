// $Id:$

#ifndef MITANA_DATATREE_MCPARTICLEFWD_H
#define MITANA_DATATREE_MCPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class MCParticle;
  typedef Collection<MCParticle>        MCParticleCol;
  typedef Array<MCParticle>             MCParticleArr;
  typedef ObjArray<MCParticle>          MCParticleOArr;
}
#endif
