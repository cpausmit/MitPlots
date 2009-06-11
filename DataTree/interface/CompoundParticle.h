//--------------------------------------------------------------------------------------------------
// $Id: CompoundParticle.h,v 1.2 2009/06/10 06:27:50 loizides Exp $
//
// CompoundParticle
//
// A compound particle class that holds other (daughter) particles. The class provides
// the same features as the CompositeParticle but allows to transfer ownership of daughters.
// This class is cannot be stored in a tree.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_COMPOUNDPARTICLE_H
#define MITANA_DATATREE_COMPOUNDPARTICLE_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  class CompoundParticle : public Particle
  {
    public:
      CompoundParticle();
      void                      AddDaughter(const Particle *p)    
                                  { fDaughters1.Add(p); ClearMom(); ClearCharge(); }
      void                      AddDaughter(Particle *p, Bool_t owned);
      void                      Clear(Option_t *opt="");
      const Particle           *Daughter(UInt_t i)    const;
      UInt_t                    NDaughters()          const;
      Bool_t			HasDaughter(const Particle *p)               const;
      Bool_t			HasCommonDaughter(const CompoundParticle *p) const;
      Bool_t			HasSameDaughters(const CompoundParticle *p)  const;
      EObjType                  ObjType()             const    { return kCompoundParticle; }

    protected:
      Double_t		        GetCharge()           const;
      void	                GetMom()              const;

      ParticleOArr              fDaughters1; //daughter particles (not owned)
      ParticleOArr              fDaughters2; //daughter particles (owned)
      
    ClassDef(CompoundParticle, 1) // Compound particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CompoundParticle::Clear(Option_t *opt)           
{ 
  // Clear object.

  fDaughters1.Clear(opt); 
  fDaughters2.Clear(opt); 
  ClearMom(); 
  ClearCharge(); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Particle *mithep::CompoundParticle::Daughter(UInt_t i) const
{
  // Return daughter at given index.

  if (i<fDaughters1.Entries())
    return fDaughters1.At(i);
  
  return fDaughters2.At(i-fDaughters1.Entries());
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::CompoundParticle::GetCharge() const 
{
  // Return sum of charge of daughter particles.

  Double_t charge = 0;
  for (UInt_t i=0; i<NDaughters(); ++i)
    charge += Daughter(i)->Charge();
  
  return charge;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CompoundParticle::GetMom() const 
{
  // Calculate the vector sum of the momenta of the daughters.

  FourVector mom;
  for (UInt_t i=0; i<NDaughters(); ++i)
    mom += (Daughter(i))->Mom();
  
  fCachedMom.SetCoordinates(mom.Pt(),mom.Eta(),mom.Phi(),mom.M()); 
}

//--------------------------------------------------------------------------------------------------
inline UInt_t mithep::CompoundParticle::NDaughters() const
{
  // Return number of daughters.

  return (fDaughters1.Entries()+fDaughters2.Entries());
}
#endif
