//
// $Id: TAMTreeBranchLoader.h 5584 2009-07-16 21:00:34Z loizides $
//

#ifndef ROOT_TAMTreeBranchLoader
#define ROOT_TAMTreeBranchLoader


#include <typeinfo>


#ifndef ROOT_TAMVirtualBranchLoader
#include "TAMVirtualBranchLoader.h"
#endif


class TClass;
class TBranch;
class TTree;
class TDataType;

class TAMTreeBranchLoader : public TAMVirtualBranchLoader {
protected:
   BranchAddr_t         fBAddr;         //branch address for the data
   Bool_t               fIsClass;       //if the branch stores a class 
                                        // (as opposed to a struct)
   Bool_t               fLeafSizeConst; //if size of leaves in branch is const
   TBranch             *fBranch;        //the branch itself (not owned)
   TClass              *fClass;         //class information from dictionary 
                                        // (not owned) (ptr=0 if fund type)
   const TDataType     *fDataType;      //fundamental data type (ptr=0 if class)

   void                 AllocateMemory();
   Bool_t               CheckBrClass(const type_info& ptrtype, 
                                     const TClass& cls);
   Bool_t               CheckBrStruct(TClass& cls);
   Bool_t               CheckFundType(const type_info& ptrtype);
   Bool_t               CheckBrType(const type_info& ptrtype);
   Bool_t               CheckBrTypeAllModules();
   void                 DeleteMemory();
   void                 SetBranchAddress();
   void                 SetLeafAddresses();

public:
   TAMTreeBranchLoader() : fBAddr(0), fIsClass(kFALSE), 
     fLeafSizeConst(kTRUE), fBranch(0), fClass(0), fDataType(0) {}
   TAMTreeBranchLoader(TAMBranchInfo *binfo);
   virtual ~TAMTreeBranchLoader();

   void                 Clear(Option_t *option="");
   void*                GetAddress() const;
   Int_t                GetEntry(Long64_t entry);
   virtual Bool_t       Notify() { return Notify(0); }
   Bool_t               Notify(TTree *tree);
   
   ClassDef(TAMTreeBranchLoader,0)  // TAM plugin to load data from a branch
};


#endif //ROOT_TAMTreeBranchLoader
