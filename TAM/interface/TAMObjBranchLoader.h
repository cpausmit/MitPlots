#ifndef ARK_TAMObjBranchLoader
#define ARK_TAMObjBranchLoader

// TAM includes
#ifndef ROOT_TAMVirtualBranchLoader
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h"
#endif

class TAMObjBranchLoader : public TAMVirtualBranchLoader {
 private:
   TObject*       fObj;        //  the header object
   Bool_t         fRequireObj; //  if true, Notify will fail if the obj cannot be loaded (default true)

   Bool_t         CheckType(const type_info& ptrtype);
   Bool_t         CheckTypeAllModules();

 protected:
   void           SetObj(TObject* o) { fObj = o; }
    
 public:
   TAMObjBranchLoader() : fObj(0), fRequireObj(kTRUE) {}
   TAMObjBranchLoader(TAMBranchInfo* brInfo);
   virtual ~TAMObjBranchLoader();
   
   void           Clear(Option_t *option="");
   void*          GetAddress() const { return fObj; }
   Int_t          GetEntry(Long64_t entry);
   using TAMVirtualBranchLoader::Notify;
   virtual Bool_t Notify(TTree* tree);

   Bool_t         IsRequiringObj() const { return fRequireObj; }

   TObject*       GetObject() { return fObj; }
   const TObject* GetObject() const { return fObj; }
   
   void           SetRequireObj(const Bool_t r) { fRequireObj = r; }
   
   ClassDef(TAMObjBranchLoader, 2) // load a TObject directly from the current TFile
};



#endif // ARK_TAMObjBranchLoader
