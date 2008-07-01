//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.7 2008/06/30 16:54:40 loizides Exp $
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H
 
#include <TRef.h>
#include <TRefArray.h>
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep 
{
  class GenParticle : public Particle
  {
    public:
      GenParticle() {}
      GenParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s) 
        : fPdgId(id), fStatus(s), fFourVector(px,py,pz,e), fDecayVertex(0,0,0) {}
      ~GenParticle() {}

      void		  AddDaughter(GenParticle *p) { fDaughters.Add(p); }
      const Vertex       &GetDecayVertex()      const { return fDecayVertex; }
      const GenParticle  *GetDaughter(UInt_t i) const;
      UInt_t              GetNDaughters()       const { return fDaughters.GetEntries(); }
      Int_t               GetPdgId()            const { return fPdgId; }
      Int_t               GetStatus()           const { return fStatus; }
      Bool_t              HasMother()           const { return fMother.IsValid(); }
      const GenParticle  *GetMother()           const;
      FourVector	  Mom()                 const { return fFourVector; }

      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(GenParticle *p)  { fMother = p; }
      
    protected:
      Int_t               fPdgId;        //pdg identifier
      Int_t               fStatus;       //status flag of generator
      FourVector          fFourVector;   //four momentum vector
      Vertex		  fDecayVertex;  //gen decay vertex
      TRef                fMother;       //reference to mother
      TRefArray           fDaughters;    //references to daughters

    ClassDef(GenParticle,1) // Generated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::GenParticle *mithep::GenParticle::GetDaughter(UInt_t i) const 
{ 
  // Return daughter corresponding to given index.

  return static_cast<const GenParticle*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::GenParticle *mithep::GenParticle::GetMother() const 
{ 
  // Return mother.

  return static_cast<const GenParticle*>(fMother.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::GenParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}
#endif
