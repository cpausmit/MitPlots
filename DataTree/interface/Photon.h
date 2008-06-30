//--------------------------------------------------------------------------------------------------
// $Id:$
//
// Photon
//
// Details to be worked out...
//
// Authors: J. Bendavid
//
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_PHOTON_H
#define DATATREE_PHOTON_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/FitVertex.h"


namespace mithep 
{
  class Photon : public CompositeParticle
  {
    public:
      Photon() {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : fFourVector(px,py,pz,e) {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t x, Double_t y, Double_t z) : fFourVector(px,py,pz,e), fConvVertex(x,y,z) {}
      ~Photon() {}
      
      FourVector 	Mom() const { return fFourVector; }  
      
      void		SetMom(Double_t px, Double_t py, Double_t pz, Double_t e) { fFourVector.SetXYZT(px, py, pz, e); }
      FitVertex*	GetVertex() { return &fConvVertex; }
	    
    protected:
      FourVector        fFourVector; // four momentum vector
      FitVertex		fConvVertex; // ConversionVertex

	
	
    ClassDef(Photon, 1) // Photon class
	
  };
}
#endif
