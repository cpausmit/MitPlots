//--------------------------------------------------------------------------------------------------
// $Id: CompositeParticle.h,v 1.16 2008/12/03 11:35:21 loizides Exp $
//
// Composite Particle
//
// A composite particle class that holds other (daughter) particles.
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_COMPOSITEPARTICLE_H
#define MITANA_DATATREE_COMPOSITEPARTICLE_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class CompositeParticle : public Particle
  {
    public:
      CompositeParticle() {}
      ~CompositeParticle() {}
    
      void                      AddDaughter(const Particle *p)    { fDaughters.Add(p);           }
      Double_t		        Charge()              const;
      void                      Clear(Option_t *opt="")           { fDaughters.Clear(opt);       }
      const Particle           *Daughter(UInt_t i)    const       { return fDaughters.At(i);     }
      UInt_t                    NDaughters()          const       { return fDaughters.Entries(); }
      Bool_t			HasDaughter(const Particle *p)                const;
      Bool_t			HasCommonDaughter(const CompositeParticle *p) const;
      Bool_t			HasSameDaughters(const CompositeParticle *p)  const;
      FourVector	        Mom()                 const;
      EObjType                  ObjType()             const       { return kCompositeParticle;   }

    protected:
      RefArray<Particle,1024>   fDaughters; //references to daughter particles
      
    ClassDef(CompositeParticle, 1) // Composite particle class
  };
}
#endif
