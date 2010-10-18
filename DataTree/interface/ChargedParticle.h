//--------------------------------------------------------------------------------------------------
// $Id: ChargedParticle.h,v 1.12 2010/10/18 01:33:09 bendavid Exp $
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
      ChargedParticle() : fCorrectedNExpectedHitsInner(0) {}

      EObjType                ObjType()    const { return kChargedParticle; }
      virtual const Track    *TrackerTrk() const { return Trk();            }
      virtual const Track    *Trk()        const { return 0;                }
      Int_t CorrectedNExpectedHitsInner()  const { return fCorrectedNExpectedHitsInner; }
      void SetCorrectedNExpectedHitsInner(Int_t n)    { fCorrectedNExpectedHitsInner = n; }

    protected:
      Double_t                GetCharge()  const;
      void                    GetMom()     const;
      Int_t                   fCorrectedNExpectedHitsInner; //corrected NExpectedHitsInner

    ClassDef(ChargedParticle, 2) // Charged particle class
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
    fCachedMom.SetCoordinates(0,0,0,GetMass());
}
#endif
