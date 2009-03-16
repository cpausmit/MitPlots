//--------------------------------------------------------------------------------------------------
// $Id: BranchTable.h,v 1.1 2009/03/13 20:24:51 loizides Exp $
//
// BranchTable
//
// A convenient table to store dependencies among branches.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BRANCHTABLE_H
#define MITANA_DATATREE_BRANCHTABLE_H

#include <THashTable.h>
#include "MitAna/DataTree/interface/BranchName.h"

namespace mithep 
{
  class BranchTable : public THashTable
  {
    public:
      BranchTable(Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash) {}

      TList             *GetBranches()                               const;
      const BranchName  *Get(const char *name)                       const;
      Bool_t             Find(const char *brname, const char *brdep) const;
      Bool_t             Find(const BranchName &bn)                  const;
      using TCollection::Print;
      void               Print(Option_t *opt="")                     const;

    ClassDef(BranchTable, 1) // Table to store branch dependencies
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::BranchName *mithep::BranchTable::Get(const char *name) const
{ 
  // Return a pointer to BranchName for given name.

  return dynamic_cast<const BranchName *>(FindObject(name)); 
}
#endif
