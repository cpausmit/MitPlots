#include "MitAna/TAM/interface/TAMBranchInfo.h"


#ifndef ROOT_TAMVirtualBranchLoader
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h"
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMBranchInfo                                                        //
//                                                                      //
// Class that deals with the user pointers and interacts with           //
// the TAMVirtualBranchLoader to set up the data addresses to           //
// which these pointers point to. Also provides basic type              //
// checking.                                                            //
//                                                                      //
// Author : Corey Reed   07/20/2004                                     //
// Author : Maarten Ballintijn   12/01/2005                             //
// Author : Constantin Loizides  12/22/2005                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


ClassImp(TAMBranchInfo)


//______________________________________________________________________________
TAMBranchInfo::TAMBranchInfo(const Char_t* branchName) :
   TNamed(branchName,0), fIsLoaded(kFALSE), fLoader(0), fUsrAddresses()
{
}


//______________________________________________________________________________
TAMBranchInfo::~TAMBranchInfo() 
{
  for (auto&& addr : fUsrAddresses)
    delete addr;

   delete fLoader;
}


//______________________________________________________________________________
Int_t TAMBranchInfo::GetEntry(Long64_t entry)
{
   // Load the data for this entry and set the user pointers.
   
   if ( fIsLoaded ) return 0;
   
   Int_t ret = -1;
   if(fLoader) {
      ret = fLoader->GetEntry(entry);
      if(ret>=0)
	 SetUsrAddrs();
   } else {
      Error("GetEntry", "Pointer to loader is zero.");
   }
      
   return ret;
}

//______________________________________________________________________________
TClass*
TAMBranchInfo::GetClass() const 
{ 
  // Return type of user address.
  if (!fLoader)
    return 0;

  return fLoader->GetClass();
}

//______________________________________________________________________________
void TAMBranchInfo::Init() 
{
   // Initialize the branch info by setting all user pointers to zero.
   
   ZeroUsrAddrs();
}


//______________________________________________________________________________
Bool_t TAMBranchInfo::Notify(TTree* tree) 
{
   // This is called when a new file is opened. It then notifies
   // the corresponding loader and sets the data address
   // if necessary.
   
   ZeroUsrAddrs();
   
   if(fLoader) {
      if(!fLoader->Notify(tree)) {
         return kFALSE;
      }
   }

   return kTRUE;
}


//______________________________________________________________________________
void TAMBranchInfo::SetUsrAddrs() 
{
   // Set all user pointers for this branch to point to the data address.

  for (auto&& addr : fUsrAddresses)
    *addr->fPtr = fLoader->GetAddress();

   fIsLoaded = kTRUE;
}


//______________________________________________________________________________
void TAMBranchInfo::ZeroUsrAddrs() 
{
   // Set all user pointers for this branch to zero.

  for (auto&& addr : fUsrAddresses)
    *addr->fPtr = 0;

   fIsLoaded = kFALSE;
}
