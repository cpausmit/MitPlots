//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.7 2008/06/24 14:01:41 loizides Exp $
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

      virtual Track    *GetTrack()  const { return 0; }
      
      FourVector        Mom()    const { return FourVector(Px(),Py(),Pz(),E()); }
      Double_t          E()      const { return sqrt(GetTrack()->P()*GetTrack()->P() + Mass()*Mass()); }
      Double_t          Eta()    const { return GetTrack()->Mom().Eta(); }
      Double_t          Phi()    const { return GetTrack()->Phi(); }
      Double_t          Pt()     const { return GetTrack()->Pt(); }
      Double_t          Px()     const { return GetTrack()->Px(); }
      Double_t          Py()     const { return GetTrack()->Py(); }
      Double_t          Pz()     const { return GetTrack()->Pz(); }
      Double_t          P()      const { return GetTrack()->P(); }
      Int_t             Charge() const { return GetTrack()->Charge(); }
      
    protected:
      
    ClassDef(Lepton, 1) // Lepton class
  };
}
#endif
