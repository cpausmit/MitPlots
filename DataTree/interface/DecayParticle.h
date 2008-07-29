//--------------------------------------------------------------------------------------------------
// $Id: DecayParticle.h,v 1.6 2008/07/28 23:13:41 paus Exp $
//
// Decay Particle
//
// Decay Particle for use in vertexing based analyses.
// Stores vertex fit information and links to daughters.
//
// Authors: J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_DECAYPARTICLE_H
#define DATATREE_DECAYPARTICLE_H
 
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DecayParticle : public CompositeParticle
  {
    public:
      // Decay type
      enum DecayType {Fast, Slow};

      DecayParticle() {}
      DecayParticle(Int_t absPdgId, DecayType decayType) :
        fAbsPdgId(absPdgId),
        fDecayType(decayType),
        fChi2(0),
        fNdof(0),
        fFittedMass(0),
        fFittedMassError(0),
        fNormalizedMass(0),
        fLxy(0),
        fLxyError(0),
        fLxyToPv(0),
        fLxyToPvError(0),
        fDxy(0),
        fDxyError(0),
        fDxyToPv(0),
        fDxyToPvError(0),
        fLz(0),
        fLzError(0),
        fLzToPv(0),
        fLzToPvError(0),
        fCTau(0),
        fCTauError(0),
        fPt(0),
        fPtError(0),
        fPosition(0,0,0) {}
      ~DecayParticle() {}

      UInt_t        AbsPdgId() const { return fAbsPdgId; }
      void          SetAbsPdgId(UInt_t absPdgId) { fAbsPdgId=absPdgId; }
      TParticlePDG *ParticlePdgEntry() const;

      Double_t  PdgMass() const;

      Double_t    Prob() const { return TMath::Prob(fChi2,fNdof); }
      Double_t    Chi2() const { return fChi2; }
      Int_t       Ndof() const { return fNdof; }
      void   SetChi2(Double_t chi2) { fChi2 = chi2;}
      void   SetNdof(Int_t    ndof) { fNdof = ndof;}
    
      // Fitted Mass
      Double_t    FittedMass() const { return fFittedMass; }
      void   SetFittedMass(Double_t fittedMass) { fFittedMass = fittedMass;}
      // Fitted Mass Error
      Double_t    FittedMassError() const { return fFittedMassError; }
      void   SetFittedMassError(Double_t fittedMassError) { fFittedMassError = fittedMassError;}
      // Lxy
      Double_t    Lxy() const { return fLxy; }
      void   SetLxy(Double_t lxy) { fLxy = lxy;}
      // Lxy Error
      Double_t    LxyError() const { return fLxyError; }
      void   SetLxyError(Double_t lxyError) { fLxyError = lxyError;}
      // LxyToPv (length to primary vertex)
      Double_t    LxyToPv() const { return fLxyToPv; }
      void   SetLxyToPv(Double_t lxyToPv) { fLxyToPv = lxyToPv;}
      // LxyToPv Error
      Double_t    LxyToPvError() const { return fLxyToPvError; }
      void   SetLxyToPvError(Double_t lxyToPvError) { fLxyToPvError = lxyToPvError;}
      // Dxy (two dimensional impact parameter)
      Double_t    Dxy() const { return fDxy; }
      void   SetDxy(Double_t dxy) { fDxy = dxy;}
      // Dxy Error
      Double_t    DxyError() const { return fDxyError; }
      void   SetDxyError(Double_t dxyError) { fDxyError = dxyError;}
      // DxyToPv (two dimensional impact parameter with respect to primary vertex)
      Double_t    DxyToPv() const { return fDxyToPv; }
      void   SetDxyToPv(Double_t dxyToPv) { fDxyToPv = dxyToPv;}
      // DlxyToPv Error
      Double_t    DxyToPvError() const { return fDxyToPvError; }
      void   SetDxyToPvError(Double_t dxyToPvError) { fDxyToPvError = dxyToPvError;}
      // Lz
      Double_t    Lz() const { return fLz; }
      void   SetLz(Double_t lz) { fLz = lz;}
      // Lz Error
      Double_t    LzError() const { return fLzError; }
      void   SetLzError(Double_t lzError) { fLzError = lzError;}
      // LzToPv (length to primary vertex)
      Double_t    LzToPv() const { return fLzToPv; }
      void   SetLzToPv(Double_t lzToPv) { fLzToPv = lzToPv;}
      // LzToPv Error
      Double_t    LzToPvError() const { return fLzToPvError; }
      void   SetLzToPvError(Double_t lzToPvError) { fLzToPvError = lzToPvError;}
      // CTau
      Double_t    CTau() const { return fCTau; }
      void   SetCTau(Double_t cTau) { fCTau = cTau;}
      // CTau Error
      Double_t    CTauError() const { return fCTauError; }
      void   SetCTauError(Double_t cTauError) { fCTauError = cTauError;}
      // Pt
      Double_t    Pt() const { return  fPt; }
      void   SetPt(Double_t pt) { fPt = pt;}
      // Pt Error
      Double_t    PtError() const { return fPtError; }
      void   SetPtError(Double_t ptError) { fPtError = ptError;}
      //----------------------------------------------------------------------------------------------
      // Accessors/Setter: Extended Vertex fit info from this level
      //----------------------------------------------------------------------------------------------
      // Position
      const ThreeVector        &position() const { return fPosition; }
      void                   setPosition(const ThreeVector &position) { fPosition = position; }
      // Error
      const ThreeSymMatrix     &error() const { return fError; }
      void                   setError(const ThreeSymMatrix &error) { fError = error; }
      // Big 7x7 Error Matrix
      const SevenSymMatrix     &bigError() const { return fBigError; }
      void                   setBigError(const SevenSymMatrix &bigError) { fBigError = bigError; }
//    void                   setBigError(const SevenMatrix    &bigError) { fBigError = bigError; }

        
    protected:
      UInt_t                fAbsPdgId;
      DecayType             fDecayType; // Decay type (either fast of slow)
      // Fit quality
      Double_t              fChi2;
      Int_t                 fNdof;
      // Base vertex fit info
      Double_t              fFittedMass;
      Double_t              fFittedMassError;
      Double_t              fNormalizedMass;
      Double_t              fLxy;
      Double_t              fLxyError;
      Double_t              fLxyToPv;
      Double_t              fLxyToPvError;
      Double_t              fDxy;
      Double_t              fDxyError;
      Double_t              fDxyToPv;
      Double_t              fDxyToPvError;
      Double_t              fLz;
      Double_t              fLzError;
      Double_t              fLzToPv;
      Double_t              fLzToPvError;
      Double_t              fCTau;
      Double_t              fCTauError;
      Double_t              fPt;
      Double_t              fPtError;
      // Extended vertex fit info
      ThreeVector           fPosition;
      ThreeSymMatrix        fError;
      SevenSymMatrix        fBigError;
      
    ClassDef(DecayParticle, 1)         // Decay particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::DecayParticle::ParticlePdgEntry() const 
{ 
  // Return entry to pdg database for the PARTICLE.

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}
#endif
