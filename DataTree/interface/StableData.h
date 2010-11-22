//--------------------------------------------------------------------------------------------------
// $Id: StableData.h,v 1.10 2009/03/20 18:23:27 loizides Exp $
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
        DaughterData(p), fMomAtVertex(mom), fNHitsBeforeVtx(0), fDlClosestHitToVtx(0), fDlClosestHitToVtxErr(0) {}
      StableData(const Particle *p, const ThreeVectorC &mom) :
        DaughterData(p), fMomAtVertex(mom), fNHitsBeforeVtx(0), fDlClosestHitToVtx(0), fDlClosestHitToVtxErr(0) {}
      StableData(const Particle *p, Double_t px, Double_t py, Double_t pz) :
        DaughterData(p), fMomAtVertex(ThreeVector(px,py,pz)), fNHitsBeforeVtx(0), fDlClosestHitToVtx(0), fDlClosestHitToVtxErr(0) {}

      Bool_t               BadLayer(Track::EHitLayer l) const { return fBadLayers.TestBit(l);      }
      const BitMask48     &BadLayers()   const { return fBadLayers;                                }
      Double_t             DlClosestHitToVtx() const { return fDlClosestHitToVtx;                  }
      Double_t             DlClosestHitToVtxErr() const { return fDlClosestHitToVtxErr;            }      
      const BitMask48      MissedLayers() const;
      UInt_t               NMissedLayers() const { return MissedLayers().NBitsSet();                   }
      UInt_t               NWrongLayers()  const { return WrongLayers().NBitsSet();                    }
      UInt_t               NWrongHits()  const { return TMath::Max(UInt_t(fNHitsBeforeVtx),NWrongLayers()); }
      UInt_t               NWrongOrMissingLayers() const { return fBadLayers.NBitsSet();             }
      UShort_t             NHitsBeforeVtx() const { return fNHitsBeforeVtx;                        }
      EObjType             ObjType()     const { return kStableData;                               }
      ThreeVectorC         ThreeMom()    const { return fMomAtVertex.V();                          }
      const BitMask48      WrongLayers() const;
      void                 SetBadLayer(Track::EHitLayer l)       { fBadLayers.SetBit(l);           }
      void                 SetBadLayers(const BitMask48 &layers) { fBadLayers = layers;            }
      void                 SetDlClosestHitToVtx(Double_t x)      { fDlClosestHitToVtx = x;         }
      void                 SetDlClosestHitToVtxErr(Double_t x)   { fDlClosestHitToVtxErr = x;      }      
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      void                 SetThreeMom(const ThreeVector &mom)   { fMomAtVertex = mom; ClearMom(); }
      void                 SetNHitsBeforeVtx(UShort_t n)         { fNHitsBeforeVtx = n;            }

    protected:
      Double_t             GetMass()     const { return Original()->Mass(); }
      void                 GetMom()      const;

      Vect3C               fMomAtVertex;      //fitted momentum at vertex
      BitMask48            fBadLayers;        //layer mask for incorrect or missing hits from
                                              //before or after the decay vertex
                                              //using same bit-layer mapping as mithep::Track
      UShort_t             fNHitsBeforeVtx;  //number of hits before the vertex position
      Double32_t           fDlClosestHitToVtx; //[0,0,14]
      Double32_t           fDlClosestHitToVtxErr; //[0,0,14]      

    ClassDef(StableData, 2) // Stable data class
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
