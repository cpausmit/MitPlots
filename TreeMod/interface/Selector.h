//--------------------------------------------------------------------------------------------------
// $Id: Selector.h,v 1.6 2008/09/28 02:37:30 loizides Exp $
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
#include "MitAna/DataTree/interface/EventHeader.h" 
#include "MitAna/DataTree/interface/LAHeader.h" 
#include "MitAna/DataTree/interface/RunInfo.h" 

namespace mithep {
  class Selector : public TAMSelector
  {
    public:
      Selector();
      ~Selector();
   
      const THashTable    &GetBranchTable()         const { return fBranchTable; }
      const EventHeader   *GetEventHeader()         const { return fEventHeader; }
      const RunInfo       *GetRunInfo()             const { return fRunInfo; }
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
      TString              fLATreeName;     //name of look-ahead tree
      TString              fLAHdrName;      //name of look-ahead event header branch
      TTree               *fRunTree;        //!run info tree in current file
      EventHeader         *fEventHeader;    //!event header for current event
      RunInfo             *fRunInfo;        //!run information for current run
      TTree               *fLATree;         //!look-ahead tree in current file
      LAHeader            *fLAHeader;       //!event header for next event
      UInt_t               fCurRunNum;      //!current run number

      ClassDef(Selector,1)
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
