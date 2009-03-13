// $Id: BranchName.cc,v 1.1 2009/03/13 08:40:01 loizides Exp $

#include "MitAna/DataTree/interface/BranchTable.h"
#include <TList.h>

ClassImp(mithep::BranchTable)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Bool_t BranchTable::Find(const char *brname, const char *brdep) const
{
  // Search for given pair of branch dependency.

  if (!brname || !brdep)
    return kFALSE;

  TList *l = GetListForObject(brname);
  if (!l)
    return kFALSE;

  TIter next(l);                           
  while (const BranchName *bn = dynamic_cast<const BranchName*>(next())) {
    if (strcmp(bn->Dep(),brdep)==0)
      return kTRUE;
  }
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t BranchTable::Find(const BranchName &bn) const
{
  // Search for given pair of branch dependency.

  return Find(bn.Name(), bn.Dep());
}

//--------------------------------------------------------------------------------------------------
void BranchTable::Print(Option_t *opt) const
{
  // Print trigger table content (not ordered!)

  TIter iter(MakeIterator());
  const BranchName *bn = dynamic_cast<const BranchName*>(iter.Next());
  while (bn) {
    bn->Print();
    bn = dynamic_cast<const BranchName*>(iter.Next());
  }
}
