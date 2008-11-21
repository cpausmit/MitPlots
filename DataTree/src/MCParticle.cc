// $Id: MCParticle.cc,v 1.1 2008/07/25 11:32:45 bendavid Exp $

#include "MitAna/DataTree/interface/MCParticle.h"

ClassImp(mithep::MCParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t MCParticle::Charge() const
{
  // Get charge from pdg lookup/

  TParticlePDG* pdgEntry = PdgEntry();
  if (pdgEntry)
    return pdgEntry->Charge()/3.0;
  else {
    Error("Charge", "Pdg code %i not found in table, returning charge=-99.0", fPdgId);
    return -99.0;
  }
}

//--------------------------------------------------------------------------------------------------
void MCParticle::Print(Option_t *opt) const
{
  // Print particle kinematics. In case option "l" is given then also print info about daughters.

  printf("id=%5d st=%2d nd=%3d gen=%d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
         PdgId(), Status(), NDaughters(), IsGenerated(), Px(), Py(), Pz(), E());

  if (opt && opt[0]=='l') {
    for (UInt_t i=0; i<NDaughters(); ++i) {
      printf("  %2d -> id=%5d st=%2d gen=%d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
             i, Daughter(i)->PdgId(), Daughter(i)->Status(), Daughter(i)->IsGenerated(),
             Daughter(i)->Px(), Daughter(i)->Py(), Daughter(i)->Pz(), Daughter(i)->E());
    }
  }
}
