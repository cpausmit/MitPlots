//--------------------------------------------------------------------------------------------------
// $Id: ChargedParticle.h,v 1.5 2008/10/31 17:41:44 bendavid Exp $
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
      ~ChargedParticle() {}

      Double_t                Charge()     const { return Trk()?Trk()->Charge():0; }
      Double_t                E()          const; 
      Double_t                Eta()        const { return Trk()?Trk()->Mom().Eta():0; }
      virtual const Track    *Trk()        const = 0;
      virtual const Track    *TrackerTrk() const = 0;
      FourVector              Mom()        const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t                Phi()        const { return Trk()?Trk()->Phi():0; }
      Double_t                P()          const { return Trk()?Trk()->P():0;  }
      Double_t                Pt()         const { return Trk()?Trk()->Pt():0; }
      Double_t                Px()         const { return Trk()?Trk()->Px():0; }
      Double_t                Py()         const { return Trk()?Trk()->Py():0; }
      Double_t                Pz()         const { return Trk()?Trk()->Pz():0; }
      
    ClassDef(ChargedParticle, 1) // Charged particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::ChargedParticle::E() const
{
  if (!Trk())
    return Mass()*Mass();

  return TMath::Sqrt(Trk()->P()*Trk()->P() + Mass()*Mass());
}
#endif
