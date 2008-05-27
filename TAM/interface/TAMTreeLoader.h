//
// $Id: TAMTreeLoader.h 5160 2008-05-20 19:52:53Z loizides $
//

#ifndef ROOT_TAMTreeLoader
#define ROOT_TAMTreeLoader


#ifndef ROOT_TAMVirtualLoader
#include "TAMVirtualLoader.h"
#endif


class TClass;
class TBranch;


class TAMTreeLoader : public TAMVirtualLoader {
public:
   TAMTreeLoader();
   virtual ~TAMTreeLoader() {}

   TAMVirtualBranchLoader *CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo);
   
   ClassDef(TAMTreeLoader,1)  // Tree branch plugin loader for TAM 
};

#endif //ROOT_TAMTreeBranchLoader
