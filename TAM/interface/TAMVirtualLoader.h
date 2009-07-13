//
// $Id: TAMVirtualLoader.h,v 1.1 2008/05/27 19:13:21 loizides Exp $
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

//______________________________________________________________________________
public:
   TAMVirtualLoader();
   virtual ~TAMVirtualLoader() {}

   virtual 
   TAMVirtualBranchLoader *CreateBranchLoader(TTree *tree, 
                                              TAMBranchInfo* brInfo) = 0;
   
   ClassDef(TAMVirtualLoader,1)  // Base class for loading plugins into TAM
};

#endif //ROOT_TAMVirtualLoader
