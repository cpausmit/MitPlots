// $Id $

#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
using namespace mitcommon;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
Double_t IsolationTools::TrackIsolation( const Track *p, Double_t extRadius, Double_t intRadius,
						  Double_t ptLow, Double_t maxVtxZDist, 
                                         Collection<Track> *tracks) {

  //Computes the Track Isolation: Summed Transverse Momentum of all tracks inside an 
  //annulus around the electron seed track.  

  double ptSum =0.;  
  for (UInt_t i=0; i<tracks->GetEntries();i++) {   
    ThreeVector *tmpTrackMomentum = new ThreeVector(tracks->At(i)->Mom().X(),
                                                    tracks->At(i)->Mom().Y(),
                                                    tracks->At(i)->Mom().Z());
    double tmpPt = tracks->At(i)->Pt();
    double deltaZ = fabs(p->Z0() - tracks->At(i)->Z0());

    //ignore the track if it is below the pt threshold
    if (tmpPt < ptLow) 
      continue;    
    //ingore the track if it is too far away in Z
    if (deltaZ > maxVtxZDist) 
      continue;
           
    double dr = MathUtils::DeltaR(p->Mom().Phi(),p->Mom().Eta(),tmpTrackMomentum->Phi(),
                                  tmpTrackMomentum->Eta());
    //add the track pt if it is inside the annulus
    if ( dr < extRadius && 
	 dr >= intRadius ) {
      ptSum += tmpPt;
    }
  }
  return ptSum;  
}

//--------------------------------------------------------------------------------------------------
Double_t IsolationTools::EcalIsolation( const SuperCluster *sc, Double_t coneSize, Double_t etLow, 
                                        Collection<BasicCluster> *basicClusters) {

  //Computes the Ecal Isolation: Summed Transverse Energy of all Basic Clusters inside a  
  //cone around the electron, excluding those that are inside the electron super cluster.

  double ecalIsol=0.;
  ThreeVector *SClusterPosition = new ThreeVector (sc->X(),sc->Y(),sc->Z());    
  const BasicCluster *basicCluster= 0;
  for (UInt_t i=0; i<basicClusters->GetEntries();i++) {    
    basicCluster = basicClusters->At(i);    
    double basicClusterChi2 = basicCluster->ChiSq();
    double basicClusterEnergy    = basicCluster->Energy();
    double basicClusterEta  = basicCluster->Eta();
    double basicClusterEt   = basicClusterEnergy*sin(2*atan(exp(basicClusterEta)));           

    if (basicClusterEt > etLow	&& basicClusterChi2 < 30. && basicCluster->AlgoId()==0) {            
      bool inSuperCluster = false;	  
      
      // loop over the basic clusters of the supercluster
      // to make sure that the basic cluster is not inside
      // the super cluster. We exclude those.
      for (UInt_t j=0; j<sc->ClusterSize(); j++) {
        const BasicCluster *tempBasicClusterInSuperCluster = sc->Cluster(j);	
        if (tempBasicClusterInSuperCluster == basicCluster) {
          inSuperCluster = true;	    
        }
      }
      
      if (!inSuperCluster) {	    
        ThreeVector *basicClusterPosition = new ThreeVector(basicCluster->X(),
                                                            basicCluster->Y(),
                                                            basicCluster->Z());          	            
        double dr = MathUtils::DeltaR(SClusterPosition->Phi(), SClusterPosition->Eta(),
                                      basicClusterPosition->Phi(),basicClusterPosition->Eta());       
        if(dr < coneSize) {
          ecalIsol += basicClusterEt;
        }
      }
    }
  } 
  return ecalIsol;
}



//--------------------------------------------------------------------------------------------------
Double_t IsolationTools::CaloTowerHadIsolation( const ThreeVector *p, Double_t extRadius, Double_t intRadius, 
                                                Double_t etLow, Collection<CaloTower> *caloTowers) {

  //Computes the CaloTower Had Et Isolation: Summed Hadronic Transverse Energy of all Calo Towers inside an 
  //annulus around the electron super cluster position
  double sumEt = 0;
  for (UInt_t i=0; i<caloTowers->GetEntries();i++) {    
    double caloTowerEt = caloTowers->At(i)->HadEt();
    double dr = MathUtils::DeltaR(caloTowers->At(i)->Phi(), caloTowers->At(i)->Eta(),p->Phi(), p->Eta());
    if (dr < extRadius && dr > intRadius && caloTowerEt > etLow) {
      sumEt += caloTowerEt;
    }
  }
  return sumEt;
}

Double_t IsolationTools::CaloTowerEmIsolation( const ThreeVector *p, Double_t extRadius, Double_t intRadius, 
                                               Double_t etLow, Collection<CaloTower> *caloTowers) {

  //Computes the CaloTower Em Et Isolation: Summed Hadronic Transverse Energy of all Calo Towers inside an 
  //annulus around the electron super cluster position
  double sumEt = 0;
  for (UInt_t i=0; i<caloTowers->GetEntries();i++) {    
    double caloTowerEt = caloTowers->At(i)->EmEt();
    double dr = MathUtils::DeltaR(caloTowers->At(i)->Phi(), caloTowers->At(i)->Eta(),p->Phi(), p->Eta());
    if (dr < extRadius && dr > intRadius && caloTowerEt > etLow) {
      sumEt += caloTowerEt;
    }
  }
  return sumEt;
}
