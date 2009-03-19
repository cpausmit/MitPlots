//--------------------------------------------------------------------------------------------------
// $Id: BranchName.h,v 1.2 2009/03/13 20:24:51 loizides Exp $
//
// BranchName
//
// A class that for a given branch name stores a branch that it depends on.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BRANCHNAME_H
#define MITANA_DATATREE_BRANCHNAME_H

#include <TString.h>
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class BranchName : public DataBase
  {
    public:
      BranchName() {}
      BranchName(const char *brname, const char *brdep) : 
        fBrName(brname), fBrDep(brdep) {}

      const char           *Dep()     const { return fBrDep;         }
      const char           *GetName() const { return fBrName;        }
      ULong_t               Hash()    const { return fBrName.Hash(); }
      const char           *Name()    const { return fBrName;        }
      EObjType              ObjType() const { return kBranchName;    }      
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fBrName;       //name of branch
      TString               fBrDep;        //name of dependency

    ClassDef(BranchName, 1) // Branch name class
  };
}
#endif
