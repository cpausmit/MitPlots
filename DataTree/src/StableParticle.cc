// $Id: Electron.cc,v 1.1 2008/06/05 16:03:35 bendavid Exp $

#include "MitAna/DataTree/interface/StableParticle.h"

ClassImp(mithep::StableParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t StableParticle::Mass() const
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
