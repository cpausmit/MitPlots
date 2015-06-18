#ifndef ROOT_TAMBranchInfo
#define ROOT_TAMBranchInfo


#include <vector>
#include <typeinfo>


#ifndef ROOT_TNamed
#include "TNamed.h"
#endif
#ifndef ROOT_TError
#include "TError.h"
#endif


class TTree;
class TAMVirtualBranchLoader;


typedef void* BranchAddr_t;

struct TAMBranchInfo : TNamed {
   // Stores the name and pointers to requested branches.
   // Inherits from TObject to allow storage in a THashTable

   struct BranchPtr_t {
      // In ROOT v4.0.8 (and prior) rootcint had trouble with a vector<void**>,
      // so instead we make a small struct to store the void** and use
      // a vector of the structs.
      //
      // Also serves as an abstract base class for the type-storing class
      // this allows the minimum number of functions & classes to be
      // templated.

      BranchAddr_t                *fPtr; //pointer to the TAModule's 
                                         // pointer to the branch object
      BranchPtr_t(BranchAddr_t* ptr) : fPtr(ptr) {}
      virtual ~BranchPtr_t()                     { (*fPtr) = 0; }
      virtual const type_info& GetType() const=0;
   };

   template <typename T>
   struct TAMTypedBrPtr : BranchPtr_t {
      TAMTypedBrPtr(BranchAddr_t* ptr) : BranchPtr_t(ptr) {}
      virtual ~TAMTypedBrPtr() {}
      virtual const type_info& GetType() const   { return typeid(T); }
   };

   Bool_t                          fIsLoaded;     //if branch is loaded 
                                                  // for current event
   TAMVirtualBranchLoader         *fLoader;       //our data (tree) loader
   std::vector<BranchPtr_t*>            fUsrAddresses; //list of pointers to each 
                                                  // mod's ptr to branch object

   TAMBranchInfo(const Char_t* branchName=0);
   virtual ~TAMBranchInfo();

   template <typename T> Bool_t    AddPtr(T*& address);
   Int_t                           GetEntry(Long64_t entry);
   TAMVirtualBranchLoader         *GetLoader()   const { return fLoader;   }
   const type_info&                GetType()     const;
   void                            Init();
   Bool_t                          IsLoaded()    const { return fIsLoaded; } 
   using                  TObject::Notify;
   Bool_t                          Notify(TTree* tree);
   void                            SetUsrAddrs();
   void                            SetLoader(TAMVirtualBranchLoader *loader) 
                                     { fLoader = loader; }
   void                            ZeroUsrAddrs();

   ClassDef(TAMBranchInfo,0)  // General per branch information
};


//______________________________________________________________________________
template <typename T> 
inline Bool_t TAMBranchInfo::AddPtr(T*& address)
{
   // Add a user pointer for this branch.

   // Must do an explicit cast to BranchAddr_t*
   BranchAddr_t* adr = reinterpret_cast<BranchAddr_t*>(&address);
   fUsrAddresses.push_back(new TAMTypedBrPtr<T>(adr));
   return kTRUE;
}

//______________________________________________________________________________
inline const type_info &TAMBranchInfo::GetType() const 
{ 
  // Return type of user address.

  return fUsrAddresses.empty() ? typeid(void) : fUsrAddresses[0]->GetType(); 
}

#endif //ROOT_TAMBranchInfo
