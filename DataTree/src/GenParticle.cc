// $Id: GenParticle.cc,v 1.1 2008/06/04 09:08:36 loizides Exp $

#include "MitAna/DataTree/interface/GenParticle.h"

ClassImp(mithep::GenParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void GenParticle::Print(Option_t */*opt*/) const
{
  printf("id=%5d st=%3d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
         PdgId(), Status(), Px(), Py(), Pz(), E());
}
