// $Id: HLTMod.cc,v 1.22 2011/11/18 00:02:02 bendavid Exp $

#include "MitAna/TreeMod/interface/HLTMod.h"
#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"

using namespace mithep;

ClassImp(mithep::HLTMod)

//--------------------------------------------------------------------------------------------------
HLTMod::HLTMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fAbort(kTRUE),
  fPrintTable(kFALSE),
  fIgnoreBits(kFALSE),
  fObjMode(kHlt),
  fBitsName(Names::gkHltBitBrn),
  fMyObjsNamePub(Form("%sTrigObjs", name)),
  fBits(0),
  fMyTrgObjs(0),
  fTriggers(0),
  fTrigObjs(0),
  fNEvents(0),
  fNAccepted(0),
  fNFailed(0)
{
  // Constructor. 
}

//--------------------------------------------------------------------------------------------------
HLTMod::~HLTMod() 
{
  // Destructor.
}

//--------------------------------------------------------------------------------------------------
void HLTMod::AddTrigger(const char *expr, UInt_t firstRun, UInt_t lastRun)
{
  // Add trigger search pattern to the list of patters. Each element of the list is logically 
  // "ored". The given expression can contain several trigger names logically "anded" (using "&"). 
  // A "!" infront of a trigger name negates the bit. For example, valid expressions are:
  // "A", "!A", "A&B", "A&!B" or "A&B&C"  

  string tname(expr);
  std::pair<std::string,std::pair<UInt_t,UInt_t> >
    element(tname,std::pair<UInt_t,UInt_t>(firstRun,lastRun));
  fTrigNames.push_back(element);
}

//--------------------------------------------------------------------------------------------------
void HLTMod::AddTrigObjs(UInt_t tid)
{
  // Add trigger objects corresponding to trigger id.

  const BitMask1024 &ba = fTrigBitsAnd.at(tid);
  const BitMask1024 &bm = fTrigBitsCmp.at(tid);
  for (UInt_t i=0; i<bm.Size(); ++i) {
    if (ba.TestBit(i)==0 && !fIgnoreBits)
      continue; // not an active trigger bit
    if (fBitsDone.TestBit(i))
      continue; // objects for this bit are already obtained
    if (bm.TestBit(i)==0) 
      continue; // excluded trigger bit (ie a !trgname)

    const TList *list = fTrigObjs->GetList(i);
    if (list) {
      TIter iter(list->MakeIterator());
      const TriggerObject *to = dynamic_cast<const TriggerObject*>(iter.Next());
      while (to) {
        if ( (fObjMode == kAll)  ||
             ((fObjMode == kHlt) && (to->IsHLT())) ||
             ((fObjMode == kL1)  && (to->IsL1())) )
          fMyTrgObjs->Add(to);    
        to = dynamic_cast<const TriggerObject*>(iter.Next());
      }
    }
    fBitsDone.SetBit(i);
  }
}
 
//--------------------------------------------------------------------------------------------------
void HLTMod::BeginRun()
{
  // Get HLT tree and set branches. Compute bitmasks to be used when comparing to the HLT bits.

  fTrigBitsAnd.clear();
  fTrigBitsCmp.clear();

  if (fPrintTable) {
    Info("BeginRun", "Get trigger table for run %d", GetEventHeader()->RunNum());
    printf(" Trigger table for run %d:\n",GetEventHeader()->RunNum());
    fTriggers->Print();
  }
  
  UInt_t runNumber = GetEventHeader()->RunNum();

  for (UInt_t i=0; i<fTrigNames.size(); ++i) {
    
    UInt_t firstRun = fTrigNames.at(i).second.first;
    UInt_t lastRun  = fTrigNames.at(i).second.second;
    
    // implement run dependence of the triggers
    if ( (!(firstRun==0 && lastRun==0)) &&
	 ( runNumber<firstRun || runNumber>lastRun ) )
      continue;
    
    BitMask1024 tmask; //trigger mask
    BitMask1024 amask; //bitand mask
    TString names(fTrigNames.at(i).first.c_str());

    TObjArray *arr = names.Tokenize("&");
    if (arr) {
      for(Int_t j=0; j<arr->GetEntries(); j++){
        TObjString *s = dynamic_cast<TObjString*>(arr->At(j));
        if (!s) 
          continue;
        TString st = s->GetString();
        bool wildcard = false;
        if (st.EndsWith("*")) {
          st.ReplaceAll("*","");
          wildcard = true;
        }
        const char *sptr = st.Data();
        Bool_t invert = kFALSE;
        if (sptr[0] == '!') { 
          invert = kTRUE; //inverted bit set
          ++sptr;
        }
        const TriggerName *tn = 0;
        if (wildcard) {
          tn = fTriggers->GetWildcard(sptr);
        }
        else {
          tn = fTriggers->Get(sptr);
        }
        if (!tn) {
          Warning("BeginRun", "Trigger %s not found.", sptr);
          continue;
        }

        UShort_t bit = tn->Id();
        if (amask.TestBit(bit)) {
          if (tmask.TestBit(bit)==invert) {
            amask.ClearBit(bit);
            tmask.ClearBit(bit);
            Warning("BeginRun", "Trigger expression %s always false.", names.Data());
            break;
          }
        } else { //always set and-mask bit 
          amask.SetBit(bit); 
          if (!invert) 
            tmask.SetBit(bit); //set trigger bit
        }
      }
      delete arr;
    }
    if (amask.NBitsSet()) {
      fTrigBitsAnd.push_back(amask);
      fTrigBitsCmp.push_back(tmask);
    }
  }
}

//--------------------------------------------------------------------------------------------------
void HLTMod::Process()
{
  // Process trigger bits for this event. If trigger bits pass the given bit mask, then obtain
  // and publish the corresponding trigger objects. If OnAccepted or OnFailed is implemented
  // in a derived class, call it. Do not stop processing this event, if fAbort is kFALSE.

  ++fNEvents; 
  LoadBranch(fBitsName);

  // match trigger bits to trigger mask and obtain trigger objects
  fMyTrgObjs = new TriggerObjectOArr(0,fMyObjsNamePub);
  fMyTrgObjs->SetOwner(kFALSE); // the objects are owned by the object table
  fBitsDone.Clear();
  Bool_t accept = kFALSE;
  for (UInt_t i = 0; i<fTrigBitsAnd.size(); ++i) {
    BitMask1024 bitmask(fBits->Get());
    bitmask &= fTrigBitsAnd.at(i);
    if (bitmask==fTrigBitsCmp.at(i)) {
      accept = kTRUE;
      AddTrigObjs(i);
    }
  }

  // take action if failed
  if (!accept) {
    ++fNFailed;
    OnFailed();
    delete fMyTrgObjs;
    if (fAbort) {
      SkipEvent(); // abort processing of this event by sub-modules
    }
    return;
  } 

  // take action if accepted
  ++fNAccepted;
  IncNEventsProcessed();
  OnAccepted();
  if (!AddObjThisEvt(fMyTrgObjs)) {
    SendError(kAbortAnalysis, "Process", 
              "Could not add my trigger objects with name %s to event.",
              fMyTrgObjs->GetName());
    return;
  }
  fMyTrgObjs = 0;
}

//--------------------------------------------------------------------------------------------------
void HLTMod::SlaveBegin()
{
  // Request trigger bit branch and obtain trigger table and objects.

  ReqBranch(fBitsName, fBits);
  
  fTriggers = GetHLTTable();
  if (!fTriggers) {
    SendError(kAbortAnalysis, "SlaveBegin", "Could not get HLT trigger table.");
    return;
  }
  fTrigObjs = GetHLTObjectsTable();
  if (!fTrigObjs) {
    SendError(kAbortAnalysis, "SlaveBegin", "Could not get HLT trigger objects table.");
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void HLTMod::SlaveTerminate()
{
  // Save number of accepted events.

  printf(" %s - Accepted events: %d (/%d)\n",GetName(),fNAccepted,fNEvents);
  SaveNEventsProcessed("hDHLTEvents");
}
