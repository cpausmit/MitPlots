//
// $Id: TAMTreeLoader.cxx,v 1.2 2009/07/13 19:20:25 loizides Exp $
//

#include "MitAna/TAM/interface/TAMTreeLoader.h"


#ifndef ROOT_TTree
#include "TTree.h"
#endif
#ifndef ROOT_TAMTreeBranchLoader
#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"
#endif


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMTreeLoader                                                        //
//                                                                      //
// This plugin loader loads the tree branch loader plugin into TAM.     //
//                                                                      //
// Author : Maarten Ballintijn     12/06/2005                           //
//	    Constantin Loizides    12/06/2005                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAMTreeLoader)


//______________________________________________________________________________
TAMTreeLoader::TAMTreeLoader()
{
   // Default constructor.
}


//______________________________________________________________________________
TAMVirtualBranchLoader *TAMTreeLoader::CreateBranchLoader(TTree *tree, 
                                                          TAMBranchInfo* brInfo)
{
   // Create branch loader if the requested branch name is found in the tree.
   
   TString brname(tree->GetAlias(brInfo->GetName()));
   if(brname.IsNull()) {
      brname=brInfo->GetName();
   }
   
   if(tree->GetBranch(brname.Data()) == 0) {
      Warning("CreateBranchLoader",
              "Could not find branch with name [%s] in tree [%s].",
              (brInfo->GetName()!=0) ? (brInfo->GetName()) : 
              "null", tree->GetName());

      return 0;
   }
   
   return new TAMTreeBranchLoader(brInfo);
}
