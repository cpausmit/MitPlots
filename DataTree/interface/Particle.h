// $Id: Particle.h,v 1.3 2008/06/04 09:08:36 loizides Exp $

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
      ~Particle() {}

      Particle(double x, double y, double z, double t) {
        fFourVector.SetXYZT(x,y,z,t);
      }
    
      Double_t         Pt()  const { return fFourVector.Pt(); }
      Double_t         Eta() const { return fFourVector.Eta(); }
      
    protected:
      FourVector       fFourVector; //momentum vector
      
      ClassDef(Particle, 1) // Particle class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_PARTICLE_H*/
