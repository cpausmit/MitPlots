//--------------------------------------------------------------------------------------------------
// CacheFlag
//
// Container for a transient Bool_t which is set by the reading streamer to kFALSE.  This meant to
// be used as a cache valid flag for transient cached quantities.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATACONT_CACHEFLAG_H
#define MITANA_DATACONT_CACHEFLAG_H

#include "MitAna/DataCont/interface/Types.h"

namespace mithep 
{
  class CacheFlag
  {
    public:
      CacheFlag() : fIsValid(kFALSE) {}
      virtual ~CacheFlag() {}

      void               ClearCache()               { fIsValid = kFALSE; }
      Bool_t             IsValid()            const { return fIsValid; }
      void               SetValid(Bool_t v = kTRUE) { fIsValid = v; }
      
    protected:
      Bool_t             fIsValid;                   //!flag whether cache is valid

    ClassDef(CacheFlag, 1) // Implementation of a transient Bool_t container
  };
}
#endif
