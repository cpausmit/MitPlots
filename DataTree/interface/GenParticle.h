// $Id: Particle.h,v 1.2 2008/06/02 04:43:14 loizides Exp $

#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H
 
#include "MitAna/DataTree/interface/Particle.h"

//--------------------------------------------------------------------------------------------------
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class GenParticle : public Particle
  {
    public:
      GenParticle() {}
      ~GenParticle() {}

      ClassDef(GenParticle,1) // Generated particle class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_GENPARTICLE_H*/
