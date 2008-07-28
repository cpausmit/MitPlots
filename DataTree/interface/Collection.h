//--------------------------------------------------------------------------------------------------
// $Id: Collection.h,v 1.9 2008/06/30 16:54:11 loizides Exp $
//
// Collection
//
// Unification of read access to a collection of objects (ArrayElements).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef mithep_COLLECTION_H
#define mithep_COLLECTION_H
 
#include "MitAna/DataTree/interface/BaseCollection.h"

namespace mithep 
{
  template<class ArrayElement>
  class Collection : public BaseCollection
  {
    public:
      Collection() {}
      ~Collection() {}

      virtual ArrayElement        *At(UInt_t idx)                       = 0;
      virtual const ArrayElement  *At(UInt_t idx)                 const = 0;
      virtual UInt_t               GetEntries()                   const = 0;
      virtual Bool_t               IsOwner()                      const = 0;
      virtual void                 Reset()                              = 0;
      virtual void                 Trim()                               = 0;
      virtual ArrayElement        *UncheckedAt(UInt_t idx)              = 0;
      virtual const ArrayElement  *UncheckedAt(UInt_t idx)        const = 0;

      virtual ArrayElement        *operator[](UInt_t idx)               = 0;
      virtual const ArrayElement  *operator[](UInt_t idx)         const = 0;

    ClassDefT(Collection,1) // Generic access to a collection of ArrayElements
  };
}
#endif
