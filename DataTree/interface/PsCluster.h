//---------------------------------------------------------------------------------------------------
// $Id: PsCluster.h,v 1.21 2012/04/20 16:06:55 bendavid Exp $
//
// PsCluster
//
// This class holds information of basic reconstructed clusters.
//
// Authors: C.Paus, J.Bendavid, S.Xie
//---------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PSCLUSTER_H
#define MITANA_DATATREE_PSCLUSTER_H

#include <TMath.h>
#include "MitCommon/DataFormats/interface/Vect3C.h"
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep
{
  class PsCluster : public DataObject
  {
    public:
      PsCluster() :
        fEnergy        (0),
        fNHits         (0),
        fInsideMustache(kFALSE),
        fPsPlane       (0)
          {}

      PsCluster(Double_t e, const ThreeVector &p) :
        fEnergy        (e),
        fPoint         (p),
        fNHits         (0),
        fInsideMustache(kFALSE),
        fPsPlane       (0)
          {}

      Double_t         Energy()                  const { return  fEnergy;       }
      Double_t         Et()                      const;
      Double_t         Eta()                     const { return  fPoint.Eta();  }
      EObjType         ObjType()                 const { return  kPsCluster; }
      Double_t         Phi()                     const { return  fPoint.Phi();  }
      ThreeVectorC     Pos()                     const { return  fPoint.V();    }
      void             Print(Option_t *opt="")   const;
      Double_t         Rho()                     const { return  fPoint.Rho();  }
      Int_t            NHits()                   const { return  fNHits;        }
      Bool_t           InsideMustache()          const { return fInsideMustache; }
      UChar_t          PsPlane()                 const { return fPsPlane;       }

      void             SetEnergy(Double_t e)                      {  fEnergy = e;     }
      void             SetXYZ(Double_t x, Double_t y, Double_t z) {  fPoint.SetXYZ(x,y,z); }
      void             SetNHits(Int_t x)                          {  fNHits = x;           }
      void             SetInsideMustache(Bool_t b)                {  fInsideMustache = b;  }
      void             SetPsPlane(UChar_t i)                      {  fPsPlane = i;         }


    protected:

      Double32_t       fEnergy;          //[0,0,14]assigned energy
      Vect3C           fPoint;           //centroid Position

      Int_t            fNHits;
      Double32_t       fSumRecHitEnergy; //energy from manual rechit sum (bug recovery band aid)
      Bool_t           fInsideMustache;  //is inside mustache profile of parent supercluster
      UChar_t          fPsPlane;         //preshower plane (0 for Ecal clusters)

      ClassDef(PsCluster, 1)             // Preshower cluster class
  };
}

//---------------------------------------------------------------------------------------------------
inline Double_t mithep::PsCluster::Et() const
{
  // Return transverse energy.

  return fEnergy*fPoint.Rho()/fPoint.V().R();
}
#endif
