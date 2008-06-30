//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.8 2008/06/24 14:01:41 loizides Exp $
//
// Track
//
// This will be re-written :-)
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_TRACK_H
#define DATATREE_TRACK_H
 
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/SimParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      Track() {}
      Track(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) :
	fPhi(phi), fD0(d0), fPt(pt), fDz(dz), fTheta(theta) {}
      ~Track() {}

      void	SetHelix (Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta);
      void	SetErrors(Double_t phiErr, Double_t d0Err, Double_t ptErr, Double_t dzErr,
			  Double_t thetaErr);
      
      Double_t	Phi()      const { return fPhi; }
      Double_t	D0()       const { return fD0; }
      Double_t	Pt()       const { return fPt; }
      Double_t	Dz()       const { return fDz; }
      Double_t	Theta()    const { return fTheta; }
      
      Double_t	PhiErr()   const { return fPhiErr; }
      Double_t	D0Err()    const { return fD0Err; }
      Double_t	PtErr()    const { return fPtErr; }
      Double_t	DzErr()    const { return fDzErr; }
      Double_t	ThetaErr() const { return fThetaErr; }

      Double_t  Px() { return cos(fPhi)*fabs(fPt); }      
      Double_t  Py() { return sin(fPhi)*fabs(fPt); }
      Double_t  Pz() { return fabs(fPt)/tan(fTheta); }
      Double_t  P() { return sqrt( Px()*Px() + Py()*Py() + Pz()*Pz() ); }
      
      ThreeVector Mom() { return ThreeVector(Px(),Py(),Pz()); }
      
      Int_t	Charge()   const { return fCharge; }
      
      void	SetCharge(Int_t charge) { fCharge = charge; }
      
      SimParticle* GetSimParticle() { return (SimParticle*)fSimParticleRef.GetObject(); }
      
      void	SetSimParticle(SimParticle* simPart) { fSimParticleRef = simPart; }
      
      
    protected:
      Double_t fPhi;      // azimuthal angle
      Double_t fD0;       // raw impact parameter
      Double_t fPt;       // transverse momentum
      Double_t fDz;       // z-displacement
      Double_t fTheta;    // polar angle
      Double_t fPhiErr;   // uncertainy on phi
      Double_t fD0Err;    // uncertainty on D0
      Double_t fPtErr;    // uncertainty on pt
      Double_t fDzErr;    // uncertainty on dz
      Double_t fThetaErr; // uncertainty on theta
      Int_t    fCharge;   // electric charge of reconstructed track
      TRef     fSimParticleRef; //reference to sim particle (for monte carlo)
	      
    ClassDef(Track, 1) // Track class
  };
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetHelix(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) 
{
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
  fPhiErr   = phiErr;
  fD0Err    = d0Err;
  fPtErr    = ptErr;
  fDzErr    = dzErr;
  fThetaErr = thetaErr;
}
#endif
