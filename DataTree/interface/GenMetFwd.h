// $Id: GenMetFwd.h,v 1.1 2009/06/15 15:00:11 loizides Exp $

#ifndef MITANA_DATATREE_GENMETFWD_H
#define MITANA_DATATREE_GENMETFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class GenMet;
  typedef Collection<GenMet>           GenMetCol;
  typedef Array<GenMet>                GenMetArr;
  typedef ObjArray<GenMet>             GenMetOArr;
}
#endif
