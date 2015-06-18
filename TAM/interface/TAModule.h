#ifndef ROOT_TAModule
#define ROOT_TAModule

// keep this for compatibility 
#define TAM_TAModule

// typeid include
#include <typeinfo>

#ifndef ROOT_TTask
#include "TTask.h"
#endif
#ifndef ROOT_Varargs
#include "Varargs.h"
#endif
#ifndef ROOT_TAMSelector
#include "MitAna/TAM/interface/TAMSelector.h"
#endif
#ifndef ROOT_TAMOutput
#include "MitAna/TAM/interface/TAMOutput.h"
#endif

class TFile;
class TStopwatch;

class TAModule : public TTask {
public:
   enum EModResult {
      kWarning,      //a problem requiring no action, just printing of a warning
      kAbortModule,  //a problem requiring this mod (and its submods) to stop
      kAbortEvent,   //a problem requiring the processing of this event to stop
      kStopModule,   //a problem requiring this module (and its submodules) 
                     // to stop for the rest of the analysis
      kAbortAnalysis //a problem requiring the analysis to stop
   };

protected:
   TAMSelector        *fSelector; //!the selector processing the tree
   TAMOutput          *fOutput;   //the list of output objects for this mod
   Bool_t              fDefActv;  //!copy of fActive so that TAMSelector can 
                                  // temporarily change this mod's active-ness 
                                  // to abort the module or the event
   UInt_t              fVerbose;  //verbosity level
   Bool_t              fStopped;  //!indicate if module (and its submodules) are
                                  // aborted for the rest of the analysis
   Bool_t              fUseName;  //if true use this module's name when 
                                  // writing the output in the flattening mode

   static const Char_t kExecBegin;           //!key to mark Begin
   static const Char_t kExecSlaveBegin;      //!key to mark SlaveBegin
   static const Char_t kExecProcess;         //!key to mark Process
   static const Char_t kExecBeginRun;        //!key to mark BeginRun
   static const Char_t kExecEndRun;          //!key to mark EndRun
   static const Char_t kExecSlaveTerminate;  //!key to mark SlaveTerminate
   static const Char_t kExecTerminate;       //!key to mark Terminate
   
   void                AbortAnalysis();
   void                AbortModule();
   void                DeactivateAll();
   void                NewOutputList(TList* list); 
   Bool_t              NotifyAll();
   void                ResetAllActiveFlags();
   void                SetAllModOutput(TAMOutput* o);
   void                SetModOutput(TAMOutput* o);
   void                StopModule();

   // utility functions to be used by derived classes
   void                AbortEvent();
   virtual Bool_t      AddObjThisEvt(TObject* obj);
   virtual Bool_t      AddObjThisEvt(TObject* obj, const char *name);
   template <class OC>
   void                AddOutput(OC* const & obj);
   const TAMSelector  *GetSelector()         const { return fSelector; }
   TAMSelector        *GetSelector()               { return fSelector; }
   Bool_t              IsEventAborted()      const;
   Bool_t              IsAnalysisAborted()   const;
   void                ls(Option_t *option)  const;
   void                LoadBranch(const Char_t* bname);
   virtual TObject    *FindObjThisEvt(const Char_t* name) const;
   virtual Bool_t      Notify()                    { return kTRUE; }
   virtual TObject    *RemoveObjThisEvt(const Char_t* name);
   void                RemoveOutput(TObject* obj);
   template <typename T>
   void                ReqBranch(const Char_t* bname, T*& address);
   void                SendError(const EModResult errLevel,
                                 const Char_t* location,
                                 const Char_t* formattedMsg, ...);
   void                SkipEvent();

   // functions to be overloaded by specific TAModule
   virtual void        Begin()           {}
   virtual void        SlaveBegin()      {}
   virtual void        Process()         {}
   virtual void        BeginRun()        {}
   virtual void        EndRun()          {}
   virtual void        SlaveTerminate()  {}
   virtual void        Terminate()       {}

public:
   
   TAModule();
   TAModule(const Char_t* name, const Char_t* title);
   virtual ~TAModule();
   
   void                SetActive(Bool_t act = kTRUE) { SetDefActive(act); }
   virtual void        Browse(TBrowser* b);
   // intentionally have no GetSelector as modules should never directly
   // interact with the selector, the input list or the output list
   Bool_t              CheckSelectors(const TAMSelector* sel,
                                      const Bool_t warn=kTRUE) const;
   // TAMSelector is a friend to allow it to call Exec
   // using the private variables such as kExecProcess
   // and to prevent TAModules inheritting from this class
   // from making such explicit calls.
   friend class TAMSelector;
   void                Exec(Option_t* option);
   TObject            *FindPublicObj(const Char_t* name) const;
   TFile              *GetCurrentFile() const;
   const TAMOutput    *GetModOutput()   const { return fOutput;          }
   TAMOutput          *GetModOutput()         { return fOutput;          }
   TList*              GetSubModules()        { return GetListOfTasks(); }
   const TList        *GetSubModules()  const { return GetListOfTasks(); }
   Bool_t              GetUseName()     const { return fUseName;         }   
   UInt_t              GetVerbosity()   const { return fVerbose;         }
   virtual void        Print(Option_t *option="") const;
   Bool_t              PublishObj(TObject* obj);
   TObject            *RetractObj(const Char_t* name);
   void                SetDefActive(Bool_t active);
   void                SetSelector(TAMSelector* sel);
   void                SetUseName(Bool_t b)          { fUseName = b;     }
   void                SetVerbosity(UInt_t vb)       { fVerbose = vb;    }

   static const char  *Version();

   ClassDef(TAModule,4) // Base class for modular processing a tree
};


//______________________________________________________________________________
template <class OC>
inline void TAModule::AddOutput(OC* const & obj) 
{
   // Add the object to the list of output objects of this module.
   // The Proof facility can then merge this object from each worker
   // computer.
   // This version of the function will also store the address of the
   // pointer, and if the pointer is a member of the module, the member
   // will be made to point to the object in the output list on the
   // client computer before Terminate is called.

   if (fOutput!=0) {
      fOutput->AddOutput(obj);
   } else {
      SendError(kAbortAnalysis,
                "AddOutput",
                "fOutput is null in module [%s]",
                GetName());
   }
}


//______________________________________________________________________________
inline Bool_t TAModule::IsEventAborted() const 
{ 
   // Return kTRUE if event has been aborted.

   return (fSelector==0) ? kFALSE : fSelector->IsEventAborted(); 
}


//______________________________________________________________________________
inline Bool_t TAModule::IsAnalysisAborted() const 
{ 
   // Return kTRUE if analysis has been aborted.

   return (fSelector==0) ? kFALSE : fSelector->IsAnalysisAborted(); 
}

//______________________________________________________________________________
template <typename T>
inline void TAModule::ReqBranch(const Char_t* bname, T*& address) 
{
   // Requests that the branch with the specified name be made available
   // during processing and that it be read in to the address specified.
   // The TAMSelector will automatically change the value of the pointer 
   // pointed to ('*address') to the address of the branch entry when it
   // is read in via LoadBranch.

   if (fSelector!=0) {
      fSelector->ReqBranch(bname, address);
   } else {
      SendError(kAbortAnalysis,
                "ReqBranch",
                "fSelector is null in module [%s]",
                GetName());
   }
}


//______________________________________________________________________________
inline void TAModule::SetDefActive(Bool_t active) 
{
   // Set the activity and make it the default behavior.

   fDefActv = active; 
   TTask::SetActive(active);   
}

#endif //ROOT_TAModule
