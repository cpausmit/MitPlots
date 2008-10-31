//--------------------------------------------------------------------------------------------------
// $Id: StableData.h,v 1.3 2008/10/16 16:19:39 bendavid Exp $
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
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/BitMask.h"
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
      Bool_t               BadLayer(Track::EHitLayer l) const { return fBadLayers.TestBit(l); }
      const BitMask48     &BadLayers() const { return fBadLayers; }
      Double_t             Mass() const { return Original()->Mass(); }
      const BitMask48      MissedHits() const;
      FourVector           Mom()  const;
      UInt_t               NWrongOrMissingHits() const { return fBadLayers.NBitsSet(); }
      UInt_t               NMissedHits() const { return MissedHits().NBitsSet(); }
      UInt_t               NWrongHits()  const { return WrongHits().NBitsSet(); }
      void                 SetBadLayer(Track::EHitLayer l) { fBadLayers.SetBit(l); }
      void                 SetBadLayers(const BitMask48 &layers) { fBadLayers = layers; }
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      void                 SetThreeMom(const ThreeVector &mom) { fMomAtVertex = mom; }
      const ThreeVector   &ThreeMom()       const { return fMomAtVertex; }
      const BitMask48      WrongHits() const;

    protected:
      ThreeVector32        fMomAtVertex;      //fitted momentum at vertex
      BitMask48            fBadLayers;        //layer mask for incorrect or missing hits from
                                              //before or after the decay vertex
                                              //using same bit-layer mapping as mithep::Track

    ClassDef(StableData, 3) // Stable daughter class
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
