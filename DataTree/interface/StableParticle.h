//--------------------------------------------------------------------------------------------------
// $Id: StableParticle.h,v 1.6 2008/10/31 17:41:44 bendavid Exp $
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
      StableParticle(UInt_t absPdgId, Track *track) : fAbsPdgId(absPdgId), fTrackRef(track) {}
      ~StableParticle() {}
      
      UInt_t               AbsPdgId()         const { return fAbsPdgId;       }
      const Track         *Trk()              const;
      const Track         *TrackerTrk()       const { return Trk();           }
      Double_t             Mass()             const;
      EObjType             ObjType()          const { return kStableParticle; }      
      TParticlePDG        *ParticlePdgEntry() const;
      void                 SetAbsPdgId(UInt_t absPdgId) { fAbsPdgId=absPdgId; }
      void	           SetTrk(Track *t)             { fTrackRef = t;      }
      
    protected:
      UInt_t               fAbsPdgId; //pdg identifier (absolute value)
      TRef	           fTrackRef; //tracker track reference
      
    ClassDef(StableParticle, 1) // Stable particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::StableParticle::Trk() const
{
  // Return tracker track.

  return static_cast<const Track*>(fTrackRef.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::StableParticle::ParticlePdgEntry() const 
{ 
  // Return entry to pdg database for the PARTICLE.

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}
#endif
