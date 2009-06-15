// $Id:$

#ifndef MITANA_DATATREE_PFCANDIDATEFWD_H
#define MITANA_DATATREE_PFCANDIDATEFWD_H

#include "MitAna/DataCont/interface/CollectionFwd.h"
#include "MitAna/DataCont/interface/ArrayFwd.h"
#include "MitAna/DataCont/interface/ObjArrayFwd.h"

namespace mithep {
  class PFCandidate;
  typedef Collection<PFCandidate>       PFCandidateCol;
  typedef Array<PFCandidate>            PFCandidateArr;
  typedef ObjArray<PFCandidate>         PFCandidateOArr;
}
#endif
