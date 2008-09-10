//--------------------------------------------------------------------------------------------------
// $Id: MCParticle.h,v 1.2 2008/07/29 12:29:47 bendavid Exp $
//
// MCParticle
//
// Stores MC information for both gen and sim level
//
// Authors: C.Loizides, J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCPARTICLE_H
#define MITANA_DATATREE_MCPARTICLE_H

#include <TRef.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
#include "MitAna/DataTree/interface/CompositeParticle.h"

namespace mithep 
{
  class MCParticle : public CompositeParticle
  {
    public:
      MCParticle() : fIsGenerated(kFALSE), fIsSimulated(kFALSE) {}
      MCParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s) : 
        fPdgId(id), fStatus(s), 
        fFourVector(px,py,pz,e), fDecayVertex(0,0,0),
        fIsGenerated(kFALSE), fIsSimulated(kFALSE) {}
      ~MCParticle() {}

      Int_t               AbsPdgId()               const { return (fPdgId<0 ? -fPdgId:fPdgId); }
      void		  AddDaughter(MCParticle *p)     { fDaughters.Add(p); }
      Double_t            Charge()                 const;
      const ThreeVector  &DecayVertex()            const { return fDecayVertex; }
      const MCParticle   *Daughter(UInt_t i)       const;
      Bool_t              HasMother()              const { return fMother.IsValid(); }
      Bool_t              IsGenerated()            const { return fIsGenerated; }
      Bool_t              IsSimulated()            const { return fIsSimulated; }
      Bool_t              IsNeutrino()             const;
      const MCParticle   *Mother()                 const;
      FourVector	  Mom()                    const { return fFourVector; }
      void                SetIsGenerated(Bool_t t=kTRUE) { fIsGenerated = t; }
      void                SetIsSimulated(Bool_t t=kTRUE) { fIsSimulated = t; }
      TParticlePDG       *PdgEntry()               const;
      Int_t               PdgId()                  const { return fPdgId; }
      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(MCParticle *p)       { fMother = p; }
      void                SetStatus(Int_t s)             { fStatus = s; }
      void                SetVertex(Double_t x, Double_t y, Double_t z);
      Int_t               Status()                 const { return fStatus; }
      void                Print(Option_t *opt="")  const;

      enum EPartType {
        kUnknown=0,
        kEl=11, kMu=13, kTau=15,
        kElNu=12, kMuNu=14, kTauNu=16,
        kGlu=21, kGamma=22
      };
      
    protected:
      Int_t               fPdgId;        //pdg identifier
      Int_t               fStatus;       //status flag of generator or simulation
      FourVector          fFourVector;   //four momentum vector
      ThreeVector         fDecayVertex;  //gen decay vertex
      TRef                fMother;       //reference to mother
      Bool_t              fIsGenerated;  //=true if generated particle
      Bool_t              fIsSimulated;  //=true if simulated particle

    ClassDef(MCParticle,2) // Generated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::MCParticle::Daughter(UInt_t i) const 
{ 
  // Return daughter corresponding to given index.

  return static_cast<const MCParticle*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::MCParticle::Mother() const 
{ 
  // Return mother.

  return static_cast<const MCParticle*>(fMother.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::MCParticle::IsNeutrino() const 
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
inline TParticlePDG *mithep::MCParticle::PdgEntry() const 
{ 
  // Return entry to pdg database.

  return TDatabasePDG::Instance()->GetParticle(fPdgId); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::MCParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}

//--------------------------------------------------------------------------------------------------
inline void mithep::MCParticle::SetVertex(Double_t x, Double_t y, Double_t z)
{
  // Set decay vertex.

  fDecayVertex.SetXYZ(x,y,z);
}
#endif
