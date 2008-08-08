// $Id: $

#include "MitAna/DataTree/interface/SuperCluster.h"

ClassImp(mithep::SuperCluster)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void SuperCluster::Print(Option_t *opt) const
{
  printf("px=%.3f py=%.3f pz=%.3f e=%.3f\n", X(), Y(), Z(), Energy());
}
