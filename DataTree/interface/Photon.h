//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.7 2008/07/14 09:41:59 loizides Exp $
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
      Photon() : fConversions(2) { SetClearBit(); }
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fFourVector(px,py,pz,e) { SetClearBit(); }
      ~Photon() {}

      void                      AddConversion(Conversion *c)  { fConversions.Add(c); }
      Int_t                     Charge()                const { return 0; }
      void                      Clear(Option_t *opt="")       { fConversions.Clear(opt); }
      Bool_t                    IsConverted()           const { return fConversions.GetEntries(); }
      const Conversion         *ConvCand(UInt_t i)      const { return fConversions.At(i); }
      UInt_t                    NConversions()          const { return fConversions.GetEntries(); }
      FourVector 	        Mom()                   const { return fFourVector; }  
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
	    
    protected:
      FourVector                fFourVector;  //four momentum vector
      RefArray<Conversion>      fConversions; //references to associated conversion candidates
	
    ClassDef(Photon,1) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}
#endif
