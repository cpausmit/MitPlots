//--------------------------------------------------------------------------------------------------
// $Id: OutputMod.h,v 1.1 2008/12/01 17:42:22 loizides Exp $
//
// OutputMod
//
// This TAM module will write all events to a new output file. This means the full content of the
// various trees.
//
// Authors: C.Paus, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_OUTPUTMOD_H
#define MITANA_TREEMOD_OUTPUTMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/Collections.h"
#include <TString.h>
#include <TRegexp.h>

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

    protected:
      void                     BeginRun();
      void                     EndRun();
      void                     Process();
      Bool_t                   Notify();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fTreeName;       //tree name
      TString                  fPrefix;         //
      TString                  fPathName;       //
      UInt_t                   fMaxSize;        //
      UInt_t                   fCompLevel;      //
      UInt_t                   fSplitLevel;     //
      UInt_t                   fBranchSize;     //
      Bool_t                   fDoReset;        //=true then reset pointers
      Bool_t                   fCheckTamBr;     //=true then check TAM loaded branches
      Bool_t                   fKeepTamBr;      //=true then keep TAM loaded branches
      StringVec                fCmdList;        //list of keep/drop statements
      TString                  fHltFwkModName;  //

    private:
      void                     CheckAndAddBranch(const char *bname, const char *cname);
      void                     CheckAndResolveDep(Bool_t solve=kFALSE);
      Bool_t                   IsAcceptedBranch(const char *bname);
      UInt_t                   GetNBranches() const           { return fBrNameList.Entries(); }
      void                     LoadBranches();
      void                     RequestBranch(const char *bname);
      void                     SetupBranches();

      TreeWriter              *fTreeWriter;     //!
      EventHeader             *fMyEventHeader;  //!
      RunInfo                 *fMyRunInfo;      //!
      LAHeader                *fMyLaHeader;     //!
      std::vector<TRegexp>     fCmdReList;      //!
      std::vector<Bool_t>      fCmdDeList;      //!
      StringVec                fBrNameList;     //!
      StringVec                fBrClassList;    //!
      TObject**                fBranches;       //!
      const UInt_t             fNBranchesMax;   //!
      HLTFwkMod               *fHltFwkMod;      //!

    ClassDef(OutputMod,1) // Output module
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
