//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.14 2008/07/16 09:32:04 bendavid Exp $
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H

#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
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
      Double_t            Charge()              const;
      const Vertex       &DecayVertex()         const { return fDecayVertex; }
      const GenParticle  *Daughter(UInt_t i)    const;
      Int_t               PdgId()               const { return fPdgId; }
      Int_t               AbsPdgId()            const { return (fPdgId<0 ? -fPdgId:fPdgId); }
      TParticlePDG       *PdgEntry()            const { return TDatabasePDG::Instance()->GetParticle(fPdgId); }
      Int_t               Status()              const { return fStatus; }
      Bool_t              HasMother()           const { return fMother.IsValid(); }
      const GenParticle  *Mother()              const;
      FourVector	  Mom()                 const { return fFourVector; }
      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(GenParticle *p)   { fMother = p; }
      void                SetVertex(Double_t x, Double_t y, Double_t z);       
      void                Print(Option_t *opt="") const;
      
    protected:
      Int_t               fPdgId;        //pdg identifier
      Int_t               fStatus;       //status flag of generator
      FourVector          fFourVector;   //four momentum vector
      Vertex		  fDecayVertex;  //gen decay vertex
      TRef                fMother;       //reference to mother

    ClassDef(GenParticle,2) // Generated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::GenParticle *mithep::GenParticle::Daughter(UInt_t i) const 
{ 
  // Return daughter corresponding to given index.

  return static_cast<const GenParticle*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::GenParticle *mithep::GenParticle::Mother() const 
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
