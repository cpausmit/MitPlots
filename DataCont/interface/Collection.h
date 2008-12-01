//--------------------------------------------------------------------------------------------------
// $Id: Collection.h,v 1.3 2008/11/20 17:49:15 loizides Exp $
//
// Collection
//
// Unification of read access to a collection of objects (ArrayElements).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_COLLECTION_H
#define MITANA_DATACONT_COLLECTION_H
 
#include "MitAna/DataCont/interface/BaseCollection.h"

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
      virtual UInt_t               GetSize()                      const = 0;
      virtual Bool_t               HasObject(const ArrayElement *obj) const = 0;
      virtual Bool_t               IsOwner()                      const = 0;
      void                         Print(Option_t *opt="")        const;
      virtual void                 Reset()                              = 0;
      virtual void                 Trim()                               = 0;
      virtual ArrayElement        *UncheckedAt(UInt_t idx)              = 0;
      virtual const ArrayElement  *UncheckedAt(UInt_t idx)        const = 0;
      virtual ArrayElement        *operator[](UInt_t idx)               = 0;
      virtual const ArrayElement  *operator[](UInt_t idx)         const = 0;

    ClassDefT(Collection,1) // Generic access to a collection of ArrayElements
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::Collection<ArrayElement>::Print(Option_t *opt) const
{
  printf("%s: Contains %d (out of %d) objs\n",
         GetName(), GetEntries(), GetSize());
}
#endif
