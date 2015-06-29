//--------------------------------------------------------------------------------------------------
// BaseCollection
//
// Base collection class (virtual) to allow efficient resetting in TAM.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATACONT_BASECOLLECTION_H
#define MITANA_DATACONT_BASECOLLECTION_H
 
#include <TObject.h>
#include "TClass.h"

namespace mithep 
{
  class BaseCollection : public TObject 
  {
    public:
      BaseCollection();

      UInt_t                       Entries()                      const;
      virtual UInt_t               GetEntries()                   const = 0;
      virtual UInt_t               GetSize()                      const = 0;
      virtual TObject             *ObjAt(UInt_t idx)                    = 0;
      virtual const TObject       *ObjAt(UInt_t idx)              const = 0;
      virtual Bool_t               IsOwner()                      const = 0;
      virtual void                 Reset()                              = 0;
      virtual void                 Trim()                               = 0;
      virtual void                 SetName(char const*)                 {}
      virtual TClass*              ElementClass()                 const { return 0; }

    protected:
      void                         Clear(Option_t */*opt*/="");

      mutable Int_t                fEntries; //!cached number of entries

    ClassDef(BaseCollection, 2) // Base class of all our collections
  };

  inline
  mithep::BaseCollection::BaseCollection() :
  fEntries(-1)
  {
    static bool ignoreFlag(false);
    if(!ignoreFlag){
      // The static variable itself is not thread-safe,
      // but there is a mutex lock within IgnoreTObjectStreamer
      // function. Multiple threads assigning the same value
      // "true" to ignoreFlag should not be a problem.

      mithep::BaseCollection::Class()->IgnoreTObjectStreamer(true);
      ignoreFlag = true;
    }
  }

  //--------------------------------------------------------------------------------------------------
  inline void mithep::BaseCollection::Clear(Option_t */*opt*/)
  { 
    // Reset cache for entries.

    fEntries = -1; 
  }

  //--------------------------------------------------------------------------------------------------
  inline UInt_t mithep::BaseCollection::Entries() const
  {
    // Return cached number of entries.

    if (fEntries<0) 
      fEntries = GetEntries();
    return fEntries;
  }

}
#endif
