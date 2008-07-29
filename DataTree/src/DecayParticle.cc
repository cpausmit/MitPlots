// $Id: DecayParticle.cc,v 1.2 2008/07/03 08:22:18 loizides Exp $

#include "MitAna/DataTree/interface/DecayParticle.h"

ClassImp(mithep::DecayParticle)

using namespace mithep;

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
