// $Id: TreeLoader.cxx 2950 2006-06-16 16:26:16Z loizides $

#include "MitAna/TreeMod/interface/TreeLoader.h"
#include <Riostream.h>
#include <TTree.h>
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"

ClassImp(mithep::TreeLoader)

using namespace mithep;

//__________________________________________________________________________________________________
TreeLoader::TreeLoader()
{
   // Default constructor.
}


//__________________________________________________________________________________________________
TAMVirtualBranchLoader *TreeLoader::CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo)
{
   // Create our branch loader if the requested branch name is found in the tree.

   if(tree->GetBranch(brInfo->GetName()) == 0) return 0;
   
   return new TreeBranchLoader(brInfo);
}
