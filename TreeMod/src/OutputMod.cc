// $Id: OutputMod.cc,v 1.7 2009/03/07 08:32:40 loizides Exp $

#include "MitAna/TreeMod/interface/OutputMod.h"
#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataUtil/interface/TreeWriter.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"

using namespace mithep;
using namespace std;

ClassImp(mithep::OutputMod)

//--------------------------------------------------------------------------------------------------
OutputMod::OutputMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fTreeName(Names::gkEvtTreeName),
  fPrefix("skimtest"),
  fPathName("."),
  fMaxSize(1024),
  fCompLevel(9),
  fSplitLevel(99),
  fBranchSize(64*1024),
  fDoReset(kFALSE),
  fCheckTamBr(kTRUE),
  fKeepTamBr(kTRUE),
  fTreeWriter(0),
  fEventHeader(0),
  fAllEventHeader(0),
  fRunInfo(0),
  fLaHeader(0),
  fNBranchesMax(1024),
  fRunTree(0),
  fLATree(0),
  fAllTree(0),
  fL1Tree(0),
  fHltTree(0),
  fRunEntries(0),
  fOrigL1Entry(-1),
  fL1Entries(0),
  fOrigHltEntry(-1),
  fHltEntries(0),
  fFileNum(0),
  fLastWrittenEvt(-1),
  fLastSeenEvt(-1),
  fCounter(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void OutputMod::BeginRun()
{
  // Create HLT tree if HLTFwkMod is being run.

  if (!HasHLTInfo())
    return;

  if (!fHltTree) {
    HLTFwkMod *hm = const_cast<HLTFwkMod*>(GetHltFwkMod());
    fTreeWriter->AddBranchToTree(hm->HLTTreeName(), hm->HLTTabName(), 
                                 TClass::GetClass(typeid(*hm->fHLTTab))->GetName(), 
                                 &(hm->fHLTTab), 32000, 0);
    fTreeWriter->AddBranchToTree(hm->HLTTreeName(), hm->HLTLabName(), 
                                 TClass::GetClass(typeid(*hm->fHLTLab))->GetName(), 
                                 &(hm->fHLTLab), 32000, 0);
    fTreeWriter->SetAutoFill(hm->HLTTreeName(), 0);
    fHltTree = fTreeWriter->GetTree(hm->HLTTreeName());
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::CheckAndAddBranch(const char *bname, const char *cname)
{
  // Check if the given branch should be kept or dropped. 

  if (IsAcceptedBranch(bname)) 
    return;

  // populate regular expression list if this was not yet done
  if (fCmdReList.size() != fCmdList.size()) {
    for (UInt_t i=0; i<fCmdList.size(); ++i) {
      const char *ptr = fCmdList.at(i).c_str();
      fCmdReList.push_back(TRegexp(ptr+5,kTRUE));
      if (ptr[0]=='k') 
        fCmdDeList.push_back(kTRUE);
      else 
        fCmdDeList.push_back(kFALSE);
    }
  }

  // decide whether given branch name should be kept or dropped
  TString brname(bname);
  Bool_t decision       = kFALSE;
  Bool_t decision_found = kFALSE;

  for (UInt_t i=0; i<fCmdList.size(); ++i) {
    TRegexp &re(fCmdReList.at(i));
    if (brname.Index(re) == kNPOS)
      continue;
    decision = fCmdDeList.at(i);
    decision_found = kTRUE;
  }

  if (!decision_found) { // no decision found: still drop branch
    Warning("CheckAndAddBranch", 
            "No decision found for branch with name %s and class %s. Branch therefore dropped!",
            bname, cname);
    return;
  }

  if (!decision) { // drop branch according to request
    SendError(kWarning, "CheckAndAddBranch", 
              "Dropped branch with name %s and class %s.", bname, cname);
    return;
  }

  // add branch to accepted branch list
  SendError(kWarning, "CheckAndAddBranch", 
            "Kept branch with name %s and class %s.", bname, cname);

  fBrNameList.push_back(string(bname));
  fBrClassList.push_back(string(cname));

  // request branch
  RequestBranch(bname);
}

//--------------------------------------------------------------------------------------------------
void OutputMod::CheckAndResolveDep(Bool_t solve) 
{
  // Check if TAM has loaded additional branches. If requested try to solve the the dependency
  // by adding the branch to the list of branches.

  const THashTable &ht = GetSel()->GetBranchTable();

  TIter iter(ht.MakeIterator());
  const TAMBranchInfo *next = dynamic_cast<const TAMBranchInfo*>(iter.Next());

  while (next) {
    const TAMBranchInfo *cur = next;
    next = dynamic_cast<const TAMBranchInfo*>(iter.Next());
    Bool_t isloaded = cur->IsLoaded();
    if (!isloaded)
      continue;

    const char *bname = cur->GetName();
    if (IsAcceptedBranch(bname))
      continue;

    TreeBranchLoader *loader = dynamic_cast<TreeBranchLoader*>(cur->GetLoader());
    if (!loader) 
      continue;

    TBranch *br = loader->GetBranch();
    if (!br) 
      continue;

    const char *cname = br->GetClassName();

    if (solve) {
      SendError(kWarning, "CheckAndResolveDep", 
                "Resolving dependency for loaded branch %s and class %s", bname,cname);

      fBrNameList.push_back(string(bname));
      fBrClassList.push_back(string(cname));
      fBranches[GetNBranches()-1] = reinterpret_cast<TObject*>(loader->GetAddress());

    } else {
      Warning("CheckAndResolveDep", "Unresolved dependency for loaded branch %s and class %s",
              bname,cname);
    }
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::EndRun()
{
  // Todo
}

//--------------------------------------------------------------------------------------------------
void OutputMod::FillAllEventHeader(Bool_t isremoved)
{
  // Fill event header into the all-event-header tree.

  const EventHeader *eh = GetEventHeader();
  fAllEventHeader->SetEvtNum(eh->EvtNum());
  fAllEventHeader->SetLumiSec(eh->LumiSec());
  fAllEventHeader->SetRunNum(eh->RunNum());
  if (isremoved) 
    fAllEventHeader->SetRunEntry(-1);
  else 
    fAllEventHeader->SetRunEntry(eh->RunEntry());
  fAllEventHeader->SetSkimmed(eh->Skimmed()+1);

  fAllTree->Fill();
}

//--------------------------------------------------------------------------------------------------
void OutputMod::FillL1Info()
{
  // Not doing anything here until the production writes out L1 information.

  if (!fL1Tree) 
    return;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::FillHltInfo()
{
  // Write HLT trigger table if needed.

  if (!fHltTree) 
    return;

  if (fOrigHltEntry == GetHltFwkMod()->fCurEnt)
    return;

  fHltTree->Fill();
  fOrigHltEntry = GetHltFwkMod()->fCurEnt;
  ++fHltEntries;
}

//--------------------------------------------------------------------------------------------------
Bool_t OutputMod::IsAcceptedBranch(const char *bname)
{
  // Return true if given branch is already in branch list. Also return true if a special
  // branch like the "EventHeader" branch is reqested. 

  // search in branch list
  for (UInt_t i=0; i<GetNBranches(); ++i) {
    if (fBrNameList.at(i).compare(bname) == 0) 
      return kTRUE;
  }

  // check if special branch that we take care of ourselves
  string name(bname);
  if (name.compare("EventHeader") == 0) {
    return kTRUE;
  }

  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
Bool_t OutputMod::Notify()
{
  // On first notify, loop over list of branches to determine the list of kept branches.

  if (GetNEventsProcessed() != 0) 
    return kTRUE;

  TTree *tree=const_cast<TTree*>(GetSel()->GetTree());
  if (!tree) 
    return kFALSE;

  TObjArray *arr = tree->GetTree()->GetListOfBranches();
  if (!arr)
    return kFALSE;

  for (Int_t i=0; i<arr->GetEntries(); ++i) {
    TBranch *br = dynamic_cast<TBranch*>(arr->At(i));
    if (!br && !br->GetMother())
      continue;
    br = br->GetMother();
    TClass *cls = TClass::GetClass(br->GetClassName());
    if (!cls)
      continue;

    if (!cls->InheritsFrom("TObject")) {
      Warning("Notify", "Found branch %s where class %s does not derive from TObject.", 
              br->GetName(), br->GetClassName());
      continue;
    } 

    CheckAndAddBranch(br->GetName(), br->GetClassName());
  }

  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::LoadBranches()
{
  // Loop over requested branches and load them.

  for (UInt_t i=0; i<GetNBranches(); ++i) {
    LoadBranch(fBrNameList.at(i).c_str());
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::Process()
{
  // Write out the kept branches of the current event. Make sure the meta information is 
  // correctly updated.

  if (GetSel()->GetCurEvt() == fLastSeenEvt) {
    Warning("Process", "Event with %ul already seen", fLastSeenEvt);
    return;
  }
  fLastSeenEvt = GetSel()->GetCurEvt();

  if (GetSel()->GetCurEvt() == fLastWrittenEvt) {
    Warning("Process", "Event with %ul already written", fLastWrittenEvt);
    return;
  }
  fLastWrittenEvt = GetSel()->GetCurEvt();
  ++fCounter;

  // prepare for tree filling
  if (!fTreeWriter->BeginEvent(fDoReset)) {
    SendError(kAbortAnalysis, "Process", "Begin event failed!");
    return;
  }

  if (GetNEventsProcessed() == 0 && fCheckTamBr) {
    CheckAndResolveDep(fKeepTamBr);    
  }

  // load all our branches
  LoadBranches();

  // pass our branches to tree writer if on first event
  if (GetNEventsProcessed() == 0) {
    SetupBranches(); 
  }

  // reset per file quantities if a new file was opened
  if (fTreeWriter->GetFileNumber()!=fFileNum) {
    fRunmap.clear();
    fRunEntries = 0;
    fL1Entries  = -1;
    fHltEntries = -1;
    fFileNum = fTreeWriter->GetFileNumber();
  }

  UInt_t runnum = GetEventHeader()->RunNum();

  // store look ahead information
  if (fRunEntries>0) {
    fLaHeader->SetRunNum(runnum);
    fLATree->Fill();
  }

  // fill event header
  fEventHeader->SetEvtNum(GetEventHeader()->EvtNum());
  fEventHeader->SetLumiSec(GetEventHeader()->LumiSec());
  fEventHeader->SetRunNum(runnum);

  // fill all event header
  //  *** note that we need to read an existing tree in 
  //      the future to make sure we can do skims of skims ***
  FillAllEventHeader(kFALSE);

  // look-up if entry is in map
  map<UInt_t,Int_t>::iterator riter = fRunmap.find(runnum);
  if (riter != fRunmap.end()) { // found existing run info
    Int_t runentry = riter->second;
    fEventHeader->SetRunEntry(runentry);

    IncNEventsProcessed();
    fTreeWriter->EndEvent(fDoReset);
    return;
  }

  // fill new run info
  Int_t runentry = fRunEntries;
  ++fRunEntries;
  fEventHeader->SetRunEntry(runentry);
  fRunmap.insert(pair<UInt_t,Int_t>(runnum,runentry));
  fRunInfo->SetRunNum(runnum);

  Int_t l1entry = fL1Entries;
  FillL1Info();
  fRunInfo->SetL1Entry(l1entry);

  Int_t hltentry = fHltEntries;
  FillHltInfo();
  fRunInfo->SetHltEntry(hltentry);
  
  fRunTree->Fill();
  
  IncNEventsProcessed();

  if (!fTreeWriter->EndEvent(fDoReset)) {
    SendError(kAbortAnalysis, "Process", "End event failed!");
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::ProcessAll()
{
  // Called by the Selector class for events that were skipped.

  if (GetSel()->GetCurEvt() == fLastSeenEvt)
    return;

  fLastSeenEvt = GetSel()->GetCurEvt();
  ++fCounter;

  // prepare for tree filling
  if (!fTreeWriter->BeginEvent(kFALSE)) {
    SendError(kAbortAnalysis, "ProcessAll", "Begin event failed!");
    return;
  }

  FillAllEventHeader(kTRUE);
}

//--------------------------------------------------------------------------------------------------
void OutputMod::RequestBranch(const char *bname) 
{
  // Request given branch from TAM.

  if (GetNBranches()>=fNBranchesMax) {
    SendError(kAbortAnalysis, "RequestBranch", "Can not request branch for %bname"
              "since maximum number of branches [%d] is reached", bname, fNBranchesMax);
    return;
  }
  
  fBranches[GetNBranches()-1] = 0;
  TAModule::ReqBranch(bname, fBranches[GetNBranches()-1]);
}

//--------------------------------------------------------------------------------------------------
void OutputMod::SetupBranches()
{
  // Setup branches in tree writer.

  for (UInt_t i=0; i<GetNBranches(); ++i) {
    const char *bname = fBrNameList.at(i).c_str();
    const char *cname = fBrClassList.at(i).c_str();
    if (!fBranches[i]) {
      SendError(kWarning, "SetupBranches", 
                "Pointer for branch with name %s and class %s is NULL.", bname, cname);
      continue;
    }
    fTreeWriter->AddBranch(bname, cname, &fBranches[i]);
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::SlaveBegin()
{
  // Setup the tree writer and create branches that can already be created at this point.

  // setup tree writer
  fTreeWriter = new TreeWriter(fTreeName, kFALSE);
  fTreeWriter->SetBaseURL(fPathName);
  fTreeWriter->SetPrefix(fPrefix);
  fTreeWriter->SetMaxSize(fMaxSize*1024*1024);
  fTreeWriter->SetCompressLevel(fCompLevel);
  fTreeWriter->SetDefaultSL(fSplitLevel);
  fTreeWriter->SetDefaultBrSize(fBranchSize);
  fTreeWriter->AddTree(fTreeName);
  fTreeWriter->DoBranchRef(fTreeName);

  // deal with my own tree objects
  fEventHeader = new EventHeader;
  fTreeWriter->AddBranch(GetSel()->GetEvtHdrName(), &fEventHeader);

  // deal with other trees
  const char *tname = 0;
  fRunInfo = new RunInfo;
  tname = GetSel()->GetRunTreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetRunInfoName(), &fRunInfo);
  fTreeWriter->SetAutoFill(tname, 0);
  fRunTree = fTreeWriter->GetTree(tname);
  fLaHeader = new LAHeader;
  tname = GetSel()->GetLATreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetLAHdrName(), &fLaHeader);
  fTreeWriter->SetAutoFill(tname,0);
  fLATree = fTreeWriter->GetTree(tname);
  fAllEventHeader = new EventHeader;
  tname = GetSel()->GetAllEvtTreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetAllEvtHdrBrn(), &fAllEventHeader);
  fAllTree = fTreeWriter->GetTree(tname);

  // get pointer to fAllTreeIn todo
  // todo
  // deal here with published objects
  // todo

  // create TObject space for TAM
  fBranches = new TObject*[fNBranchesMax];       

  // adjust checks for TAM branches
  if (fKeepTamBr)
    fCheckTamBr = kTRUE;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::SlaveTerminate()
{
  // Terminate tree writing and do cleanup.

  delete fTreeWriter;
  fTreeWriter = 0;

  delete fEventHeader;
  delete fRunInfo;
  delete fLaHeader;
  delete fAllEventHeader;

  delete[] fBranches; 

  Double_t frac =  100.*GetNEventsProcessed()/fCounter;
  SendError(kWarning, "SlaveTerminate", "Stored %.2g%% events (%ld out of %ld)", 
            frac, GetNEventsProcessed(), fCounter);
}
