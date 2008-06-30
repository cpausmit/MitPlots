//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.2 2008/06/05 16:03:35 bendavid Exp $
//
// Composite Particle
//
// Details to be worked out...
//
// Authors: J.Bendavid...
//
//--------------------------------------------------------------------------------------------------


#ifndef DATATREE_COMPOSITEPARTICLE_H
#define DATATREE_COMPOSITEPARTICLE_H
 
#include "MitAna/DataTree/interface/RefArray.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class CompositeParticle : public Particle
  {
    public:
      CompositeParticle() {}
      ~CompositeParticle() {}
    
      const RefArray<Particle> *GetDaughters() const { return &fDaughters; }
    
      void			AddDaughter(Particle* p) { fDaughters.Add(p); }
      virtual Int_t		Charge() const;
      Bool_t			HasDaughter(const Particle* p) const;
      Bool_t			HasSameDaughters(CompositeParticle* p) const;
      Bool_t			HasCommonDaughter(CompositeParticle* p) const;
      virtual FourVector	Mom() const;
        
    protected:
      RefArray<Particle>        fDaughters; //
      
    ClassDef(CompositeParticle, 1)
  };
}
#endif
