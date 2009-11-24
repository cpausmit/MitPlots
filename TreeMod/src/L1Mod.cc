// $Id: L1Mod.cc,v 1.1 2009/11/24 14:27:33 loizides Exp $

#include "MitAna/TreeMod/interface/L1Mod.h"
#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/L1TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"

using namespace mithep;

ClassImp(mithep::L1Mod)

//--------------------------------------------------------------------------------------------------
L1Mod::L1Mod(const char *name, const char *title) : 
  BaseMod(name,title),
  fAbort(kTRUE),
  fPrintTable(kFALSE),
  fIgnoreBits(kFALSE),
  fBitsName(Names::gkL1TechBitsBrn),
  fBits(0),
  fTriggers(0),
  fNEvents(0),
  fNAcceped(0),
  fNFailed(0)
{
  // Constructor. 
}

//--------------------------------------------------------------------------------------------------
L1Mod::~L1Mod() 
{
  // Destructor.
}

//--------------------------------------------------------------------------------------------------
void L1Mod::AddTrigger(const char *expr)
{
  // Add trigger search pattern to the list of patters. Each element of the list is logically 
  // "ored". The given expression can contain several trigger names logically "anded" (using "&"). 
  // A "!" infront of a trigger name negates the bit. For example, valid expressions are:
  // "A", "!A", "A&B", "A&!B" or "A&B&C"  

  string tname(expr);
  fTrigNames.push_back(tname);
}

//--------------------------------------------------------------------------------------------------
void L1Mod::BeginRun()
{
  // Get L1 tree and set branches. Compute bitmasks to be used when comparing to the L1 bits.

  fTrigBitsAnd.clear();
  fTrigBitsCmp.clear();

  if (fPrintTable) 
    fTriggers->Print();

  for (UInt_t i=0; i<fTrigNames.size(); ++i) {
    BitMask64 tmask; //trigger mask
    BitMask64 amask; //bitand mask
    TString names(fTrigNames.at(i).c_str());

    TObjArray *arr = names.Tokenize("&");
    if (arr) {
      for(Int_t j=0; j<arr->GetEntries(); j++){
        TObjString *s = dynamic_cast<TObjString*>(arr->At(j));
        if (!s) 
          continue;
        const char *sptr = s->GetString().Data();
        Bool_t invert = kFALSE;
        if (sptr[0] == '!') { 
          invert = kTRUE; //inverted bit set
          ++sptr;
        }
        const TriggerName *tn = fTriggers->Get(sptr);
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
void L1Mod::Process()
{
  // Process trigger bits for this event. If trigger bits pass the given bit mask, then obtain
  // and publish the corresponding trigger objects. If OnAccepted or OnFailed is implemented
  // in a derived class, call it. Do not stop processing this event, if fAbort is kFALSE.

  ++fNEvents; 
  LoadBranch(fBitsName);

  // match trigger bits to trigger mask
  fBitsDone.Clear();
  Bool_t accept = kFALSE;
  for (UInt_t i = 0; i<fTrigBitsAnd.size(); ++i) {
    BitMask64 bitmask(fBits->Get());
    bitmask &= fTrigBitsAnd.at(i);
    if (bitmask==fTrigBitsCmp.at(i)) {
      accept = kTRUE;
    }
  }

  // take action if failed
  if (!accept) {
    ++fNFailed;
    OnFailed();
    if (fAbort) {
      SkipEvent(); // abort processing of this event by sub-modules
    }
    return;
  } 

  // take action if accepted
  ++fNAcceped;
  IncNEventsProcessed();
  OnAccepted();
}

//--------------------------------------------------------------------------------------------------
void L1Mod::SlaveBegin()
{
  // Request trigger bit branch and obtain trigger table and objects.

  ReqBranch(fBitsName, fBits);
  
  if (fBitsName.Contains("Algo"))
    fTriggers = GetL1AlgoTable();
  else
    fTriggers = GetL1TechTable();

  if (!fTriggers) {
    SendError(kAbortAnalysis, "SlaveBegin", "Could not get HLT trigger table.");
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void L1Mod::SlaveTerminate()
{
  // Save number of accepted events.

  SaveNEventsProcessed("hDL1Events");
}
