// $Id: Particle.h,v 1.2 2008/06/02 04:43:14 loizides Exp $

#ifndef DATATREE_DATAOBJECT_H
#define DATATREE_DATAOBJECT_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// DataObject
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class DataObject : public TObject
  {
    public:
      DataObject() {}
      ~DataObject() {}
  
      ClassDef(DataObject, 1) // Basic data object class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_DATAOBJECT_H*/
