// $Id: Selector.cc,v 1.1 2008/06/23 10:54:03 loizides Exp $

#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/DataTree/interface/Names.h"

#include <TProcessID.h>
#include <TFile.h>
#include <TTree.h>


using namespace mithep;

ClassImp(mithep::Selector)

//__________________________________________________________________________________________________
Selector::Selector() :
  fDoRunInfo(kTRUE),
  fRunTree(0),
  fEventHeader(0),
  fRunInfo(0),
  fCurRunNum(UInt_t(-1)),
  fLATree(0),
  fLAHeader(0)
{
}

//__________________________________________________________________________________________________
Selector::~Selector()
{
}

//__________________________________________________________________________________________________
Bool_t Selector::BeginRun()
{
  // Determines whether we are at beginning of a new run.

  if (!fDoRunInfo) 
    return kFALSE;

  LoadBranch(Names::gkEvtHeaderBrn);
  if (!fEventHeader) 
    return kFALSE;

  if (ConsistentRunNum())
    return kFALSE;

  UpdateRunInfo();
  return ValidRunNum();
}

//__________________________________________________________________________________________________
Bool_t Selector::EndRun()
{
  // Determines whether we are at the end of a run.

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

//__________________________________________________________________________________________________
Bool_t Selector::Notify()
{
  // The Notify() function is called when a new file is opened. Here, we check for a new run info
  // tree. 

  if (!GetCurrentFile()) 
    return kTRUE;

  if (fDoRunInfo) 
    UpdateRunInfoTree();

  return TAMSelector::Notify();
}

//__________________________________________________________________________________________________
void Selector::SlaveBegin(TTree* tree)
{
  // The SlaveBegin() function is called after the Begin() function and can be used to setup
  // analysis on the slaves. Here, we request the event header branch.

  if (fDoRunInfo) {
    ReqBranch(Names::gkEvtHeaderBrn, fEventHeader);
  }

  TAMSelector::SlaveBegin(tree);
}

//__________________________________________________________________________________________________
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

//__________________________________________________________________________________________________
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
  fRunTree = dynamic_cast<TTree*>(f->Get(Names::gkRunTreeName));
  if (!fRunTree) {
    Fatal("UpdateRunInfoTree", "Can not find run info tree with name %s", Names::gkRunTreeName);
  }

  // set branches 
  if (fRunTree->GetBranch(Names::gkRunInfoBrn)) {
    fRunTree->SetBranchAddress(Names::gkRunInfoBrn, &fRunInfo);
  } else {
    Fatal("UpdateRunInfoTree", "Can not find run info branch with name %s", Names::gkRunInfoBrn);
  }

  // look-ahead tree
  fLATree = dynamic_cast<TTree*>(f->Get(Names::gkLATreeName));
  if (!fLATree) {
    Fatal("UpdateRunInfoTree", "Can not find look-ahead tree with name %s", Names::gkLATreeName);
  }

  // set branches 
  if (fLATree->GetBranch(Names::gkLAHeaderBrn)) {
    fLATree->SetBranchAddress(Names::gkLAHeaderBrn, &fLAHeader);
  } else {
    Fatal("UpdateRunInfoTree", "Can not find look-ahead branch with name %s", Names::gkLAHeaderBrn);
  }
}
