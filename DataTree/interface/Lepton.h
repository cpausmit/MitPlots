//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.9 2008/07/01 08:54:57 loizides Exp $
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

      Int_t                   Charge()    const { return Trk()->Charge(); }
      Double_t                E()         const; 
      Double_t                Eta()       const { return Trk()->Mom().Eta(); }
      virtual const Track    *Trk()       const { return 0; }
      FourVector              Mom()       const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t                Phi()       const { return Trk()->Phi(); }
      Double_t                P()         const { return Trk()->P(); }
      Double_t                Pt()        const { return Trk()->Pt(); }
      Double_t                Px()        const { return Trk()->Px(); }
      Double_t                Py()        const { return Trk()->Py(); }
      Double_t                Pz()        const { return Trk()->Pz(); }
      
    ClassDef(Lepton, 1) // Lepton class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Lepton::E() const
{
  return TMath::Sqrt(Trk()->P()*Trk()->P() + Mass()*Mass());
}
#endif
