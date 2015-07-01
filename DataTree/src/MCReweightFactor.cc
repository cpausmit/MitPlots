#include "MitAna/DataTree/interface/MCReweightFactor.h"

ClassImp(mithep::MCReweightFactor)

namespace mithep {

  mithep::MCReweightFactor::MCReweightFactor() :
    fId(),
    fWeightGroupCombination(),
    fWeightGroupType(),
    fScaleFactor(1.)
  {
  }

}
