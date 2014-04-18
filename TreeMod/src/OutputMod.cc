// $Id: OutputMod.cc,v 1.19 2011/03/11 04:03:54 bendavid Exp $

#include "MitAna/TreeMod/interface/OutputMod.h"
#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataTree/interface/BranchTable.h"
#include "MitAna/DataTree/interface/EventHeaderCol.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataUtil/interface/TreeWriter.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"

#include "MitAna/DataTree/interface/PhotonCol.h"

using namespace mithep;
using namespace std;

ClassImp(mithep::OutputMod)

//--------------------------------------------------------------------------------------------------
OutputMod::OutputMod(const char *name, const char *title) : 
  BaseMod        (name,title),
  fTreeName      (Names::gkEvtTreeName),
  fPrefix        ("skimtest"),
  fPathName      ("."),
  fMaxSize       (1024),
  fCompLevel     (9),
  fSplitLevel    (99),
  fBranchSize    (16*1024),
  fDoReset       (kFALSE),
  fCheckBrDep    (kTRUE),
  fUseBrDep      (kTRUE),
  fCheckTamBr    (kTRUE),
  fKeepTamBr     (kFALSE),
  fTreeWriter    (0),
  fEventHeader   (0),
  fAllEventHeader(0),
  fRunInfo       (0),
  fLaHeader      (0),
  fBranchTable   (0),
  fBranches      (0),
  fNBranchesMax  (1024),
  fRunTree       (0),
  fLATree        (0),
  fAllTree       (0),
  fSkimmedIn     (0),
  fHltTree       (0),
  fHLTTab        (new vector<string>),
  fHLTLab        (new vector<string>),
  fRunEntries    (0),
  fHltEntries    (0),
  fFileNum       (-1),
  fLastWrittenEvt(-1),
  fLastSeenEvt   (-1),
  fCounter       (0),
  fGoodPhotons   (0)
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
                                 TClass::GetClass(typeid(*fHLTTab))->GetName(), 
                                 &fHLTTab, 32000, 0);
    fTreeWriter->AddBranchToTree(hm->HLTTreeName(), hm->HLTLabName(), 
                                 TClass::GetClass(typeid(*fHLTLab))->GetName(), 
                                 &fHLTLab, 32000, 0);
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
  Bool_t  decision       = kFALSE;
  Bool_t  decision_found = kFALSE;

  for (UInt_t i=0; i<fCmdList.size(); ++i) {
    TRegexp &re(fCmdReList.at(i));
    if (brname.Index(re) == kNPOS)
      continue;
    decision = fCmdDeList.at(i);
    decision_found = kTRUE;
  }

  if (!decision_found) { // no decision found: still drop branch
    Warning("CheckAndAddBranch", 
            "No decision found for branch '%s' and class '%s'. Branch therefore dropped!",
            bname, cname);
    return;
  }

  if (!decision) { // drop branch according to request
    Info("CheckAndAddBranch", 
         "Dropped branch '%s' and class '%s'", bname, cname);
    return;
  }

  // add branch to accepted branch list
  Info("CheckAndAddBranch", 
       "Kept branch '%s' and class '%s'", bname, cname);

  fBrNameList .push_back(string(bname));
  fBrClassList.push_back(string(cname));
}

//--------------------------------------------------------------------------------------------------
Bool_t OutputMod::CheckAndResolveBranchDep()
{
  // Checks dependency in BranchTable. Resolve dependency automatically if fUserBrDep is kTRUE.

  TFile *cfile = const_cast<TFile*>(GetSel()->GetCurrentFile());
  if (!cfile) {
    SendError(kAbortAnalysis, "CheckAndResolveBranchDep", "Could not get pointer to current file!");
    return kFALSE;
  }

  BranchTable *br = dynamic_cast<BranchTable*>(cfile->Get(Names::gkBranchTable));
  if (!br) {
    SendError(kAbortAnalysis, "CheckAndResolveBranchDep", "Could not get pointer to branch table!");
    return kFALSE;
  }

  TList *blist = br->GetBranches();
  if (!blist) {
    SendError(kAbortAnalysis, "CheckAndResolveBranchDep", "Could not get list of branches!");
    return kFALSE;
  }

  fBranchTable = new BranchTable;
  fBranchTable->SetName(Names::gkBranchTable);
  fBranchTable->SetOwner();

  TList sht;
  sht.SetOwner(kTRUE);
  for (UInt_t i=0; i<fBrNameList.size(); ++i) {
    sht.Add(new TObjString(fBrNameList.at(i).c_str()));
  }

  for (UInt_t i=0; i<fBrNameList.size(); ++i) {
    TString brname(fBrNameList.at(i));
    if (!blist->FindObject(brname))
      continue;
    TList *bdeps = br->GetDepBranches(brname);
    if (!bdeps)
      continue;

    // check dependency
    TIter iter(bdeps->MakeIterator());
    const TObjString *n = dynamic_cast<const TObjString*>(iter.Next());
    while (n) {
      if (sht.FindObject(n->GetName())) {
        // dependent branch is already accepted
        fBranchTable->Add(new BranchName(brname,n->GetName()));
      } else {
        if (fUseBrDep) {
          const TObjArray *arr = GetSel()->GetTree()->GetTree()->GetListOfBranches();
          TBranch *br = dynamic_cast<TBranch*>(arr->FindObject(n->GetName()));
          if (!br) {
            Error("CheckAndResolveBranchDep", 
                  "Could not get branch '%s' to resolve dependency for branch '%s'", 
               n->GetName(), brname.Data());
          } else {
            Info("CheckAndResolveBranchDep", 
                 "Adding branch '%s' to resolve dependency for branch '%s'", 
                 n->GetName(), brname.Data());
            fBrNameList .push_back(string(n->GetName()));
            fBrClassList.push_back(br->GetClassName());
            sht.Add(new TObjString(n->GetName()));
            fBranchTable->Add(new BranchName(brname,n->GetName()));
          } 
        } else {
          Warning("CheckAndResolveBranchDep", 
                  "Unresolved dependency of branch '%s' and '%s' ",
                  n->GetName(), brname.Data());
        }
      } 
      n = dynamic_cast<const TObjString*>(iter.Next());
    }
    delete bdeps;
  }
  delete blist;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::CheckAndResolveTAMDep(Bool_t solve) 
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
      Info("CheckAndResolveTAMDep", 
           "Resolving dependency for loaded branch '%s' and class '%s'", bname,cname);

      fBrNameList. push_back(string(bname));
      fBrClassList.push_back(string(cname));
      fBranches[GetNBranches()-1] = reinterpret_cast<TObject*>(loader->GetAddress());

    } else {
      Warning("CheckAndResolveTAMDep", 
              "Unresolved dependency for loaded branch '%s' and class '%s'",
              bname,cname);
    }
  }
}

//--------------------------------------------------------------------------------------------------
void OutputMod::EndRun()
{
  // Nothing to be done at this point.
}

//--------------------------------------------------------------------------------------------------
void OutputMod::FillAllEventHeader(Bool_t isremoved)
{
  // Fill event header into the all-event-header tree.

  if (!fTreeWriter->BeginEvent(kFALSE)) {
    SendError(kAbortAnalysis, "FillAllEventHeader", "Begin event failed!");
    return;
  }

  if (fSkimmedIn) { // copy alread skimmed headers if any there
    const UInt_t n = fSkimmedIn->GetEntries();
    for (UInt_t i=0; i<n; ++i) {
      const EventHeader  *eh = fSkimmedIn->At(i);
      *fAllEventHeader = *eh;
      fAllEventHeader->SetSkimmed(eh->Skimmed()+1);
      fAllTree->Fill();
    }
  }

  const EventHeader  *eh = GetEventHeader();
  *fAllEventHeader = *eh;
  if (isremoved) {
    fAllEventHeader->SetRunEntry(-1);
    fAllEventHeader->SetSkimmed(eh->Skimmed()+1);
  } else {
    fAllEventHeader->SetRunEntry(eh->RunEntry());
    fAllEventHeader->SetSkimmed(eh->Skimmed());
  }

  fAllTree->Fill();
}

//--------------------------------------------------------------------------------------------------
void OutputMod::FillHltInfo()
{
  // Write HLT trigger table if needed.

  if (!fHltTree) 
    return;

  HLTFwkMod *hm = const_cast<HLTFwkMod*>(GetHltFwkMod());
  vector<string> *trigtable = hm->fHLTTab;
  vector<string> *labels = hm->fHLTLab;

  Bool_t doCopy = kFALSE;
  if (fHLTTab->size()==0) {
    doCopy = kTRUE;
  } else {
    // check if existing table contains all necessary paths: 
    // if so keep it, otherwise store the new one  

    if ((fHLTTab->size() != trigtable->size()) || 
        (fHLTLab->size() != labels->size())) {
      doCopy = kTRUE;
    } else {
      // need to check more thoroughly

      for (UInt_t i=0; i<trigtable->size(); ++i) {
        if (trigtable->at(i) != fHLTTab->at(i)) {
          doCopy = kTRUE;
          break;
        }
      }
      if (!doCopy) {
        for (UInt_t i=0; i<labels->size(); ++i) {
        if (labels->at(i) != fHLTLab->at(i)) {
            doCopy = kTRUE;
            break;
          }
        }
      }
    }
  }

  if (!doCopy)
    return;

  fHLTTab->resize(trigtable->size());
  copy(trigtable->begin(),trigtable->end(), fHLTTab->begin());
  fHLTLab->resize(labels->size());
  copy(labels->begin(),labels->end(), fHLTLab->begin());

  ++fHltEntries;
  fHltTree->Fill();
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

  const TTree *tree=GetSel()->GetTree();
  if (!tree) 
    return kFALSE;

  const TObjArray *arr = tree->GetTree()->GetListOfBranches();
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
      Warning("Notify", "Found branch '%s' where class '%s' does not derive from TObject", 
              br->GetName(), br->GetClassName());
      continue;
    } 

    CheckAndAddBranch(br->GetName(), br->GetClassName());
  }

  if (fCheckBrDep && !CheckAndResolveBranchDep())
    return kFALSE;

  RequestBranches();
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::LoadBranches()
{
  // Loop over requested branches and load them.

  for (UInt_t i=0; i<GetNBranches(); ++i)
    LoadBranch(fBrNameList.at(i).c_str());
}

//--------------------------------------------------------------------------------------------------
void OutputMod::Process()
{
  // Write out the kept branches of the current event. Make sure the meta information is 
  // correctly updated.

  if (GetSel()->GetCurEvt() == fLastSeenEvt) {
    Warning("Process", "Event with %lld already seen", fLastSeenEvt);
    return;
  }
  fLastSeenEvt = GetSel()->GetCurEvt();

  if (GetSel()->GetCurEvt() == fLastWrittenEvt) {
    Warning("Process", "Event with %lld already written", fLastWrittenEvt);
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
    CheckAndResolveTAMDep(fKeepTamBr);
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
    fHLTTab->clear();
    fHLTLab->clear();
    fRunEntries = 0;
    fHltEntries = 0;
    fFileNum = fTreeWriter->GetFileNumber();
    if (fBranchTable)
      fTreeWriter->StoreObject(fBranchTable);
  }

  UInt_t runnum = GetEventHeader()->RunNum();

  // store look ahead information
  if (fRunEntries>0) {
    fLaHeader->SetRunNum(runnum);
    fLATree->Fill();
  }

  // fill event header
  *fEventHeader = *GetEventHeader();

  // fill all event header
  FillAllEventHeader(kFALSE);

  // look-up if entry is in map
  map<UInt_t,Int_t>::iterator riter = fRunmap.find(runnum);
  if (riter != fRunmap.end()) { // found existing run info
    Int_t runEntry = riter->second;
    fEventHeader->SetRunEntry(runEntry);

    IncNEventsProcessed();
    fTreeWriter->EndEvent(fDoReset);
    return;
  }

  // fill new run info
  Int_t runEntry = fRunEntries;
  ++fRunEntries;
  fEventHeader->SetRunEntry(runEntry);
  fRunmap.insert(pair<UInt_t,Int_t>(runnum,runEntry));
  fRunInfo->SetRunNum(runnum);

  Int_t hltEntry = fHltEntries;
  FillHltInfo();
  if (hltEntry < fHltEntries)
    fRunInfo->SetHltEntry(hltEntry);
  else
    fRunInfo->SetHltEntry(hltEntry-1);
  
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
  FillAllEventHeader(kTRUE);
}

//--------------------------------------------------------------------------------------------------
void OutputMod::RequestBranches() 
{
  // Loop over requested branches and request them.

  for (UInt_t i=0; i<GetNBranches(); ++i) {
    if (i>=fNBranchesMax) {
      SendError(kAbortAnalysis, "RequestBranches", "Cannot request branch '%s' "
                "since maximum number of branches [%d] is reached", 
                fBrNameList.at(i).c_str(), fNBranchesMax);
      return;
    }
    fBranches[i] = 0;
    TAModule::ReqBranch(fBrNameList.at(i).c_str(), fBranches[i]);
  }
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
                "Pointer for branch '%s' and class '%s' is NULL", bname, cname);
      continue;
    }
    Int_t bsize = fBranchSize;
    TString cnamestr(cname);
    if ((bsize<128*1024) && (cnamestr.Contains("mithep::MCParticle"))) {
      bsize=128*1024;
    } else if ((bsize<32*1024) && (cnamestr.Contains("mithep::CaloTower"))) {
      bsize=32*1024;
    }

    fTreeWriter->AddBranch(bname, cname, &fBranches[i], bsize);
  }

  // deal here with additional published objects
  for (UInt_t i=0; i<fAddList.size(); ++i) {
    TString objname(fAddList.at(i));
    TObject *obj = FindPublicObj(objname);
    if (obj) {
      fBranches[fNBranchesMax+i] = obj;
      fTreeWriter->AddBranch(objname, obj->ClassName(), &fBranches[fNBranchesMax+i], fBranchSize);
      Info("SlaveBegin", "Adding additional branch named '%s' as requested", objname.Data());
    } else {
      SendError(kAbortAnalysis, "SlaveBegin", 
                "Object named '%s' for additional branch is NULL", objname.Data());
    }
  }

}

//--------------------------------------------------------------------------------------------------
void OutputMod::SlaveBegin()
{
  // Setup the tree writer and create branches that can already be created at this point.

  // setup tree writer
  fTreeWriter = new TreeWriter (fTreeName, kFALSE);
  fTreeWriter->SetBaseURL      (fPathName);
  fTreeWriter->SetPrefix       (fPrefix);
  fTreeWriter->SetMaxSize      (fMaxSize*1024*1024);
  fTreeWriter->SetCompressLevel(fCompLevel);
  fTreeWriter->SetDefaultSL    (fSplitLevel);
  fTreeWriter->SetDefaultBrSize(fBranchSize);
  fTreeWriter->AddTree         (fTreeName);
  fTreeWriter->DoBranchRef     (fTreeName);

  // deal with my own tree objects
  fEventHeader = new EventHeader;
  fTreeWriter->AddBranch(GetSel()->GetEvtHdrName(), &fEventHeader);

  // deal with other trees
  const char *tname = 0;
  fRunInfo = new RunInfo;
  tname = GetSel()->GetRunTreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetRunInfoName(), &fRunInfo);
  fTreeWriter->SetAutoFill(tname, 0);
  // the run tree first
  fRunTree = fTreeWriter->GetTree(tname);
  fLaHeader = new LAHeader;
  tname = GetSel()->GetLATreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetLAHdrName(), &fLaHeader);
  fTreeWriter->SetAutoFill(tname, 0);
  // the Look Ahead tree next
  fLATree = fTreeWriter->GetTree(tname);
  fAllEventHeader = new EventHeader;
  tname = GetSel()->GetAllEvtTreeName();
  fTreeWriter->AddBranchToTree(tname, GetSel()->GetAllEvtHdrBrn(), &fAllEventHeader);
  fAllTree = fTreeWriter->GetTree(tname);
  fTreeWriter->SetAutoFill(tname, 0);

  // get pointer to all event headers
  fSkimmedIn = GetPublicObj<EventHeaderCol>(Names::gkSkimmedHeaders);

  // create TObject space for TAM
  fBranches = new TObject*[fNBranchesMax + fAddList.size()];       

  // adjust checks for TAM branches
  if (fKeepTamBr)
    fCheckTamBr = kTRUE;
}

//--------------------------------------------------------------------------------------------------
void OutputMod::SlaveTerminate()
{
  // Terminate tree writing and do cleanup.

  RetractObj(Names::gkSkimmedHeaders);

  delete fTreeWriter;
  fTreeWriter = 0;

  delete fEventHeader;
  delete fRunInfo;
  delete fLaHeader;
  delete fAllEventHeader;

  delete[] fBranches; 

  Double_t frac =  100.*GetNEventsProcessed()/fCounter;
  Info("SlaveTerminate", "Stored %.2f%% events (%d out of %lld)", 
       frac, GetNEventsProcessed(), fCounter);
}
