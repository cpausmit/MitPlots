#include "MitAna/PhysicsMod/interface/MCProcessSelectionMod.h"
#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::MCProcessSelectionMod)

//--------------------------------------------------------------------------------------------------
MCProcessSelectionMod::MCProcessSelectionMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fMCEventInfoName(Names::gkMCEvtInfoBrn),
  fAbort(kTRUE),
  fDefaultAccept(kTRUE),
  fNEvents(0),
  fNAcceped(0),
  fNFailed(0),
  hProcessId(0)
{
  // Constructor. 
}

//--------------------------------------------------------------------------------------------------
MCProcessSelectionMod::~MCProcessSelectionMod() 
{
  // Destructor.
}


//--------------------------------------------------------------------------------------------------
void MCProcessSelectionMod::BeginRun()
{
    
}

//--------------------------------------------------------------------------------------------------
void MCProcessSelectionMod::Process()
{
  // Increment counters and stop further processing of an event if current run is excluded

  ++fNEvents; 

  //accept by default
  if ( (fDefaultAccept && fExcludedProcessIds.size()==0) ) {
    ++fNAcceped;
    IncNEventsProcessed();
    OnAccepted();
    return;
  }

  auto* mcEventInfo = GetObject<MCEventInfo>(fMCEventInfoName);
  
  Int_t processid = mcEventInfo->ProcessId();
  hProcessId->Fill(processid);
  
  Bool_t accepted = kFALSE;
  Bool_t excluded = kFALSE;
  
  //check if process is explicitly accepted
  for (std::vector<Int_t>::const_iterator it = fAcceptedProcessIds.begin(); it!=fAcceptedProcessIds.end(); ++it) {
    if (processid == *it) {
      accepted = kTRUE;
      break;
    }
  }
  
  //check if process is explicitly excluded
  for (std::vector<Int_t>::const_iterator it = fExcludedProcessIds.begin(); it!=fExcludedProcessIds.end(); ++it) {
    if (processid == *it) {
      excluded = kTRUE;
      break;
    }
  }
  
  //construct final decision
  Bool_t fAcceptCurrentEvent = (fDefaultAccept || accepted) && !excluded;

  
  // take action if failed
  if (!fAcceptCurrentEvent) {
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
void MCProcessSelectionMod::SlaveBegin()
{

  hProcessId = new TH1F("hProcessId","hProcessId",501,-0.5,500.5);
  AddOutput(hProcessId);
}

//--------------------------------------------------------------------------------------------------
void MCProcessSelectionMod::SlaveTerminate()
{
  // Save number of accepted events.

  SaveNEventsProcessed();
}
