// $Id: VertexFwd.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_PIXELHITFWD_H
#define MITANA_DATATREE_PIXELHITFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PixelHit;
  typedef Collection<PixelHit>            PixelHitCol;
  typedef Array<PixelHit>                 PixelHitArr;
  typedef ObjArray<PixelHit>              PixelHitOArr;
}
#endif
