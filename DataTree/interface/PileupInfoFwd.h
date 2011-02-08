// $Id: MetFwd.h,v 1.1 2009/06/15 15:00:13 loizides Exp $

#ifndef MITANA_DATATREE_PILEUPINFOFWD_H
#define MITANA_DATATREE_PILEUPINFOFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PileupInfo;
  typedef Collection<PileupInfo>               PileupInfoCol;
  typedef Array<PileupInfo>                    PileupInfoArr;
  typedef ObjArray<PileupInfo>                 PileupInfoOArr;
}
#endif
