//--------------------------------------------------------------------------------------------------
// $Id: ProcIDRef.h,v 1.3 2008/12/10 11:26:52 loizides Exp $
//
// CacheFlag
//
// Container for a transient Bool_t which is set by the reading streamer to kFALSE
// This meant to be used as a cache valid flag for transient cached quantities.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CACHEFLAG
#define MITANA_DATATREE_CACHEFLAG

#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class CacheFlag : public TObject
  {
    public:
      CacheFlag() : fIsValid(kFALSE) {};
      ~CacheFlag() {}

      Bool_t             IsValid()            const { return fIsValid; }
      void               ClearCache()               { fIsValid = kFALSE; }
      void               SetCache(Bool_t v = kTRUE) { fIsValid = v; }
      
    protected:
      Bool_t         fIsValid; //!flag whether cache is valid

    ClassDef(CacheFlag, 1) // Implementation of our own TProcIDRef
  };
}
#endif
