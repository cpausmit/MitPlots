//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.5 2009/02/18 15:38:55 loizides Exp $
//
// BranchName
//
// A class to hold a name and a number, ie the trigger name and trigger bit.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BRANCHNAME_H
#define MITANA_DATATREE_BRANCHNAME_H

#include <string>
#include <TObject.h> 
#include <TString.h>
#include <THashTable.h>
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class BranchName : public DataBase
  {
    public:
      BranchName() {}
      BranchName(const char *brname, const char *brdep) : 
        fBrName(brname), fBrDep(brdep) {}

      const char           *Name() const { return fBrName; }
      const char           *Dep()  const { return fBrDep; }
//      EObjType              ObjType() const { return kBranchName; }      
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fBrName;       //name
      TString               fBrDep;        //name

    ClassDef(BranchName, 1) // Branch name class
  };
#if 0
//--------------------------------------------------------------------------------------------------
// BranchTable
//
// A convenient THashTable for storage of BranchNames (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
  class BranchTable : public THashTable
  {
    public:
      BranchTable(Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash) {}

      const BranchName *Get(const char *name)   const;
      UShort_t           GetId(const char *name) const;
      using TCollection::Print;
      void               Print(Option_t *opt="") const;
  };
#endif
}

#if 0
//--------------------------------------------------------------------------------------------------
inline const mithep::BranchName *mithep::BranchTable::Get(const char *name) const
{ 
  // Return BranchName pointer for given name.

  return dynamic_cast<const BranchName *>(FindObject(name)); 
}

//--------------------------------------------------------------------------------------------------
inline UShort_t mithep::BranchTable::GetId(const char *name) const
{
  // Return trigger id of trigger with given name.

  const mithep::BranchName *tn = Get(name); 
  if (tn) 
    return tn->Id();
  
  Error("GetId", "BranchName for %s not found. Returning 65535.", name);
  return 65535;
}
#endif
#endif
