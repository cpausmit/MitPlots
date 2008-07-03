//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.3 2008/07/02 19:28:43 bendavid Exp $
//
// Photon
//
// Details to be worked out...
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_PHOTON_H
#define DATATREE_PHOTON_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/RefArray.h"
#include "MitAna/DataTree/interface/Conversion.h"

namespace mithep 
{
  class Photon : public Particle
  {
    public:
      Photon() {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : fFourVector(px,py,pz,e) {}
      ~Photon() {}

      void                      AddConversion(Conversion *c);
      Int_t                     Charge()                const { return 0; }
      Bool_t                    IsConverted()           const { return fConversions.GetEntries(); }
      const Conversion         *GetConversion(UInt_t i) const { return fConversions.At(i); }
      UInt_t                    GetNConversions()       const { return fConversions.GetEntries(); }
      FourVector 	        Mom()                   const { return fFourVector; }  
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
	    
    protected:
      FourVector                fFourVector;  //four momentum vector
      RefArray<Conversion>      fConversions; //references to associated conversion candidates
	
    ClassDef(Photon,1) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::AddConversion(Conversion *c)  
{ 
  // Add a conversion object.

  fConversions.Add(c); 
  fConversions.Trim();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}
#endif
