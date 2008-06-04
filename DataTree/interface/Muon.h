// $Id: Particle.h,v 1.2 2008/06/02 04:43:14 loizides Exp $

#ifndef DATATREE_MUON_H
#define DATATREE_MUON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

//--------------------------------------------------------------------------------------------------
//
// Muon
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Muon : public Lepton
  {
    public:
      Muon() {}
      ~Muon() {}

      ClassDef(Muon, 1) // Muon class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_MUON_H*/
