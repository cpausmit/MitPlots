// $Id: Particle.cc,v 1.1 2008/05/27 19:24:49 loizides Exp $

#include "MitAna/DataTree/interface/Particle.h"

ClassImp(mithep::Particle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void Particle::Print(Option_t *opt) const
{
  printf("px=%.3f py=%.3f pz=%.3f e=%.3f\n", Px(), Py(), Pz(), E());
}
