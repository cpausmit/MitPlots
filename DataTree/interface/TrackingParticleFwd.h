// $Id: MCParticleFwd.h,v 1.1 2009/06/15 15:00:13 loizides Exp $

#ifndef MITANA_DATATREE_TRACKINGPARTICLEFWD_H
#define MITANA_DATATREE_TRACKINGPARTICLEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class TrackingParticle;
  typedef Collection<TrackingParticle>  TrackingParticleCol;
  typedef Array<TrackingParticle>       TrackingParticleArr;
  typedef ObjArray<TrackingParticle>    TrackingParticleOArr;
}
#endif
