//--------------------------------------------------------------------------------------------------
// $Id: SuperCluster.h,v 1.6 2008/11/14 14:46:35 bendavid Exp $
//
// SuperCluster
//
// This class holds the super cluster information.
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
      SuperCluster() : fEnergy(0), fEtaWidth(0), fPreshowerEnergy(0), 
                       fPhiWidth(0), fRawEnergy(0) {}     
      ~SuperCluster() {}
 
      const BasicCluster  *Cluster(UInt_t i)       const { return fClusters.At(i); }
      UInt_t               ClusterSize()           const { return fClusters.GetEntries(); }
      Double_t             Energy()                const { return fEnergy; }      
      Double_t             Eta()                   const { return fPoint.Eta(); }
      Double_t             EtaWidth()              const { return fEtaWidth; }
      EObjType             ObjType()               const { return kSuperCluster; }      
      Double_t             Phi()                   const { return fPoint.Phi(); }
      Double_t             PhiWidth()              const { return fPhiWidth; }
      void                 Print(Option_t *opt="") const;
      Double_t             PreshowerEnergy()       const { return fPreshowerEnergy; }
      Double_t             RawEnergy()             const { return fRawEnergy; }      
      const BasicCluster  *Seed()                  const;       
      Double_t             X()                     const { return fPoint.X(); }
      Double_t             Y()                     const { return fPoint.Y(); }
      Double_t             Z()                     const { return fPoint.Z(); }
      void	           AddCluster(const BasicCluster *c)            { fClusters.Add(c);       }
      void	           SetEnergy(Double_t energy)                   { fEnergy = energy;       }
      void	           SetEtaWidth(Double_t etaWidth)               { fEtaWidth = etaWidth;   }
      void	           SetPhiWidth(Double_t phiWidth)               { fPhiWidth = phiWidth;   }
      void	           SetPreshowerEnergy(Double_t e)               { fPreshowerEnergy = e;   }
      void	           SetRawEnergy(Double_t rawEnergy)             { fRawEnergy = rawEnergy; }
      void	           SetSeed(const BasicCluster *s)               
                             { fSeedRef = const_cast<BasicCluster*>(s); } 
      void	           SetXYZ(Double_t x, Double_t y, Double_t z)   { fPoint.SetXYZ(x,y,z);   }
      
    protected:
      Double32_t                  fEnergy;          //super cluster energy     
      Double32_t                  fEtaWidth;        //width in Phi
      ThreeVector32               fPoint;           //centroid Position
      Double32_t                  fPreshowerEnergy; //energy in the preshower
      Double32_t                  fPhiWidth;        //width in Phi
      Double32_t                  fRawEnergy;       //super cluster raw energy
      RefArray<BasicCluster,1024> fClusters;        //assigned basic clusters
      TRef                        fSeedRef;         //seed cluster

    ClassDef(SuperCluster, 1) // Super cluster class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::BasicCluster *mithep::SuperCluster::Seed() const 
{ 
  // Return basic cluster seed.

  return static_cast<const BasicCluster*>(fSeedRef.GetObject()); 
}
#endif
