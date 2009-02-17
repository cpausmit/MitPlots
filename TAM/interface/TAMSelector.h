//
// $Id: TAMSelector.h,v 1.8 2008/12/04 13:50:56 loizides Exp $
//

#ifndef ROOT_TAMSelector
#define ROOT_TAMSelector

// keep this for compatibility 
#define TAM_TAMSelector


#ifndef ROOT_TSelector
#include "TSelector.h"
#endif
#ifndef ROOT_THashTable
#include "THashTable.h"
#endif
#ifndef ROOT_List
#include "TList.h"
#endif
#ifndef ROOT_TAMBranchInfo
#include "TAMBranchInfo.h"
#endif   
#ifndef ROOT_TAMVirtualLoader
#include "TAMVirtualLoader.h"
#endif   
#ifndef ROOT_Riostream
#include <Riostream.h>
#endif


class TBranch;
class TTree;
class TFile;
class TAModule;
class TAMOutput;
class TBranchRef;

class TAMSelector : public TSelector {
protected:
   
   struct TAMEvtObj : TNamed {
      // Class for storing event objects:
      // It assumes ownership of the object.
      // It is needed to force the THashTable to call Hash on a TNamed
      // to allow lookup using the hash value given the object's name
      // (as opposed to its pointer value, as is done for TObject's).
      TObject* fObj; //the object
      TAMEvtObj(TObject* obj) : TNamed(obj->GetName(),0), fObj(obj) {}
      TAMEvtObj(TObject* obj, const char *name) : TNamed(name,0), fObj(obj) {}
      virtual ~TAMEvtObj() { if (fObj!=0) delete fObj; }
   };

   class TAMAutoLoadProxy : public TObject {
      // Class that acts as a proxy between the TRefTable, TAM and TBranchRef.
      // If SetDoProxy(kTRUE) is called TRef branch auto-loading will be done via
      // TAM loaders.
   protected:
       TAMSelector *fSel;          //ptr to TAMSelector (we are a friend)
       TRefTable   *fOrig;         //ptr to original TRefTable filled by I/O (owner is TBranchRef)
       TRefTable   *fFake;         //ptr to our fake TRefTable of which we are owner
       Long64_t     fCurEntry;     //cache of current entry
       Bool_t       fBrRead[1024]; //flag which TBranchRef branch was read

   public:
       TAMAutoLoadProxy(TAMSelector *sel, Bool_t e=kFALSE);
       virtual ~TAMAutoLoadProxy();
       void   Disable();
       void   Enable();
       Bool_t Notify();
   };

   TTree            *fTree;            //!the tree or chain
   TAMAutoLoadProxy *fProxy;           //!the proxy for autoload branch loading
   THashTable        fBranchTable;     //!table of requested branches
   THashTable        fEventObjs;       //!table of objects available to any module while the current event is processed
   TAModule         *fAModules;        //!the top-most TAModule. nothing but a container for more modules
   Long64_t          fCurEvt;          //!the current event
   TList            *fOwnInput;        //!keep pointer to own input list in case it was created by us 
   Bool_t            fAnalysisAborted; //!true if the analysis should be aborted
   Bool_t            fModAborted;      //!true if one or more modules(s) have been aborted
   Bool_t            fEventAborted;    //!true if the current event should be aborted
   Bool_t            fActNotify;       //!true if notify is active (avoiding recursive calls of Notify())
   UInt_t            fObjCounter;      //!keep object counter for resetting it in the process loop
   UInt_t            fObjCounterRun;   //!keep object counter for resetting it in the process loop when end of run is reached
   UInt_t            fVerbosity;       //true if one wants to print debug info
   Bool_t            fDoProxy;         //true if TAMAutoLoadProxy should be enabled
   TList             fLoaders;         //list of data loaders

   void              AddNewOutputLists();
   void              CleanObjTable(TProcessID *pid, UInt_t lastKeptUID) const;
   void              ClearAllLoaders();
   void              CopyModsFromInput();
   Bool_t            FindLoader(TAMBranchInfo* brInfo);
   void              LoadBranch(TAMBranchInfo* brInfo);
   void              TakeModsFromInput();
   void              TakeLoadersFromInput();
   void              ZeroAllBranches();

   friend class TAMAutoLoadProxy;
   
public:
   TAMSelector();
   virtual ~TAMSelector();
   
   void              AbortAnalysis();
   void              AbortEvent();
   void              AbortModule(TAModule* mod);
   virtual void      AddInput(TAModule* mod);
   void              AddLoader(TAMVirtualLoader *loader) { fLoaders.AddLast(loader); }
   virtual Bool_t    AddObjThisEvt(TObject* obj);
   virtual Bool_t    AddObjThisEvt(TObject* obj, const char *name);
   void              Begin(TTree* tree);
   virtual Bool_t    BeginRun()                { return kFALSE; }
   virtual Bool_t    EndRun()                  { return kFALSE; }
   TAMOutput        *FindModOutput(const TAModule* mod);
   virtual TObject  *FindObjThisEvt(const Char_t* name) const;
   virtual TObject  *FindPublicObj(const Char_t* name)  const;
   Long64_t          GetCurEvt()         const { return fCurEvt; }
   const TFile      *GetCurrentFile()    const;
   TFile            *GetCurrentFile();
   const TAMOutput  *GetModOutput()      const;
   TAMOutput        *GetModOutput();
   const TAModule   *GetTopModule()      const { return fAModules; }
   const TTree      *GetTree()           const { return fTree; }
   TTree            *GetTree()                 { return fTree; }
   UInt_t            GetVerbosity()      const { return fVerbosity; }
   void              Init(TTree* tree);
   Bool_t            IsAModAborted()     const { return fModAborted; }
   Bool_t            IsEventAborted()    const { return fEventAborted; }
   Bool_t            IsAnalysisAborted() const { return fAnalysisAborted; }
   void              LoadBranch(const Char_t* bname);
   Bool_t            Notify();
   Bool_t            Process(Int_t entry) { return Process(static_cast<Long64_t>(entry)); }
   Bool_t            Process(Long64_t entry);
   virtual Bool_t    PublishObj(TObject* obj);
   template <typename T>
   void              ReqBranch(const Char_t* bname, T*& address);
   virtual TObject  *RemoveObjThisEvt(const Char_t* name);
   virtual TObject  *RetractObj(const Char_t* name);
   void              SetDoProxy(Bool_t b)      { fDoProxy = b; }
   void              SetVerbosity(UInt_t vb)   { fVerbosity = vb; }
   void              SlaveBegin(TTree* tree);
   void              SlaveTerminate();
   void              Terminate();
   Int_t             Version()           const { return 1; }
   
   ClassDef(TAMSelector,8)
};


//______________________________________________________________________________
template <typename T>
inline void TAMSelector::ReqBranch(const Char_t* bname, T*& address)
{
   // Tells the selector that a branch with the given name may be
   // used by an TAModule and that the the module will access the branch
   // using the pointer 'address'.

   TAMBranchInfo* brInfo = 
     dynamic_cast<TAMBranchInfo*>( fBranchTable.FindObject(bname) );

   if (brInfo==0) {
      brInfo = new TAMBranchInfo(bname);
      fBranchTable.Add(brInfo);
   }

   if (!brInfo->AddPtr(address)) 
     AbortAnalysis();
}


#endif //ROOT_TAMSelector
