//--------------------------------------------------------------------------------------------------
// $Id: Conversion.h,v 1.1 2008/07/02 19:28:43 bendavid Exp $
//
// Conversion
//
// Details to be worked out...
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_CONVERSION_H
#define DATATREE_CONVERSION_H

#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/FitVertex.h"
#include "MitAna/DataTree/interface/Electron.h"

namespace mithep 
{
  class Conversion : public CompositeParticle
  {
    public:
      Conversion() : fVertex(0,0,0) {}
      Conversion(Double_t x, Double_t y, Double_t z) : fVertex(x,y,z) {}
      Conversion(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) : 
        fVertex(x,y,z,xErr,yErr,zErr) {}
      ~Conversion() {}
      
      const Electron           *GetDaughter(UInt_t i) const;
      const FitVertex          &GetVertex()           const { return fVertex; }
      FitVertex                &GetVertex()                 { return fVertex; }
        
    protected:
      FitVertex                 fVertex; //reconstructed decay vertex
      
    ClassDef(Conversion,1) // Conversion class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Electron *mithep::Conversion::GetDaughter(UInt_t i) const 
{ 
  // Return reference to electron daughters.

  return static_cast<const mithep::Electron*>(fDaughters.At(i)); 
}
#endif
