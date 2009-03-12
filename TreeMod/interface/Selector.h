//--------------------------------------------------------------------------------------------------
// $Id: Selector.h,v 1.10 2008/12/10 14:20:27 loizides Exp $
//
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
#include "MitAna/DataTree/interface/Collections.h" 
#include "MitAna/DataTree/interface/EventHeader.h" 
#include "MitAna/DataTree/interface/LAHeader.h" 
#include "MitAna/DataTree/interface/RunInfo.h" 

namespace mithep {
  class OutputMod;

  class Selector : public TAMSelector
  {
    public:
      Selector();
      ~Selector();

      const char          *GetAllEvtTreeName()      const { return fAllEvtTreeName; }
      const char          *GetAllEvtHdrBrn()        const { return fAllEvtHdrBrn;   }
      const THashTable    &GetBranchTable()         const { return fBranchTable; }
      const char          *GetEvtHdrName()          const { return fEvtHdrName;     }
      const EventHeader   *GetEventHeader()         const { return fEventHeader; }
      const char          *GetLATreeName()          const { return fLATreeName;     }
      const char          *GetLAHdrName()           const { return fLAHdrName;      }
      const char          *GetRunTreeName()         const { return fRunTreeName;    }
      const char          *GetRunInfoName()         const { return fRunInfoName;    }
      const RunInfo       *GetRunInfo()             const { return fRunInfo;     }
      Bool_t               ValidRunInfo()           const;
      Bool_t               ValidRunNum()            const { return fCurRunNum!=UInt_t(-1); }

    protected:
      Bool_t               BeginRun();
      Bool_t               ConsistentRunNum()       const;
      Bool_t               EndRun();
      Bool_t               Notify();
      void                 SlaveBegin(TTree* tree);
      void                 UpdateRunInfo();
      void                 UpdateRunInfoTree();

      Bool_t               fDoRunInfo;      //=true then get RunInfo (def=1)
      TString              fEvtHdrName;     //name of event header branch
      TString              fRunTreeName;    //name of run info tree
      TString              fRunInfoName;    //name of run info branch
      TString              fAllEvtHdrBrn;   //name of all-event header branch
      TString              fLATreeName;     //name of look-ahead tree
      TString              fLAHdrName;      //name of look-ahead event header branch
      TString              fAllEvtTreeName; //name of all-event tree
      TTree               *fRunTree;        //!run info tree in current file
      EventHeader         *fEventHeader;    //!event header for current event
      RunInfo             *fRunInfo;        //!run information for current run
      TTree               *fLATree;         //!look-ahead tree in current file
      LAHeader            *fLAHeader;       //!event header for next event
      UInt_t               fCurRunNum;      //!current run number
      TList                fOutputMods;     //!pointer to output modules
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
