//--------------------------------------------------------------------------------------------------
// $Id: CompositeParticle.h,v 1.22 2009/07/13 11:00:18 loizides Exp $
//
// CompositeParticle
//
// A composite particle class that holds other (daughter) particles.
//
// Authors: J.Bendavid, C.Loizides, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_COMPOSITEPARTICLE_H
#define MITANA_DATATREE_COMPOSITEPARTICLE_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class CompositeParticle : public Particle
  {
    public:
      CompositeParticle() {}
    
      void                      AddDaughter      (const Particle *p)
                                  { fDaughters.Add(p); ClearMom(); ClearCharge(); }
      void                      Clear            (Option_t *opt="")
                                  { fDaughters.Clear(opt); ClearMom(); ClearCharge(); }
      const Particle           *Daughter         (UInt_t i) const  { return fDaughters.At(i); }
      UInt_t                    NDaughters       ()         const  { return fDaughters.Entries(); }
      Bool_t			HasDaughter      (const Particle *p)          const;
      Bool_t			HasCommonDaughter(const CompositeParticle *p) const;
      Bool_t			HasSameDaughters (const CompositeParticle *p) const;
      EObjType                  ObjType          ()                           const
                                  { return kCompositeParticle;   }

      // Some structural tools
      void                      Mark()                const;

    protected:
      Double_t		        GetCharge()           const;
      void	                GetMom()              const;

      RefArray<Particle>        fDaughters; //references to daughter particles
      
    ClassDef(CompositeParticle, 1) // Composite particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CompositeParticle::Mark() const
{
  // mark myself
  mithep::DataObject::Mark();
  // mark my dependencies if they are there
  for (UInt_t i=0; i<NDaughters(); i++)
    fDaughters.At(i)->Mark();
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::CompositeParticle::GetCharge() const 
{
  // Return sum of charge of daughter particles.

  Double_t charge = 0;
  for (UInt_t i=0; i<NDaughters(); ++i)
    charge += Daughter(i)->Charge();
  
  return charge;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CompositeParticle::GetMom() const 
{
  // Calculate the vector sum of the momenta of the daughters.

  FourVector mom;
  for (UInt_t i=0; i<NDaughters(); ++i)
    mom += (Daughter(i))->Mom();
  
  fCachedMom.SetCoordinates(mom.Pt(),mom.Eta(),mom.Phi(),mom.M()); 
}
#endif
