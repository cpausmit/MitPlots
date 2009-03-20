// $Id:$

#include "MitAna/DataTree/interface/BasicCluster.h"

ClassImp(mithep::BasicCluster)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void BasicCluster::Print(Option_t */*opt*/) const
{
  // Print some info about the cluster.

  printf("energy=%.3f eta=%.3f phi=%.3f\n", Energy(), Eta(), Phi());
}
