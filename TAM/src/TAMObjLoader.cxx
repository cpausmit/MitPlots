#include "MitAna/TAM/interface/TAMObjLoader.h"

#include "MitAna/TAM/interface/TAMObjBranchLoader.h"

ClassImp(TAMObjLoader);
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMObjLoader                                                         //
//                                                                      //
// Use TAMObjBranchLoader to load the TObject whose name in the file    //
// is the branch name requested by the module.                          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

TAMVirtualBranchLoader* TAMObjLoader::CreateBranchLoader(TTree* /*tree*/,
                                                         TAMBranchInfo* brInfo) {
   if (fObjName.CompareTo(brInfo->GetName())==0) {
      TAMObjBranchLoader* b = new TAMObjBranchLoader(brInfo);
      b->SetRequireObj(fRequireObj);
      return b;
   }
   return 0;
}

