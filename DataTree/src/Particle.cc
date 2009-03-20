// $Id: Particle.cc,v 1.4 2008/12/01 17:30:01 loizides Exp $

#include "MitAna/DataTree/interface/Particle.h"

ClassImp(mithep::Particle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void Particle::Print(Option_t */*opt*/) const
{
  // Print particle kinematics.

  printf("pt=%.3f eta=%.3f phi=%.3f\n", Pt(), Eta(), Phi());
}
