//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.8 2008/06/30 16:54:40 loizides Exp $
//
// Lepton
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_LEPTON_H
#define DATATREE_LEPTON_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Lepton : public Particle
  {
    public:
      Lepton() {}
      ~Lepton() {}

      Int_t                   Charge()    const { return GetTrack()->Charge(); }
      Double_t                E()         const; 
      Double_t                Eta()       const { return GetTrack()->Mom().Eta(); }
      virtual const Track    *GetTrack()  const { return 0; }
      FourVector              Mom()       const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t                Phi()       const { return GetTrack()->Phi(); }
      Double_t                P()         const { return GetTrack()->P(); }
      Double_t                Pt()        const { return GetTrack()->Pt(); }
      Double_t                Px()        const { return GetTrack()->Px(); }
      Double_t                Py()        const { return GetTrack()->Py(); }
      Double_t                Pz()        const { return GetTrack()->Pz(); }
      
    ClassDef(Lepton, 1) // Lepton class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Lepton::E() const
{
  return TMath::Sqrt(GetTrack()->P()*GetTrack()->P() + Mass()*Mass());
}
#endif
