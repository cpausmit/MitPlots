//--------------------------------------------------------------------------------------------------
// $Id: SimParticle.h,v 1.6 2008/07/14 20:55:19 loizides Exp $
//
// SimParticle
//
// Details to be worked out...
//
// Authors: J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_SIMPARTICLE_H
#define DATATREE_SIMPARTICLE_H
 
#include <TRef.h>
#include "MitAna/DataTree/interface/GenParticle.h"

namespace mithep 
{
  class SimParticle : public GenParticle
  {
    public:
      SimParticle() {}
      SimParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id) 
        : GenParticle(px,py,pz,e,id,0) {}
      ~SimParticle() {}
      
      const SimParticle   *Daughter(UInt_t i)    const;
      const GenParticle   *GenPart()             const;
      Bool_t               IsGenerated()         const    { return fGenPartRef.IsValid(); }
      const SimParticle   *Mother()              const;
      void                 SetGenPart(GenParticle* p)     { fGenPartRef = p; }

    protected:
      TRef		   fGenPartRef; //reference to generated particle

    ClassDef(SimParticle,1) // Simulated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::SimParticle *mithep::SimParticle::Daughter(UInt_t i) const 
{ 
  // Return daughter corresponding to given index.

  return static_cast<const SimParticle*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::GenParticle *mithep::SimParticle::GenPart() const 
{ 
  // Return reference to generated particle.

  return static_cast<const GenParticle*>(fGenPartRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::SimParticle *mithep::SimParticle::Mother() const 
{ 
  // Return mother.

  return static_cast<const SimParticle*>(fMother.GetObject()); 
}
#endif
