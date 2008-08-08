// $ Exp $

#include "MitAna/DataTree/interface/BasicCluster.h"

ClassImp(mithep::BasicCluster)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void BasicCluster::Print(Option_t *opt) const
{
  printf("px=%.3f py=%.3f pz=%.3f e=%.3f\n", X(), Y(), Z(), Energy());
}
