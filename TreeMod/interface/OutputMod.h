//--------------------------------------------------------------------------------------------------
// $Id: OutputMod.h,v 1.4 2008/12/04 13:55:06 loizides Exp $
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
#include "MitAna/DataTree/interface/Collections.h"
#include <TString.h>
#include <TRegexp.h>
#include <map>

namespace mithep
{
  class TreeWriter;
  class EventHeader;
  class RunInfo;
  class LAHeader;
  class HLTFwkMod;

  class OutputMod : public BaseMod
  {
    public:
      OutputMod(const char *name  = "OutputMod", const char *title = "Output module");
      ~OutputMod() {}

      void                     Drop(const char *bname);
      void                     Keep(const char *bname);
      void                     CheckTamBranches(Bool_t b)    { fCheckTamBr = b; }
      void                     KeepTamBranches(Bool_t b)     { fKeepTamBr  = b; }
      void                     SetTreeName(const char *name) { fTreeName = name; }
      void                     SetFileName(const char *name) { fPrefix = name; }
      void                     SetPathName(const char *name) { fPathName = name; }
      void                     SetMaxFileSize(UInt_t m)      { fMaxSize = m; }
      void                     SetDefCompression(UInt_t l)   { fCompLevel = l; }
      void                     SetDefSplitLevel(UInt_t l)    { fSplitLevel = l; }
      void                     SetDefBranchSize(UInt_t s)    { fBranchSize = s; }

    protected:
      void                     BeginRun();
      void                     EndRun();
      Bool_t                   Notify();
      void                     Process();
      void                     ProcessAll();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fTreeName;       //tree name
      TString                  fPrefix;         //file prefix for filename
      TString                  fPathName;       //path name to be used
      UInt_t                   fMaxSize;        //maximum file size [MB]
      UInt_t                   fCompLevel;      //compression levels
      UInt_t                   fSplitLevel;     //default split levels
      UInt_t                   fBranchSize;     //default branch sizes [Byte]
      Bool_t                   fDoReset;        //=true then reset pointers
      Bool_t                   fCheckTamBr;     //=true then check TAM loaded branches
      Bool_t                   fKeepTamBr;      //=true then keep TAM loaded branches
      StringVec                fCmdList;        //list of keep/drop statements

    private:
      void                     CheckAndAddBranch(const char *bname, const char *cname);
      void                     CheckAndResolveDep(Bool_t solve=kFALSE);
      Bool_t                   IsAcceptedBranch(const char *bname);
      void                     FillAllEventHeader(Bool_t isremoved);
      void                     FillL1Info();
      void                     FillHltInfo();
      UInt_t                   GetNBranches() const          { return fBrNameList.Entries(); }
      void                     LoadBranches();
      void                     RequestBranch(const char *bname);
      void                     SetupBranches();

      TreeWriter              *fTreeWriter;      //!tree writer holding trees and writing the files
      EventHeader             *fEventHeader;     //!my event header (written)
      EventHeader             *fAllEventHeader;  //!my all event header (written)
      RunInfo                 *fRunInfo;         //!my run info
      LAHeader                *fLaHeader;        //!my look ahead header
      std::vector<TRegexp>     fCmdReList;       //!branch list from fCmdList
      std::vector<Bool_t>      fCmdDeList;       //!keep/drop list from fCmdList
      StringVec                fBrNameList;      //!branch list to be kept
      StringVec                fBrClassList;     //!corresponding class list
      TObject**                fBranches;        //!branches to be written
      const UInt_t             fNBranchesMax;    //!maximum number of supported top-level branches
      TTree                   *fRunTree;         //!runinfo tree
      TTree                   *fLATree;          //!look-ahead tree
      TTree                   *fAllTree;         //!all-event-header tree
      TTree                   *fAllTreeIn;       //!all-event-header tree (input)
      TTree                   *fL1Tree;          //!L1 trigger tree (not owned)
      TTree                   *fHltTree;         //!HLT trigger tree (not owned)
      Int_t                    fRunEntries;      //!number of run info entries
      std::map<UInt_t,Int_t>   fRunmap;          //!map between run number and entry number
      Int_t                    fOrigL1Entry;     //!entry for original tree when table was copied
      Int_t                    fL1Entries;       //!number of l1 info entries
      Int_t                    fOrigHltEntry;    //!entry for original tree when table was copied
      Int_t                    fHltEntries;      //!number of hlt info entries
      UShort_t                 fFileNum;         //!file number of current file
      Long64_t                 fLastWrittenEvt;  //!entry of last written event
      Long64_t                 fLastSeenEvt;     //!entry of last seen event
      Long64_t                 fCounter;         //!count number of events

      friend class Selector;

    ClassDef(OutputMod, 1) // Output module
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::OutputMod::Drop(const char *bname)
{ 
  // Add branch name to be dropped (can be regular expression)

  fCmdList.AddCopy(std::string(Form("drop %s", bname))); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::OutputMod::Keep(const char *bname)
{ 
  // Add branch name to be kept (can be regular expression)

  fCmdList.AddCopy(std::string(Form("keep %s", bname))); 
}
#endif
