//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.7 2008/07/28 23:13:41 paus Exp $
//
// BaseCollection
//
// Base collection class (virtual) to allow efficient resetting in TAM.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef mithep_BASECOLLECTION_H
#define mithep_BASECOLLECTION_H
 
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
