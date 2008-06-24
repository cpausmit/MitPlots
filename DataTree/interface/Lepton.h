//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.6 2008/06/18 19:08:14 loizides Exp $
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
      Lepton(Double_t px, Double_t py, Double_t pz, Double_t e) : Particle(px,py,pz,e) {}
      ~Lepton() {}
      
      Track*	GetTrack() {return &fTrack;}
      Int_t	Charge() const {return fTrack.Charge();}

    protected:
      Track	fTrack; // track associated with lepton
      
    ClassDef(Lepton, 1) // Lepton class
  };
}
#endif
