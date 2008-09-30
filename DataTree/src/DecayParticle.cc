// $Id: DecayParticle.cc,v 1.3 2008/07/29 12:29:47 bendavid Exp $

#include "MitAna/DataTree/interface/DecayParticle.h"

ClassImp(mithep::DecayParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t DecayParticle::Charge() const 
{
  // Return sum of charge of daughter particles.

  Double_t charge = 0;
  for (UInt_t i=0; i<NDaughters(); ++i)
    charge += DaughterDat(i)->Charge();
  
  return charge;
}

//--------------------------------------------------------------------------------------------------
Double_t DecayParticle::PdgMass() const
{
  // Get Mass from Pdg Lookup

  TParticlePDG* pdgEntry = ParticlePdgEntry();
  if (pdgEntry)
    return pdgEntry->Mass();
  else {
    return -99.0;
    printf("Absolute Pdg Code %i not found in table, returning Mass=-99.0 GeV", fAbsPdgId);
  }
}
