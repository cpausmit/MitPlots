// $Id: TreeBranchLoader.cc,v 1.2 2008/07/03 08:22:19 loizides Exp $

#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include <Riostream.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClass.h>
#include <TFile.h>
#include "MitAna/DataCont/interface/BaseCollection.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"

ClassImp(mithep::TreeBranchLoader)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
TreeBranchLoader::TreeBranchLoader(TAMBranchInfo *binfo) : 
  TAMTreeBranchLoader(binfo), 
  fDoReset(kFALSE)
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
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
