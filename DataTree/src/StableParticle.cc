// $Id: StableParticle.cc,v 1.2 2009/02/18 15:38:55 loizides Exp $

#include "MitAna/DataTree/interface/StableParticle.h"

ClassImp(mithep::StableParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
TParticlePDG *mithep::StableParticle::PdgEntry() const 
{ 
  // Return entry to pdg database for the particle.

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}
