// $Id: Lepton.h,v 1.1 2008/06/04 09:08:36 loizides Exp $

#ifndef DATATREE_LEPTON_H
#define DATATREE_LEPTON_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

//--------------------------------------------------------------------------------------------------
//
// Lepton
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid...
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Lepton : public Particle
  {
    public:
      Lepton() {}
      ~Lepton() {}

      Lepton(Double_t x, Double_t y, Double_t z, Double_t t) {fFourVector.SetXYZT(x,y,z,t);}
      
      Track* GetTrack() {return &fTrack;}
      Int_t Charge() {return fTrack.Charge();}

    protected:
      Track fTrack;
      
      ClassDef(Lepton, 1) // Lepton class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_LEPTON_H*/
