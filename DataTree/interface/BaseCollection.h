//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.5 2008/06/24 14:01:41 loizides Exp $
//
// BaseCollection
//
// Base collection class (virtual) to allow efficient resetting in TAM.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_BASECOLLECTION_H
#define DATATREE_BASECOLLECTION_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class BaseCollection : public TObject 
  {
    public:
      BaseCollection() {}
      ~BaseCollection() {}

      virtual UInt_t               GetEntries()                   const = 0;
      virtual Bool_t               IsOwner()                      const = 0;
      virtual void                 Reset()                              = 0;
      virtual void                 Trim()                               = 0;

    ClassDef(BaseCollection,1) // Base class of all our collections
  };
}
#endif
