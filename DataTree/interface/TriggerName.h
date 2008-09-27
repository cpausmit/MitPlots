//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.1 2008/09/17 04:07:28 loizides Exp $
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
#include <THashTable.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class TriggerName : public TObject
  {
    public:
      TriggerName() : fId(0) {}
      TriggerName(const char *name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const std::string &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const TString &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      ~TriggerName() {}

      UShort_t              Id()      const { return fId; }
      const char           *GetName() const { return fName; }
      ULong_t               Hash()    const { return fHash; }
      const char           *Name()    const { return fName; }
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fName;        //name
      UShort_t              fId;          //id
      UInt_t                fHash;        //hash

    ClassDef(TriggerName, 1) // Trigger name class
  };

//--------------------------------------------------------------------------------------------------
// TriggerTable
//
// A convenient THashTable for storage of TriggerNames (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
  class TriggerTable : public THashTable
  {
    public:
      TriggerTable(Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash) {}
      ~TriggerTable() {}

      const TriggerName *Get(const char *name)   const;
      UShort_t           GetId(const char *name) const;
      using TCollection::Print;
      void               Print(Option_t *opt="") const;
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerName *mithep::TriggerTable::Get(const char *name) const
{ 
  // Return TriggerName pointer for given name.

  return dynamic_cast<const TriggerName *>(FindObject(name)); 
}

//--------------------------------------------------------------------------------------------------
inline UShort_t mithep::TriggerTable::GetId(const char *name) const
{
  // Return trigger id of trigger with given name.

  const mithep::TriggerName *tn = Get(name); 
  if (tn) 
    return tn->Id();
  
  Error("GetId", "TriggerName for %s not found. Returning 65535.", name);
  return 65535;
}

#endif
