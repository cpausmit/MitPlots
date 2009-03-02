// $Id: Selector.cc,v 1.9 2008/12/12 16:57:42 bendavid Exp $

#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/TreeMod/interface/OutputMod.h"
#include <TProcessID.h>
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>

using namespace mithep;

ClassImp(mithep::Selector)

//--------------------------------------------------------------------------------------------------
Selector::Selector() :
  fDoRunInfo(kTRUE),
  fEvtHdrName(Names::gkEvtHeaderBrn),
  fRunTreeName(Names::gkRunTreeName),
  fRunInfoName(Names::gkRunInfoBrn),
  fAllEvtHdrBrn(Names::gkAllEvtHeaderBrn),
  fLATreeName(Names::gkLATreeName),
  fLAHdrName(Names::gkLAHeaderBrn),
  fAllEvtTreeName(Names::gkAllEvtTreeName),
  fRunTree(0),
  fEventHeader(0),
  fRunInfo(0),
  fLATree(0),
  fLAHeader(0),
  fCurRunNum(UInt_t(-1))
{
  // Constructor.

  fOutputMods.SetOwner(kFALSE);
  gROOT->GetListOfSpecials()->Add(this);
}

//--------------------------------------------------------------------------------------------------
Selector::~Selector()
{
  // Destructor.

  fRunTree     = 0;
  fEventHeader = 0;
  fRunInfo     = 0;
  fLATree      = 0;
  fLAHeader    = 0;
  fCurRunNum   = UInt_t(-1);
  gROOT->GetListOfSpecials()->Remove(this);
}

//--------------------------------------------------------------------------------------------------
Bool_t Selector::BeginRun()
{
  // Determines whether we are at beginning of a new run.

  if (!fDoRunInfo) 
    return kFALSE;

  LoadBranch(fEvtHdrName);
  if (!fEventHeader) 
    return kFALSE;

  if (ConsistentRunNum())
    return kFALSE;

  UpdateRunInfo();
  return ValidRunNum();
}

//--------------------------------------------------------------------------------------------------
Bool_t Selector::EndRun()
{
  // Determines whether we are at the end of a run. Also, do treat special case of output module 
  // here so that in any case it can process the event.

  if (IsAModAborted() || IsEventAborted()) { // deal with output module if needed: Do this here,
    TIter it(fOutputMods.MakeIterator());    // avoids having to copy/rewrite large parts of
    OutputMod *o = 0;                        // TAMSelector::Process and interaction with TAModule
    while ((o=static_cast<OutputMod*>(it.Next())) != 0)
      o->ProcessAll();
  }

  if (!fDoRunInfo) 
    return kFALSE;

  if (!ValidRunNum())
    return kFALSE;

  // determine if run will end
  if (fCurEvt+1==fTree->GetTree()->GetEntries())
    return kTRUE; // we are at last entry in current file

  fLAHeader=0;
  Int_t ret = fLATree->GetEvent(fCurEvt);
  if (ret<0 || fLAHeader==0) {
    Error("EndRun", "Could not get entry lookahead entry for next event,"
                    " assuming end of run %ld reached!", fCurRunNum);
    return kTRUE;
  }

  return (fLAHeader->RunNum()!=fCurRunNum);
}

//--------------------------------------------------------------------------------------------------
Bool_t Selector::Notify()
{
  // The Notify() function is called when a new file is opened. 
  // Here, we check for a new run info tree. 

  if (!GetCurrentFile()) 
    return kTRUE;

  if (fDoRunInfo) 
    UpdateRunInfoTree();

  //needed to force caching to occur for all files  
  fTree->GetTree()->SetCacheSize(fTree->GetCacheSize());
    
  return TAMSelector::Notify();
}

//--------------------------------------------------------------------------------------------------
void Selector::SearchOutputMods(const TAModule *mod)
{
  // Search for output module among list of modules.

  if (!mod)
    return;

  const OutputMod *o = dynamic_cast<const OutputMod*>(mod);
  if (o)
    fOutputMods.Add(const_cast<OutputMod*>(o));

  const TList *tasks = mod->GetSubModules();
  if (!tasks) 
    return;

  TIter it(tasks->MakeIterator());
  TObject *ob = 0;
  while ((ob=it.Next()) != 0) {
    TAModule *nmod = dynamic_cast<TAModule*>(ob);
    if (nmod) 
      SearchOutputMods(nmod);
  }
}

//--------------------------------------------------------------------------------------------------
void Selector::SlaveBegin(TTree *tree)
{
  // The SlaveBegin() function is called after the Begin() function and can be used to setup
  // analysis on the slaves. Here, we request the event header branch.

  if (fDoRunInfo) {
    ReqBranch(fEvtHdrName, fEventHeader);
  }

  SearchOutputMods(GetTopModule());

  TAMSelector::SlaveBegin(tree);
}

//--------------------------------------------------------------------------------------------------
void Selector::UpdateRunInfo() 
{
  // Update the run info to be consistent with the information from the event header.

  fRunInfo   = 0;

  if (!fRunTree) 
    return;

  Int_t ret = fRunTree->GetEvent(fEventHeader->RunEntry());
  if (ret<0 || fRunInfo==0) {
    Error("UpdateRunInfo", "Error updating run info for run %ld, entry %ld, return value %d", 
          fEventHeader->RunNum(), fEventHeader->RunEntry(), ret);
    return;
  }

  fCurRunNum = fEventHeader->RunNum();
  if (!ValidRunInfo()) {
    Error("UpdateRunInfo", "Error updating run info, run values do not match %d %d", 
          fCurRunNum, fRunInfo->RunNum());
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void Selector::UpdateRunInfoTree() 
{
  // Get the run info tree from current file and set our branches.

  // first erase previous entries
  fRunTree   = 0;
  fRunInfo   = 0;
  fCurRunNum = UInt_t(-1);
  fLATree    = 0;
  fLAHeader  = 0;

  // get current file and retrieve trees
  TFile *f = GetCurrentFile();
  if (!f) {
    Error("UpdateRunInfoTree", "Ptr to current file is null");
    return;
  }

  // run info tree
  fRunTree = dynamic_cast<TTree*>(f->Get(fRunTreeName));
  if (!fRunTree) {
    Fatal("UpdateRunInfoTree", "Can not find run info tree with name %s", fRunTreeName.Data());
  }

  // set branches 
  if (fRunTree->GetBranch(fRunInfoName)) {
    fRunTree->SetBranchAddress(fRunInfoName, &fRunInfo);
  } else {
    Fatal("UpdateRunInfoTree", "Can not find run info branch with name %s", fRunInfoName.Data());
  }

  // look-ahead tree
  fLATree = dynamic_cast<TTree*>(f->Get(fLATreeName));
  if (!fLATree) {
    Fatal("UpdateRunInfoTree", "Can not find look-ahead tree with name %s", fLATreeName.Data());
  }

  // set branches 
  if (fLATree->GetBranch(fLAHdrName)) {
    fLATree->SetBranchAddress(fLAHdrName, &fLAHeader);
  } else {
    Fatal("UpdateRunInfoTree", "Can not find look-ahead branch with name %s", fLAHdrName.Data());
  }
}
