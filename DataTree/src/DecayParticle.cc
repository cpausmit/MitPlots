// $Id: DecayParticle.cc,v 1.5 2008/10/29 17:02:55 bendavid Exp $

#include "MitAna/DataTree/interface/DecayParticle.h"

ClassImp(mithep::DecayParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Bool_t DecayParticle::HasDaughter(const Particle* p) const 
{
  // Return true if given particle is among daughters.

  if(!p) return kFALSE;

  if (!NDaughters())
    return kFALSE;

  for (UInt_t i=0; i<NDaughters(); ++i)
    if (Daughter(i)==p)
      return kTRUE;
  
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t DecayParticle::HasCommonDaughter(const DecayParticle *p) const 
{
  // Return true if a common daughter exists.

  if(!p) return kFALSE;

  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (HasDaughter(p->Daughter(i)))
      return kTRUE;
	
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t DecayParticle::HasSameDaughters(const DecayParticle* p) const 
{
  // Return true if daughters are the same.

  if(!p) return kFALSE;

  if (NDaughters()!= p->NDaughters())
    return kFALSE;
		
  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (!HasDaughter(p->Daughter(i))) 
        return kFALSE;
	
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
Double_t DecayParticle::PdgMass() const
{
  // Get mass from pdg lookup.

  TParticlePDG* pdgEntry = ParticlePdgEntry();
  if (pdgEntry)
    return pdgEntry->Mass();
  else {
    Error("PdgMass", 
          "Absolute pdg code %i not found in table, returning mass=-99.0 GeV", fAbsPdgId);
    return -99.0;
  }
}
