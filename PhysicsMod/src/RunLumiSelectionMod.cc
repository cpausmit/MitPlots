// $Id: RunLumiSelectionMod.cc,v 1.1 2010/05/03 11:36:01 bendavid Exp $

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
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
      //check if run is included
      MapType::const_iterator it = fAcceptedRunsLumis.find(runLumi.first);
      if (it!=fAcceptedRunsLumis.end()) {
        //check lumis
        const MapType::mapped_type &lumiPairList = it->second;
        for (MapType::mapped_type::const_iterator jt = lumiPairList.begin(); jt<lumiPairList.end(); ++jt) {
          if (runLumi.second >= jt->first && runLumi.second <= jt->second) {
            //found lumi in accepted range
            fAcceptCurrentRunLumi = kTRUE;
          }
        }
      }
      else {
        //run not in JSON file, reject it
        fAcceptCurrentRunLumi = kFALSE;
      }
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

  //read json file into boost property tree
  boost::property_tree::ptree jsonTree;
  boost::property_tree::read_json(filepath,jsonTree);
  
  //loop through boost property tree and fill the MapType structure with the list of good lumi
  //ranges for each run
  for (boost::property_tree::ptree::const_iterator it = jsonTree.begin(); it!=jsonTree.end(); ++it) {
    UInt_t runNumber = boost::lexical_cast<UInt_t>(it->first);
    MapType::mapped_type &lumiPairList = fAcceptedRunsLumis[runNumber];
    boost::property_tree::ptree lumiPairListTree = it->second;
    for (boost::property_tree::ptree::const_iterator jt = lumiPairListTree.begin(); jt!=lumiPairListTree.end(); ++jt) {
      boost::property_tree::ptree lumiPairTree = jt->second;
      if (lumiPairTree.size()==2) {
        UInt_t firstLumi = boost::lexical_cast<UInt_t>(lumiPairTree.begin()->second.data());
        UInt_t lastLumi = boost::lexical_cast<UInt_t>((++lumiPairTree.begin())->second.data());
        lumiPairList.push_back(std::pair<UInt_t,UInt_t>(firstLumi,lastLumi));
      }
    }
  }

  //dump run and lumi ranges from MapType structure to verify correct json parsing
  if (0) {
    printf("Iterating over parsed JSON:\n");
    for (MapType::const_iterator it = fAcceptedRunsLumis.begin(); it != fAcceptedRunsLumis.end(); ++it) {
      printf("  Run %u:\n",it->first);
      for (MapType::mapped_type::const_iterator jt = it->second.begin(); jt < it->second.end(); ++jt) {
        printf("    Lumis %u - %u\n",jt->first,jt->second);
      }
    }

  }

}
