//--------------------------------------------------------------------------------------------------
// $Id: StableData.h,v 1.1 2008/09/19 11:58:02 bendavid Exp $
//
// StableData
//
// Additional information on a stable daughter which is specific to a particular decay
// 
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_STABLEDATA_H
#define MITANA_DATATREE_STABLEDATA_H
 
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class StableData : public DaughterData
  {
    public:
      StableData() {}
      StableData(Particle* p, const ThreeVector &mom) :
        DaughterData(p),
        fMomAtVertex(mom) {}
      StableData(Particle* p, Double_t px, Double_t py, Double_t pz) :
        DaughterData(p),
        fMomAtVertex(px,py,pz) {}
      virtual ~StableData() {}

      Double_t             Px()   const { return fMomAtVertex.X(); }
      Double_t             Py()   const { return fMomAtVertex.Y(); }
      Double_t             Pz()   const { return fMomAtVertex.Z(); }
      Double_t             P()    const { return fMomAtVertex.R(); }
      Double_t             E()    const { return TMath::Sqrt(P()*P()+Mass()*Mass()); }
      Double_t             Mass() const { return Original()->Mass(); }
      FourVector           Mom()  const;
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      void                 SetThreeMom(const ThreeVector &mom) { fMomAtVertex = mom; }
      const ThreeVector   &ThreeMom()       const { return fMomAtVertex; }

    protected:
      ThreeVector           fMomAtVertex;      //fitted momentum at vertex

    ClassDef(StableData, 1) // Stable daughter class
  };
}
//-------------------------------------------------------------------------------------------------
inline mithep::FourVector mithep::StableData::Mom() const
{
  // Return Momentum

  return FourVector(Px(), Py(), Pz(), E());
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableData::SetThreeMom(Double_t px, Double_t py, Double_t pz)
{
  // Set four momentum.

  fMomAtVertex.SetXYZ(px, py, pz);
}
#endif
