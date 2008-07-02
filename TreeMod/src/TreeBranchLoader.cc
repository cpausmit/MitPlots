// $Id: TreeBranchLoader.cxx 5095 2008-03-17 21:07:09Z loizides $

#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include <Riostream.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClass.h>
#include <TFile.h>
#include "MitAna/DataTree/interface/BaseCollection.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"

ClassImp(mithep::TreeBranchLoader)

using namespace mithep;

//__________________________________________________________________________________________________
TreeBranchLoader::TreeBranchLoader(TAMBranchInfo *binfo) : 
  TAMTreeBranchLoader(binfo), 
  fDoReset(kFALSE)
{
  // Default constructor.
}

//__________________________________________________________________________________________________
void TreeBranchLoader::Clear(Option_t *option)
{
  // Clear objects in Objects that allocated memory on the heap.

  if(!fIsClass || !fBAddr) 
    return;

  if(fDoReset) {
    BaseCollection *c = static_cast<BaseCollection*>(fBAddr);
    c->Reset();
    return;
  } 

  TAMTreeBranchLoader::Clear(option);
}

//__________________________________________________________________________________________________
Bool_t TreeBranchLoader::Notify(TTree* tree)
{
  // Notify via TAMSelector that is being connected to a (new) file.
  // First call base class to perform type checking,
  // then check whether we have HIROOT specific collection
  // in branch.

  fDoReset = kFALSE;

  Bool_t ret = TAMTreeBranchLoader::Notify(tree);
  if(ret && fIsClass) {
    fDoReset = fClass->InheritsFrom("BaseCollection");
  }

  return ret;
}
