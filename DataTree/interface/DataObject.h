//--------------------------------------------------------------------------------------------------
// $Id: DataObject.h,v 1.6 2008/07/02 21:43:15 loizides Exp $
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
      Bool_t               GetCacheBit() const { return TestBit(15); }

    protected:
      void                 SetClearBit()       { SetBit(14); }
      void                 SetCacheBit()       { SetBit(15); }
      void                 ResetCacheBit()     { SetBit(15,0); }

    ClassDef(DataObject, 1) // Basic data object class
  };
}
#endif
