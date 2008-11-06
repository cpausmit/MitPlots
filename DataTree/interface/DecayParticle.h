//--------------------------------------------------------------------------------------------------
// $Id: DecayParticle.h,v 1.16 2008/10/31 18:56:42 bendavid Exp $
//
// Decay Particle
//
// Decay Particle for use in vertexing based analyses.
// Stores vertex fit information (including four momentum) and links to daughters.
//
// Note that Charge is still computed as a recursive loop over daughters, as inherited from
// CompositeParticle, but momentum is returned from the internally stored four vector
//
// Authors: C.Paus, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_DECAYPARTICLE_H
#define DATATREE_DECAYPARTICLE_H
 
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DecayParticle : public Particle
  {
    public:
      DecayParticle() {}
      DecayParticle(Int_t absPdgId) :
        fAbsPdgId (absPdgId),
        fChi2     (0),
        fNdof     (0),
        fMassError(0),
        fLxy      (0),
        fLxyError (0),
        fDxy      (0),
        fDxyError (0),
        fLz       (0),
        fLzError  (0) {}

      ~DecayParticle() {}

      UInt_t        AbsPdgId()         const { return fAbsPdgId; }
      void          SetAbsPdgId(UInt_t apid) { fAbsPdgId=apid; }
      TParticlePDG *ParticlePdgEntry() const;
      Double_t      PdgMass()          const;
      Double_t      Prob()             const { return TMath::Prob(fChi2,fNdof); }
      Double_t      Chi2()             const { return fChi2; }
      Int_t         Ndof()             const { return fNdof; }
      void          SetChi2(Double_t chi2) { fChi2 = chi2;}
      void          SetNdof(Int_t    ndof) { fNdof = ndof;}
      using TObject::Error;
    
      // Fitted Mass Error
      Double_t      MassError() const { return fMassError; }
      void       SetMassError(Double_t massError) { fMassError = massError;}
      // Lxy
      Double_t      Lxy() const { return fLxy; }
      void       SetLxy(Double_t lxy) { fLxy = lxy;}
      // Lxy Error
      Double_t      LxyError() const { return fLxyError; }
      void       SetLxyError(Double_t lxyError) { fLxyError = lxyError;}
      // Dxy (two dimensional impact parameter)
      Double_t      Dxy() const { return fDxy; }
      void       SetDxy(Double_t dxy) { fDxy = dxy;}
      // Dxy Error
      Double_t      DxyError() const { return fDxyError; }
      void       SetDxyError(Double_t dxyError) { fDxyError = dxyError;}
      // Lz
      Double_t      Lz() const { return fLz; }
      void       SetLz(Double_t lz) { fLz = lz;}
      // Lz Error
      Double_t      LzError() const { return fLzError; }
      void       SetLzError(Double_t lzError) { fLzError = lzError;}

      //--------------------------------------------------------------------------------------------
      // Accessors/Setter: Extended Vertex fit info from this level
      //--------------------------------------------------------------------------------------------
      Double_t               Charge()              const;

      //Momentum Accessors/setter
      FourVector	     Mom() const { return fMomentum; }
      void                   SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                   SetMom(const FourVector &p) { fMomentum = p; }
      
      UInt_t                 NDaughters()          const { return fDaughterData.Entries(); }
      const Particle        *Daughter(UInt_t i)    const { return DaughterDat(i)->Original(); }
      const DaughterData    *DaughterDat(UInt_t i) const { return fDaughterData.At(i); }
      Bool_t                 HasDaughter(const Particle *p)                const;
      Bool_t                 HasCommonDaughter(const DecayParticle *p) const;
      Bool_t                 HasSameDaughters(const DecayParticle *p)  const;
  
      void                   AddDaughterData(DaughterData *ddata) { fDaughterData.Add(ddata); }
      
      const ThreeVector      Position()            const;
      const ThreeVector      RelativePosition()    const;
      
      const Vertex          *PriVertex()           const;
      void                   SetPriVertex(Vertex *v) { fPriVertex = v; }
      
    protected:
      UInt_t                 fAbsPdgId;
      // Fit quality
      Double_t               fChi2;
      Int_t                  fNdof;
      // Base vertex fit info
      Double_t               fMassError;
      Double_t               fLxy;
      Double_t               fLxyError;
      Double_t               fDxy;
      Double_t               fDxyError;
      Double_t               fLz;
      Double_t               fLzError;
      // Extended vertex fit info
      FourVector             fMomentum; //momentum fourvector
      RefArray<DaughterData,32> fDaughterData; //momentum of daughters at vertex
      TRef                   fPriVertex; //reference to primary vertex
      
    ClassDef(DecayParticle, 1)
  };
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::DecayParticle::ParticlePdgEntry() const 
{ 
  // return entry to pdg database for the particle

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // set four vector

  fMomentum.SetXYZT(px,py,pz,e);
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector mithep::DecayParticle::Position() const
{
  // return absolute position of decay

  const mithep::Vertex *pv = PriVertex();
    
  if (pv)
    return ( pv->Position() + RelativePosition() );
  else
    return RelativePosition();
    
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector mithep::DecayParticle::RelativePosition() const
{
  // compute the position vector of the decay vertex relative to the primary vertex

  mithep::ThreeVector dz(0,0,fLz*TMath::Abs(fMomentum.Pz())/fMomentum.Pz());
  
  mithep::ThreeVector momPerp(fMomentum.Px(),fMomentum.Py(),0);
  mithep::ThreeVector zHat(0,0,1.0);
  
  mithep::ThreeVector dxy   = -momPerp.Cross(zHat)*fDxy/momPerp.R();
  mithep::ThreeVector dlxy  =  momPerp*fLxy/momPerp.R();
  
  return (dxy+dlxy+dz);
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Vertex *mithep::DecayParticle::PriVertex() const
{
  // return primary vertex

  return static_cast<const Vertex*>(fPriVertex.GetObject());
}
#endif
