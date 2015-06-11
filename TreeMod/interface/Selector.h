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
#include "MitAna/DataTree/interface/EventHeader.h" 
#include "MitAna/DataTree/interface/LAHeader.h" 
#include "MitAna/DataTree/interface/RunInfo.h" 
#include "MitAna/DataTree/interface/MCRunInfo.h" 

namespace mithep {
  class OutputMod;

  class Selector : public TAMSelector
  {
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

    protected:
      Bool_t               BeginRun();
      Bool_t               ConsistentRunNum()         const;
      Bool_t               EndRun();
      Bool_t               Notify();
      Bool_t               Process(Long64_t entry);
      void                 SlaveBegin(TTree* tree);
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

#endif
