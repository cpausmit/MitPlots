#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"


#ifndef ROOT_RVersion
#include <RVersion.h>
#endif
#ifndef ROOT_TError
#include "TError.h"
#endif
#ifndef ROOT_TClass
#include "TClass.h"
#endif
#ifndef ROOT_TList
#include "TList.h"
#endif
#ifndef ROOT_TFile
#include "TFile.h"
#endif
#ifndef ROOT_TBranch
#include "TBranch.h"
#endif
#ifndef ROOT_TLeaf
#include "TLeaf.h"
#endif
#ifndef ROOT_TDataMember
#include "TDataMember.h"
#endif
#ifndef ROOT_TDataType
#include "TDataType.h"
#endif
#ifndef ROOT_TTree
#include "TTree.h"
#endif
#ifndef ROOT_TROOT
#include "TROOT.h"
#endif
#ifndef ROOT_TClonesArray
#include "TClonesArray.h"
#endif


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMTreeBranchLoader                                                  //
//                                                                      //
// Default TAM plugin that loads data from single tree branches         //
// into memory.                                                         //
//                                                                      //
// Author : Corey Reed           07/20/2004                             //
//          Maarten Ballintijn   12/06/2005                             //
//          Constantin Loizides  12/06/2005                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAMTreeBranchLoader)


#if ROOT_VERSION_CODE < ROOT_VERSION(5,11,3)
#define R__ASSERT(e) \
   if (!(e)) Fatal("", kAssertMsg, _QUOTE_(e), __LINE__, __FILE__)
#endif


//______________________________________________________________________________
TAMTreeBranchLoader::TAMTreeBranchLoader(TAMBranchInfo *binfo)
   : TAMVirtualBranchLoader(binfo), fBAddr(0), fIsClass(kFALSE), 
     fLeafSizeConst(kTRUE), fBranch(0)
{
   // Default constructor.
}


//______________________________________________________________________________
TAMTreeBranchLoader::~TAMTreeBranchLoader()
{
   // Destructor.

   DeleteMemory();
   fBranch = 0;
}


//______________________________________________________________________________
void TAMTreeBranchLoader::AllocateMemory()
{
   // Allocate memory on heap.

   R__ASSERT(fClass != 0);

   if(fBAddr!=0) {
      Fatal("AllocateMemory", 
            "Address already allocated! Must call DeleteMemory() first!");
      return;
   }

   fBAddr = fClass->New();
}

//______________________________________________________________________________
Bool_t TAMTreeBranchLoader::CheckBrStruct(TClass& cls) 
{
   // Given pointer is a class/struct type for a list of fundamental leaves:
   // Check that the members correspond to the leaves,
   // also check that the size of the members does not change
   // (the compiler may buffer the memory between different sized
   // members, which causes SetBranchAddress to give unexpected results).

   TList* members = cls.GetListOfDataMembers();
   if ( (members!=0) && (members->IsEmpty()==kFALSE) ) {
      TObjArray* lvs = fBranch->GetListOfLeaves();
      if (lvs!=0) {
         if (members->GetSize() == lvs->GetEntriesFast()) {
            TIter nextlf(lvs);
            TIter nextmem(members);
            TDataMember* dm = dynamic_cast<TDataMember*>(nextmem());
            TLeaf* lf = dynamic_cast<TLeaf*>(nextlf());
            const Int_t size = dm->GetUnitSize();
            for (; ( (lf!=0) && (dm!=0) );
                 dm = dynamic_cast<TDataMember*>(nextmem()),
                 lf = dynamic_cast<TLeaf*>(nextlf()) ) {
               if (strcmp(lf->GetTypeName(),dm->GetTypeName())!=0) {
                  Error("CheckBrStruct",
                        "Member [%s] of class [%s] is of type [%s], "
                        "while leaf [%s] if of type [%s].",
                        dm->GetName(), cls.GetName(),
                        dm->GetTypeName(), lf->GetName(),
                        lf->GetTypeName());
                  return kFALSE;
               } else {
                  fLeafSizeConst &= (size == dm->GetUnitSize());
               }
            }
            return kTRUE;
         } else {
            Error("CheckBrStruct",
                  "Pointer of type [%s] has [%d] members, while branch "
                  "[%s] has [%d] leaves.",
                  cls.GetName(), members->GetSize(),
                  fBranch->GetName(), lvs->GetEntriesFast());
         }
      } else {
         Error("CheckBrStruct",
               "Could not get list of leaves for branch [%s].",
               fBranch->GetName());
      }
   } else {
      Error("CheckBrStruct",
            "Could not get list of members for type [%s].",
            cls.GetName());
   }

   return kFALSE;
}


//______________________________________________________________________________
Bool_t TAMTreeBranchLoader::CheckBrType(TClass& cl) 
{
   // Check that the specified type (of the user's pointer) corresponds with
   // what is in the tree:
   // 1. Check if the tree stores a class of the specified type
   // 2. Check the specified type is a class/struct (that is in the TClass
   //    dictionary!!) whose members correspond to the leaves in the branch.

   R__ASSERT(gROOT);
   
   // first try the branch (works only for classes)
   TClass* onfile = gROOT->GetClass(fBranch->GetClassName());
   if (onfile) {
      // known class
      fIsClass = kTRUE;
      fClass = onfile;

      if (onfile->InheritsFrom(&cl))
        return kTRUE;
      else {
        Error("CheckBrType",
              "Class of first leaf in branch [%s] is [%s], "
              "different (not equal/derived) from pointer type [%s].",
              fBranch->GetName(), onfile->GetName(), cl.GetName());
        return kFALSE;
      }
   }
   else {
     // pointer is a class/struct, branch is list of fundamentals
     fClass = &cl;
     return CheckBrStruct(cl);
   }
}

//______________________________________________________________________________
Bool_t TAMTreeBranchLoader::CheckBrTypeAllModules()
{
   // Loop over each user address and check that it's of the correct type
   // for the data contained in this branch.

  for (auto&& addr : GetBInfo()->fUsrAddresses) {
    TClass* cl = addr->GetClass();
    if (!cl) {
      Error("CheckBrType",
            "Pointer for branch [%s] does not have a defined TClass, or "
            "is a class/struct which is not in the TClass dictionary. "
            "This is not supported. See documentation.",
            fBranch->GetName());
      return false;
    }
    if (!CheckBrType(*cl))
      return false;
  }

  return true;
}

//______________________________________________________________________________
void TAMTreeBranchLoader::Clear(Option_t */*option*/)
{
   // Clear objects in TClonesArrays that allocated memory on the heap.

   if(!fIsClass || !fBAddr) 
      return;

   TString classname(fBranch->GetClassName()); 	 
   if (classname.CompareTo("TClonesArray")==0) { 	 
      TClonesArray* ca = reinterpret_cast<TClonesArray*>(fBAddr); 	 
      if (ca!=0) { 	 
         ca->Clear("C"); 	 
      } else { 	 
         Error("Clear", "Could not clear the clones array for branch %s",
               fBranch->GetName()); 	 
      } 	 
   }
}


//______________________________________________________________________________
void TAMTreeBranchLoader::DeleteMemory()
{
   // Delete (previously) allocated memory on heap.

   if(fClass && fBAddr) {
      fClass->Destructor(fBAddr);
      fBAddr = 0;
   }
}


//______________________________________________________________________________
void* TAMTreeBranchLoader::GetAddress() const
{
   // Return the branch address.

   return fBAddr;
}


//______________________________________________________________________________
Int_t TAMTreeBranchLoader::GetEntry(Long64_t entry)
{
   // Get requested entry.

   Int_t ret = 0;

   // do not reread branch
   if (entry!=fBranch->GetReadEntry()) 
     ret = fBranch->GetEntry(entry);

   if(ret<0) {
      Error("GetEntry",
	    "I/O error in file [%s] (at entry %lld) "
            "when accessing branch with name [%s] in requested branch list.",
	    (fBranch->GetFileName()!=0) ? (fBranch->GetFileName()) : "null", 
            entry, fBranch->GetName());
   }

   return ret;
}


//______________________________________________________________________________
Bool_t TAMTreeBranchLoader::Notify(TTree* tree)
{
   // Notify via TAMSelector and TAMBranchInfo that a tree is
   // being connected from a (new) file.
   // Therefore get branch information and perform type checking.
   // Set branch address if CheckBrType() was successful.

   R__ASSERT( tree != 0 );

   // get branch with requested branch name
   // first check if given name is alias
   TString brname(tree->GetAlias(GetBInfo()->GetName()));
   if (brname.IsNull())
      brname=GetBInfo()->GetName();
   fBranch = tree->GetBranch(brname);

   if (fBranch == 0) {
      Error("Notify", "GetBranch(%s) failed.", GetBInfo()->GetName());
      return kFALSE;
   }
   
   if (GetBInfo()->fUsrAddresses.size()) {
      // get branch information and check if types match
     if (CheckBrTypeAllModules()==kFALSE) {
        Error("Notify", "CheckBrTypeAllModules failed.");
        return kFALSE;
     }
   } else {
      // zero usr addresses (only possible for autoloading)
      TClass* cls = gROOT->GetClass(fBranch->GetClassName());
      if (cls != 0) { // known class
         fIsClass = kTRUE;
         fClass = cls;
      }
   }

   // allocate memory on heap at fBAddr
   if(!fBAddr)
      AllocateMemory();

   // set the branch address to point to fBAddr
   SetBranchAddress();

   return kTRUE;
}


//______________________________________________________________________________
void TAMTreeBranchLoader::SetBranchAddress() 
{
   // Set the branch address to point to our memory (fBAddr).

   if (fIsClass) {
      // branch stores object
      fBranch->SetAddress( &(fBAddr) );
   } else {
      // branch stores fundamentals
      if (fLeafSizeConst) {
         fBranch->SetAddress(fBAddr);
      } else {
         SetLeafAddresses();
      }
   }
}


//______________________________________________________________________________
void TAMTreeBranchLoader::SetLeafAddresses() 
{
   // Loop over the leaves in the branch and the data members of
   // a (typical) struct/class used to read the branch
   // assign the individual leaves to have address corresponding to
   // fBAddr + (offset of each data member). This function is
   // only used when the data members of the struct have different sizes and
   // assumes that each module's pointer references a class or struct that
   // is organized in the same way as any other module.
   // CheckBrStruct() assures that this really is the case.
   
  TClass* cls = GetBInfo()->GetClass();
  if (cls!=0) {
    TList* members = cls->GetListOfDataMembers();
    if ( (members!=0) && (members->IsEmpty()==kFALSE) ) {
      TObjArray* lvs = fBranch->GetListOfLeaves();
      if (lvs!=0) {
        if (members->GetSize() == lvs->GetEntriesFast()) {
          TIter nextlf(lvs);
          TIter nextmem(members);
          TDataMember* dm = dynamic_cast<TDataMember*>(nextmem());
          TLeaf* lf = dynamic_cast<TLeaf*>(nextlf());
          for (; ( (lf!=0) && (dm!=0) );
               dm = dynamic_cast<TDataMember*>(nextmem()),
                 lf = dynamic_cast<TLeaf*>(nextlf()) ) {
            // the cast is just to prevent compiler warnings
            lf->SetAddress( static_cast<Char_t*>(fBAddr)
                            + dm->GetOffset() );
          }
        } else {
          Error("SetLeafAddresses",
                "Class [%s] has [%d] members, while branch [%s] "
                "has [%d] leaves.",
                cls->GetName(), members->GetSize(),
                fBranch->GetName(), lvs->GetEntriesFast());
        }
      } else {
        Error("SetLeafAddresses",
              "Could not get list of leaves for branch [%s].",
              fBranch->GetName());
      }
    } else {
      Error("SetLeafAddresses",
            "Could not get list of data members for class [%s].",
            cls->GetName());
    }
  } else {
    Error("SetLeafAddresses",
          "Could not get class for branch %s.",
          GetBInfo()->GetName());
  }
}
