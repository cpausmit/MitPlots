//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.10 2008/07/01 14:05:22 loizides Exp $
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep 
{
  class GenParticle : public CompositeParticle
  {
    public:
      GenParticle() : CompositeParticle(16) {}
      GenParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s) : 
        CompositeParticle(16), fPdgId(id), fStatus(s), 
        fFourVector(px,py,pz,e), fDecayVertex(0,0,0) {}
      ~GenParticle() {}

      void		  AddDaughter(GenParticle *p) { fDaughters.Add(p); }
      Int_t               Charge()              const { return fCharge/3; }
      const Vertex       &GetDecayVertex()      const { return fDecayVertex; }
      const GenParticle  *GetDaughter(UInt_t i) const;
      Int_t               GetPdgId()            const { return fPdgId; }
      Int_t               GetStatus()           const { return fStatus; }
      Bool_t              HasMother()           const { return fMother.IsValid(); }
      const GenParticle  *GetMother()           const;
      FourVector	  Mom()                 const { return fFourVector; }

      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(GenParticle *p)  { fMother = p; }
      void                SetVertex(Double_t x, Double_t y, Double_t z);       
      
    protected:
      Int_t               fCharge;       //charge (*3 to allow storage of fractional charges) 
      Int_t               fPdgId;        //pdg identifier
      Int_t               fStatus;       //status flag of generator
      FourVector          fFourVector;   //four momentum vector
      Vertex		  fDecayVertex;  //gen decay vertex
      TRef                fMother;       //reference to mother

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

//--------------------------------------------------------------------------------------------------
inline void mithep::GenParticle::SetVertex(Double_t x, Double_t y, Double_t z)
{
  // Set decay vertex.

  fDecayVertex.SetXYZ(x,y,z);
}
#endif
