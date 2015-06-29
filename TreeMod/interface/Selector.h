//--------------------------------------------------------------------------------------------------
// Our selector class for modular processing of a tree (or chain). In addition to the generic
// TAMSelector it determines the begin and end of a run and does the necessary bookkeeping. 
// Modules can ask the selector to provide the run information.
//
// Authors: C.Loizides, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_SELECTOR_H
#define MITANA_TREEMOD_SELECTOR_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TAM/interface/TAMSelector.h" 
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h" 
#include "MitAna/DataCont/interface/BaseCollection.h"
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
    const char*          GetAllEvtTreeName()        const { return fAllEvtTreeName;        }
    const char*          GetAllEvtHdrBrn()          const { return fAllEvtHdrBrn;          }
    const THashTable&    GetBranchTable()           const { return fBranchTable;           }
    const char*          GetEvtHdrName()            const { return fEvtHdrName;            }
    const EventHeader*   GetEventHeader()           const { return fEventHeader;           }
    const char*          GetLATreeName()            const { return fLATreeName;            }
    const char*          GetLAHdrName()             const { return fLAHdrName;             }
    const char*          GetRunTreeName()           const { return fRunTreeName;           }
    const char*          GetRunInfoName()           const { return fRunInfoName;           }
    const char*          GetMCRunInfoName()         const { return fMCRunInfoName;         }
    const RunInfo*       GetRunInfo()               const { return fRunInfo;               }
    const MCRunInfo*     GetMCRunInfo()             const { return fMCRunInfo;             }
    template <class T>
    T*                   GetObject(char const* name, Bool_t warn);
    Bool_t               ValidRunInfo()             const;
    Bool_t               ValidMCRunInfo()           const { return fMCRunInfo != 0;        }
    Bool_t               ValidRunNum()              const { return fCurRunNum!=UInt_t(-1); }
    void                 SetAllEvtHdrBrn(const char* n)   { fAllEvtHdrBrn   = n; }
    void                 SetAllEvtTreeName(const char* n) { fAllEvtTreeName = n; }
    void                 SetDoRunInfo(Bool_t b)           { fDoRunInfo      = b; }
    void                 SetEvtHdrName(const char* n)     { fEvtHdrName     = n; }
    void                 SetLAHdrName(const char* n)      { fLAHdrName      = n; }
    void                 SetLATreeName(const char* n)     { fLATreeName     = n; }
    void                 SetRunInfoName(const char* n)    { fRunInfoName    = n; }
    void                 SetMCRunInfoName(const char* n)  { fMCRunInfoName  = n; }
    void                 SetRunTreeName(const char* n)    { fRunTreeName    = n; }

    class ObjInfo : public TNamed {
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
        TNamed("", "")
      {}
      ObjInfo(char const* name, SrcType type = nSrcTypes) :
        TNamed(name, ""),
        fSourceType(type)
      {}
      ~ObjInfo()
      {
        delete fCollection;
      }

      Bool_t IsEvtObject() const { return fSourceType == kEvtObject; }
      Bool_t IsPublic() const { return fSourceType == kPublic && fAddr != 0; }
      Bool_t IsBranch() const { return fSourceType == kBranch && fBranchInfo != 0; }

      SrcType fSourceType = nSrcTypes;
      TClass const* fObjType = 0;
      BranchAddr_t fAddr = 0;
      BaseCollection* fCollection = 0; //pointer array when a collection is requested
      Bool_t fCollectionCached = kFALSE;
      TAMBranchInfo* fBranchInfo = 0;
    };

    // Helper class implementing the GetObject function.
    // Needed to perform partial template specialization for the case of Collection<O>
    template<class T>
    class GetObjectHelper {
    public:
      static T* Get(mithep::Selector&, char const* name, Bool_t warn);
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
    TTree*               fRunTree;        //!run info tree in current file
    EventHeader*         fEventHeader;    //!event header for current event
    RunInfo*             fRunInfo;        //!run information for current run
    MCRunInfo*           fMCRunInfo;      //!MC run information for current run
    TTree*               fLATree;         //!look-ahead tree in current file
    LAHeader*            fLAHeader;       //!event header for next event
    UInt_t               fCurRunNum;      //!current run number
    TList                fOutputMods;     //!pointer(s) to output modules
    TObjArray            fTrash;          //!pointers to trashed objects
    THashTable           fObjInfoStore;   //!single-point pointer store for GetObject function

  private:
    void                 SearchOutputMods(const TAModule* mod);

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

#include "SelectorGetObject.h"

#endif
