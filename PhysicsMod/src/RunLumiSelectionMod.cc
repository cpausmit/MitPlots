// $Id: RunLumiSelectionMod.cc,v 1.1 2010/01/18 14:35:43 bendavid Exp $

#include "MitAna/PhysicsMod/interface/RunLumiSelectionMod.h"
#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::RunLumiSelectionMod)

//--------------------------------------------------------------------------------------------------
RunLumiSelectionMod::RunLumiSelectionMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fAbort(kTRUE),
  fDefaultAccept(kFALSE),
  fNEvents(0),
  fNAcceped(0),
  fNFailed(0),
  fAcceptCurrentRun(kFALSE)
{
  // Constructor. 
}

//--------------------------------------------------------------------------------------------------
RunLumiSelectionMod::~RunLumiSelectionMod() 
{
  // Destructor.
}


//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::BeginRun()
{
  //Decide if this run should be accepted and cache decision.
  UInt_t run = GetRunInfo()->RunNum();
  Bool_t accepted = kFALSE;
  Bool_t excluded = kFALSE;
  
  //check if run is explicitly accepted
  for (UIntBounds::const_iterator it = fAcceptedRuns.begin(); it!=fAcceptedRuns.end(); ++it) {
    if (run>=it->first && run<=it->second) {
      accepted = kTRUE;
      break;
    }
  }
  
  //check if run is explicitly excluded
  for (UIntBounds::const_iterator it = fExcludedRuns.begin(); it!=fExcludedRuns.end(); ++it) {
    if (run>=it->first && run<=it->second) {
      excluded = kTRUE;
      break;
    }
  }
  
  //construct final decision
  fAcceptCurrentRun = (fDefaultAccept || accepted) && !excluded;
  
}

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::Process()
{
  // Increment counters and stop further processing of an event if current run is excluded

  ++fNEvents; 

  // take action if failed
  if (!fAcceptCurrentRun) {
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
void RunLumiSelectionMod::SlaveBegin()
{

}

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::SlaveTerminate()
{
  // Save number of accepted events.

  SaveNEventsProcessed();
}
