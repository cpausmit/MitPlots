// $Id: DataObject.h,v 1.2 2008/06/11 13:48:37 loizides Exp $

#ifndef DATATREE_DATAOBJECT_H
#define DATATREE_DATAOBJECT_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// DataObject
//
// This is the common base class for all objects in the tree. 
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
}
#endif
