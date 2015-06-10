//--------------------------------------------------------------------------------------------------
// $Id: TriggerTable.h,v 1.2 2009/11/24 15:57:37 loizides Exp $
//
// TriggerTable
//
// A convenient THashTable for storage of TriggerNames (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERTABLE_H
#define MITANA_DATATREE_TRIGGERTABLE_H

#include <string>
#include <TObject.h> 
#include <TString.h>
#include <THashTable.h>
#include "MitAna/DataTree/interface/TriggerName.h"

namespace mithep 
{
  class TriggerTable : public THashTable
  {
    public:
      TriggerTable(Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash) {}

      const TriggerName *Get(const char *name)     const;
      const TriggerName *GetWildcard(const char *name) const;      
      const TriggerName *Get(const std::string &s) const { return Get(s.c_str()); }
      UShort_t           GetId(const char *name)   const;
      using TCollection::Print;
      void               Print(Option_t *opt="")   const;

    ClassDef(TriggerTable, 1) // A convenient trigger table
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerName *mithep::TriggerTable::Get(const char *name) const
{ 
  // Return TriggerName pointer for given name.

  return dynamic_cast<const TriggerName *>(FindObject(name)); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerName *mithep::TriggerTable::GetWildcard(const char *name) const
{ 
  // Return TriggerName pointer for given name.

  TIterator *it = MakeIterator();
  
  TObject* tempObj=0;
  
  while((tempObj=it->Next())) {
    TString tmpstr(tempObj->GetName());
    if (tmpstr.BeginsWith(name)) {
      delete it;
      printf("returning wildcard trigger %s\n",tempObj->GetName());
      return dynamic_cast<const TriggerName *>(tempObj); 
    }
  }
  
  return 0;

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
