#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitAna/DataTree/interface/LHERunInfo.h"

ClassImp(mithep::MCRunInfo)

mithep::MCRunInfo::MCRunInfo() :
  fInternalXSec(-1.),
  fInternalXSecErr(-1.),
  fExternalLOXSec(-1.),
  fExternalLOXSecErr(-1.),
  fExternalNLOXSec(-1.),
  fExternalNLOXSecErr(-1.),
  fLHERunInfoRef()
{
}

mithep::MCRunInfo::~MCRunInfo()
{
}
