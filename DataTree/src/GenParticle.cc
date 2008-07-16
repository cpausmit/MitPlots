// $Id: GenParticle.cc,v 1.2 2008/07/15 11:31:08 loizides Exp $

#include "MitAna/DataTree/interface/GenParticle.h"

ClassImp(mithep::GenParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t GenParticle::Charge() const
{
  // Get Charge from Pdg Lookup

  TParticlePDG* pdgEntry = PdgEntry();
  if (pdgEntry)
    return pdgEntry->Charge()/3.0;
  else {
    return -99.0;
    printf("Pdg Code %i not found in table, returning Charge=-99.0", fPdgId);
  }
}

//--------------------------------------------------------------------------------------------------
void GenParticle::Print(Option_t */*opt*/) const
{
  printf("id=%5d st=%3d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
         PdgId(), Status(), Px(), Py(), Pz(), E());
}
