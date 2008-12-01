// $Id: Particle.cc,v 1.3 2008/11/21 20:15:02 loizides Exp $

#include "MitAna/DataTree/interface/Particle.h"

ClassImp(mithep::Particle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void Particle::Print(Option_t */*opt*/) const
{
  // Print particle kinematics.

  printf("px=%.3f py=%.3f pz=%.3f e=%.3f\n", Px(), Py(), Pz(), E());
}
