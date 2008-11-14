//--------------------------------------------------------------------------------------------------
// $Id: BasicCluster.h,v 1.3 2008/09/17 04:21:16 loizides Exp $
//
// Basic Clusters
//
// Details to be worked out...
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
      BasicCluster() : fEnergy(0.0), fPoint(0,0,0) {}
      BasicCluster(Double_t Energy, ThreeVector Point) : 
	fEnergy(Energy), fPoint(Point) {}
      ~BasicCluster() {}
     
      Int_t	       AlgoId()                 const { return fAlgoId; }
      Double_t	       ChiSq()                  const { return fChiSq; }      
      Double_t         Energy()                 const { return fEnergy; }      
      Double_t         Eta()                    const { return fPoint.Eta(); }
      Double_t         Phi()                    const { return fPoint.Phi(); }
      Double_t         X()                      const { return fPoint.X(); }
      Double_t         Y()                      const { return fPoint.Y(); }
      Double_t         Z()                      const { return fPoint.Z(); }      
      void             Print(Option_t *opt="")  const;

      void	       SetAlgoId(Int_t AlgoId)                    { fAlgoId = AlgoId; }
      void	       SetChiSq(Double_t ChiSq)                   { fChiSq = ChiSq; }           
      void	       SetEnergy(Double_t Energy)                 { fEnergy = Energy; }      
      void	       SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z); }
 
    protected:
      
      Double32_t       fEnergy;  //BasicCluster energy      
      ThreeVector32    fPoint;   //Centroid Position
      Int_t            fAlgoId;  //Algorithm ID: island = 0, hybrid = 1, fixedMatrix = 2, 
                                 //dynamicHybrid = 3, multi5x5 = 4
      Double32_t       fChiSq;   //Chi sq       
      
      ClassDef(BasicCluster, 1)  // BasicCluster class
  };
}
#endif
