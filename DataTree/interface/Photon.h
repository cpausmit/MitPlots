//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.1 2008/06/30 16:51:16 loizides Exp $
//
// Photon
//
// Details to be worked out...
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_PHOTON_H
#define DATATREE_PHOTON_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/FitVertex.h"
#include "MitAna/DataTree/interface/Electron.h"

namespace mithep 
{
  class Photon : public CompositeParticle
  {
    public:
      Photon() {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : fFourVector(px,py,pz,e) {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t x, Double_t y, Double_t z) : 
        fFourVector(px,py,pz,e), fConvVertex(x,y,z) {}
      ~Photon() {}

      const Electron           *GetDaughter(UInt_t i) const;
      const FitVertex          &GetVertex()           const { return fConvVertex; }
      FourVector 	        Mom()                 const { return fFourVector; }  
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
	    
    protected:
      FourVector                fFourVector; //four momentum vector
      FitVertex		        fConvVertex; //conversion vertex
	
    ClassDef(Photon,1) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Electron *mithep::Photon::GetDaughter(UInt_t i) const 
{ 
  // Return reference to electron daughters.

  return static_cast<const mithep::Electron*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}
#endif
