//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.1 2008/07/29 10:36:20 loizides Exp $
//
// BaseCollection
//
// Base collection class (virtual) to allow efficient resetting in TAM.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_BASECOLLECTION_H
#define MITANA_DATACONT_BASECOLLECTION_H
 
#include <TObject.h>

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
