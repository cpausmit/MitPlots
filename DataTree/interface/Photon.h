//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.14 2008/09/14 03:23:27 bendavid Exp $
//
// Photon
//
// Details to be worked out...
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PHOTON_H
#define MITANA_DATATREE_PHOTON_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class Photon : public Particle
  {
    public:
      Photon() {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fFourVector(px,py,pz,e) {}
      ~Photon() {}

      void                      AddConversion(Conversion *c)  { fConversions.Add(c); }
      Double_t                  Charge()                const { return 0; }
      void                      Clear(Option_t *opt="")       { fConversions.Clear(opt); }
      Bool_t                    IsConverted()           const { return fIsConverted; }
      const Conversion         *ConvCand(UInt_t i)      const { return fConversions.At(i); }
      UInt_t                    NConversions()          const { return fConversions.GetEntries(); }
      const SuperCluster       *SCluster()              const;
      FourVector 	        Mom()                   const { return fFourVector; }
      void                      SetIsConverted(Bool_t isConv) { fIsConverted = isConv; }
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                      SetSuperCluster(SuperCluster* sc) { fSuperClusterRef = sc; }
	    
    protected:
      FourVector                fFourVector;  //four momentum vector
      RefArray<Conversion,128>  fConversions; //references to associated conversion candidates
      Bool_t                    fIsConverted; //conversion flag
      TRef                      fSuperClusterRef; //superCluster
	
    ClassDef(Photon,1) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}

//--------------------------------------------------------------------------------------------------
inline const mithep::SuperCluster *mithep::Photon::SCluster() const
{
  // Return Super cluster

  return static_cast<const SuperCluster*>(fSuperClusterRef.GetObject());
}
#endif
