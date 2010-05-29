// $Id: RunLumiSelectionMod.cc,v 1.2 2010/05/06 17:30:17 bendavid Exp $

#include "MitAna/PhysicsMod/interface/RunLumiSelectionMod.h"
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::RunLumiSelectionMod)

//--------------------------------------------------------------------------------------------------
RunLumiSelectionMod::RunLumiSelectionMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fAbort(kTRUE),
  fAcceptMC(kFALSE),
  fNEvents(0),
  fNAcceped(0),
  fNFailed(0),
  fAcceptCurrentRunLumi(kFALSE)
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
  
}

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::Process()
{
  // Increment counters and stop further processing of an event if current run is excluded

  ++fNEvents; 

  RunLumiPairType runLumi(GetEventHeader()->RunNum(),GetEventHeader()->LumiSec());

  //check decision only if lumi section has changed
  if (runLumi != fCurrentRunLumi) {
    fAcceptCurrentRunLumi = kFALSE;
    //check for MC default accept
    if (fAcceptMC && GetEventHeader()->IsMC()) {
      fAcceptCurrentRunLumi = kTRUE;
    }
    else {
      fAcceptCurrentRunLumi = fAcceptedRunsLumis.HasRunLumi(runLumi);
    }
    fCurrentRunLumi = runLumi;
    if (0) {
      printf("Run %u, Lumi %u, accepted = %i\n",runLumi.first,runLumi.second,fAcceptCurrentRunLumi);
    }
  }

  // take action if failed
  if (!fAcceptCurrentRunLumi) {
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

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::AddJSONFile(const std::string &filepath) 
{
  //pass JSON file to map object
  fAcceptedRunsLumis.AddJSONFile(filepath);
}
