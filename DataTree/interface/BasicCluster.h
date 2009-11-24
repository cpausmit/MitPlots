//--------------------------------------------------------------------------------------------------
// $Id: BasicCluster.h,v 1.12 2009/04/08 10:22:59 loizides Exp $
//
// BasicCluster
//
// This class holds information of basic reconstructed clusters.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BASICCLUSTER_H
#define MITANA_DATATREE_BASICCLUSTER_H
 
#include <TMath.h>
#include "MitCommon/DataFormats/interface/Vect3C.h"
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class BasicCluster : public DataObject
  {
    public:
      BasicCluster() : fEnergy(0) {}
      BasicCluster(Double_t e, const ThreeVector &p) : 
        fEnergy(e), fPoint(p) {}
     
      Double_t         Energy()                 const { return fEnergy;       }       
      Double_t         Et()                     const;
      Double_t         Eta()                    const { return fPoint.Eta();  }
      EObjType         ObjType()                const { return kBasicCluster; }       
      Double_t         Phi()                    const { return fPoint.Phi();  }
      ThreeVectorC     Pos()                    const { return fPoint.V();    }
      void             Print(Option_t *opt="")  const;
      Double_t         Rho()                    const { return fPoint.Rho();  }
      void	       SetEnergy(Double_t energy)                 { fEnergy = energy;     }      
      void	       SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z); } 

    protected:
        
      Double32_t       fEnergy;  //[0,0,14]assigned energy      
      Vect3C           fPoint;   //centroid Position
      
      ClassDef(BasicCluster, 1)  // Basic cluster class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::BasicCluster::Et() const
{
  // Return transverse energy.

  return fEnergy*fPoint.Rho()/fPoint.V().R();
}
#endif
