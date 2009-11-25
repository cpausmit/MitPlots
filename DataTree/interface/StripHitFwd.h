// $Id: StriphitFwd.h,v 1.1 2009/09/25 08:39:10 loizides Exp $

#ifndef MITANA_DATATREE_STRIPHITFWD_H
#define MITANA_DATATREE_STRIPHITFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class StripHit;
  typedef Collection<StripHit>            StripHitCol;
  typedef Array<StripHit>                 StripHitArr;
  typedef ObjArray<StripHit>              StripHitOArr;
}
#endif
