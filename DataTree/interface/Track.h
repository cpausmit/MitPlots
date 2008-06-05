// $Id: Track.h,v 1.1 2008/06/04 09:08:36 loizides Exp $

#ifndef DATATREE_TRACK_H
#define DATATREE_TRACK_H
 
#include "MitAna/DataTree/interface/DataObject.h"

//--------------------------------------------------------------------------------------------------
//
// Track
//
// Details to be worked out...
//
// Authors: C.Loizides, J. Bendavid
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      Track() {}
      Track(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) {
      	fPhi=phi;
	fD0=d0;
	fPt=pt;
	fDz=dz;
	fTheta=theta;
      }
      ~Track() {}

      void SetHelix(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) {
      	fPhi=phi;
	fD0=d0;
	fPt=pt;
	fDz=dz;
	fTheta=theta;
      }
      
      void SetErrors(Double_t phiErr, Double_t d0Err, Double_t ptErr, Double_t dzErr, Double_t thetaErr) {
      	fPhiErr=phiErr;
	fD0Err=d0Err;
	fPtErr=ptErr;
	fDzErr=dzErr;
	fThetaErr=thetaErr;
      }
      
      Double_t Phi() {return fPhi;}
      Double_t D0() {return fD0;}
      Double_t Pt() {return fPt;}
      Double_t Dz() {return fDz;}
      Double_t Theta() {return fTheta;}
      
      Double_t PhiErr() {return fPhiErr;}
      Double_t D0Err() {return fD0Err;}
      Double_t PtErr() {return fPtErr;}
      Double_t DzErr() {return fDzErr;}
      Double_t ThetaErr() {return fThetaErr;}
      
      Int_t Charge() {return fCharge;}
      
      void SetCharge(Int_t charge) {fCharge=charge;}
      
    protected:
    	Double_t fPhi;
    	Double_t fD0;
	Double_t fPt;
	Double_t fDz;
	Double_t fTheta;
	
	Double_t fPhiErr;
    	Double_t fD0Err;
	Double_t fPtErr;
	Double_t fDzErr;
	Double_t fThetaErr;
	
	Int_t fCharge;
	
	
      
      ClassDef(Track, 1) // Track class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_TRACK_H*/
