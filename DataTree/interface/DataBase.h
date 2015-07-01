//--------------------------------------------------------------------------------------------------
// DataBase
//
// This is the common base class for all objects in the tree that do not require the TObject bits to
// be written out (as opposed to DataObject).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DATABASE_H
#define MITANA_DATATREE_DATABASE_H
 
#include "MitAna/DataTree/interface/ObjTypes.h"
#include <TObject.h>
#include "TClass.h"

namespace mithep
{
  class DataBase : public TObject
  {
    public:
      DataBase();

      Bool_t               Is(EObjType t) const { return (ObjType()==t); }
      Bool_t               IsCached()     const { return TestBit(23);    }
      Bool_t               MustClear()    const { return TestBit(14);    }
      Bool_t               MustDelete()   const { return TestBit(15);    }
      virtual Int_t        ObjId()        const { return ObjType()*1000; }
      virtual EObjType     ObjType()      const { return kDataBase;      }

    protected:
      void                 ResetCacheBit()      { SetBit(23,0);          }
      void                 SetCacheBit()        { SetBit(23);            }
      void                 SetClearBit()        { SetBit(14);            }
      void                 SetDeleteBit()       { SetBit(15);            }

    ClassDef(DataBase, 2) // Common base for objects that do not get referenced
  };

  inline
  DataBase::DataBase()
  {
    static bool ignoreFlag(false);
    if(!ignoreFlag){
      // The static variable itself is not thread-safe,
      // but there is a mutex lock within IgnoreTObjectStreamer
      // function. Multiple threads assigning the same value
      // "true" to ignoreFlag should not be a problem.

      DataBase::Class()->IgnoreTObjectStreamer(true);
      ignoreFlag = true;
    }
  }

}
#endif
