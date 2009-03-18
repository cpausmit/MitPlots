//--------------------------------------------------------------------------------------------------
// $Id: Conversion.h,v 1.14 2009/03/18 15:25:48 loizides Exp $
//
// Conversion
//
// This class holds information about reconstructed conversions from CMSSW.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CONVERSION_H
#define MITANA_DATATREE_CONVERSION_H

#include "MitCommon/DataFormats/interface/Vect3C.h"
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Electron.h"

namespace mithep 
{
  class Conversion : public CompositeParticle
  {
    public:
      Conversion() : fDCotTheta(0), fEOverP(0), fPairMass(0) {}
      Conversion(Double_t x, Double_t y, Double_t z) : 
        fVertex(x,y,z), fDCotTheta(0), fEOverP(0), fPairMass(0) {}
      Conversion(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) : 
        fVertex(x,y,z,xErr,yErr,zErr) ,fDCotTheta(0), fEOverP(0), fPairMass(0) {}
      Conversion(const Vertex &v) : 
        fVertex(v) ,fDCotTheta(0), fEOverP(0), fPairMass(0) {}
      
      const Electron        *Daughter(UInt_t i)         const;
      Double_t               DCotTheta()                const { return fDCotTheta;    }
      Double_t               EOverP()                   const { return fEOverP;       }
      Double_t               PairMass()                 const { return fPairMass;     }
      const ThreeVector     &PairMomentum()             const { return fPairMomentum; }
      const Vertex          &DecayVertex()              const { return fVertex;       }
      EObjType               ObjType()                  const { return kConversion;   }
      void                   SetDCotTheta(Double_t dCotTh)    { fDCotTheta = dCotTh;  }
      void                   SetEOverP(Double_t eOverP)       { fEOverP = eOverP;     }
      void                   SetPairMass(Double_t pairMass)   { fPairMass = pairMass; }
      void                   SetPairMomentum(Double_t px, Double_t py, Double_t pz);
        
    protected:
      Vertex                 fVertex;       //reconstructed decay vertex
      ThreeVector32          fPairMomentum; //momentum of tracks at conversion point
      Double32_t             fDCotTheta;    //[0,0,14]delta cot theta wrt tracks at conversion point
      Double32_t             fEOverP;       //[0,0,14]energy over momentum of conversion tracks
      Double32_t             fPairMass;     //[0,0,14]mass of electron-positron pair at conversion
      
    ClassDef(Conversion,1) // Conversion class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Electron *mithep::Conversion::Daughter(UInt_t i) const 
{ 
  // Return reference to electron daughters.

  return static_cast<const mithep::Electron*>(fDaughters.At(i)); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Conversion::SetPairMomentum(Double_t px, Double_t py, Double_t pz)
{ 
  // Set pair momentum.

  fPairMomentum.SetXYZ(px,py,pz);
  ClearMom();
}
#endif
