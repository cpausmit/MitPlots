//
// $Id: TAModule.cxx,v 1.6 2009/07/16 15:06:56 loizides Exp $
//

#include "MitAna/TAM/interface/TAModule.h"


#ifndef ROOT_RVersion
#include <RVersion.h>
#endif
#ifndef ROOT_TError
#include "TError.h"
#endif
#ifndef ROOT_TIterator
#include "TIterator.h"
#endif
#ifndef ROOT_TROOT
#include "TROOT.h"
#endif
#ifndef ROOT_TRegexp
#include "TRegexp.h"
#endif
#ifndef ROOT_TAMOutput
#include "MitAna/TAM/interface/TAMOutput.h"
#endif


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                                                                      //
// TAModule                                                             //
//                                                                      //
// Abstract base class for processing trees. This class allows trees    //
// to be processed in a modular fashion. All iteraction with the tree   //
// itself is taken care of by TAMSelector.                              //
//                                                                      //
//                                                                      //
// Usage:                                                               //
//    - Make a class that (publically) derives from TAModule            //
//        - The class should have member variables (pointers) to the    //
//          objects that will be read in and used from the tree.        //
//          For example, if a module will need the event info branch    //
//          from the tree, it could have a member variable such as:     //
//             TEventInfo* fEvtInfo;                                    //
//          Note: Such pointers should be initialized to null.          //
//                DO NOT assign them to 'new' objects as this will      //
//                result in a memory leak. The TAMSelector will         //
//                automatically make these pointers point to valid      //
//                objects after the corresponding tree branch has been  //
//                read in for the current entry.                        //
//    - Override any of the following functions as needed:              //
//        - Begin()                                                     //
//           - In Proof, this function is called by the client.         //
//             For most applications, this function will not be needed. //
//        - SlaveBegin()                                                //
//           - In Proof, this function is called by each slave server.  //
//             Histograms should be created by a module here.           //
//             All branches that the module may need during Process     //
//             should be requested here using ReqBranch.                //
//             For the above example, one would call:                   //
//                ReqBranch("eventInfo",fEvtInfo);                      //
//        - Process()                                                   //
//           - The TAMSelector (fSelector) will call this function      //
//             on the TAModule hierarchy for every entry in the tree.   //
//             Here one should only load branches as needed to first    //
//             perform the event selection. If and only if an event     //
//             passes the selection, one should then load the branches  //
//             needed for analysis. This is why requested branches are  //
//             NOT automatically loaded.                                //
//             Continuing the example, to load the event info branch:   //
//                LoadBranch("eventInfo");                              //
//                cout << "Event Num=" << fEvtInfo->fEventNum << endl;  //
//             The module can then perform analysis and/or fill         //
//             histograms.                                              //
//        - SlaveTerminate()                                            //
//           - In Proof, this function is called by each slave server   //
//             after the Process loop.                                  //
//        - Terminate()                                                 //
//           - In Proof, this function is called by the client at the   //
//             end of the analysis.                                     //
//             Here, a module can save results to a file or present     //
//             them graphically.                                        //
//                                                                      //
// A module may be active or inactive (controlled by TTask::SetActive). //
// When a module is not active, its sub modules are not executed.       //
//                                                                      //
// Author : Corey Reed            07/20/2004                            //
// Author : Constantin Loizides   07/12/2006                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAModule)


#if ROOT_VERSION_CODE <=ROOT_VERSION(5,11,3)
#define R__ASSERT(e) \
   if (!(e)) Fatal("", kAssertMsg, _QUOTE_(e), __LINE__, __FILE__)
#endif

const Char_t TAModule::kExecBegin          = 10;
const Char_t TAModule::kExecSlaveBegin     = 20;
const Char_t TAModule::kExecProcess        = 30;
const Char_t TAModule::kExecBeginRun       = 40;
const Char_t TAModule::kExecEndRun         = 50;
const Char_t TAModule::kExecSlaveTerminate = 60;
const Char_t TAModule::kExecTerminate      = 70;


//______________________________________________________________________________
TAModule::TAModule() :
   fSelector(0),
   fOutput(0),
   fDefActv(IsActive()), // in principal, no need to initialze fDefActv   
   fVerbose(0),
   fStopped(kFALSE),
   fUseName(kFALSE)
{
   // Default constructor.
}


//______________________________________________________________________________
TAModule::TAModule(const Char_t* name, const Char_t* title) :
   TTask(name, title),
   fSelector(0),
   fOutput(0),
   fDefActv(IsActive()), // in principal, no need to initialze fDefActv   
   fVerbose(0),
   fStopped(kFALSE),
   fUseName(kFALSE)
{
   // Normal constructor:
   // Use SetSelector on the top-most module to recursively set
   // the selector for all mods.
}


//______________________________________________________________________________
TAModule::~TAModule() 
{
   // Destructor.
}


//______________________________________________________________________________
void TAModule::AbortAnalysis() 
{
   // Abort the analysis

   SetDefActive(kFALSE);
   fSelector->AbortAnalysis();
}


//______________________________________________________________________________
void TAModule::AbortEvent() 
{
   // Abort this event

   fSelector->AbortEvent();
}


//______________________________________________________________________________
void TAModule::AbortModule() 
{
   // Abort the module and all sub-modules until the next call in TAMSelector.

   fSelector->AbortModule(this);   
}


//______________________________________________________________________________
Bool_t TAModule::AddObjThisEvt(TObject* obj) 
{
   // Add this object to the list of objects stored for this event.
   // See further description below.

   if(obj)
      return AddObjThisEvt(obj,obj->GetName());
   else {
      Error("AddObjThisEvt",
            "Can not add null object to event.");
      return kFALSE;
   }
}


//______________________________________________________________________________
Bool_t TAModule::AddObjThisEvt(TObject* obj, const char *name) 
{
   // Add this object to the list of objects stored for this event.
   // NOTE:
   //    - The object must have a unique name.
   //    - The object must be on the heap.
   //    - The object will be owned by the selector and deleted at the
   //      end of the processing of the current event.
   //
   // Returns true iff the object meets the requirements and is added to
   // the list successfully.

   if (fSelector!=0) {
      return fSelector->AddObjThisEvt(obj,name);
   } else {
      Error("AddObjThisEvt",
            "No selector exists, so there is no list of objects for "
            "this event. Object named [%s] not added to this event.",
            name);
   }
   return 0;
}


//______________________________________________________________________________
void TAModule::Browse(TBrowser* b) 
{
   // Browse this module's (and its sub modules) output if there is any
   // otherwise just browse the tree of modules.

   if (fOutput!=0) fOutput->Browse(b);
   else TTask::Browse(b);
}


//______________________________________________________________________________
Bool_t TAModule::CheckSelectors(const TAMSelector* sel, 
                                const Bool_t warn/*=kTRUE*/) const 
{
   // Checks the tree of TAModules to be sure that each module has the
   // specified selector.
   
   Bool_t check = (fSelector->IsEqual(sel));
   if ( warn && (!check) ) {
      Warning("CheckSelectors",
              "Selector of module [%s] is different from specified selector.",
              GetName());
   }
   TAModule* obj=0;
   TIter nextobj(fTasks);
   while ( (obj = dynamic_cast<TAModule*>(nextobj())) ) {
      check &= obj->CheckSelectors(sel);
   }
   return check;
}


//______________________________________________________________________________
void TAModule::DeactivateAll() 
{
   // Recursively sets the active flag of this and all sub modules
   // to false. Store their former activity flag in fDefActv so that
   // they can be reset to that state by ResetAllActiveFlags().
   
   TTask::SetActive(kFALSE);
   
   TAModule* task=0;
   TIter nextobj(fTasks);
   while ( (task = dynamic_cast<TAModule*>(nextobj())) ) {
      task->DeactivateAll();
   }
}


//______________________________________________________________________________
void TAModule::Exec(Option_t* option) 
{
   // Executes the module corresponding to the given option.
   // To be called only by TAMSelector.
   // Checks the address of the private static variables
   // to ensure that the TTask execute functions can not be
   // called by derived classes.
   // This function must not be overridden!

   R__ASSERT(option);
   
   if (option == &kExecBegin) {
      Begin();
   } else if (option == &kExecSlaveBegin) {
      SlaveBegin();
   } else if (option == &kExecProcess) {
      Process();
   } else if (option == &kExecBeginRun) {
      BeginRun();
   } else if (option == &kExecEndRun) {
      EndRun();
   } else if (option == &kExecSlaveTerminate) {
      SlaveTerminate();
   } else if (option == &kExecTerminate) {
      Terminate();
   } else {
      SendError(kAbortAnalysis,
                "Exec",
                "Invalid option [%s] at %p. Function must only be called "
                "by TAMSelector.",
                option, static_cast<const void*>(option));
   };
}


//______________________________________________________________________________
TFile* TAModule::GetCurrentFile() const 
{
   // Returns the current file that the tree is in.
   
   return (fSelector) ? (fSelector->GetCurrentFile()) : 0;
}


//______________________________________________________________________________
TObject* TAModule::FindObjThisEvt(const Char_t* name) const 
{
   // Looks for the object with the specified name that was added to 
   // this event. If not found, returns 0.

   if (fSelector!=0) {
      return fSelector->FindObjThisEvt(name);
   } else {
      Error("FindObjThisEvt",
            "No selector exists, so there is no list of objects for "
            "this event. Could not find object named [%s].",
            name);
   }
   return 0;
}


//______________________________________________________________________________
TObject* TAModule::FindPublicObj(const Char_t* name) const 
{
   // Looks for the public object with the specified name. If not found,
   // returns 0. Note: TAModules are not public objects and will not be 
   // found by this function.

   if (fSelector!=0) {
      return fSelector->FindPublicObj(name);
   } else {
      Error("FindPublicObj",
            "No selector exists, so there is no list of public objects. "
            "Could not find object named [%s].",
            name);
   }
   return 0;
}


//______________________________________________________________________________
void TAModule::ls(Option_t *option) const
{
   // List the modules inside this module and its submodules if requested.
   // Note: The following is take from TTask::ls(option) but fixed to avoid 
   // usage of null string in TRegexp.

   TROOT::IndentLevel();
   std::cout <<GetName()<<"\t"<<GetTitle()<<std::endl;
   TString opta = option;
   TString opt  = opta.Strip(TString::kBoth);
   if (opt.IsNull()) return;

   TRegexp re(opt, kTRUE);
   TROOT::IncreaseDirLevel();
   TObject *obj;
   TIter nextobj(fTasks);
   while ((obj = static_cast<TObject*>(nextobj()))) {
      TString s = obj->GetName();
      if (s.Index(re) == kNPOS) continue;
      obj->ls(option);
   }
   TROOT::DecreaseDirLevel();
}


//______________________________________________________________________________
void TAModule::LoadBranch(const Char_t* bname) 
{
   // Loads the current entry for the specified branch.
   // This function should be called by specific TAModules (classes that
   // inherit from this one) to get the current entry from the tree for
   // the branch of the specified name.
   // The branch must have already been requested (see
   // ReqBranch).
   // The actual entry is gotten from the tree by TAMSelector
   // to ensure that the same branch is not loaded more than once
   // for a given event.
   
   if (fSelector!=0) {
      fSelector->LoadBranch(bname);
   } else {
      SendError(kAbortAnalysis,
                "LoadBranch",
                "fSelector is null in module [%s]",
                GetName());
   }
}


//______________________________________________________________________________
void TAModule::NewOutputList(TList* list) 
{
   // Make a hierarchy of TAMOutput objects corresponding to this
   // module and all its sub modules. This must only be called once! Analysis
   // will abort if this module already has an associated TAMOutput object.
   // The input list is assumed to be the fOutput member of the TAMSelector
   // and must never be null.
   
   R__ASSERT(list);
   if (fOutput!=0) {
      if (GetVerbosity()>0) {
         SendError(kWarning,
                   "NewOutputList",
                   "New output list requested in module [%s] but one has "
                   "already been made. This should only happen if the module "
                   "has been added to more than one TAMSelector. "
                   "Set verbosity to 0 to remove this message.", GetName());
      }
      
      if (fOutput->GetMod()!=this) {
         if ((GetVerbosity()>0) && (fOutput->GetMod()!=0)) {
            Warning("NewOutputList",
                    "Output of [%s] was associated with module at %p. "
                    "Resetting to this (%p).",
                    GetName(), (void*)fOutput->GetMod(), (void*)this);
         }
         fOutput->SetMod(this);
      }
      
      if (list->FindObject(fOutput)==0) {
         list->Add(fOutput);
      }
   } else {
      fOutput = new TAMOutput(this);
      fOutput->SetOwner();
      list->Add(fOutput);
   }

   TAModule* task=0;
   TIter nextobj(fTasks);
   while ( (task = dynamic_cast<TAModule*>(nextobj())) ) {
      task->NewOutputList(fOutput);
   }
}


//______________________________________________________________________________
Bool_t TAModule::NotifyAll() 
{
   // Recursively call Notify.
   
   Bool_t ret = Notify();
   TAModule* task=0;
   TIter nextobj(fTasks);
   while ( (task = dynamic_cast<TAModule*>(nextobj())) ) {
      ret &= task->NotifyAll();
   }
   return ret;
}


//______________________________________________________________________________
void TAModule::Print(Option_t *option/*=""*/) const 
{
   // Print the modules inside this module and its submodules.

   ls(option);
}


//______________________________________________________________________________
Bool_t TAModule::PublishObj(TObject* obj) 
{
   // Adds an object to a list of objects which is outside the module
   // hierarchy. This can be used to pass objects (for example, calibrations)
   // between modules. Objects in this list are available before Begin
   // until the end of SlaveTerminate. They are not guaranteed to be available
   // during or after Terminate.
   // Checks (by name) if the object is already in the list. If it is, returns
   // kFALSE and does not publish the object.
   // NOTE: These objects are NOT owned by the list! Whatever creates these
   // objects must take care to (1) remove the object from the list using
   // RetractObj()  and (2) delete the object.
   // Also NOTE: will not publish TAModule objects.

   if (fSelector!=0) {
      return fSelector->PublishObj(obj);
   } else {
      Error("PublishObj",
            "No selector exists, so there is no list of public objects. "
            "Object named [%s] not published.",
            (obj!=0) ? obj->GetName() : "NULL");
   }
   return kFALSE;
}


//______________________________________________________________________________
TObject* TAModule::RemoveObjThisEvt(const Char_t* name) 
{
   // Finds the  object with the specified name and removes it from
   // the list of objects added to this event.
   // Returns the object that was removed.

   if (fSelector!=0) {
      return fSelector->RemoveObjThisEvt(name);
   } else {
      Error("RemoveObjThisEvt",
            "No selector exists, so there is no list of objects for "
            "this event. Object named [%s] not removed from this event.",
            name);
   }
   return 0;
}


//______________________________________________________________________________
void TAModule::RemoveOutput(TObject* obj) 
{
   // Remove the object from the list of output objects of this module.
   
   R__ASSERT(fOutput);
   fOutput->RemoveOutput(obj);
}


//______________________________________________________________________________
void TAModule::ResetAllActiveFlags() 
{
   // Recursively reset the activity flag of this and all sub modules
   // to their fDefActv values.
   
   if(fStopped) // this module is permanently aborted
      return;

   SetActive(fDefActv);
   
   TAModule* task=0;
   TIter nextobj(fTasks);
   while ( (task = dynamic_cast<TAModule*>(nextobj())) ) {
      task->ResetAllActiveFlags();
   }
}


//______________________________________________________________________________
TObject* TAModule::RetractObj(const Char_t* name) {
   // Finds the public object with the specified name and removes it from
   // the list of public objects. Returns the object that was retracted.
   // Note: TAModules are not public objects and will not be removed by 
   // this function.
   
   if (fSelector!=0) {
      return fSelector->RetractObj(name);
   } else {
      Error("RetractObj",
            "No selector exists, so there is no list of public objects. "
            "Object named [%s] not retracted.",
            name);
   }
   return 0;
}


//______________________________________________________________________________
void TAModule::SendError(const EModResult errLevel,
                         const Char_t* location,
                         const Char_t* formattedMsg, ...) 
{
   // Sends an error using the TError facility.
   // If errLevel is kAbortAnalysis or greater, the error is sent
   // as type 'kBreak'.
   // If errLevel is kWarning, the error is sent as type 'kWarning'.
   // Otherwise it is sent as type 'kError'.
   
   va_list ap;
   va_start(ap,va_(formattedMsg));
   if (errLevel>=kAbortAnalysis) {
     DoError(::kBreak, location, va_(formattedMsg), ap);
      AbortAnalysis();
   } else if (errLevel>=kStopModule) {
     DoError(::kError, location, va_(formattedMsg), ap);
      StopModule();
   } else if (errLevel>=kAbortEvent) {
     DoError(::kError, location, va_(formattedMsg), ap);
      AbortEvent();
   } else if (errLevel>=kAbortModule) {
     DoError(::kError, location, va_(formattedMsg), ap);
      AbortModule();
   } else if (errLevel==kWarning) {
     DoError(::kWarning, location, va_(formattedMsg), ap);
   } else {
      Error("SendError",
            "Unhandled error level [%d] specified when trying to send the "
            "following error:",static_cast<Int_t>(errLevel));
      DoError(::kError, location, va_(formattedMsg), ap);
   }
   va_end(ap);
}


//______________________________________________________________________________
void TAModule::SetAllModOutput(TAMOutput* o) 
{
   // Recursively set the output objects for this module and its submodules
   // see SetModOutput().
   
   SetModOutput(o);
   
   if ( fTasks->IndexOf(fTasks->Last()) == o->IndexOf(o->Last()) ) {
      TAModule* task=0;
      TAMOutput* taskOutput=0;
      TIter nextobj(fTasks);
      TIter nextout(o);
      while ( (task = dynamic_cast<TAModule*>(nextobj())) &&
              (taskOutput = dynamic_cast<TAMOutput*>(nextout())) ) {
         task->SetAllModOutput(taskOutput);
      }
   } else {
      SendError(kAbortAnalysis,
                "SetAllModOutput",
                "Can not set output for submodules of [%s]. Module contains %d "
                "submodules, different from the Output which contains %d "
                "suboutputs.",
                GetName(),
                fTasks->IndexOf(fTasks->Last())+1,
                o->IndexOf(o->Last())+1);
   }
}


//______________________________________________________________________________
void TAModule::SetModOutput(TAMOutput* o) 
{
   // Check that the output object has the same name as this module
   // If so, set 'o' to be this module's output and set o's module to this.
   
   if (o!=0) {
      TString on(o->GetName());
      if (on.CompareTo(GetName())==0) {
         fOutput = o;
         o->SetMod(this);
      } else {
         SendError(kAbortAnalysis,
                   "SetModOutput",
                   "Output named [%s] different from module named [%s]."
                   "Can not set mod output to module.",
                   on.Data(), GetName());
      }
   } else {
      SendError(kAbortAnalysis,
                "SetModOutput",
                "Can not set mod output to null object.");
   }
}


//______________________________________________________________________________
void TAModule::SetSelector(TAMSelector* sel) 
{
   // Recursively set the selector for this module and all contained
   // modules to 'sel'.

   fSelector = sel;
   
   TAModule* obj=0;
   TIter nextobj(fTasks);
   while ( (obj = dynamic_cast<TAModule*>(nextobj())) ) {
      obj->SetSelector(sel);
   }
}


//______________________________________________________________________________
void TAModule::SkipEvent() 
{
   // Aborts the processing of the current event by this task (and prevents
   // its subtasks from processing the event) without sending an error
   // message.
   //
   // It is designed for use by event selection type modules.
   //
   // If an error message is desired, use SendError with an error level of
   // kSkipModule to both print the message and skip the event. There is no
   // need to call both SendError(kSkipModule,...) and SkipEvent().
   
   AbortModule();
}


//______________________________________________________________________________
void TAModule::StopModule() 
{
   // Stop the module for the rest of the analysis.

   fStopped = kTRUE;
   fSelector->AbortModule(this);   
}

//______________________________________________________________________________
const char *TAModule::Version() 
{ 
   // Return a TAM version string.

#ifndef TAM_RELEASE
#define TAM_RELEASE "Unknown"
#endif

   return TAM_RELEASE;
}
