// $Id: CompositeParticle.cc,v 1.5 2008/07/16 18:56:49 loizides Exp $

#include "MitAna/DataTree/interface/CompositeParticle.h"

ClassImp(mithep::CompositeParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t CompositeParticle::Charge() const 
{
  // Return sum of charge of daughter particles.

  Double_t charge = 0;
  for (UInt_t i=0; i<NDaughters(); ++i)
    charge += Daughter(i)->Charge();
  
  return charge;
}

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

//--------------------------------------------------------------------------------------------------
FourVector CompositeParticle::Mom() const 
{
  // Return the vector sum of the momenta of the daughters.

  FourVector mom;
  for (UInt_t i=0; i<NDaughters(); ++i)
    mom += (Daughter(i))->Mom();
  
  return mom;
}
