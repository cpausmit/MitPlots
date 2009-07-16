//
// $Id: TAMTreeLoader.h,v 1.2 2009/07/13 19:20:24 loizides Exp $
//

#ifndef ROOT_TAMTreeLoader
#define ROOT_TAMTreeLoader


#ifndef ROOT_TAMVirtualLoader
#include "MitAna/TAM/interface/TAMVirtualLoader.h"
#endif


class TClass;
class TBranch;


class TAMTreeLoader : public TAMVirtualLoader {
public:
   TAMTreeLoader();
   virtual ~TAMTreeLoader() {}

   TAMVirtualBranchLoader *CreateBranchLoader(TTree *tree, 
                                              TAMBranchInfo* brInfo);
   
   ClassDef(TAMTreeLoader,1)  // Tree branch plugin loader for TAM 
};

#endif //ROOT_TAMTreeBranchLoader
