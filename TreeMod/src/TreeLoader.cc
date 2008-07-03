// $Id: TreeLoader.cc,v 1.1 2008/07/02 16:34:06 loizides Exp $

#include "MitAna/TreeMod/interface/TreeLoader.h"
#include <Riostream.h>
#include <TTree.h>
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"

ClassImp(mithep::TreeLoader)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
TreeLoader::TreeLoader()
{
   // Default constructor.
}


//--------------------------------------------------------------------------------------------------
TAMVirtualBranchLoader *TreeLoader::CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo)
{
   // Create our branch loader if the requested branch name is found in the tree.

   if(tree->GetBranch(brInfo->GetName()) == 0) return 0;
   
   return new TreeBranchLoader(brInfo);
}
