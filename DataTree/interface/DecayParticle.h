//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.2 2008/06/05 16:03:35 bendavid Exp $
//
// Decay Particle
//
// Details to be worked out...
//
// Authors: J.Bendavid...
//
//--------------------------------------------------------------------------------------------------


#ifndef DATATREE_DECAYPARTICLE_H
#define DATATREE_DECAYPARTICLE_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/FitVertex.h"
#include <TRefArray.h>

namespace mithep 
{
  class DecayParticle : public CompositeParticle
  {
    public:
      DecayParticle() : fVertex(0,0,0) {}
      DecayParticle(Double_t x, Double_t y, Double_t z) : fVertex(x,y,z) {}
      DecayParticle(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) : fVertex(x,y,z,xErr,yErr,zErr) {}
      ~DecayParticle() {}
      
      FitVertex*	GetVertex() { return &fVertex; }
        
    protected:
      FitVertex		fVertex;
      
    ClassDef(DecayParticle, 1)
  };
}
#endif
