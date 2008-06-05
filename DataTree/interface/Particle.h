// $Id: Particle.h,v 1.4 2008/06/04 14:04:47 loizides Exp $

#ifndef DATATREE_PARTICLE_H
#define DATATREE_PARTICLE_H
 
#include "MitAna/DataTree/interface/DataObject.h"

//--------------------------------------------------------------------------------------------------
//
// Particle
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() {}
      Particle(Double_t px, Double_t py, Double_t pz, Double_t e) : fFourVector(px,py,pz,e) {}
      ~Particle() {}
    
      Double_t         E()   const { return fFourVector.E(); }
      Double_t         Eta() const { return fFourVector.Eta(); }
      Double_t         Phi() const { return fFourVector.Phi(); }
      Double_t         Pt()  const { return fFourVector.Pt(); }
      Double_t         Px()  const { return fFourVector.Px(); }
      Double_t         Py()  const { return fFourVector.Py(); }
      Double_t         Pz()  const { return fFourVector.Pz(); }
      
    protected:
      FourVector       fFourVector; //momentum vector
      
      ClassDef(Particle, 1) // Particle class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_PARTICLE_H*/
