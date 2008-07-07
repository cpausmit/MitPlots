//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.9 2008/07/01 08:54:57 loizides Exp $
//
// Jet
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_JET_H
#define DATATREE_JET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Jet : public Particle
  {
    public:
      Jet() {}
      ~Jet() {}

    ClassDef(Jet, 1) // Jet class
  };
}
#endif
