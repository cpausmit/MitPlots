//--------------------------------------------------------------------------------------------------
// $Id: Particle.h,v 1.8 2008/06/11 13:48:37 loizides Exp $
//
// Particle
//
// Details to be worked out...
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_PARTICLE_H
#define DATATREE_PARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() {}
      Particle(Double_t px, Double_t py, Double_t pz, Double_t e) : fFourVector(px,py,pz,e) {}
      ~Particle() {}
    
      Double_t          E()    const { return fFourVector.E(); }
      Double_t          Eta()  const { return fFourVector.Eta(); }
      Double_t          Mass() const { return TMath::Sqrt(fFourVector.M2()); }
      const FourVector &Mom()  const { return fFourVector; }      
      Double_t          Phi()  const { return fFourVector.Phi(); }
      Double_t          Pt()   const { return fFourVector.Pt(); }
      Double_t          Px()   const { return fFourVector.Px(); }
      Double_t          Py()   const { return fFourVector.Py(); }
      Double_t          Pz()   const { return fFourVector.Pz(); }

    protected:
      FourVector       fFourVector; // four momentum vector
      
      ClassDef(Particle, 1) // Particle class
  };
}
#endif
