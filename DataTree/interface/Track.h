//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.17 2008/09/10 03:33:27 loizides Exp $
//
// Track
//
// We store the CMSSW track parameterization
// Parameters associated to the 5D curvilinear covariance matrix:
// (qoverp, lambda, phi, dxy, dsz)
// defined as:
// qoverp = q / abs(p) = signed inverse of momentum [1/GeV]
// lambda = pi/2 - polar angle at the given point
// phi = azimuth angle at the given point
// dxy = -vx*sin(phi) + vy*cos(phi) [cm]
// dsz = vz*cos(lambda) - (vx*cos(phi)+vy*sin(phi))*sin(lambda) [cm]
// (See http://cmslxr.fnal.gov/lxr/source/DataFormats/TrackReco/interface/TrackBase.h)
//
// Format for fHits: (We do not use anything resembling reco::HitPattern from CMSSW because that
// data format requires 800 bits per track!)
// There is a one to one mapping between bits and tracker layers, where layers are enumerated
// seperately in the PXB, PXF, TIB, TID, TOB, TEC and r-phi and stereo modules are treated as
// seperate layers in those detectors which have them
// (TIB L1,L2, TID L1,L2, TOB L1,L2, TEC L1,L2,L5).
// 
// A bit value of 1 indicates a hit in the corresponding layer, and 0 indicates no hit.
//
// Note that currently this only stores information about hits in the Tracker,
// but muon chamber information will likely be added as well.
//
// Bit-Layer assignments (starting from bit 0):
// Bit  0: PXB L1
// Bit  1: PXB L2
// Bit  2: PXB L3
// Bit  3: PXF L1
// Bit  4: PXF L2
// Bit  5: TIB L1 r-phi
// Bit  6: TIB L1 stereo
// Bit  7: TIB L2 r-phi
// Bit  8: TIB L2 stereo
// Bit  9: TIB L3 r-phi
// Bit 10: TIB L4 r-phi
// Bit 11: TID L1 r-phi
// Bit 12: TID L1 stereo
// Bit 13: TID L2 r-phi
// Bit 14: TID L2 stereo
// Bit 15: TID L3 r-phi
// Bit 16: TOB L1 r-phi
// Bit 17: TOB L1 stereo
// Bit 18: TOB L2 r-phi
// Bit 19: TOB L2 stereo
// Bit 20: TOB L3 r-phi
// Bit 21: TOB L4 r-phi
// Bit 22: TOB L5 r-phi
// Bit 23: TOB L6 r-phi
// Bit 24: TEC L1 r-phi
// Bit 25: TEC L1 stereo
// Bit 26: TEC L2 r-phi
// Bit 27: TEC L2 stereo
// Bit 28: TEC L3 r-phi
// Bit 29: TEC L4 r-phi
// Bit 30: TEC L5 r-phi
// Bit 31: TEC L5 stereo
// Bit 32: TEC L6 r-phi
// Bit 33: TEC L7 r-phi
// Bit 34: TEC L8 r-phi
// Bit 35: TEC L9 r-phi
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRACK_H
#define MITANA_DATATREE_TRACK_H
 
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/BitMask.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      enum EHitLayer { 
        PXB1, 
        PXB2,
        PXB3,
        PXF1,
        PXF2,
        TIB1,
        TIB1S,
        TIB2,
        TIB2S,
        TIB3,
        TIB4,
        TID1,
        TID1S,
        TID2,
        TID2S,
        TID3,
        TOB1,
        TOB1S,
        TOB2,
        TOB2S,
        TOB3,
        TOB4,
        TOB5,
        TOB6,
        TEC1,
        TEC1S,
        TEC2,
        TEC2S,
        TEC3,
        TEC4,
        TEC5,
        TEC5S,
        TEC6,
        TEC7,
        TEC8,
        TEC9 
      };

      Track() : fQOverP(0), fQOverPErr(0), fLambda(0), fLambdaErr(0),
                fPhi0(0), fPhi0Err(0), fDxy(0), fDxyErr(0), fDsz(0), fDszErr(0),
                fChi2(0), fNdof(0) {}
      Track(Double_t qOverP, Double_t lambda, Double_t phi0, Double_t dxy, Double_t dsz) :
	        fQOverP(qOverP), fQOverPErr(0), fLambda(lambda), fLambdaErr(0),
                fPhi0(phi0), fPhi0Err(0), fDxy(dxy), fDxyErr(0), fDsz(dsz), fDszErr(0),
                fChi2(0), fNdof(0) {}
      ~Track() {}

      Int_t	         Charge()         const { return (fQOverP>0) ? 1 : -1; }
      Double_t           Chi2()           const { return fChi2; }
      void               ClearHit(EHitLayer l)  { fHits.ClearBit(l); } 
      Double_t	         D0()             const { return -fDxy; }
      Double_t	         D0Err()          const { return fDxyErr; }
      Double_t           Dsz()            const { return fDsz; }
      Double_t           DszErr()         const { return fDszErr; }
      Double_t           Dxy()            const { return fDxy; }
      Double_t           DxyErr()         const { return fDxyErr; }
      Double_t           E(Double_t m)    const { return TMath::Sqrt(E2(m)); }
      Double_t           E2(Double_t m)   const { return P2()+m*m; }
      Bool_t             Hit(EHitLayer l) const { return fHits.TestBit(l); }
      Double_t           Lambda()         const { return fLambda; }
      Double_t           LambdaErr()      const { return fLambdaErr; }
      const MCParticle  *MCPart()         const;
      ThreeVector        Mom()            const { return ThreeVector(Px(),Py(),Pz()); }
      FourVector         Mom4(Double_t m) const { return FourVector(Px(),Py(),Pz(),E(m)); }
      UInt_t             Ndof()           const { return fNdof; }
      UInt_t             NHits()          const { return fHits.NBitsSet(); }
      Double_t           P2()             const { return P()*P(); }
      Double_t           P()              const { return TMath::Abs(1./fQOverP); }
      Double_t           Phi()            const { return fPhi0; }
      Double_t	         Phi0()           const { return fPhi0; }
      Double_t	         Phi0Err()        const { return fPhi0Err; }
      Double_t	         Pt()             const { return TMath::Abs(TMath::Cos(fLambda)/fQOverP); }
      Double_t           Px()             const { return Pt()*TMath::Cos(fPhi0); }      
      Double_t           Py()             const { return Pt()*TMath::Sin(fPhi0); }
      Double_t           Pz()             const { return P()*TMath::Sin(fLambda); }
      Double_t           QOverP()         const { return fQOverP; }
      Double_t           QOverPErr()      const { return fQOverPErr; }
      Double_t           Theta()          const { return (TMath::PiOver2() - fLambda); }
      Double_t           Z0()             const { return fDsz/TMath::Cos(fLambda); }
      void               SetChi2(Double_t chi2) { fChi2 = chi2; }
      void	         SetErrors(Double_t qOverPErr, Double_t lambdaErr, Double_t phi0Err, 
                                   Double_t dXyErr, Double_t dSzErr);
      void               SetHelix (Double_t qOverP, Double_t lambda, Double_t phi0, 
                                   Double_t dXy, Double_t dSz);
      void               SetHit(EHitLayer l)      { fHits.SetBit(l); }
      void               SetNdof(UInt_t dof)      { fNdof = dof; }
      void	         SetMCPart(MCParticle *p) { fMCParticleRef = p; }

    protected:
      BitMask64          fHits;                //storage for mostly hit information
      Double_t           fQOverP;              //signed inverse of momentum [1/GeV]
      Double_t           fQOverPErr;           //error of q/p
      Double_t           fLambda;              //pi/2 - polar angle at the reference point
      Double_t           fLambdaErr;           //error of lambda
      Double_t           fPhi0;                //azimuth angle at the given point
      Double_t           fPhi0Err;             //error of azimuthal angle
      Double_t           fDxy;                 //transverse distance to reference point [cm]
      Double_t           fDxyErr;              //error of transverse distance
      Double_t           fDsz;                 //longitudinal distance to reference point [cm]
      Double_t           fDszErr;              //error of longitudinal distance
      Double_t           fChi2;                //chi squared of track fit
      UInt_t             fNdof;                //degree-of-freedom of track fit
      TRef               fMCParticleRef;       //reference to sim particle (for monte carlo)
	      
    ClassDef(Track, 1) // Track class
  };
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetHelix(Double_t qOverP, Double_t lambda, Double_t phi0, 
                                   Double_t dxy, Double_t dsz)
{
  // Set helix parameters.

  fQOverP = qOverP;
  fLambda = lambda;
  fPhi0   = phi0;
  fDxy    = dxy;
  fDsz    = dsz;
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetErrors(Double_t qOverPErr, Double_t lambdaErr, Double_t phi0Err, 
                                   Double_t dxyErr, Double_t dszErr)
{
  // Set helix errors.

  fQOverPErr = qOverPErr;
  fLambdaErr = lambdaErr;
  fPhi0Err   = phi0Err;
  fDxyErr    = dxyErr;
  fDszErr    = dszErr;
}

//--------------------------------------------------------------------------------------------------
inline
const mithep::MCParticle *mithep::Track::MCPart() const 
{ 
  // Get reference to simulated particle.

  return static_cast<const MCParticle*>(fMCParticleRef.GetObject()); 
}
#endif
