// $Id: Collections.h,v 1.2 2008/05/27 19:59:54 loizides Exp $

#ifndef DATATREE_COLLECTIONS_H
#define DATATREE_COLLECTIONS_H
 
#include "MitAna/DataTree/interface/Collection.h"
#include "MitAna/DataTree/interface/Vector.h"
#include "MitAna/DataTree/interface/Particle.h"

//--------------------------------------------------------------------------------------------------
//
// Collections
//
// This header file defines the standard types for the collections we want to use.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  typedef Collection<Particle> ParticleCollection;

} /*namespace mithep*/

#endif /*DATATREE_COLLECTIONS_H*/
