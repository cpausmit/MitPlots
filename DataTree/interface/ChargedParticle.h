//--------------------------------------------------------------------------------------------------
// $Id: ChargedParticle.h,v 1.3 2008/07/29 07:55:40 loizides Exp $
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

      Double_t                Charge()    const { return Trk()->Charge(); }
      Double_t                E()         const; 
      Double_t                Eta()       const { return Trk()->Mom().Eta(); }
      virtual const Track    *Trk()       const = 0;
      FourVector              Mom()       const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t                Phi()       const { return Trk()->Phi(); }
      Double_t                P()         const { return Trk()->P();  }
      Double_t                Pt()        const { return Trk()->Pt(); }
      Double_t                Px()        const { return Trk()->Px(); }
      Double_t                Py()        const { return Trk()->Py(); }
      Double_t                Pz()        const { return Trk()->Pz(); }
      
    ClassDef(ChargedParticle, 1) // Charged particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::ChargedParticle::E() const
{
  return TMath::Sqrt(Trk()->P()*Trk()->P() + Mass()*Mass());
}
#endif
