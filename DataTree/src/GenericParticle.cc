// $Id: GenericParticle.cc,v 1.5 2009/03/20 18:23:27 loizides Exp $

#include "MitAna/DataTree/interface/GenericParticle.h"

ClassImp(mithep::GenericParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void GenericParticle::Print(Option_t */*opt*/) const
{
  // Print particle kinematics.

  printf("pt=%.3f eta=%.3f phi=%.3f\n", Pt(), Eta(), Phi());
}
