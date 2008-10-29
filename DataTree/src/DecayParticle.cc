// $Id: DecayParticle.cc,v 1.4 2008/09/30 12:53:59 bendavid Exp $

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
