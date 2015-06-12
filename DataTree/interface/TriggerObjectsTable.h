//--------------------------------------------------------------------------------------------------
// $Id: TriggerObject.h,v 1.11 2009/07/13 06:37:34 loizides Exp $
//
// TriggerObjectsTable
//
// A convenient THashTable for storage of TriggerObjects (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECTSTABLE_H
#define MITANA_DATATREE_TRIGGEROBJECTSTABLE_H

#include <THashTable.h>
#include "MitAna/DataTree/interface/TriggerTable.h"

namespace mithep 
{
  class TriggerObjectsTable : public THashTable
  {
    private:
      class MyKey : public TObject
      { 
        public:
          MyKey(ULong_t hash) : fHash(hash) {}
          ULong_t Hash() const { return fHash; }
        protected:
          ULong_t fHash; //hash value
      };

    public:
      TriggerObjectsTable(const TriggerTable *table, 
                          Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash), fTriggers(table) {}

      const TList         *GetList(const char *name) const;
      const TList         *GetList(ULong_t id)       const;
      using TCollection::Print;
      void                 Print(Option_t *opt="")   const;
 
    protected:
      const TriggerTable  *fTriggers; //!trigger table

    ClassDef(TriggerObjectsTable, 1) // Hash table for trigger objects
  };
}

//--------------------------------------------------------------------------------------------------
inline const TList *mithep::TriggerObjectsTable::GetList(const char *name) const
{ 
  // Return list of trigger objects for given trigger name.

  ULong_t id = fTriggers->GetId(name);
  return GetList(id);
}

//--------------------------------------------------------------------------------------------------
inline const TList *mithep::TriggerObjectsTable::GetList(ULong_t id) const
{ 
  // Return list of trigger objects for given trigger id (bit).

  MyKey key(id); 
  return const_cast<const TList*>(GetListForObject(&key)); 
}
#endif
