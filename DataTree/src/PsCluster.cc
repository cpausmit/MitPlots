// $Id: PSCluster.cc,v 1.3 2009/03/20 18:23:27 loizides Exp $

#include "MitAna/DataTree/interface/PsCluster.h"

ClassImp(mithep::PsCluster)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void PsCluster::Print(Option_t */*opt*/) const
{
  // Print some info about the cluster.

  printf("energy=%.3f eta=%.3f phi=%.3f\n", Energy(), Eta(), Phi());
}
