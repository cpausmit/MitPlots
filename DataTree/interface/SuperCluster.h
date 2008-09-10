//--------------------------------------------------------------------------------------------------
// $Id: SuperCluster.h,v 1.2 2008/08/18 09:27:42 sixie Exp $
//
// SuperCluster
//
// Details to be worked out...
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_SUPERCLUSTER_H
#define MITANA_DATATREE_SUPERCLUSTER_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class SuperCluster : public DataObject
  {
    public:
      SuperCluster() : fEnergy(0.0), fPoint(0,0,0) , fRawEnergy(-1.0) {}     
      ~SuperCluster() {}
 
      const BasicCluster  *Cluster(UInt_t i)       const { return fClusters.At(i); }
      UInt_t               ClusterSize()           const { return fClusters.GetEntries(); }
      Double_t             Energy()                const { return fEnergy; }      
      Double_t             Eta()                   const { return fPoint.Eta(); }
      Double_t             EtaWidth()              const { return fEtaWidth; }
      Double_t             Phi()                   const { return fPoint.Phi(); }
      Double_t             PhiWidth()              const { return fPhiWidth; }
      Double_t             PreshowerEnergy()       const { return fPreshowerEnergy; }
      Double_t             RawEnergy()             const { return fRawEnergy; }      
      const BasicCluster  *Seed()                  const;       
      Double_t             X()                     const { return fPoint.X(); }
      Double_t             Y()                     const { return fPoint.Y(); }
      Double_t             Z()                     const { return fPoint.Z(); }
      void                 Print(Option_t *opt="") const;

      void	           AddCluster( BasicCluster *Cluster)           { fClusters.Add(Cluster); }
      void	           SetEnergy(Double_t Energy)                   { fEnergy = Energy;       }
      void	           SetEtaWidth(Double_t EtaWidth)               { fEtaWidth = EtaWidth;   }
      void	           SetPhiWidth(Double_t PhiWidth)               { fPhiWidth = PhiWidth;   }
      void	           SetPreshowerEnergy(Double_t PreshowerEnergy) { fPreshowerEnergy 
                                                                            = PreshowerEnergy;    }
      void	           SetRawEnergy(Double_t RawEnergy)             { fRawEnergy = RawEnergy; }
      void	           SetSeed( BasicCluster* SeedRef)              { fSeedRef = SeedRef;     } 
      void	           SetXYZ(Double_t x, Double_t y, Double_t z)   { fPoint.SetXYZ(x,y,z);   }
      
    protected:
      
      Double_t                  fEnergy;          //Supercluster energy     
      Double_t                  fEtaWidth;        //Width in Phi
      ThreeVector               fPoint;           //Centroid Position
      Double_t                  fPreshowerEnergy; //Energy in the preshower
      Double_t                  fPhiWidth;        //Width in Phi
      Double_t                  fRawEnergy;       //Supercluster raw energy
      RefArray<BasicCluster>    fClusters;        //||BasicClusters in this SuperCluster
      TRef                      fSeedRef;         //the seed cluster

      ClassDef(SuperCluster, 1) // Generic particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::BasicCluster *mithep::SuperCluster::Seed() const 
{ 
  // Return tracker track.

  return static_cast<const BasicCluster*>(fSeedRef.GetObject()); 
}
#endif
