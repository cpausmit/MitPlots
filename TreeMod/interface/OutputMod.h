//--------------------------------------------------------------------------------------------------
// $Id: $
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

  class OutputMod : public BaseMod
  {
    public:
      OutputMod(const char *name  = "OutputMod", const char *title = "Output module");
      ~OutputMod() {}

      void                     Drop(const char *bname);
      void                     Keep(const char *bname);
      void                     SetCheckDep(Bool_t b) { fCheckDep = b; }

    protected:
      void                     BeginRun();
      void                     EndRun();
      void                     Process();
      Bool_t                   Notify();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fTreeName;    //tree name
      TString                  fPrefix;      //
      TString                  fPathName;    //
      UInt_t                   fMaxSize;     //
      UInt_t                   fCompLevel;   //
      UInt_t                   fSplitLevel;  //
      UInt_t                   fBranchSize;  //
      Bool_t                   fDoReset;     //=true then reset pointers
      Bool_t                   fCheckDep;    //=true then check auto-loaded branches
      StringVec                fCmdList;     //list of keep/drop statements

    private:
      void                     CheckAndAddBranch(const char *bname, const char *cname);
      Bool_t                   IsAcceptedBranch(const char *bname);
      UInt_t                   GetNBranches() { return fBrNameList.Entries(); }
      void                     LoadBranches();
      void                     RequestBranch(const char *bname);
      void                     ResolveDep(Bool_t solve=kFALSE);
      void                     SetupBranches();

      TreeWriter              *fTreeWriter;     //!
      EventHeader             *fEventHeader;    //!
      std::vector<TRegexp>     fCmdReList;      //!
      std::vector<Bool_t>      fCmdDeList;      //!
      StringVec                fBrNameList;     //!
      StringVec                fBrClassList;    //!
      TObject**                fBranches;       //!
      const UInt_t             fNBranchesMax;   //!

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
