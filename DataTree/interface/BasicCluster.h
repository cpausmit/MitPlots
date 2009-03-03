//--------------------------------------------------------------------------------------------------
// $Id: BasicCluster.h,v 1.7 2009/02/18 15:38:54 loizides Exp $
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
      Double_t         Eta()                    const { return fPoint.Eta();  }
      EObjType         ObjType()                const { return kBasicCluster; }       
      Double_t         Phi()                    const { return fPoint.Phi();  }
      Double_t         X()                      const { return fPoint.X();    }
      Double_t         Y()                      const { return fPoint.Y();    }
      Double_t         Z()                      const { return fPoint.Z();    }        
      void             Print(Option_t *opt="")  const;
      void	       SetEnergy(Double_t energy)                 { fEnergy = energy;     }      
      void	       SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z); } 

    protected:
        
      Double32_t       fEnergy;  //assigned energy      
      ThreeVector32    fPoint;   //centroid Position
      
      ClassDef(BasicCluster, 1)  // Basic cluster class
  };
}
#endif
