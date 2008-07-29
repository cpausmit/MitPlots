//--------------------------------------------------------------------------------------------------
// $Id: StableParticle.h,v 1.1 2008/07/25 16:04:44 bendavid Exp $
//
// StableParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_STABLEPARTICLE_H
#define DATATREE_STABLEPARTICLE_H
 
#include "MitAna/DataTree/interface/ChargedParticle.h"

namespace mithep 
{
  class StableParticle : public ChargedParticle
  {
    public:
      StableParticle() {}
      StableParticle(UInt_t absPdgId, Track *track) : fAbsPdgId(absPdgId), fTrackRef(track) {}
      ~StableParticle() {}
      
      UInt_t               AbsPdgId()         const { return fAbsPdgId; }
      const Track         *Trk()              const;
      Double_t             Mass()             const;
      TParticlePDG        *ParticlePdgEntry() const;
      
      void                 SetAbsPdgId(UInt_t absPdgId) { fAbsPdgId=absPdgId; }
      void	           SetTrk(Track* t) { fTrackRef = t; }
      
    protected:
      UInt_t               fAbsPdgId; //pdg identifier (absolute value)
      TRef	           fTrackRef; //tracker track reference
      
    ClassDef(StableParticle, 1) // StableParticle class
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
