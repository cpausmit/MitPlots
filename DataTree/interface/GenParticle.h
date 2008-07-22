//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.16 2008/07/17 08:21:07 loizides Exp $
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
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep 
{
  class GenParticle : public CompositeParticle
  {
    public:
      GenParticle() {}
      GenParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s) : 
        fPdgId(id), fStatus(s), 
        fFourVector(px,py,pz,e), fDecayVertex(0,0,0) {}
      ~GenParticle() {}

      Int_t               AbsPdgId()            const { return (fPdgId<0 ? -fPdgId:fPdgId); }
      void		  AddDaughter(GenParticle *p) { fDaughters.Add(p); }
      Double_t            Charge()              const;
      const Vertex       &DecayVertex()         const { return fDecayVertex; }
      const GenParticle  *Daughter(UInt_t i)    const;
      Bool_t              HasMother()           const { return fMother.IsValid(); }
      Bool_t              IsNeutrino()          const;
      const GenParticle  *Mother()              const;
      FourVector	  Mom()                 const { return fFourVector; }
      TParticlePDG       *PdgEntry()            const;
      Int_t               PdgId()               const { return fPdgId; }
      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(GenParticle *p)   { fMother = p; }
      void                SetVertex(Double_t x, Double_t y, Double_t z);       
      Int_t               Status()              const { return fStatus; }
      void                Print(Option_t *opt="") const;

      enum EPartType {
        kUnknown=0,
        kEl=11, kMu=13, kTau=15,
        kElNu=12, kMuNu=14, kTauNu=16,
        kGlu=21, kGamma=22
      };
      
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
inline Bool_t mithep::GenParticle::IsNeutrino() const 
{ 
  // Return true if particle is neutrino.

  Int_t ap = AbsPdgId();
  if ((ap==kElNu) ||
      (ap==kMuNu) ||
      (ap==kTauNu)) 
    return kTRUE;

  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::GenParticle::PdgEntry() const 
{ 
  // Return entry to pdg database.

  return TDatabasePDG::Instance()->GetParticle(fPdgId); 
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
