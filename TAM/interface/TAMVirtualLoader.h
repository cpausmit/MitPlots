//
// $Id: TAMVirtualLoader.h 5584 2009-07-16 21:00:34Z loizides $
//

#ifndef ROOT_TAMVirtualLoader
#define ROOT_TAMVirtualLoader


#ifndef ROOT_TObject
#include "TObject.h"
#endif


class TTree;
struct TAMBranchInfo;
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
