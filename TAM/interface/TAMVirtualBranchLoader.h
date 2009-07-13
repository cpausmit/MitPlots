//
// $Id: TAMVirtualBranchLoader.h,v 1.1 2008/05/27 19:13:21 loizides Exp $
//

#ifndef ROOT_TAMVirtualBranchLoader
#define ROOT_TAMVirtualBranchLoader


#ifndef ROOT_TObject
#include "TObject.h"
#endif
#ifndef ROOT_TAMBranchInfo
#include "TAMBranchInfo.h"
#endif


class TTree;


class TAMVirtualBranchLoader : public TObject {
   TAMBranchInfo       *fBInfo; //corresponding TAMBranchInfo (not owned)

public:
   TAMVirtualBranchLoader(TAMBranchInfo *binfo);
   virtual ~TAMVirtualBranchLoader() {}

   virtual void         Clear(Option_t *option="");
   virtual void*        GetAddress()                const;
   TAMBranchInfo       *GetBInfo()                  const { return fBInfo; }
   virtual Int_t        GetEntry(Long64_t entry);
   using       TObject::Notify;
   virtual Bool_t       Notify(TTree *tree);
   
   ClassDef(TAMVirtualBranchLoader,1)  // Base class for data loader plugins
};

#endif //ROOT_TAMVirtualBranchLoader
