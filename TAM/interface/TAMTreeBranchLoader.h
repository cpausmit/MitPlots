#ifndef ROOT_TAMTreeBranchLoader
#define ROOT_TAMTreeBranchLoader


#include <typeinfo>


#ifndef ROOT_TAMVirtualBranchLoader
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h"
#endif


class TClass;
class TBranch;
class TTree;


class TAMTreeBranchLoader : public TAMVirtualBranchLoader {
protected:
   BranchAddr_t         fBAddr;         //branch address for the data
   Bool_t               fIsClass;       //if the branch stores a class 
                                        // (as opposed to a struct)
   Bool_t               fLeafSizeConst; //if size of leaves in branch is const
   TBranch             *fBranch;        //the branch itself (not owned)
   TClass              *fClass;         //class information from dictionary 
                                        // (not owned)

   void                 AllocateMemory();
   Bool_t               CheckBrClass(const type_info& ptrtype, 
                                     const TClass& cls);
   Bool_t               CheckBrStruct(TClass& cls);
   Bool_t               CheckBrType(const type_info& ptrtype);
   Bool_t               CheckBrTypeAllModules();
   void                 DeleteMemory();
   void                 SetBranchAddress();
   void                 SetLeafAddresses();

public:
   TAMTreeBranchLoader(TAMBranchInfo *binfo);
   virtual ~TAMTreeBranchLoader();

   void                 Clear(Option_t *option="");
   void*                GetAddress() const;
   Int_t                GetEntry(Long64_t entry);
   using       TObject::Notify;
   Bool_t               Notify(TTree *tree) override;
   
   ClassDef(TAMTreeBranchLoader,0)  // TAM plugin to load data from a branch
};


#endif //ROOT_TAMTreeBranchLoader
