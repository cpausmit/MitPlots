//--------------------------------------------------------------------------------------------------
// $Id: StableParticle.h,v 1.9 2009/02/18 15:38:55 loizides Exp $
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
      TParticlePDG        *ParticlePdgEntry() const;
      void                 SetAbsPdgId(UInt_t absPdgId) { fAbsPdgId=absPdgId; ClearMom(); }
      void	           SetTrk(const Track *t) { fTrackRef = t; ClearMom(); ClearCharge(); }
      
    protected:
      Double_t             GetMass()          const;

      UInt_t               fAbsPdgId; //pdg identifier (absolute value)
      Ref<Track>           fTrackRef; //tracker track reference
      
    ClassDef(StableParticle, 1) // Stable particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::StableParticle::GetMass() const
{
  // Get Mass from Pdg Lookup

  TParticlePDG* pdgEntry = ParticlePdgEntry();
  if (pdgEntry)
    return pdgEntry->Mass();
  else {
    Error("GetMass", 
          "Absolute pdg code %i not found in table, returning mass=-99.0 GeV", fAbsPdgId);
    return -99.0;
  }
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::StableParticle::ParticlePdgEntry() const 
{ 
  // Return entry to pdg database for the PARTICLE.

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}
#endif
