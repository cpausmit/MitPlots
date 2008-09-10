//--------------------------------------------------------------------------------------------------
// $Id:$
//
// IsolationTools
//
// Isolation functions to compute various kinds of isolation
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_UTILS_ISOLATIONTOOLS_H
#define MITANA_UTILS_ISOLATIONTOOLS_H

#include <TMath.h>
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/CaloTower.h"

namespace mithep
{
  class IsolationTools {
    public:
      static Double_t TrackIsolation ( const mithep::Track *p, Double_t extRadius, Double_t intRadius, 
                                             Double_t ptLow, Double_t maxVtxZDist, 
                                             mithep::Collection<mithep::Track> *tracks ); 
      static Double_t EcalIsolation ( const SuperCluster *sc, Double_t coneSize, 
                                       Double_t etLow, mithep::Collection<mithep::BasicCluster> 
                                       *basicClusters );
      static Double_t CaloTowerHadIsolation ( const ThreeVector *p,  Double_t extRadius, Double_t intRadius, 
                                              Double_t etLow, mithep::Collection<mithep::CaloTower> 
                                              *caloTowers );
      static Double_t CaloTowerEmIsolation ( const ThreeVector *p,  Double_t extRadius, Double_t intRadius, 
                                              Double_t etLow, mithep::Collection<mithep::CaloTower> 
                                              *caloTowers );
  };
}
#endif
