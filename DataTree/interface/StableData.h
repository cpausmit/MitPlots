//--------------------------------------------------------------------------------------------------
// $Id: StableData.h,v 1.9 2009/03/18 15:44:32 loizides Exp $
//
// StableData
//
// Additional information on a stable daughter which is specific to a particular decay.
// 
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_STABLEDATA_H
#define MITANA_DATATREE_STABLEDATA_H
 
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Types.h"
#include "MitCommon/DataFormats/interface/Vect3C.h"

namespace mithep 
{
  class StableData : public DaughterData
  {
    public:
      StableData() {}
      StableData(const Particle *p, const ThreeVector &mom) :
        DaughterData(p), fMomAtVertex(mom) {}
      StableData(const Particle *p, const ThreeVectorC &mom) :
        DaughterData(p), fMomAtVertex(mom) {}
      StableData(const Particle *p, Double_t px, Double_t py, Double_t pz) :
        DaughterData(p), fMomAtVertex(ThreeVector(px,py,pz)) {}

      Bool_t               BadLayer(Track::EHitLayer l) const { return fBadLayers.TestBit(l);      }
      const BitMask48     &BadLayers()   const { return fBadLayers;                                }
      const BitMask48      MissedHits()  const;
      UInt_t               NMissedHits() const { return MissedHits().NBitsSet();                   }
      UInt_t               NWrongHits()  const { return WrongHits().NBitsSet();                    }
      UInt_t               NWrongOrMissingHits() const { return fBadLayers.NBitsSet();             }
      EObjType             ObjType()     const { return kStableData;                               }
      ThreeVectorC         ThreeMom()    const { return fMomAtVertex.V();                          }
      const BitMask48      WrongHits()   const;
      void                 SetBadLayer(Track::EHitLayer l)       { fBadLayers.SetBit(l);           }
      void                 SetBadLayers(const BitMask48 &layers) { fBadLayers = layers;            }
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      void                 SetThreeMom(const ThreeVector &mom)   { fMomAtVertex = mom; ClearMom(); }

    protected:
      Double_t             GetMass()     const { return Original()->Mass(); }
      void                 GetMom()      const;

      Vect3C               fMomAtVertex;      //fitted momentum at vertex
      BitMask48            fBadLayers;        //layer mask for incorrect or missing hits from
                                              //before or after the decay vertex
                                              //using same bit-layer mapping as mithep::Track

    ClassDef(StableData, 1) // Stable data class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableData::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMomAtVertex.Rho(),fMomAtVertex.Eta(),fMomAtVertex.Phi(),GetMass()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableData::SetThreeMom(Double_t px, Double_t py, Double_t pz)
{
  // Set four momentum.

  fMomAtVertex.SetXYZ(px, py, pz);
  ClearMom();
}
#endif
