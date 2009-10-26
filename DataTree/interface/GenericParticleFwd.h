// $Id: GenericParticleFwd.h,v 1.1 2009/06/15 15:00:12 loizides Exp $

#ifndef MITANA_DATATREE_GENERICPARTICLEFWD_H
#define MITANA_DATATREE_GENERICPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class GenericParticle;
  typedef Collection<GenericParticle>   GenericParticleCol;
  typedef Array<GenericParticle>        GenericParticleArr;
  typedef ObjArray<GenericParticle>     GenericParticleOArr;
}
#endif
