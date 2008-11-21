// $Id: Particle.cc,v 1.2 2008/07/15 11:31:08 loizides Exp $

#include "MitAna/DataTree/interface/Particle.h"

ClassImp(mithep::Particle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void Particle::Print(Option_t *opt) const
{
  // Print particle kinematics.

  printf("px=%.3f py=%.3f pz=%.3f e=%.3f\n", Px(), Py(), Pz(), E());
}
