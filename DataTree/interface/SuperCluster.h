//--------------------------------------------------------------------------------------------------
// $Id: SuperCluster.h,v 1.12 2009/04/08 10:24:33 loizides Exp $
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
#include "MitCommon/DataFormats/interface/Vect3C.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class SuperCluster : public DataObject
  {
    public:
      SuperCluster() : fEnergy(0), fEtaWidth(0), fPreshowerEnergy(0), 
                       fPhiWidth(0), fRawEnergy(0) {}     
 
      void	              AddCluster(const BasicCluster *c)          { fClusters.Add(c);       }
      const BasicCluster     *Cluster(UInt_t i)       const { return fClusters.At(i);              }
      UInt_t                  ClusterSize()           const { return fClusters.Entries();          }
      Int_t                   Compare(const TObject *o) const;   
      Double_t                Energy()                const { return fEnergy;                      }
      Double_t                Eta()                   const { return fPoint.Eta();                 }
      Double_t                EtaWidth()              const { return fEtaWidth;                    }
      Bool_t                  IsSortable()            const { return kTRUE;                        }
      EObjType                ObjType()               const { return kSuperCluster;                }
      Double_t                Phi()                   const { return fPoint.Phi();                 }
      Double_t                PhiWidth()              const { return fPhiWidth;                    }
      ThreeVectorC            Point()                 const { return fPoint.V();                   }
      void                    Print(Option_t *opt="") const;
      Double_t                PreshowerEnergy()       const { return fPreshowerEnergy;             }
      Double_t                RawEnergy()             const { return fRawEnergy;                   }
      Double_t                Rho()                   const { return fPoint.Rho();                 }
      const BasicCluster     *Seed()                  const { return fSeedRef.Obj();               }
      void	              SetEnergy(Double_t energy)                 { fEnergy = energy;       }
      void	              SetEtaWidth(Double_t etaWidth)             { fEtaWidth = etaWidth;   }
      void	              SetPhiWidth(Double_t phiWidth)             { fPhiWidth = phiWidth;   }
      void	              SetPreshowerEnergy(Double_t e)             { fPreshowerEnergy = e;   }
      void	              SetRawEnergy(Double_t rawEnergy)           { fRawEnergy = rawEnergy; }
      void	              SetSeed(const BasicCluster *s)             { fSeedRef = s;           }
      void	              SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z);   }
      
    protected:
      Vect3C                  fPoint;           //centroid Position
      Double32_t              fEnergy;          //[0,0,14]super cluster energy     
      Double32_t              fEtaWidth;        //[0,0,14]width in Phi
      Double32_t              fPreshowerEnergy; //[0,0,14]energy in the preshower
      Double32_t              fPhiWidth;        //[0,0,14]width in Phi
      Double32_t              fRawEnergy;       //[0,0,14]super cluster raw energy
      RefArray<BasicCluster>  fClusters;        //assigned basic clusters
      Ref<BasicCluster>       fSeedRef;         //seed cluster

    ClassDef(SuperCluster, 1) // Super cluster class
  };
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::SuperCluster::Compare(const TObject *o) const
{
  // Default compare function for sorting according to transverse momentum. 
  // Returns -1 if this object is smaller than given object, 0 if objects are 
  // equal and 1 if this is larger than given object.

  const mithep::SuperCluster *s = dynamic_cast<const mithep::SuperCluster *>(o);
  if (!s)
    return 1;

  Double_t mye = Energy();
  Double_t e   = s->Energy();
  if (mye>e)
    return -1;
  else if (e>mye)
    return +1;
  return 0;
}
#endif
