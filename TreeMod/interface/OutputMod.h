//--------------------------------------------------------------------------------------------------
// $Id: OutputMod.h,v 1.11 2009/07/17 19:18:34 loizides Exp $
//
// OutputMod
//
// This TAM module writes selected events and selected branches to a new output file. 
//
// Authors: C.Paus, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_OUTPUTMOD_H
#define MITANA_TREEMOD_OUTPUTMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/EventHeaderFwd.h"
#include <map>
#include <string>
#include <vector>
#include <TString.h>
#include <TRegexp.h>

namespace mithep
{
  class TreeWriter;
  class EventHeader;
  class RunInfo;
  class LAHeader;
  class HLTFwkMod;
  class BranchTable;

  class OutputMod : public BaseMod
  {
    public:
      OutputMod(const char *name  = "OutputMod", const char *title = "Output module");

      void                        AddNewBranch(const char *bname);
      void                        Drop(const char *bname);
      void                        Keep(const char *bname);
      void                        SetCheckBrDep(Bool_t b)       { fCheckBrDep = b; }
      void                        SetDefBranchSize(UInt_t s)    { fBranchSize = s; }
      void                        SetDefCompression(UInt_t l)   { fCompLevel  = l; }
      void                        SetDefSplitLevel(UInt_t l)    { fSplitLevel = l; }
      void                        SetFileName(const char *n)    { fPrefix     = n; }
      void                        SetMaxFileSize(UInt_t m)      { fMaxSize    = m; }
      void                        SetPathName(const char *n)    { fPathName   = n; }
      void                        SetTreeName(const char *n)    { fTreeName   = n; }
      void                        SetUseBrDep(Bool_t b)         { fUseBrDep   = b; }

    protected:
      void                        BeginRun();
      void                        EndRun();
      Bool_t                      Notify();
      void                        Process();
      void                        ProcessAll();
      void                        SlaveBegin();
      void                        SlaveTerminate();

      TString                     fTreeName;       //tree name
      TString                     fPrefix;         //file prefix for filename
      TString                     fPathName;       //path name to be used
      UInt_t                      fMaxSize;        //maximum file size [MB]
      UInt_t                      fCompLevel;      //compression levels
      UInt_t                      fSplitLevel;     //default split levels
      UInt_t                      fBranchSize;     //default branch sizes [Byte]
      Bool_t                      fDoReset;        //=true then reset pointers
      Bool_t                      fCheckBrDep;     //=true then check branch dependencies
      Bool_t                      fUseBrDep;       //=true then resolve branch dependencies
      Bool_t                      fCheckTamBr;     //=true then check TAM loaded branches
      Bool_t                      fKeepTamBr;      //=true then keep TAM loaded branches
      std::vector<std::string>    fCmdList;        //list of keep/drop statements
      std::vector<std::string>    fAddList;        //list of additional branches

    private:
      void                        CheckAndAddBranch(const char *bname, const char *cname);
      Bool_t                      CheckAndResolveBranchDep();
      void                        CheckAndResolveTAMDep(Bool_t solve=kFALSE);
      Bool_t                      IsAcceptedBranch(const char *bname);
      void                        FillAllEventHeader(Bool_t isremoved);
      void                        FillHltInfo();
      UInt_t                      GetNBranches() const          { return fBrNameList.size(); }
      void                        LoadBranches();
      void                        RequestBranches();
      void                        SetupBranches();

      TreeWriter                 *fTreeWriter;      //!tree writer holding trees + writing the files
      EventHeader                *fEventHeader;     //!my event header (written)
      EventHeader                *fAllEventHeader;  //!my all event header (written)
      RunInfo                    *fRunInfo;         //!my run info
      LAHeader                   *fLaHeader;        //!my look ahead header
      BranchTable                *fBranchTable;     //!my branch table
      std::vector<TRegexp>        fCmdReList;       //!branch list from fCmdList
      std::vector<Bool_t>         fCmdDeList;       //!keep/drop list from fCmdList
      std::vector<std::string>    fBrNameList;      //!branch list to be kept
      std::vector<std::string>    fBrClassList;     //!corresponding class list
      TObject**                   fBranches;        //!branches to be written
      const UInt_t                fNBranchesMax;    //!max number of supported top-level branches
      TTree                      *fRunTree;         //!runinfo tree
      TTree                      *fLATree;          //!look-ahead tree
      TTree                      *fAllTree;         //!all-event-header tree
      const EventHeaderCol       *fSkimmedIn;       //!skimmed event headers (input)
      TTree                      *fHltTree;         //!HLT trigger tree (not owned)
      std::vector<std::string>   *fHLTTab;          //!HLT trigger names
      std::vector<std::string>   *fHLTLab;          //!HLT module labels
      Int_t                       fRunEntries;      //!number of run info entries
      std::map<UInt_t,Int_t>      fRunmap;          //!map between run number and entry number
      Int_t                       fHltEntries;      //!number of hlt info entries
      Short_t                     fFileNum;         //!file number of current file
      Long64_t                    fLastWrittenEvt;  //!entry of last written event
      Long64_t                    fLastSeenEvt;     //!entry of last seen event
      Long64_t                    fCounter;         //!count number of events

      friend class Selector;

    ClassDef(OutputMod, 1) // Output module
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::OutputMod::AddNewBranch(const char *bname)
{ 
  // Add new branch with given name. The content is taken 
  // from the public object list.

  fAddList.push_back(std::string(bname)); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::OutputMod::Drop(const char *bname)
{ 
  // Add branch name to be dropped (can be regular expression)

  fCmdList.push_back(std::string(Form("drop %s", bname))); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::OutputMod::Keep(const char *bname)
{ 
  // Add branch name to be kept (can be regular expression)

  fCmdList.push_back(std::string(Form("keep %s", bname))); 
}
#endif
