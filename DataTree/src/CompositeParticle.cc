// $Id: CompositeParticle.cc,v 1.6 2009/02/18 08:18:36 bendavid Exp $

#include "MitAna/DataTree/interface/CompositeParticle.h"

ClassImp(mithep::CompositeParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Bool_t CompositeParticle::HasDaughter(const Particle* p) const 
{
  // Return true if given particle is among daughters.

  if(!p) return kFALSE;

  return fDaughters.HasObject(p);
}

//--------------------------------------------------------------------------------------------------
Bool_t CompositeParticle::HasCommonDaughter(const CompositeParticle *p) const 
{
  // Return true if a common daughter exists.

  if(!p) return kFALSE;

  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (HasDaughter(p->Daughter(i)))
      return kTRUE;
	
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t CompositeParticle::HasSameDaughters(const CompositeParticle* p) const 
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
