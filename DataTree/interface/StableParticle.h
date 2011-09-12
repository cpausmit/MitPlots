//--------------------------------------------------------------------------------------------------
// $Id: StableParticle.h,v 1.11 2009/03/18 15:44:32 loizides Exp $
//
// StableParticle
//
// Generic stable particle with track. Stores absolute pdg code and link to track.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_STABLEPARTICLE_H
#define MITANA_DATATREE_STABLEPARTICLE_H
 
#include "MitAna/DataTree/interface/ChargedParticle.h"

namespace mithep 
{
  class StableParticle : public ChargedParticle
  {
    public:
      StableParticle() : fAbsPdgId(0) {}
      StableParticle(UInt_t absPdgId) : fAbsPdgId(absPdgId) {}
      StableParticle(UInt_t absPdgId, const Track *track) : fAbsPdgId(absPdgId), fTrackRef(track) {}
      
      UInt_t               AbsPdgId()         const { return fAbsPdgId;       }
      const Track         *Trk()              const { return fTrackRef.Obj(); }
      const Track         *TrackerTrk()       const { return Trk();           }
      EObjType             ObjType()          const { return kStableParticle; }      
      TParticlePDG        *PdgEntry()         const;
      void                 SetAbsPdgId(UInt_t apdg) { fAbsPdgId=apdg; ClearMom();               }
      void	           SetTrk(const Track *t)   { fTrackRef = t; ClearMom(); ClearCharge(); }
      
    protected:
      Double_t             GetMass()          const;

      UInt_t               fAbsPdgId;    //pdg identifier (absolute value)
      Ref<Track>           fTrackRef;    //tracker track reference
      
    ClassDef(StableParticle, 1) // Stable particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::StableParticle::GetMass() const
{
  // Get mass from pdg lookup.

  TParticlePDG *pdgEntry = PdgEntry();
  if (pdgEntry)
    return pdgEntry->Mass();
  else {
    Error("GetMass", 
          "Absolute pdg code %i not found in table, returning mass=-99.0 GeV", fAbsPdgId);
    return -99.0;
  }
}
#endif
