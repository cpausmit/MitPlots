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
  fAcceptAll(kFALSE),
  fNEvents(0),
  fNAcceped(0),
  fNFailed(0),
  fAcceptCurrentRunLumi(kFALSE),
  fRunLumiGraph(0)
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
    if (fAcceptAll || (fAcceptMC && GetEventHeader()->IsMC())) {
      fAcceptCurrentRunLumi = kTRUE;
    }
    else {
      fAcceptCurrentRunLumi = fAcceptedRunsLumis.HasRunLumi(runLumi);
    }
    fCurrentRunLumi = runLumi;
    if (fAcceptCurrentRunLumi) {
      fRunLumiSet.Add(runLumi);
    }
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

//   fRunLumiVector = new RunLumiVector;
//   fRunLumiVector->SetName("ProcessedRunsLumis");
//   AddOutput(fRunLumiVector);

}

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::SlaveTerminate()
{
  // Save number of accepted events.

  const RunLumiSet::SetType &theset = fRunLumiSet.runLumiSet();

  UInt_t setSize = theset.size();
  Double_t *runArray = new Double_t[setSize];
  Double_t *lumiArray = new Double_t[setSize];
  
  UInt_t arrayPos = 0;
  for (RunLumiSet::SetType::const_iterator it = theset.begin(); it!=theset.end(); ++it) {
    printf("first = %u, second = %u\n",it->first,it->second);
    runArray[arrayPos] = it->first;
    lumiArray[arrayPos] = it->second;
    ++arrayPos;
  }

  fRunLumiGraph = new TGraph(setSize,runArray,lumiArray);
  fRunLumiGraph->SetName("ProcessedRunsLumis");
  AddOutput(fRunLumiGraph);
  
  delete runArray;
  delete lumiArray;
  
  SaveNEventsProcessed();
}

//--------------------------------------------------------------------------------------------------
void RunLumiSelectionMod::AddJSONFile(const std::string &filepath) 
{
  //pass JSON file to map object
  fAcceptedRunsLumis.AddJSONFile(filepath);
}
