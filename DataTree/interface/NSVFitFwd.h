// $Id: NSVFitFwd.h,v 1.1 2009/06/15 15:00:13 loizides Exp $

#ifndef MITANA_DATATREE_NSVFITFWD_H
#define MITANA_DATATREE_NSVFITFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class NSVFit;
  typedef Collection<NSVFit>               NSVFitCol;
  typedef Array<NSVFit>                    NSVFitArr;
  typedef ObjArray<NSVFit>                 NSVFitOArr;
}
#endif
