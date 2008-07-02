//--------------------------------------------------------------------------------------------------
// $Id: DataObject.h,v 1.5 2008/06/24 14:01:41 loizides Exp $
//
// DataObject
//
// This is the common base class for all objects in the tree. 
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_DATAOBJECT_H
#define DATATREE_DATAOBJECT_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DataObject : public TObject
  {
    public:
      DataObject() {}
      ~DataObject() {}

      Bool_t               GetClearBit() const { return TestBit(14); }

    protected:
      void                 SetClearBit()       { SetBit(14); }

    ClassDef(DataObject, 1) // Basic data object class
  };
}
#endif
