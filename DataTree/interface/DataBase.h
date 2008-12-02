//--------------------------------------------------------------------------------------------------
// $Id: DataBase.h,v 1.14 2008/09/17 04:21:16 loizides Exp $
//
// DataBase
//
// This is the common base class for all objects in the tree that do not require the TObject
// bits to be written out (as opposed to DataObject).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DATABASE_H
#define MITANA_DATATREE_DATABASE_H
 
#include <TObject.h>

namespace mithep
{
  class DataBase : public TObject
  {
    public:
      DataBase() {}
      ~DataBase() {}

      Bool_t               IsCached()    const { return TestBit(23); }
      Bool_t               MustClear()   const { return TestBit(14); }
      Bool_t               MustDelete()  const { return TestBit(15); }

    protected:
      void                 ResetCacheBit()     { SetBit(23,0); }
      void                 SetCacheBit()       { SetBit(23);   }
      void                 SetClearBit()       { SetBit(14);   }
      void                 SetDeleteBit()      { SetBit(15);   }

    ClassDef(DataBase, 1)
  };
}
#endif
