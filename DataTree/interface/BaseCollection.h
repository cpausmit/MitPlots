// $Id: BaseCollection.h,v 1.2 2008/06/11 13:48:37 loizides Exp $

#ifndef DATATREE_BASECOLLECTION_H
#define DATATREE_BASECOLLECTION_H
 
#include <TObject.h>
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// BaseCollection
//
// Base collection class (virtual) to allow efficient resetting in TAM.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class BaseCollection : public TObject 
  {
    public:
      BaseCollection() {}
      ~BaseCollection() {}

      virtual UInt_t               GetEntries()                   const = 0;
      virtual void                 Reset()                              = 0;

      ClassDef(BaseCollection,1) // Base class of all our collections
  };
}
#endif
