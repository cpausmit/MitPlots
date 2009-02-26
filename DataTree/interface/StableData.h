//--------------------------------------------------------------------------------------------------
// $Id: StableData.h,v 1.6 2009/02/18 15:38:54 loizides Exp $
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
        DaughterData(p), fMomAtVertex(mom) {}
      StableData(Particle* p, Double_t px, Double_t py, Double_t pz) :
        DaughterData(p), fMomAtVertex(px,py,pz) {}

      Bool_t               BadLayer(Track::EHitLayer l) const { return fBadLayers.TestBit(l); }
      const BitMask48     &BadLayers()   const { return fBadLayers; }
      const BitMask48      MissedHits()  const;
      UInt_t               NMissedHits() const { return MissedHits().NBitsSet(); }
      UInt_t               NWrongHits()  const { return WrongHits().NBitsSet(); }
      UInt_t               NWrongOrMissingHits() const { return fBadLayers.NBitsSet(); }
      EObjType             ObjType()     const { return kStableData; }      
      const ThreeVector   &ThreeMom()    const { return fMomAtVertex; }
      const BitMask48      WrongHits()   const;
      void                 SetBadLayer(Track::EHitLayer l)       { fBadLayers.SetBit(l); }
      void                 SetBadLayers(const BitMask48 &layers) { fBadLayers = layers; }
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      void                 SetThreeMom(const ThreeVector &mom)   { fMomAtVertex = mom; ClearMom(); }

    protected:
      Double_t             GetMass()     const { return Original()->Mass(); }
      void                 GetMom()      const;

      ThreeVector32        fMomAtVertex;      //fitted momentum at vertex
      BitMask48            fBadLayers;        //layer mask for incorrect or missing hits from
                                              //before or after the decay vertex
                                              //using same bit-layer mapping as mithep::Track

    ClassDef(StableData, 1) // Stable daughter class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableData::GetMom() const
{
  // Get momentum values from stored values.

  Double_t pt = TMath::Sqrt(fMomAtVertex.X()*fMomAtVertex.X()+fMomAtVertex.Y()*fMomAtVertex.Y());
  fCachedMom.SetCoordinates(pt,fMomAtVertex.Eta(),fMomAtVertex.Phi(),GetMass()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableData::SetThreeMom(Double_t px, Double_t py, Double_t pz)
{
  // Set four momentum.

  fMomAtVertex.SetXYZ(px, py, pz);
  ClearMom();
}
#endif
