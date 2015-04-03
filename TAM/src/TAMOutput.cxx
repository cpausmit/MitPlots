//
// $Id: TAMOutput.cxx,v 1.8 2012/03/30 01:08:39 paus Exp $
//

#include "MitAna/TAM/interface/TAMOutput.h"
#include "TTree.h"

#ifndef ROOT_TClass
#include "TClass.h"
#endif
#ifndef ROOT_Riostream
#include "Riostream.h"
#endif
#ifndef ROOT_RVersion
#include "RVersion.h"
#endif
#ifndef ROOT_TIterator
#include "TIterator.h"
#endif
#ifndef ROOT_TObjArray
#include "TObjArray.h"
#endif
#ifndef ROOT_TError
#include "TError.h"
#endif
#ifndef ROOT_TH1
#include "TH1.h"
#endif
#ifndef ROOT_TROOT
#include "TROOT.h"
#endif
#ifndef ROOT_TDataMember
#include "TDataMember.h"
#endif
#ifndef ROOT_TDirectory
#include "TDirectory.h"
#endif
#ifndef TAM_TAModule
#include "MitAna/TAM/interface/TAModule.h"
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMOutput                                                            //
//                                                                      //
// Stores the output objects of a module for use with the Proof         //
// facility. This object is itself a list of all sub modules output     //
// objects, so that whatever TAModule hierarchy exists is duplicated in //
// the TAMOutput hierarchy. Thus, only the tree of TAMOutput objects    //
// needs to be streamed in to the master from the worker computers when //
// merging output objects in a Proof analsys, and not the complete      //
// TAModule objects themselves. This is useful since an TAModule object //
// is in principal arbitrarily large, and only the list of output       //
// objects needs to be merged.                                          //
//                                                                      //
// This class provides the functionality to merge the list of output    //
// objects correctly throughout the hierarchy of TAMOutput objects.     //
//                                                                      //
// The existence of this class is hidden to classes inheritting from    //
// TAModule. Such end-user modules need only add the desired output     //
// objects (such as histograms) to their output list by calling         //
// TAModule::AddOutput(TObject*&).                                      //
//                                                                      //
// Author : Corey Reed   07/20/2004                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAMOutput)
ClassImp(TAMOutput::TAMModInspector)
ClassImp(TAMOutput::TAMModInspector::TAMModMember)


#if ROOT_VERSION_CODE < ROOT_VERSION(5,11,3)
#define R__ASSERT(e) \
   if (!(e)) Fatal("", kAssertMsg, _QUOTE_(e), __LINE__, __FILE__)
#endif


//______________________________________________________________________________
TAMOutput::TAMModInspector::TAMModInspector() :
   fOutputMembers(TCollection::kInitHashTableCapacity, 1)
{
   // Default constructor.

   fOutputMembers.SetOwner(kTRUE);
}


//______________________________________________________________________________
TAMOutput::TAMModInspector::~TAMModInspector() 
{
   // Destructor.
}


//______________________________________________________________________________
void TAMOutput::TAMModInspector::AddOutput(TObject* obj, const void* adr) 
{
   // Set the title of the TAMModMember for this object to the name of the obj.

   TAMModMember* mem = FindModMemberWithAddr(adr);
   if (mem!=0) {
     mem->SetName(obj->GetName());
   } // else output object is not (pointed to by) a member of the module
}


//______________________________________________________________________________
void TAMOutput::TAMModInspector::Inspect(TClass* cl, const Char_t* parent,
                                         const Char_t* name, const void* addr) 
{
   // Set the address of the mod member to addr.
   // If no mod member yet exists for this member, make it (but with no name).

   if (cl->InheritsFrom(TAModule::Class())) {
      TAMModMember* mem = FindModMemberWithMemberName(name);
      if (mem==0) {
         if ( (cl!=0) && (name!=0) && (addr!=0) ) {
            TString fullname(parent);
            fullname.Append(name);
            fOutputMembers.Add(new TAMModMember(0, fullname.Data(),
                                                const_cast<void*>(addr), cl));
         } else {
            ::Error("TAMOutput::TAMModInspector::Inspect",
                    "Can not store TAMModMember with class at %p, "
                    "name=%s, addr=%p",
                    static_cast<void*>(cl), 
                    name, static_cast<const void*>(addr));
         }
      } else {
         mem->fAddr = const_cast<void*>(addr);
      }
   } // else don't bother; it can't point to an output object
}


//______________________________________________________________________________
void TAMOutput::TAMModInspector::RemoveOutput(TObject* obj) 
{
   // Remove the TAMModMember for this object.

   TAMModMember* mem = dynamic_cast<TAMModMember*>(
      fOutputMembers.FindObject(obj->GetName()));
   if (mem!=0) {
      fOutputMembers.Remove(mem);
   }
}


//______________________________________________________________________________
TAMOutput::TAMModInspector::TAMModMember* 
   TAMOutput::TAMModInspector::FindModMemberWithAddr(const void* addr) 
{
   // Find the mod member that has the specified address

   TIter nextmem(fOutputMembers.MakeIterator());
   TAMModMember* mem=0;
   while ( (mem = dynamic_cast<TAMModMember*>(nextmem())) ) {
      if (mem->fAddr == addr) return mem;
   }
   return 0;
}


//______________________________________________________________________________
TAMOutput::TAMModInspector::TAMModMember* 
   TAMOutput::TAMModInspector::FindModMemberWithMemberName(const Char_t* mn) 
{
   // Find the mod member that has the specified member name.

   TIter nextmem(fOutputMembers.MakeIterator());
   TString memname(mn);
   TAMModMember* mem=0;
   while ( (mem = dynamic_cast<TAMModMember*>(nextmem())) ) {
      if (memname.CompareTo(mem->GetTitle())==0) return mem;
   }
   return 0;
}


//______________________________________________________________________________
void TAMOutput::TAMModInspector::SetMemberAddrFor(TObject* obj, 
                                                  const UInt_t verbose) 
{
   // Find the specified module's member for the specified object
   // and make the member point to the specified object.
   // If the member is not a pointer, does nothing.

   if (obj!=0) {
      TAMModMember* mem = dynamic_cast<TAMModMember*>(
         fOutputMembers.FindObject(obj->GetName()));
      if (mem!=0) {
         // it's silly, but mem->fMClass comes from IsA(), which does
         // not "load" the class, so the data member list is empty.
         TClass* cl = TClass::GetClass(mem->fMClass->GetName());
         if (cl!=0) {
            // test if the module's member is actually a pointer to a class
            // (as opposed to an array of pointers,
            // an instance of the class, etc.)
            TDataMember* dm = cl->GetDataMember(mem->GetTitle());
            if (dm!=0) {
               TString memberString(dm->GetTypeName());
               memberString += "*";
               if (memberString.CompareTo(dm->GetFullTypeName())==0) {
                  void*& modobj = *(static_cast<void**>(mem->fAddr));
                  if (modobj!=obj) {
                     if (modobj!=0) {
                        ::Warning("TAMOutput::TAMModInspector::"
                                  "SetMemberAddrFor",
                                  "Module pointer [%s] is pointing to "
                                  "non-zero address "
                                  "%p. Setting it to point to "
                                  "output object [%s] at %p. "
                                  "Possible memory leak/stomp.",
                                  mem->GetTitle(), 
                                  static_cast<void*>(modobj), 
                                  obj->GetName(), 
                                  static_cast<void*>(obj));
                     }
                     modobj = obj;
                  } // else it's already pointing to the right place
               } else {
                  // not a pointer to a class
                  if (verbose>9) {
                     ::Warning("TAMOutput::TAMModInspector::"
                               "SetMemberAddrFor",
                               "Module member [%s] is of type "
                               "[%s], not a pointer "
                               "to a class (inheriting from TObject). "
                               "Could not "
                               "automatically make this member "
                               "point to [%s] "
                               "from the output list.\n"
                               "Set verbosity below 10 to "
                               "remove this message.",
                               mem->GetTitle(), dm->GetFullTypeName(),
                               obj->GetName());
                  }
               }
            } else {
               ::Error("TAMOutput::TAMModInspector::SetMemberAddrFor",
                       "Could not get data member (%p) [%s] of module [%s]. "
                       "Could not set member address for object [%s].",
                       static_cast<void*>(dm), 
                       mem->GetTitle(), mem->fMClass->GetName(),
                       obj->GetName());
            }
         } else {
            ::Error("TAMOutput::TAMModInspector::SetMemberAddrFor",
                    "No class info for the module. "
                    "Can not set member address for [%s].",
                    obj->GetName());
         }
      } // else output object is not (pointed to by) a member of the module
   } else {
      ::Error("TAMOutput::TAMModInspector::SetMemberAddrFor",
              "Can not set member address for null object.");
   }
}


//______________________________________________________________________________
void TAMOutput::TAMModInspector::Streamer(TBuffer &R__b) 
{
   // Stream an object of class TAMOutput::TAMModInspector.

   //This works around a msvc bug and should be harmless on other platforms
   typedef TAMOutput::TAMModInspector thisClass;
   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      fOutputMembers.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, thisClass::IsA());
   } else {
      R__c = R__b.WriteVersion(thisClass::IsA(), kTRUE);
      fOutputMembers.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}


//______________________________________________________________________________
TAMOutput::TAMOutput() :
   fMod(0) 
{
   // Default constructor.

   SetOwner(kTRUE);
   fOutput.SetOwner(kFALSE);
}


//______________________________________________________________________________
TAMOutput::TAMOutput(TAModule* mod) :
   fMod(mod) 
{
   // Normal constructor.

   SetOwner(kTRUE);
   fOutput.SetOwner(kFALSE);
   fCurOutput.SetOwner(kFALSE);
   if (mod!=0) SetName(mod->GetName());
}


//______________________________________________________________________________
TAMOutput::~TAMOutput() 
{
   // Destructor.
}


//______________________________________________________________________________
void TAMOutput::Browse(TBrowser* b) 
{
   // Browse the output of this module
   
   fOutput.Browse(b);
   TList::Browse(b);
}


//______________________________________________________________________________
void TAMOutput::CallMerge(TObject* obj, TList& list) 
{
   // Uses the obj's TClass::GetMerge function to call the merge,
   // if available. If not, simply add all the objects in list to
   // the output list of this module.
   // To be called only by MergeOutput(TCollection*)

   R__ASSERT(obj);
   
   TClass* cls = obj->IsA();
   R__ASSERT(cls != 0);
   // ROOT::MergeFunc_t is a typedef in Rtypes.h
   // typedef Long64_t (*MergeFunc_t)(void*, TCollection*, TFileMergeInfo*);
   ROOT::MergeFunc_t mf = cls->GetMerge();
   if (mf != 0) {
     mf(obj, &list, 0);
   } else {
      // No Merge interface, return individual objects
      TObject* obj=0;
      while ( (obj = list.First()) ) {
         fCurOutput.Add(obj);
         list.Remove(obj);
      }
   }
}


//______________________________________________________________________________
void TAMOutput::CheckHistDir(TObject* obj) 
{
   // If obj is a histogram, set directory to null.
   
   if (obj->InheritsFrom(TH1::Class())) {
      TH1* hist = dynamic_cast<TH1*>(obj);
      if (hist!=0) hist->SetDirectory(0);
   }
}


//______________________________________________________________________________
void TAMOutput::DeleteIterators(vector<TIterator*>& iters) {
   // Deletes each iterator in the vector.
   
   vector<TIterator*>::const_iterator send  = iters.end();
   for (vector<TIterator*>::iterator  siter = iters.begin();
        siter!=send; siter++) {
      delete (*siter);
   }
}


//______________________________________________________________________________
TAMOutput* TAMOutput::FindModOutput(const TAModule* mod) 
{
   // Finds the TAMOutput object associated with the specified TAModule
   // (either being this one, or one of its sub modules).
   // Returns 0 if no such TAMOutput object is found.
   
   if (fMod==mod) {
      return this;
   } else {
      TIter nextModOutput(MakeIterator());
      TAMOutput* out=0, * tout=0;
      while ( (out = dynamic_cast<TAMOutput*>(nextModOutput())) ) {
         tout = out->FindModOutput(mod);
         if (tout!=0) return tout;
      }
   }
   return 0;
}


//______________________________________________________________________________
TAMOutput* TAMOutput::FindModOutput(const Char_t* name) 
{
   // Finds the (first) TAMOutput object with the specified name
   // (either being this one, or one of its sub modules)
   // Returns 0 if no such TAMOutput object is found.
   TString nm(name);
   if (nm.CompareTo(GetName())==0) {
      return this;
   } else {
      TIter nextModOutput(MakeIterator());
      TAMOutput* out=0, * tout=0;
      while ( (out = dynamic_cast<TAMOutput*>(nextModOutput())) ) {
         tout = out->FindModOutput(name);
         if (tout!=0) return tout;
      }
   }
   return 0;
}


//______________________________________________________________________________
TObject* TAMOutput::FindOutput(const Char_t* obj) 
{
   // Finds the object with the specified name in the list of output objects
   // of this module.
   // First check the saved output, then check the output for this current
   // processing.
   
   TObject* fobj = fOutput.FindObject(obj);
   if (fobj==0) {
      fobj = fCurOutput.FindObject(obj);
   }
   return fobj;
}


//______________________________________________________________________________
TObject* TAMOutput::FindOutput(const TObject* obj) 
{
   // Finds the specified object in the list of output objects of this module.
   // First check the saved output, then check the output for this current
   // processing.
   
   TObject* fobj = fOutput.FindObject(obj);
   if (fobj==0) {
      fobj = fCurOutput.FindObject(obj);
   }
   return fobj;
   
}


//______________________________________________________________________________
TObject* TAMOutput::FindOutput(const Char_t* module, const Char_t* obj) {
   // Finds the specified object from the output of the specified module
   // Note: "module" must be either this module, or a submodule of this module
   // First check the saved output, then check the output for this current
   // processing.
   
   TAMOutput* outmod = FindModOutput(module);
   if (outmod!=0) {
      TObject* outp = outmod->FindOutput(obj);
      if (outp==0) {
         Warning("FindOutput",
                 "Could not find output named [%s] in module [%s].",
                 obj, outmod->GetName());
      }
      return outp;
   } else {
      Warning("FindOutput","Could not find (sub)module with name [%s].",
              module);
   }
   return 0;
}


//______________________________________________________________________________
void TAMOutput::ls(Option_t* option) const 
{
   // List the output objects inside this module and its submodules.
   
   TROOT::IndentLevel();
   std::cout << "Output of " << GetName() << ":" << std::endl;

   fOutput.ls(option);

   TROOT::IncreaseDirLevel();
   TList::ls(option);
   TROOT::DecreaseDirLevel();
}


//______________________________________________________________________________
Long64_t TAMOutput::Merge(TCollection* list) 
{
   // Called by Proof after SlaveTerminate() and before Terminate()
   // to merge the output objects from each worker ("slave") computer.
   // First merge the actual output objects from this module, then
   // recursively proceed through the sub modules to merge their objects.
   
   // merge this module's output objects
   Long64_t mergeCount = MergeOutput(list);

   // then merge its sub modules' objects:
   if (!IsEmpty()) { // (if we have any sub modules)
      TAMOutput* out=0, * tout=0;
      // for each slave, get an iterator over sub modules
      // can't use any TCollection since TIterators are not TObjects
      vector<TIterator*> slaveIters;
      TIter nextSlave(list);
      while ( (tout = dynamic_cast<TAMOutput*>(nextSlave())) ) {
         slaveIters.push_back(tout->MakeIterator());
      }

      // loop over sub modules
      TIter nextModOutput(MakeIterator());
      while ( (out = dynamic_cast<TAMOutput*>(nextModOutput())) ) {
         // make a list of sub modules from each slave
         TObjArray subList(list->GetSize());
         
         vector<TIterator*>::const_iterator send  = slaveIters.end();
         for (vector<TIterator*>::iterator  siter = slaveIters.begin();
              siter!=send; siter++) {
            // add the object corresponding to 'out' from each slave
            subList.Add((*siter)->Next());
         }
         // merge the list of sub modules
         out->Merge(&subList);
      }
      
      // cleanup
      DeleteIterators(slaveIters);
   }

   return mergeCount;
}


//______________________________________________________________________________
Long64_t TAMOutput::MergeOutput(TCollection* list) 
{
   // Merges the actual output objects in fCurOutput given a list of
   // all the TAMOutput objects from the worker computers that
   // correspond to this one.
   // To be called only by Merge(TCollection*)
   
   if (!(fCurOutput.IsEmpty())) { // (if there are any output objects)
      TAMOutput* tout=0;
      // for each slave, get an iterator over the fCurOutput list
      // can't use any TCollection since TIterators are not TObjects
      vector<TIterator*> slaveIters;
      TIter nextSlave(list);
      while ( (tout = dynamic_cast<TAMOutput*>(nextSlave())) ) {
         slaveIters.push_back(tout->GetCurOutputList()->MakeIterator());
      }

      // loop over fCurOutput
      TIter nextOutputObj(fCurOutput.MakeIterator());
      TObject* outObj=0;
      while ( (outObj = nextOutputObj()) ) {
         // make a list of 'outObj' from each slave
         TList objsToMerge;
         
         vector<TIterator*>::const_iterator send  = slaveIters.end();
         for (vector<TIterator*>::iterator  siter = slaveIters.begin();
              siter!=send; siter++) {
            // add the object corresponding to 'outObj' from each slave
            objsToMerge.AddLast((*siter)->Next());
         }
         // merge 'outObj'
         CallMerge(outObj, objsToMerge);
      }
      
      // cleanup
      DeleteIterators(slaveIters);
   }

   return list->GetEntries();
}


//______________________________________________________________________________
void TAMOutput::NullClassFor(void* adr, const Char_t* tid) const 
{
   // Print warning that the class for the pointer sent to AddOutput() is not
   // in the ROOT class dictionary.

   Error("AddOutput",
         "(%s): Could not get class info for object at %p with typeid %s.",
         GetName(), adr, tid);
}


//______________________________________________________________________________
void TAMOutput::NullObjInAddOutput() const 
{
   // Print warning that a null pointer was sent to AddOutput().
   Error("AddOutput",
         "(%s): Can not add null object to output.", GetName());
}

void TAMOutput::Print(Option_t *wildcard) const 
{
   // Print the output objects inside this module and its submodules.
   
   TROOT::IndentLevel();
   std::cout << "Output of " << GetName() << ":" << std::endl;

   fOutput.Print(wildcard);

   TROOT::IncreaseDirLevel();
   TList::Print(wildcard);
   TROOT::DecreaseDirLevel();
}

//______________________________________________________________________________
void TAMOutput::RemoveOutput(TObject* obj) 
{
   // Removes the object from the list of output objects of this module.

   fInspector.RemoveOutput(obj);
   fOutput.Remove(obj);
   fCurOutput.Remove(obj);
}


//______________________________________________________________________________
void TAMOutput::SetAllOutputMembers(const Bool_t setAddresses) {
   // Recursively set the module's output members.
   // If setAddresses is true, make them point to the output objects.

   SetOutputMembers(setAddresses);
   
   TIter nextout(MakeIterator());
   TAMOutput* out=0;
   while ( (out = dynamic_cast<TAMOutput*>(nextout())) ) {
      out->SetAllOutputMembers(setAddresses);
   }
}


//______________________________________________________________________________
void TAMOutput::SetOutputMembers(const Bool_t setAddresses) 
{
   // Det the module's output members.
   // If setAddresses is true, make them point to the output objects.
   
   R__ASSERT(fMod!=0);
   
   // first update the addresses of the members
   Char_t parent[kParentStrLen];
   memset(parent, 0, kParentStrLen * sizeof(Char_t));
   fMod->ShowMembers(fInspector);
   
   if (setAddresses) {
      // loop through output objects and set the corresponding members
      TIter nextout(fCurOutput.MakeIterator());
      TObject* obj=0;
      while ( (obj = nextout()) ) {
         fInspector.SetMemberAddrFor(obj, fMod->GetVerbosity());
      }
   }
}


//______________________________________________________________________________
void TAMOutput::StoreAllOutputObjs() 
{
   // Recursively set move output objects from fCutOutput to fOutput
   // to be called after Merge, but before Terminate.
   // To be called only by TAModule.
   
   StoreOutputObjs();
   
   TIter nextout(MakeIterator());
   TAMOutput* out=0;
   while ( (out = dynamic_cast<TAMOutput*>(nextout())) ) {
      out->StoreAllOutputObjs();
   }
}


//______________________________________________________________________________
void TAMOutput::StoreOutputObjs() 
{
   // Iterate over fCurOutput and move the objects to fOutput
   // to be called after Merge, but before Terminate.
   // To be called only by StoreAllOutputObjs.
   
   if (fCurOutput.IsEmpty()==kFALSE) { // (if there are any output objects)
      // loop over fCurOutput
      TIter nextOutputObj(fCurOutput.MakeIterator());
      TObject* outObj=0;
      while ( (outObj = nextOutputObj()) ) {
         fOutput.Add(outObj);
      }
      fCurOutput.Clear("nodelete");
   }
}


//______________________________________________________________________________
void TAMOutput::WarnNameDuplicate(const TObject* obj) const 
{
   // Print warning that the output list already contains an object with
   // the same name.

   Warning("AddOutput",
           "(%s): Output list already contains object with name [%s]. "
           "Adding object at %p with duplicate name.",
           GetName(),
           (obj!=0) ? obj->GetName() : "",
           static_cast<const void*>(obj));
}


#if ROOT_VERSION_CODE > ROOT_VERSION(4,0,8)
//______________________________________________________________________________
Int_t TAMOutput::Write(const char* name, Int_t option, Int_t bsize) 
{
   // For this (newer) root version, put the code in the const function.
   // Wow this is ugly.. but it's backward compatible!

   return (static_cast<const TAMOutput*>(this))->Write(name,option,bsize);
}

Int_t TAMOutput::Write(const char* name, Int_t option, Int_t bsize) const
#else
//______________________________________________________________________________
Int_t TAMOutput::Write(const char* name, Int_t option, Int_t bsize) const 
{
   // For older root, put the code in the non-const function (so TList::Write
   // can be called).
   // Wow this is ugly.. but it's backward compatible!

   return (const_cast<TAMOutput*>(this))->Write(name,option,bsize);
}

//______________________________________________________________________________
Int_t TAMOutput::Write(const char* name, Int_t option, Int_t bsize)
#endif
{
   // Write all output objects.
   // Default behavior is to go through this module and all sub modules and
   // write all the output objects, flattening the module hierarchy.
   // If the 'TObject::kSingleKey' option is specified, the TAMOutput
   // objects themselves will be written, thus preserving the module hierarchy.
   // If option==-99, the module hierarchy will be preserved, but TDirectories
   // will be used instead of TAMOutput objects.

   if (option == -99) {
      Int_t nbytes = 0;
      nbytes += WriteCol(&fOutput, name, 0, bsize);
      TIter nextMod(MakeIterator());
      TObject* obj = 0;
      while ( (obj = nextMod()) ) {
         TDirectory* newdir = 0;
         Int_t counter = 0;
         TString dirname(obj->GetName());
         while (gDirectory->GetListOfKeys()->FindObject(dirname)) {
            if (counter>0) {
               dirname=Form("%s_%d",obj->GetName(),counter);
            }
            ++counter;
         }
         newdir = gDirectory->mkdir(dirname);
         TDirectory::TContext context(newdir);	 
         nbytes += obj->Write(name, option, bsize);
      }
      return nbytes;
   } else if ( (option & TObject::kSingleKey) ) {
      // here, the TList write will work just fine since it will actually
      // call the streamer on the module output objects
      // (through TObject::Write)
      return TList::Write(name, option, bsize);
   } else {
      // flatten the module hierarchy and dump all output objects to the file
      Int_t nbytes = WriteCol(&fOutput, name, option, bsize);
      TIter nextMod(MakeIterator());
      TObject* obj=0;
      while ( (obj = nextMod()) ) {
         nbytes += obj->Write(name, option, bsize);
      }
      return nbytes;
   }
}


//______________________________________________________________________________
Int_t TAMOutput::WriteCol(const TCollection *col, const char* name, 
                          Int_t option, Int_t bsize) const
{
   // Write elements of collection. Check and solve name collisions.
  
   Int_t nbytes = 0;
   TObject *obj = 0;
   TIter next(col);
   while ((obj = next())) {
      TCollection *col2 = dynamic_cast<TCollection*>(obj);
      if (col2) {
         nbytes += WriteCol(col2, name, option, bsize);
         continue;
      }
      TString tmpname(obj->GetName());
      if (name)
        tmpname = name;
      TString oname(tmpname);
      Int_t counter = 0;
      if (GetMod()->GetUseName()) { //if true always append module name
        oname=Form("%s_%s",GetMod()->GetName(), tmpname.Data());
        counter = 1;
      }
      while (gDirectory->GetListOfKeys()->FindObject(oname)) {
         if (counter==0) {
            oname=Form("%s_%s",GetMod()->GetName(), tmpname.Data());
         } else {
            oname=Form("%s_%s_%d",GetMod()->GetName(), tmpname.Data(), counter);
         }
         ++counter;
      }
      if (counter>0) {
         Warning("Write", "Renamed output object from \"%s\" to \"%s\"",
                 tmpname.Data(), oname.Data());
      }

      TTree *treeobj = dynamic_cast<TTree*>(obj);
      if (treeobj && treeobj->GetDirectory()->GetFile())
	obj = treeobj->CloneTree();
      
      nbytes += obj->Write(oname, option, bsize);
   }
   return nbytes;
}
