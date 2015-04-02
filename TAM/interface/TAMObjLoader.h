#ifndef ROOT_TAMObjLoader
#define ROOT_TAMObjLoader

#ifndef ROOT_TAMVirtualLoader
#include "TAMVirtualLoader.h"
#endif
#ifndef ROOT_TString
#include "TString.h"
#endif

class TAMObjLoader : public TAMVirtualLoader {
 private:
   TString         fObjName;    //  name of the object to load. must match the modules' ReqBranch
   Bool_t          fRequireObj; //  fail if the object cannot be loaded (default: true)

 public:
   TAMObjLoader(const Char_t* objName="", const Bool_t reqObj=kTRUE) : 
      fObjName(objName), fRequireObj(reqObj) {}
   virtual ~TAMObjLoader() {}
   
   const Char_t*            GetObjName() const { return fObjName.Data(); }
   Bool_t                   IsRequiringObj() const { return fRequireObj; }
   
   void                     SetObjName(const Char_t* n) { fObjName = n; }
   void                     SetRequireObj(const Bool_t r) { fRequireObj = r; }
   
   
   TAMVirtualBranchLoader*  CreateBranchLoader(TTree *tree,
                                               TAMBranchInfo* brInfo);

   ClassDef(TAMObjLoader, 3); // use TAMObjBranchLoader to load a TObject from the current file
};

#endif // ROOT_TAMObjLoader
