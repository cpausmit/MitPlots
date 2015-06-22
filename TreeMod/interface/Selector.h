//--------------------------------------------------------------------------------------------------
// Our selector class for modular processing of a tree (or chain). In addition to the generic
// TAMSelector it determines the begin and end of a run and does the necessary bookkeeping. 
// Modules can ask the selector to provide the run information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_SELECTOR_H
#define MITANA_TREEMOD_SELECTOR_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TAM/interface/TAMSelector.h" 
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h" 
#include "MitAna/DataTree/interface/EventHeader.h" 
#include "MitAna/DataTree/interface/LAHeader.h" 
#include "MitAna/DataTree/interface/RunInfo.h" 
#include "MitAna/DataTree/interface/MCRunInfo.h" 

#include <typeindex>

namespace mithep {
  class OutputMod;

  class Selector : public TAMSelector {
  public:
    Selector();
    ~Selector();

    void                 AddToTrash(TObject *obj)         { fTrash.AddLast(obj);           }
    const char          *GetAllEvtTreeName()        const { return fAllEvtTreeName;        }
    const char          *GetAllEvtHdrBrn()          const { return fAllEvtHdrBrn;          }
    const THashTable    &GetBranchTable()           const { return fBranchTable;           }
    const char          *GetEvtHdrName()            const { return fEvtHdrName;            }
    const EventHeader   *GetEventHeader()           const { return fEventHeader;           }
    const char          *GetLATreeName()            const { return fLATreeName;            }
    const char          *GetLAHdrName()             const { return fLAHdrName;             }
    const char          *GetRunTreeName()           const { return fRunTreeName;           }
    const char          *GetRunInfoName()           const { return fRunInfoName;           }
    const char          *GetMCRunInfoName()         const { return fMCRunInfoName;         }
    const RunInfo       *GetRunInfo()               const { return fRunInfo;               }
    const MCRunInfo     *GetMCRunInfo()             const { return fMCRunInfo;             }
    template <class T>
    T const*             GetObject(char const* name, Bool_t warn);
    Bool_t               ValidRunInfo()             const;
    Bool_t               ValidMCRunInfo()           const { return fMCRunInfo != 0;        }
    Bool_t               ValidRunNum()              const { return fCurRunNum!=UInt_t(-1); }
    void                 SetAllEvtHdrBrn(const char *n)   { fAllEvtHdrBrn   = n; }
    void                 SetAllEvtTreeName(const char *n) { fAllEvtTreeName = n; }
    void                 SetDoRunInfo(Bool_t b)           { fDoRunInfo      = b; }
    void                 SetEvtHdrName(const char *n)     { fEvtHdrName     = n; }
    void                 SetLAHdrName(const char *n)      { fLAHdrName      = n; }
    void                 SetLATreeName(const char *n)     { fLATreeName     = n; }
    void                 SetRunInfoName(const char *n)    { fRunInfoName    = n; }
    void                 SetMCRunInfoName(const char *n)  { fMCRunInfoName  = n; }
    void                 SetRunTreeName(const char *n)    { fRunTreeName    = n; }

    class ObjInfo : public TObjString {
    // Helper class to associate an object name with its source type and class type.
    // BaseMod traditional interfaces (e.g. ReqEventObject) use only the source type.
    public:
      enum SrcType {
        kEvtObject,
        kPublic,
        kBranch,
        nSrcTypes
      };

      ObjInfo() :
        TObjString("")
      {}
      ObjInfo(char const* name, SrcType type = nSrcTypes) :
        TObjString(name),
        fSourceType(type)
      {}
      ~ObjInfo()
      {}
      SrcType SourceType() const { return fSourceType; }
      Bool_t IsEvtObject() const { return fSourceType == kEvtObject; }
      Bool_t IsPublic() const { return fSourceType == kPublic && fAddr != 0; }
      Bool_t IsBranch() const { return fSourceType == kBranch && fBranchInfo != 0; }
      TClass const* ObjType() const { return fObjType; }
      BranchAddr_t& Addr() { return fAddr; }
      TAMBranchInfo* BranchInfo() { return fBranchInfo; }

      void SetSourceType(SrcType type) { fSourceType = type; }
      void SetObjType(TClass* type) { fObjType = type; }
      void SetBranchInfo(TAMBranchInfo* info) { fBranchInfo = info; }
      
    protected:
      SrcType fSourceType = nSrcTypes;
      TClass const* fObjType = 0;
      BranchAddr_t fAddr = 0;
      TAMBranchInfo* fBranchInfo = 0;
    };

  protected:
    Bool_t               BeginRun() override;
    Bool_t               ConsistentRunNum() const;
    Bool_t               EndRun() override;
    Bool_t               Notify() override;
    Bool_t               Process(Long64_t entry) override;
    void                 SlaveBegin(TTree* tree) override;
    void                 UpdateRunInfo();
    void                 UpdateRunInfoTree();

    Bool_t               fDoRunInfo;      //=true then get RunInfo (def=1)
    TString              fEvtHdrName;     //name of event header branch
    TString              fRunTreeName;    //name of run info tree
    TString              fRunInfoName;    //name of run info branch
    TString              fMCRunInfoName;  //name of MC run info branch
    TString              fAllEvtHdrBrn;   //name of all-event header branch
    TString              fLATreeName;     //name of look-ahead tree
    TString              fLAHdrName;      //name of look-ahead event header branch
    TString              fAllEvtTreeName; //name of all-event tree
    TTree               *fRunTree;        //!run info tree in current file
    EventHeader         *fEventHeader;    //!event header for current event
    RunInfo             *fRunInfo;        //!run information for current run
    MCRunInfo           *fMCRunInfo;      //!MC run information for current run
    TTree               *fLATree;         //!look-ahead tree in current file
    LAHeader            *fLAHeader;       //!event header for next event
    UInt_t               fCurRunNum;      //!current run number
    TList                fOutputMods;     //!pointer(s) to output modules
    TObjArray            fTrash;          //!pointers to trashed objects
    THashTable           fObjInfoStore;   //!single-point pointer store for GetObject function

  private:
    void                 SearchOutputMods(const TAModule *mod);

    friend class OutputMod;

    ClassDef(Selector, 1) // Customized selector class
  };
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Selector::ConsistentRunNum() const
{
  return (ValidRunNum() && fCurRunNum==fEventHeader->RunNum());
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Selector::ValidRunInfo() const
{
  return (fRunInfo && fCurRunNum==fRunInfo->RunNum());
}

template<class T>
T const*
mithep::Selector::GetObject(char const* name, Bool_t warn)
{
  // Find object of the given name from the list of event objects,
  // public objects, and branches in this order.

  auto* info = static_cast<ObjInfo*>(fObjInfoStore.FindObject(name));

  if (info) {
    if (warn && !info->ObjType()->InheritsFrom(T::Class())) {
      Warning("GetObject", "Type mismatch (%s != %s) for requested object %s.", T::Class()->GetName(), info->ObjType()->GetName(), name);
      return 0;
    }

    if (info->IsEvtObject()) {
      auto* obj = dynamic_cast<T*>(FindObjThisEvt(name));

      if (warn && !obj)
        Warning("GetObject", "Object %s of type %s is registered as an event object but was not found in the current event.", name, T::Class()->GetName());
      return obj;
    }
    else if (info->IsPublic()) {
      return reinterpret_cast<T*>(info->Addr());
    }
    else if (info->IsBranch()) {
      LoadBranch(info->BranchInfo());
      return reinterpret_cast<T*>(info->Addr());
    }

    // Info is somehow broken. Delete and create a new one
    fObjInfoStore.Remove(info);
    delete info;
  }

  info = new ObjInfo(name);

  auto* obj = dynamic_cast<T*>(FindObjThisEvt(name));

  if (obj) {
    info->SetSourceType(ObjInfo::kEvtObject);
  }
  else {
    obj = dynamic_cast<T*>(FindPublicObj(name));
    if (obj) {
      info->SetSourceType(ObjInfo::kPublic);
      info->Addr() = reinterpret_cast<BranchAddr_t>(obj);
    }
    else {
      auto* branchInfo = static_cast<TAMBranchInfo*>(fBranchTable.FindObject(name));
      bool newBranchInfo = false;
      if (!branchInfo) {
        branchInfo = new TAMBranchInfo(name);
        newBranchInfo = true;
      }

      if (!branchInfo->GetLoader() && (!FindLoader(branchInfo) || !branchInfo->Notify(fTree))) {
        // warning already issued by FindLoader
        delete info;
        if (newBranchInfo)
          delete branchInfo;
        return 0;
      }

      info->SetSourceType(ObjInfo::kBranch);

      if (newBranchInfo)
        fBranchTable.Add(branchInfo);

      info->SetBranchInfo(branchInfo);
      branchInfo->AddPtr(reinterpret_cast<T*&>(info->Addr()));
      if (branchInfo->IsLoaded())
        info->Addr() = branchInfo->GetLoader()->GetAddress();
      else
        LoadBranch(branchInfo);

      obj = reinterpret_cast<T*>(info->Addr());
    }
  }

  info->SetObjType(obj->IsA());
  fObjInfoStore.Add(info);

  return obj;
}

#endif
