//--------------------------------------------------------------------------------------------------
// $Id: Lepton.h,v 1.9 2008/07/01 08:54:57 loizides Exp $
//
// Met
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_MET_H
#define DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() {}
      ~Met() {}

    ClassDef(Met, 1) // Met class
  };
}
#endif
