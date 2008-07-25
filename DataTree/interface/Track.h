//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.13 2008/07/14 20:55:19 loizides Exp $
//
// Track
//
// This will/must be re-written :-)
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_TRACK_H
#define DATATREE_TRACK_H
 
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      Track() : fPhi(0), fD0(0), fPt(0), fDz(0), fTheta(0), fPhiErr(0), fD0Err(0), fPtErr(0),
                fDzErr(0), fThetaErr(0), fCharge(0) {}
      Track(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) :
	fPhi(phi), fD0(d0), fPt(pt), fDz(dz), fTheta(theta), fPhiErr(0), fD0Err(0), fPtErr(0),
        fDzErr(0), fThetaErr(0), fCharge(0) {}
      ~Track() {}

      Int_t	         Charge()       const { return fCharge; }      
      Double_t	         D0()           const { return fD0; }
      Double_t	         D0Err()        const { return fD0Err; }
      Double_t	         Dz()           const { return fDz; }
      Double_t	         DzErr()        const { return fDzErr; }
      ThreeVector        Mom()          const { return ThreeVector(Px(),Py(),Pz()); }
      Double_t           P2()           const { return Px()*Px()+Py()*Py()+Pz()*Pz(); }
      Double_t           P()            const { return TMath::Sqrt(P2()); }
      Double_t           Px()           const { return TMath::Cos(fPhi)*fabs(fPt); }      
      Double_t           Py()           const { return TMath::Sin(fPhi)*fabs(fPt); }
      Double_t           Pz()           const { return TMath::Abs(fPt)/TMath::Tan(fTheta); }
      Double_t	         Phi()          const { return fPhi; }
      Double_t	         PhiErr()       const { return fPhiErr; }
      Double_t	         Pt()           const { return fPt; }
      Double_t	         PtErr()        const { return fPtErr; }
      Double_t	         Theta()        const { return fTheta; }
      Double_t	         ThetaErr()     const { return fThetaErr; }
      
      FourVector         Mom4(double m) const { return FourVector(Px(),Py(),Pz(),E(m)); }
      Double_t           E2(double m)   const { return P2()+m*m; }
      Double_t           E(double m)    const { return TMath::Sqrt(E2(m)); }

      void	         SetCharge(Int_t charge) { fCharge = charge; }
      void               SetHelix (Double_t phi, Double_t d0, Double_t pt, 
                                   Double_t dz, Double_t theta);
      void	         SetErrors(Double_t phiErr, Double_t d0Err, Double_t ptErr, 
                                   Double_t dzErr, Double_t thetaErr);
      
      const MCParticle  *MCPart()      const;
      void	         SetMCPart(MCParticle *p) { fMCParticleRef = p; }
      
    protected:
      Double_t           fPhi;            //azimuthal angle
      Double_t           fD0;             //raw impact parameter
      Double_t           fPt;             //transverse momentum
      Double_t           fDz;             //z-displacement
      Double_t           fTheta;          //polar angle
      Double_t           fPhiErr;         //uncertainy on phi
      Double_t           fD0Err;          //uncertainty on D0
      Double_t           fPtErr;          //uncertainty on pt
      Double_t           fDzErr;          //uncertainty on dz
      Double_t           fThetaErr;       //uncertainty on theta
      Int_t              fCharge;         //electric charge of reconstructed track
      TRef               fMCParticleRef; //reference to sim particle (for monte carlo)
	      
    ClassDef(Track, 1) // Track class
  };
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetHelix(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) 
{
  // Set helix parameters.

  fPhi   = phi;
  fD0    = d0;
  fPt    = pt;
  fDz    = dz;
  fTheta = theta;
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetErrors(Double_t phiErr, Double_t d0Err, Double_t ptErr, Double_t dzErr,
			      Double_t thetaErr) 
{
  // Set helix errors.

  fPhiErr   = phiErr;
  fD0Err    = d0Err;
  fPtErr    = ptErr;
  fDzErr    = dzErr;
  fThetaErr = thetaErr;
}

//--------------------------------------------------------------------------------------------------
inline
const mithep::MCParticle *mithep::Track::MCPart() const 
{ 
  // Get reference to simulated particle.

  return static_cast<const MCParticle*>(fMCParticleRef.GetObject()); 
}
#endif
