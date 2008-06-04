// $Id: Particle.h,v 1.2 2008/06/02 04:43:14 loizides Exp $

#ifndef DATATREE_TRACK_H
#define DATATREE_TRACK_H
 
#include "MitAna/DataTree/interface/DataObject.h"

//--------------------------------------------------------------------------------------------------
//
// Track
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      Track() {}
      ~Track() {}

      ClassDef(Track, 1) // Track class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_TRACK_H*/
