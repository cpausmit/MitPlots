#include "MitAna/TAM/interface/TAMObjBranchLoader.h"

// ROOT includes
#include <TFile.h>
#include <TError.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>

// for compatibility
#if ROOT_VERSION_CODE < ROOT_VERSION(5,11,3) && !defined(R__ASSERT)
#define R__ASSERT Assert
#endif

ClassImp(TAMObjBranchLoader)
////////////////////////////////////////////////////////////////////////////////
//
// $Id: TAMObjBranchLoader.cxx,v 1.2 2008/10/17 14:09:40 cjreed Exp $
//
// Load a TObject directly from the TFile. Type checking IS performed, to compare
// each module's pointer with the TClass info of the object.
//
// The object is read from file during Notify, and GetAddress of this loader
// returns the memory address of the object read from disk.
//
// The object is deleted at the beginning of Notify and in the destructor, so
// external sources should not delete the object.
//
////////////////////////////////////////////////////////////////////////////////


TAMObjBranchLoader::TAMObjBranchLoader(TAMBranchInfo* brInfo) : 
   TAMVirtualBranchLoader(brInfo),
   fObj(0), fRequireObj(kTRUE) {
   // constructor
}

TAMObjBranchLoader::~TAMObjBranchLoader() {
   // destructor
   delete fObj;
}
   
//______________________________________________________________________________
void TAMObjBranchLoader::Clear(Option_t* /*option*/)
{
   // If this object is a TClonesArrays, clear the objs in the array which
   // allocated memory on the heap.
   
   if (fObj!=0 && fObj->IsA()!=0 && fObj->IsA()->InheritsFrom("TClonesArray")) {
      // shouldn't need dynamic cast now that we've checked the inheritance
      TClonesArray* ca = static_cast<TClonesArray*>(fObj);
      ca->Clear("C");
   }
   
}

Int_t TAMObjBranchLoader::GetEntry(Long64_t /*entry*/) {
   // don't need to do anything
   
   return 0;
}

Bool_t TAMObjBranchLoader::CheckTypeAllModules() {
   // Loop over each user address and check that it's of the correct type
   // for the object to be read
   
   Bool_t isok=kTRUE;
   vector<TAMBranchInfo::BranchPtr_t*>::const_iterator ptr,
                                          end = GetBInfo()->fUsrAddresses.end();
   for (ptr=GetBInfo()->fUsrAddresses.begin(); (ptr!=end) && isok; ptr++) {
      isok &= CheckType((*ptr)->GetType());
   }
   return isok;
}

Bool_t TAMObjBranchLoader::CheckType(const type_info& ptrtype) {
   // check that the object being read is of the correct type
   
   R__ASSERT( fObj != 0 );
   
   const TClass* ocl = fObj->IsA();
   if (ocl!=0) {
      
      const type_info *oti = ocl->GetTypeInfo();
      if (oti!=0 && (*oti)==ptrtype) {
         return kTRUE;
      } else {
         const TClass *ptrcls = gROOT->GetClass(ptrtype);
         if (ptrcls!=0) {
            
            if ( ocl->InheritsFrom(ptrcls) ) {
               return kTRUE;
            } else {
               Error("CheckType",
                     "Cannot read object of type [%s] "
                     "with pointer of type [%s]",
                     ocl->GetName(), ptrcls->GetName());
            }
            
         } else {
            Error("CheckType",
                  "Could not get class for module's pointer of type [%s]",
                  ptrtype.name());
         }
      }
      
   } else {
      Error("CheckType",
            "Could not get class of [%s] at [%p]",
            fObj->GetName(), static_cast<const void*>(fObj));
   }
   return kFALSE;
}

Bool_t TAMObjBranchLoader::Notify(TTree* tree) {
   // load the header from the current file into memory
   
   R__ASSERT( tree != 0 );
   
   delete fObj; fObj=0;
   
   TFile* file = tree->GetCurrentFile();
   if (file!=0 && file->IsZombie()==kFALSE) {
      
      fObj = file->Get(GetBInfo()->GetName());
      if (fObj!=0) {
         
         if (CheckTypeAllModules()) {
            return kTRUE;
         } else {
            delete fObj; fObj=0;
            Error("Notify", "CheckBrTypeAllModules failed.");
         }
         
      } else {
         Error("Notify",
               "Could not get [%s] from [%s].",
               GetBInfo()->GetName(),
               file->GetName());
         return (fRequireObj==kFALSE);
      }
      
   } else {
      Error("Notify","Could not open the current file.");
   }
   return kFALSE;
}
