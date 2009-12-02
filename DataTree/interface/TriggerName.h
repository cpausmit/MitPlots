//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.6 2009/03/24 16:10:15 loizides Exp $
//
// TriggerName
//
// A class to hold a name and a number, ie the trigger name and trigger bit.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERNAME_H
#define MITANA_DATATREE_TRIGGERNAME_H

#include <string>
#include <TObject.h> 
#include <TString.h>
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class TriggerName : public DataBase
  {
    public:
      TriggerName() : fId(0), fHash(0) {}
      TriggerName(const char *name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const std::string &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const TString &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}

      Int_t                     Compare(const TObject *o) const;   
      UShort_t              Id()         const { return fId;   }
      Bool_t                IsSortable() const { return kTRUE; }
      const char           *GetName()    const { return fName; }
      ULong_t               Hash()       const { return fHash; }
      const char           *Name()       const { return fName; }
      EObjType              ObjType()    const { return kTriggerName; }      
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fName;        //name
      UShort_t              fId;          //id
      UInt_t                fHash;        //hash

    ClassDef(TriggerName, 1) // Trigger name class
  };
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::TriggerName::Compare(const TObject *o) const
{
  // Default compare function for sorting according to transverse momentum. 
  // Returns -1 if this object is smaller than given object, 0 if objects are 
  // equal and 1 if this is larger than given object.

  const mithep::TriggerName *t = dynamic_cast<const mithep::TriggerName *>(o);
  if (!t)
    return 1;

  Double_t myid = Id();
  Double_t id   = t->Id();
  if (myid<id)
    return -1;
  else if (id<myid)
    return +1;
  return 0;
}
#endif
