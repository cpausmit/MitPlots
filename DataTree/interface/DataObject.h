//--------------------------------------------------------------------------------------------------
// $Id: DataObject.h,v 1.8 2008/07/13 08:28:33 loizides Exp $
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

      Bool_t               MustClear()   const { return TestBit(14); }
      Bool_t               MustDelete()  const { return TestBit(15); }
      Bool_t               IsCached()    const { return TestBit(23); }

    protected:
      void                 SetClearBit()       { SetBit(14); }
      void                 SetDeleteBit()      { SetBit(15); }
      void                 SetCacheBit()       { SetBit(23); }
      void                 ResetCacheBit()     { SetBit(23,0); }

    ClassDef(DataObject, 1) // Basic data object class
  };
}
#endif
