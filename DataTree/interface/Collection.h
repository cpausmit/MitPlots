// $Id: Collection.h,v 1.1 2008/05/27 19:24:49 loizides Exp $

#ifndef DATATREE_COLLECTION_H
#define DATATREE_COLLECTION_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// Collection
//
// Unification of access to a collection of objects (ArrayElements)
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  template<class ArrayElement>
  class Collection : public TObject 
  {
    public:
      Collection() {}
      virtual ~Collection() {}

      virtual void                 Add(const ArrayElement &)            = 0;
      virtual ArrayElement        &At(const UInt_t idx)                 = 0;
      virtual const ArrayElement  &At(const UInt_t idx)           const = 0;
      virtual UInt_t               GetEntries()                   const = 0;
      virtual void                 Reset()                              = 0;
      virtual void                 Trim()                               = 0;

      virtual ArrayElement        &operator[](const UInt_t idx)         = 0;
      virtual const ArrayElement  &operator[](const UInt_t idx)   const = 0;

      ClassDefT(Collection,1) // Generic access to a collection of ArrayElements
  };

} /*namespace mithep*/

#endif /*DATATREE_COLLECTION_H*/
