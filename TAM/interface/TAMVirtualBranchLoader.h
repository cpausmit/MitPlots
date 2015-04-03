//
// $Id: TAMVirtualBranchLoader.h 5584 2009-07-16 21:00:34Z loizides $
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
private:
   TAMBranchInfo       *fBInfo; //corresponding TAMBranchInfo (not owned)

public:
   TAMVirtualBranchLoader() : fBInfo(0) {}
   TAMVirtualBranchLoader(TAMBranchInfo *binfo);
   virtual ~TAMVirtualBranchLoader() {}

   virtual void         Clear(Option_t *option="");
   virtual void*        GetAddress()                const;
         TAMBranchInfo *GetBInfo()                        { return fBInfo; }
   const TAMBranchInfo *GetBInfo()                  const { return fBInfo; }
   virtual Int_t        GetEntry(Long64_t entry);
   virtual Bool_t       Notify() { return Notify(0); }
   virtual Bool_t       Notify(TTree *tree);
   
   ClassDef(TAMVirtualBranchLoader,1)  // Base class for data loader plugins
};

#endif //ROOT_TAMVirtualBranchLoader
