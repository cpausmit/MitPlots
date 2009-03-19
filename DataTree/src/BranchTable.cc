// $Id: BranchTable.cc,v 1.2 2009/03/16 19:31:14 loizides Exp $

#include "MitAna/DataTree/interface/BranchTable.h"
#include <TObjString.h>
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
TList *BranchTable::GetBranches() const
{
  // Get list of branches. This list has to be deleted by the user of this function.

  TList *l = 0;
  TIter iter(MakeIterator());
  const BranchName *bn = dynamic_cast<const BranchName*>(iter.Next());
  if (bn) {
    l = new TList;
    l->SetOwner(1);
  }
  while (bn) {
    if (!l->FindObject(bn->Name())) {
      l->Add(new TObjString(bn->Name()));
    }
    bn = dynamic_cast<const BranchName*>(iter.Next());
  }
  return l;
}

//--------------------------------------------------------------------------------------------------
TList *BranchTable::GetDepBranches(const char *brname) const
{
  // Get list of dependent branches for given branch name. 
  // This list has to be deleted by the user of this function.

  TList *bl = GetListForObject(brname);
  if (!bl)
    return 0;

  TList *l = 0;
  TIter iter(bl->MakeIterator());
  const BranchName *bn = dynamic_cast<const BranchName*>(iter.Next());
  if (bn) {
    l = new TList;
    l->SetOwner(1);
  }
  while (bn) {
    if ((strcmp(brname,bn->Name())==0) && (!l->FindObject(bn->Dep()))) {
      l->Add(new TObjString(bn->Dep()));
    }
    bn = dynamic_cast<const BranchName*>(iter.Next());
  }
  return l;
}

//--------------------------------------------------------------------------------------------------
void BranchTable::Print(Option_t *opt) const
{
  // Print trigger table content (not ordered!)

  TList *br = GetBranches();
  if (!br) 
    return;

  TIter iter(br->MakeIterator());
  const TObjString *n = dynamic_cast<const TObjString*>(iter.Next());
  while (n) {
    TList *bl = GetDepBranches(n->GetName());
    if (bl) {
      TIter iter2(bl->MakeIterator());
      const TObjString *d = dynamic_cast<const TObjString*>(iter2.Next());
      printf("%s -> ", n->GetName());
      while (d) {
        printf("%s ", d->GetName());
        d = dynamic_cast<const TObjString*>(iter2.Next());
      }
      printf("\n");
      delete bl;
    }
    n = dynamic_cast<const TObjString*>(iter.Next());
  }
  delete br;
}
