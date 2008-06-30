// $Id: Muon.cc,v 1.1 2008/06/04 09:08:36 loizides Exp $

#include "MitAna/DataTree/interface/CompositeParticle.h"


ClassImp(mithep::CompositeParticle)

using namespace mithep;

Int_t CompositeParticle::Charge() const {
	Int_t charge = 0;
	for (Int_t i=0; i<GetDaughters()->GetEntries(); i++)
		charge += ((Particle*)GetDaughters()->At(i))->Charge();
	
	return charge;
}

// Bool_t CompositeParticle::HasDaughter(const Particle* p) {
// 	if ( fDaughters.IndexOf(p) >= 0 )
// 		return true;
// 	else
// 		return false;
// }

Bool_t CompositeParticle::HasDaughter(const Particle* p) const {
	if ( fDaughters.GetEntries() == 0 )
		return false;

	for (UInt_t i=0; i<fDaughters.GetEntries(); i++)
		if (fDaughters.At(i)==p)
			return true;

	return false;
}

Bool_t CompositeParticle::HasSameDaughters(CompositeParticle* p) const {
	if ( fDaughters.GetEntries() != p->GetDaughters()->GetEntries())
		return false;
		
	for (Int_t i=0; i<p->GetDaughters()->GetEntries();i++)
		if (!HasDaughter( (Particle*)p->GetDaughters()->At(i) ) )
			return false;
	
	return true;
}

Bool_t CompositeParticle::HasCommonDaughter(CompositeParticle* p) const {
	for (Int_t i=0; i<p->GetDaughters()->GetEntries();i++)
		if (HasDaughter( (Particle*)p->GetDaughters()->At(i) ) )
			return true;
	
	return false;
}

FourVector CompositeParticle::Mom() const {
	FourVector mom;
	for (Int_t i=0; i<GetDaughters()->GetEntries(); i++)
		mom += ((Particle*)GetDaughters()->At(i))->Mom();
	
	return mom;
}
