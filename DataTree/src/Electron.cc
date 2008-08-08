// $Id: $

#include "MitAna/DataTree/interface/Electron.h"

Double_t mithep::Electron::ComputeTrackIsolation( Double_t extRadius, Double_t intRadius,
						  Double_t ptLow, Double_t maxVtxZDist, Collection<Track> *tracks) {

  //Computes the Track Isolation: Summed Transverse Momentum of all tracks inside an 
  //annulus around the electron seed track.  

  int counter;
  double ptSum =0.;

  const Track *electronTrack = this->Trk() ;
  ThreeVector *electronTrackMomentum = new ThreeVector(electronTrack->Mom().X(),electronTrack->Mom().Y(),electronTrack->Mom().Z());    

  for (UInt_t i=0; i<tracks->GetEntries();i++) {   
    ThreeVector *tmpTrackMomentum = new ThreeVector(tracks->At(i)->Mom().X(),tracks->At(i)->Mom().Y(),tracks->At(i)->Mom().Z());
    double tmpPt = tracks->At(i)->Pt();
    double deltaZ = fabs(electronTrack->Z0() - tracks->At(i)->Z0());

    //ignore the track if it is below the pt threshold
    if (tmpPt < ptLow) 
      continue;    
    //ingore the track if it is too far away in Z
    if (deltaZ > maxVtxZDist) 
      continue;
        
    double dphi = (fabs(tmpTrackMomentum->Phi() - electronTrackMomentum->Phi()) > TMath::Pi())?(fabs(tmpTrackMomentum->Phi() - electronTrackMomentum->Phi()) - 2*TMath::Pi()):(fabs(tmpTrackMomentum->Phi() - electronTrackMomentum->Phi()));
    double deta = fabs(tmpTrackMomentum->Eta() - electronTrackMomentum->Eta());
    double dr = TMath::Sqrt(dphi*dphi + deta*deta);   

    //add the track pt if it is inside the annulus
    if ( dr < extRadius && 
	 dr >= intRadius ) {
      ++counter ;
      ptSum += tmpPt;
    }
  }
  return ptSum;  
}

Double_t mithep::Electron::ComputeEcalIsolation( Double_t coneSize, Double_t etLow, Collection<BasicCluster> *basicClusters) {

  //Computes the Ecal Isolation: Summed Transverse Energy of all Basic Clusters inside a  
  //cone around the electron, excluding those that are inside the electron super cluster.

  double ecalIsol=0.;
  ThreeVector *SClusterPosition = new ThreeVector (this->SCluster()->X(),this->SCluster()->Y(),this->SCluster()->Z());    

  const BasicCluster *basicCluster= 0;
  for (UInt_t i=0; i<basicClusters->GetEntries();i++) {    
    basicCluster = basicClusters->At(i);    
    double basicClusterChi2 = basicCluster->ChiSq();
    double basicClusterEnergy    = basicCluster->Energy();
    double basicClusterEta  = basicCluster->Eta();
    double basicClusterEt   = basicClusterEnergy*sin(2*atan(exp(basicClusterEta)));           

    if (basicClusterEt > etLow	&& basicClusterChi2 < 30.) {            
      bool inSuperCluster = false;	  
      
      // loop over the basic clusters of the supercluster
      // to make sure that the basic cluster is not inside
      // the super cluster. We exclude those.
      for (UInt_t j=0; j<this->SCluster()->ClusterSize(); j++) {
        const BasicCluster *tempBasicClusterInSuperCluster = this->SCluster()->Cluster(j);	
        if (tempBasicClusterInSuperCluster == basicCluster) {
          inSuperCluster = true;	    
        }
      }
      
      if (!inSuperCluster) {	    
        ThreeVector *basicClusterPosition = new ThreeVector(basicCluster->X(),
                                                            basicCluster->Y(),
                                                            basicCluster->Z());          	  
        double dphi = (fabs(SClusterPosition->Phi() - basicClusterPosition->Phi()) > TMath::Pi())?(fabs(SClusterPosition->Phi() - basicClusterPosition->Phi()) - 2*TMath::Pi()):(fabs(SClusterPosition->Phi() - basicClusterPosition->Phi()));
        double deta = fabs(SClusterPosition->Eta() - basicClusterPosition->Eta());
        double dr = TMath::Sqrt(dphi*dphi + deta*deta);	  
        if(dr < coneSize) {
          ecalIsol += basicClusterEt;
        }
      }
    }
  } 
  return ecalIsol;
}

ClassImp(mithep::Electron)


