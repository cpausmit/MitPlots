//--------------------------------------------------------------------------------------------------
// $Id: ChargedParticle.h,v 1.8 2009/02/18 15:38:54 loizides Exp $
//
// ChargedParticle
//
// Abstract base class for particles which have a corresponding track.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CHARGEDPARTICLE_H
#define MITANA_DATATREE_CHARGEDPARTICLE_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class ChargedParticle : public Particle
  {
    public:
      ChargedParticle() {}

      EObjType                ObjType()    const { return kChargedParticle; }
      virtual const Track    *TrackerTrk() const { return Trk();            }
      virtual const Track    *Trk()        const = 0;

    protected:
      Double_t                GetCharge()  const;
      void                    GetMom()     const;

    ClassDef(ChargedParticle, 1) // Charged particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::ChargedParticle::GetCharge() const
{
  // Get charge from track.

  const mithep::Track *trk = Trk();
  if (trk) 
    return trk->Charge();
  else 
    return 0;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::ChargedParticle::GetMom() const
{
  // Get momentum values from track.

  const mithep::Track *trk = Trk();
  if (trk)
    fCachedMom.SetCoordinates(trk->Pt(),trk->Eta(),trk->Phi(),GetMass());
  else 
    fCachedMom.SetCoordinates(0,0,0,0);
}
#endif
