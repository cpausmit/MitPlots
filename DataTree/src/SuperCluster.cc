// $Id: SuperCluster.cc,v 1.2 2009/03/18 15:44:32 loizides Exp $

#include "MitAna/DataTree/interface/SuperCluster.h"

ClassImp(mithep::SuperCluster)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void SuperCluster::Print(Option_t */*opt*/) const
{
  // Print info about the cluster.

  printf("energy=%.3f eta=%.3f phi=%.3f\n", Energy(), Eta(), Phi());
}
