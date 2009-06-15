// $Id: HLTFwkMod.cc,v 1.8 2009/03/23 22:15:15 loizides Exp $

#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"

using namespace mithep;

ClassImp(mithep::HLTFwkMod)


//--------------------------------------------------------------------------------------------------
HLTFwkMod::HLTFwkMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fHLTTreeName(Names::gkHltTreeName),
  fHLTTabName(Names::gkHltTableBrn),
  fHLTLabName(Names::gkHltLabelBrn),
  fObjsName(Names::gkHltObjBrn),
  fRelsName(Form("%sRelation",fObjsName.Data())),
  fHLTTabNamePub(Form("%sFwk",fHLTTabName.Data())),
  fHLTLabNamePub(Form("%sFwk",fHLTLabName.Data())),
  fObjsNamePub(Form("%sFwk",fObjsName.Data())),
  fNMaxTriggers(256),
  fObjs(0),
  fRels(0),
  fReload(0),
  fHLTTree(0),
  fHLTTab(0),
  fHLTLab(0),
  fCurEnt(-2),
  fTriggers(new TriggerTable(fNMaxTriggers)),
  fLabels(new TriggerTable(fNMaxTriggers*16)),
  fTrigObjs(new TriggerObjectsTable(fTriggers,fNMaxTriggers))
{
  // Constructor.

  fTriggers->SetName(fHLTTabNamePub);
  fTriggers->SetOwner();
  fLabels->SetName(fHLTLabNamePub);
  fLabels->SetOwner();
  fTrigObjs->SetName(fObjsNamePub);
  fTrigObjs->SetOwner();
}

//--------------------------------------------------------------------------------------------------
HLTFwkMod::~HLTFwkMod() 
{
  // Destructor.

  fReload  =  0;
  fHLTTree =  0;
  fHLTTab  =  0;
  fHLTLab  =  0;
  fCurEnt  = -2;
  delete fTriggers;
  fTriggers = 0;
  delete fLabels;
  fLabels   = 0;
  delete fTrigObjs;
  fTrigObjs = 0;
}

//--------------------------------------------------------------------------------------------------
void HLTFwkMod::BeginRun()
{
  // Get HLT tree and set branches if new file was opened. Read next entry in HLT key
  // depending on entry in RunInfo.

  if (fReload) {

    // reset to be (re-)loaded variables
    fReload  =  0;
    fHLTTree =  0;
    fHLTTab  =  0;
    fHLTLab  =  0;
    fCurEnt  = -2;

    // get current file
    TFile *file = GetCurrentFile();
    if (!file) 
      return;

    // get HLT tree
    fHLTTree = dynamic_cast<TTree*>(file->Get(fHLTTreeName));
    if (!fHLTTree) {
      SendError(kAbortAnalysis, "BeginRun",
                "Cannot find HLT tree with name %s.", fHLTTreeName.Data());
    }

    // get HLT trigger name branch
    if (fHLTTree->GetBranch(fHLTTabName)) {
      fHLTTree->SetBranchAddress(fHLTTabName, &fHLTTab);
    } else {
      SendError(kAbortAnalysis, "BeginRun",
                "Cannot find HLT tree branch with name %s.", fHLTTabName.Data());
    }

    // get HLT module labels branch
    if (fHLTTree->GetBranch(fHLTLabName)) {
      fHLTTree->SetBranchAddress(fHLTLabName, &fHLTLab);
    } else {
      SendError(kAbortAnalysis, "BeginRun",
                "Cannot find HLT tree branch with name %s.", fHLTLabName.Data());
    }
  }

  // get entry for HLT info
  const RunInfo *runinfo = GetRunInfo();
  if (!runinfo) {
    SendError(kAbortAnalysis, "BeginRun",
              "Cannot obtain run info object from selector.");
    return;
  }

  // load trigger table
  if (runinfo->HltEntry()!=fCurEnt) {
    MDB(kAnalysis, 1)
      Info("BeginRun", "Loading trigger table for run %ld", runinfo->RunNum());
    
    fCurEnt = runinfo->HltEntry();
    Bool_t load = LoadTriggerTable();
    if (!load) {
      SendError(kAbortAnalysis, "BeginRun",
                "Cannot load trigger table for next entry (%ld).", fCurEnt);
      return;
    }

    MDB(kAnalysis, 2) {
      Info("BeginRun", "Printing tables for run %ld", runinfo->RunNum());
      cout << " --- Trigger table ---" << endl;
      fTriggers->Print();
      cout << " --- Module lables ---" << endl;
      fLabels->Print();
    }
  }
}

//--------------------------------------------------------------------------------------------------
Bool_t HLTFwkMod::LoadTriggerTable()
{
  // Load next trigger (and module) table from HLT tree.

  if (fCurEnt<0)
    return kFALSE;

  // delete old tables
  fTriggers->Delete();
  fLabels->Delete();

  // load next event in HLT tree
  fHLTTab = 0;
  fHLTLab = 0;
  Int_t ret = fHLTTree->GetEvent(fCurEnt);
  if (ret<0 || fHLTTab==0 || fHLTTab==0 ) {
    SendError(kAbortAnalysis, "LoadTriggerTable", 
              "Could not get trigger data for next entry (%ld).", fCurEnt);
    return kFALSE;
  }

  // check size of trigger table
  if (fHLTTab->size()>fNMaxTriggers) {
    SendError(kAbortAnalysis, "LoadTriggerTable", 
              "Size of trigger table (%ld) larger than maximum (%ld).", 
              fHLTTab->size(), fNMaxTriggers);
    return kFALSE;
  }

  // add trigger names
  for (UInt_t i=0; i<fHLTTab->size(); ++i) {
    TriggerName *tname = new TriggerName(fHLTTab->at(i),i);
    fTriggers->Add(tname);
  } 

  // add module labels
  for (UInt_t i=0; i<fHLTLab->size(); ++i) {
    TriggerName *tname = new TriggerName(fHLTLab->at(i),i);
    fLabels->Add(tname);
  } 

  return kTRUE;
}  

//--------------------------------------------------------------------------------------------------
Bool_t HLTFwkMod::Notify()
{
  // Save notification of a new file, which will trigger the reloading of the tables and bitmasks.

  fReload = kTRUE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void HLTFwkMod::Process()
{
  // Read trigger objects and relation branch and fill our object table.

  fTrigObjs->Delete();

  LoadBranch(fObjsName);
  LoadBranch(fRelsName);

  for (UInt_t i=0; i<fRels->Entries(); ++i) {
    const TriggerObjectRel *rel = fRels->At(i);
    if (!rel) continue;

    const TriggerObjectBase *ob = fObjs->At(rel->ObjInd());
    if (!ob) continue;

    TriggerObject *obj = new TriggerObject(rel->TrgId(), rel->Type(), ob->Id(), 
                                           ob->Pt(), ob->Eta(), ob->Phi(), ob->Mass());

    obj->SetTrigName(fHLTTab->at(rel->TrgId()).c_str());
    obj->SetModuleName(fHLTLab->at(rel->ModInd()).c_str());
    obj->SetFilterName(fHLTLab->at(rel->FilterInd()).c_str());
    fTrigObjs->Add(obj);
  }
}

//--------------------------------------------------------------------------------------------------
void HLTFwkMod::SlaveBegin()
{
  // Request branches for trigger objects and relation, and publish our tables.

  ReqBranch(fObjsName, fObjs);
  ReqBranch(fRelsName, fRels);

  if (!PublishObj(fTriggers)) {
    SendError(kAbortAnalysis, "SlaveBegin", 
              "Could not publish HLT trigger table with name %s.", fTriggers->GetName());
    return;
  }
  if (!PublishObj(fTrigObjs)) {
    SendError(kAbortAnalysis, "SlaveBegin", 
              "Could not publish HLT trigger objects table with name %s.", fTrigObjs->GetName());
    return;
  }
  if (!PublishObj(fLabels)) {
    SendError(kAbortAnalysis, "SlaveBegin", 
              "Could not publish HLT labels with name %s.", fLabels->GetName());
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void HLTFwkMod::SlaveTerminate()
{
  // Retract our published objects.

  RetractObj(fTriggers->GetName());
  RetractObj(fLabels->GetName());
  RetractObj(fTrigObjs->GetName());
}
