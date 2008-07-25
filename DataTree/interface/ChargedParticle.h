//--------------------------------------------------------------------------------------------------
// $Id: ChargedParticle.h,v 1.13 2008/07/16 10:00:58 bendavid Exp $
//
// ChargedParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_CHARGEDPARTICLE_H
#define DATATREE_CHARGEDPARTICLE_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class ChargedParticle : public Particle
  {
    public:
      ChargedParticle() {}
      ~ChargedParticle() {}

      Double_t                Charge()    const { return BestTrk()->Charge(); }
      Double_t                E()         const; 
      Double_t                Eta()       const { return BestTrk()->Mom().Eta(); }
      virtual const Track    *BestTrk()   const=0;
      FourVector              Mom()       const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t                Phi()       const { return BestTrk()->Phi(); }
      Double_t                P()         const { return BestTrk()->P();  }
      Double_t                Pt()        const { return BestTrk()->Pt(); }
      Double_t                Px()        const { return BestTrk()->Px(); }
      Double_t                Py()        const { return BestTrk()->Py(); }
      Double_t                Pz()        const { return BestTrk()->Pz(); }
      
    ClassDef(ChargedParticle, 1) // ChargedParticle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::ChargedParticle::E() const
{
  return TMath::Sqrt(BestTrk()->P()*BestTrk()->P() + Mass()*Mass());
}
#endif
