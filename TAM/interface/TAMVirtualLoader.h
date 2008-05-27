//
// $Id: TAMVirtualLoader.h 2775 2006-04-29 18:01:04Z loizides $
//

#ifndef ROOT_TAMVirtualLoader
#define ROOT_TAMVirtualLoader


#ifndef ROOT_TObject
#include "TObject.h"
#endif


class TTree;
class TAMBranchInfo;
class TAMVirtualBranchLoader;


class TAMVirtualLoader : public TObject {

public:
   TAMVirtualLoader();
   virtual ~TAMVirtualLoader() {}

   virtual TAMVirtualBranchLoader  *CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo) = 0;
   
   ClassDef(TAMVirtualLoader,1)  // Abstract base class for loading plugins into TAM
};

#endif //ROOT_TAMVirtualLoader
