// $Id: Particle.h,v 1.1 2008/05/27 19:24:49 loizides Exp $

#ifndef DATATREE_PARTICLE_H
#define DATATREE_PARTICLE_H
 
#include "MitAna/DataTree/interface/Types.h"
#include <TObject.h>

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
  class Particle : public FourVector
  {
    public:
      Particle() {}
      virtual ~Particle() {}

      Particle(double x, double y, double z, double t) {
         SetXYZT(x,y,z,t); 
      }
  
      ClassDef(Particle, 1) // Particle class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_PARTICLE_H*/
