//--------------------------------------------------------------------------------------------------
// $Id: MCParticle.h,v 1.9 2008/11/24 14:11:47 loizides Exp $
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
        fPdgId(id), fStatus(s), fFourVector(FourVector(px,py,pz,e)), fDecayVertex(0,0,0),
        fIsGenerated(kFALSE), fIsSimulated(kFALSE) {}
      ~MCParticle() {}

      Int_t               AbsPdgId()               const { return (fPdgId<0 ? -fPdgId:fPdgId); }
      void		  AddDaughter(const MCParticle *p) { fDaughters.Add(p); }
      Double_t            Charge()                 const;
      const ThreeVector  &DecayVertex()            const { return fDecayVertex; }
      const MCParticle   *Daughter(UInt_t i)       const;
      const MCParticle   *DistinctMother()         const;
      using CompositeParticle::HasDaughter;
      const MCParticle   *FindDaughter(Int_t pid, 
                                       Bool_t checkCharge=kFALSE, const MCParticle *start=0) const;
      const MCParticle   *FindMother(Int_t pid, Bool_t checkCharge=kFALSE) const;
      Bool_t              HasDaughter(Int_t pid, Bool_t checkCharge=kFALSE) const;
      Bool_t              HasMother()              const { return fMother.IsValid(); }
      Bool_t              HasMother(const MCParticle *m)                    const;
      Bool_t              HasMother(Int_t pid, Bool_t checkCharge=kFALSE)   const;
      Bool_t              Is(Int_t pid, Bool_t checkCharge=kFALSE)          const;
      Bool_t              IsGenerated()            const { return fIsGenerated; }
      Bool_t              IsNeutrino()             const;
      Bool_t              IsQuark()                const { return (AbsPdgId()>0 && AbsPdgId()<7); }
      Bool_t              IsSimulated()            const { return fIsSimulated; }
      const MCParticle   *Mother()                 const;
      FourVector	  Mom()                    const { return FourVector(fFourVector); }
      void                SetIsGenerated(Bool_t t=kTRUE) { fIsGenerated = t; }
      void                SetIsSimulated(Bool_t t=kTRUE) { fIsSimulated = t; }
      TParticlePDG       *PdgEntry()               const;
      Int_t               PdgId()                  const { return fPdgId; }
      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void		  SetMother(const MCParticle *p) { fMother = const_cast<MCParticle*>(p); }
      void                SetStatus(Int_t s)             { fStatus = s; }
      void                SetVertex(Double_t x, Double_t y, Double_t z);
      void                SetPdgId(Int_t s)              {  fPdgId = s; }
      Int_t               Status()                 const { return fStatus; }
      void                Print(Option_t *opt="")  const;

      enum EPartType {
        kUnknown=0, 
        kUp=1, kDown=2, kStrange=3, kCharm=4, kBottom=5, kTop=6,
        kEl=11, kMu=13, kTau=15, 
        kElNu=12, kMuNu=14, kTauNu=16,
        kGlu=21, kGamma=22, kZ=23, kW=24, kH=25,
        kZp=32, kZpp=33, kWp=34, kH0=35, kA0=36, kHp=37,
        kPi0=111, kEta=221
      };
      
    protected:
      Int_t               fPdgId;        //pdg identifier
      Int_t               fStatus;       //status flag of generator or simulation
      FourVectorM32       fFourVector;   //four momentum vector
      ThreeVector32       fDecayVertex;  //gen decay vertex
      TRef                fMother;       //reference to mother
      Bool_t              fIsGenerated;  //=true if generated particle
      Bool_t              fIsSimulated;  //=true if simulated particle

    ClassDef(MCParticle,3) // Generated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::MCParticle::Daughter(UInt_t i) const 
{ 
  // Return daughter corresponding to given index.

  return static_cast<const MCParticle*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::MCParticle::DistinctMother() const 
{ 
  // Return mother, walking up the tree until a particle with a different pdg from this one
  // is found.

  const mithep::MCParticle *mother = Mother();
  
  if (!mother) 
    return 0;
  
  while (mother->PdgId()==fPdgId)
    mother = mother->Mother();
    
  return mother;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::MCParticle::HasDaughter(Int_t pid, Bool_t checkCharge) const
{
  // Return true if a particle with given pdg code is found amoung daughters.
  // If checkCharge is false then just the type of particle is checked 
  // (ie particle and anti-particle).

  if (checkCharge) {
    for (UInt_t i=0; i<NDaughters(); ++i)
      if (Daughter(i)->PdgId()==pid) 
        return kTRUE;
  } else {
    Int_t apid = pid>0?pid:-pid;
    for (UInt_t i=0; i<NDaughters(); ++i)
      if (Daughter(i)->AbsPdgId()==apid) 
        return kTRUE;
  }
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::MCParticle::HasMother(const MCParticle *m) const
{
  // Return true if the given particle is among mothers. (Note the comparison
  // is made on pointers and therefore will fail if you work on copies.)

  if (!m) 
    return kFALSE;

  const mithep::MCParticle *mother = Mother();
  while (mother && mother!=m)
    mother = mother->Mother();

  if (mother) 
    return kTRUE;
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::MCParticle::HasMother(Int_t pid, Bool_t checkCharge) const
{
  // Return true if a particle with given pdg code is found amoung mothers.
  // If checkCharge is false then just the type of particle is checked 
  // (ie particle and anti-particle).

  const mithep::MCParticle *mother = Mother();
  
  if (checkCharge) {
    while (mother && mother->PdgId()!=pid)
      mother = mother->Mother();
  } else {
    Int_t apid = pid>0?pid:-pid;
    while (mother && mother->AbsPdgId()!=apid)
      mother = mother->Mother();
  }

  if (mother) 
    return kTRUE;
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::MCParticle::Is(Int_t pid, Bool_t checkCharge) const 
{ 
  // Return true if particle is of given type. If checkCharge is false then just the type of 
  // particle is checked (ie particle and anti-particle).

  if (checkCharge) 
    return (PdgId() == pid);

  Int_t apid = pid>0?pid:-pid;
  return (AbsPdgId() == apid);
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
inline const mithep::MCParticle *mithep::MCParticle::Mother() const 
{ 
  // Return mother.

  return static_cast<const MCParticle*>(fMother.GetObject()); 
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
