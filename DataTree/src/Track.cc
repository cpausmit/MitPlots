// $Id: Track.cc,v 1.1 2008/06/04 09:08:36 loizides Exp $

#include "MitAna/DataTree/interface/Track.h"

ClassImp(mithep::Track)

using namespace mithep;

void	Track::SetHelix(Double_t phi, Double_t d0, Double_t pt, Double_t dz, Double_t theta) {
      	fPhi=phi;
	fD0=d0;
	fPt=pt;
	fDz=dz;
	fTheta=theta;
      }
      
void	Track::SetErrors(Double_t phiErr, Double_t d0Err, Double_t ptErr, Double_t dzErr, Double_t thetaErr) {
      	fPhiErr=phiErr;
	fD0Err=d0Err;
	fPtErr=ptErr;
	fDzErr=dzErr;
	fThetaErr=thetaErr;
      }
