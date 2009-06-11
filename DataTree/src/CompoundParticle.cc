// $Id: CompoundParticle.cc,v 1.3 2009/06/10 14:38:56 loizides Exp $

#include "MitAna/DataTree/interface/CompoundParticle.h"

ClassImp(mithep::CompoundParticle)

using namespace mithep;

CompoundParticle::CompoundParticle() 
  : fDaughters1(2), fDaughters2(2)
{ 
  // Constructor.

  fDaughters1.SetOwner(kFALSE); 
  fDaughters2.SetOwner(kTRUE); 
}

//--------------------------------------------------------------------------------------------------
void CompoundParticle::AddDaughter(Particle *p, Bool_t owned=kTRUE)    
{ 
  // Add daughter to list of daughters. If owned=kTRUE make sure it will be deleted when
  // CompoundParticle will be deleted.

  if(owned) 
    fDaughters2.AddOwned(p); 
  else 
    fDaughters1.Add(p); 

  ClearMom(); 
  ClearCharge(); 
}

//--------------------------------------------------------------------------------------------------
Bool_t CompoundParticle::HasDaughter(const Particle *p) const 
{
  // Return true if given particle is among daughters.

  if(!p) 
    return kFALSE;

  return (fDaughters1.HasObject(p) || fDaughters2.HasObject(p)); 
}

//--------------------------------------------------------------------------------------------------
Bool_t CompoundParticle::HasCommonDaughter(const CompoundParticle *p) const 
{
  // Return true if a common daughter exists.

  if(!p) 
    return kFALSE;

  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (HasDaughter(p->Daughter(i)))
      return kTRUE;
	
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t CompoundParticle::HasSameDaughters(const CompoundParticle *p) const 
{
  // Return true if daughters are the same.

  if(!p) 
    return kFALSE;

  if (NDaughters()!= p->NDaughters())
    return kFALSE;
		
  for (UInt_t i=0; i<p->NDaughters(); ++i)
    if (!HasDaughter(p->Daughter(i))) 
        return kFALSE;
	
  return kTRUE;
}
