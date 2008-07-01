//--------------------------------------------------------------------------------------------------
// $Id: DecayParticle.h,v 1.1 2008/06/30 16:50:39 loizides Exp $
//
// Decay Particle
//
// Details to be worked out...
//
// Authors: J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_DECAYPARTICLE_H
#define DATATREE_DECAYPARTICLE_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/FitVertex.h"

namespace mithep 
{
  class DecayParticle : public CompositeParticle
  {
    public:
      DecayParticle() {}
      DecayParticle(Double_t x, Double_t y, Double_t z) : fVertex(x,y,z) {}
      DecayParticle(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) : 
        fVertex(x,y,z,xErr,yErr,zErr) {}
      ~DecayParticle() {}
      
      const FitVertex        &GetVertex() { return fVertex; }
        
    protected:
      FitVertex		      fVertex; //reconstructed decay vertex
      
    ClassDef(DecayParticle, 1) //Decay particle class
  };
}
#endif
