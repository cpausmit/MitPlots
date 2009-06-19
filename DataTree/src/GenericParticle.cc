// $Id: GenericParticle.cc,v 1.2 2009/04/09 11:24:46 loizides Exp $

#include "MitAna/DataTree/interface/GenericParticle.h"

ClassImp(mithep::GenericParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void GenericParticle::Print(Option_t */*opt*/) const
{
  // Print particle kinematics.

  printf("pt=%.3f eta=%.3f phi=%.3f c=%.1f t=%d\n", Pt(), Eta(), Phi(), Charge(), ObjType());
}
