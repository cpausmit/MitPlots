// $Id: Particle.h,v 1.2 2008/06/02 04:43:14 loizides Exp $

#ifndef DATATREE_LEPTON_H
#define DATATREE_LEPTON_H
 
#include "MitAna/DataTree/interface/Particle.h"

//--------------------------------------------------------------------------------------------------
//
// Lepton
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Lepton : public Particle
  {
    public:
      Lepton() {}
      ~Lepton() {}

      ClassDef(Lepton, 1) // Lepton class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_LEPTON_H*/
