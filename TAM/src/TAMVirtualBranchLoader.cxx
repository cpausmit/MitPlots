//
// $Id: TAMVirtualBranchLoader.cxx,v 1.1 2008/05/27 19:13:21 loizides Exp $
//

#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h"


#ifndef ROOT_TTree
#include "TTree.h"
#endif
#ifndef ROOT_TError
#include "TError.h"
#endif


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMVirtualBranchLoader                                               //
//                                                                      //
// Abstract base class for loading data into TAM. Every TAM plugin      //
// (data loader) needs to derive from this class.                       //
//                                                                      //
// Author : Maarten Ballintijn   12/06/2005                             //
//          Constantin Loizides  12/22/2005                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAMVirtualBranchLoader)


//______________________________________________________________________________
TAMVirtualBranchLoader::TAMVirtualBranchLoader(TAMBranchInfo *binfo)
  : fBInfo(binfo)
{
   // Default constructor.
}


//______________________________________________________________________________
void TAMVirtualBranchLoader::Clear(Option_t */*option*/)
{
   // Clear branch loader before processing the next event,
   // eg. use this function to clear objects or arrays that
   // use heap memory.

   MayNotUse("Clear");
}

//______________________________________________________________________________
void* TAMVirtualBranchLoader::GetAddress() const
{
   // Returns the address to which the user pointer will
   // be set. 

   MayNotUse("NewBrAddress");
   return 0;
}


//______________________________________________________________________________
Int_t TAMVirtualBranchLoader::GetEntry(Long64_t /*entry*/)
{
   // Load the data for this branch.

   MayNotUse("GetEntry");

   return 0;
}


//______________________________________________________________________________
Bool_t TAMVirtualBranchLoader::Notify(TTree * /*tree*/)
{
   // Notify on opening of a new file. 
   // Can be used to setup data structures (eg. allocate
   // underlying memory if necessary) and to do the type
   // checking (see TAMTreeBranchLoader::Notify()).

   MayNotUse("Notify");

   return kFALSE;
}
