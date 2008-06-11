// $Id: BaseCollection.h,v 1.1 2008/06/05 10:06:29 loizides Exp $

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

      virtual void                 Reset()                              = 0;

      ClassDef(BaseCollection,1) // Base class of all our collections
  };
}
#endif
