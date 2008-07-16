// $Id: CompositeParticle.cc,v 1.3 2008/07/14 20:55:19 loizides Exp $

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
Bool_t CompositeParticle::HasCommonDaughter(const CompositeParticle *p) const 
{
  // Return true if a common daughter exists.

  if(!p) return kFALSE;

  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (IsDaughter(p->Daughter(i)))
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
    if (!IsDaughter(p->Daughter(i))) 
        return kFALSE;
	
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
Bool_t CompositeParticle::IsDaughter(const Particle* p) const 
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
FourVector CompositeParticle::Mom() const 
{
  // Return the vector sum of the momenta of the daughters.

  FourVector mom;
  for (UInt_t i=0; i<NDaughters(); ++i)
    mom += (Daughter(i))->Mom();
  
  return mom;
}
