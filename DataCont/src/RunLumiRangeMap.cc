// $Id: RunLumiRangeMap.cc,v 1.1 2010/05/29 18:10:14 bendavid Exp $

#include "MitAna/DataCont/interface/RunLumiRangeMap.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include "MitCommon/JSONSpirit/src/json_spirit.h"
#include <TClass.h>

ClassImp(mithep::RunLumiRangeMap)

//--------------------------------------------------------------------------------------------------
Bool_t mithep::RunLumiRangeMap::HasRunLumi(const RunLumiPairType &runLumi) const
{
  // Check if a given run,lumi pair is included in the mapped lumi ranges

  //check if run is included in the map
  MapType::const_iterator it = fMap.find(runLumi.first);
  if (it!=fMap.end()) {
    //check lumis
    const MapType::mapped_type &lumiPairList = it->second;
    for (MapType::mapped_type::const_iterator jt = lumiPairList.begin(); jt<lumiPairList.end(); ++jt) {
      if (runLumi.second >= jt->first && runLumi.second <= jt->second) {
        //found lumi in accepted range
        return kTRUE;
      }
    }
  }

  return kFALSE;

}

//--------------------------------------------------------------------------------------------------
void mithep::RunLumiRangeMap::AddJSONFile(const std::string &filepath) 
{

  //read json file into boost property tree
  boost::property_tree::ptree jsonTree;
  boost::property_tree::read_json(filepath,jsonTree);
  
  //loop through boost property tree and fill the MapType structure with the list of good lumi
  //ranges for each run
  for (boost::property_tree::ptree::const_iterator it = jsonTree.begin(); it!=jsonTree.end(); ++it) {
    UInt_t runNumber = boost::lexical_cast<UInt_t>(it->first);
    MapType::mapped_type &lumiPairList = fMap[runNumber];
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
    for (MapType::const_iterator it = fMap.begin(); it != fMap.end(); ++it) {
      printf("  Run %u:\n",it->first);
      for (MapType::mapped_type::const_iterator jt = it->second.begin(); jt < it->second.end(); ++jt) {
        printf("    Lumis %u - %u\n",jt->first,jt->second);
      }
    }

  }

}

//--------------------------------------------------------------------------------------------------
void mithep::RunLumiRangeMap::DumpJSONFile(const std::string &filepath) 
{

  json_spirit::Object jsonTree;
  
  for (MapType::const_iterator it = fMap.begin(); it!=fMap.end(); ++it) {
    UInt_t runnum  = it->first;
    json_spirit::Array lumiPairListArray;
    const MapType::mapped_type &lumiPairList = it->second;
    for (MapType::mapped_type::const_iterator jt = lumiPairList.begin(); jt<lumiPairList.end(); ++jt) {
      json_spirit::Array lumiPairArray;
      lumiPairArray.push_back(int(jt->first));
      lumiPairArray.push_back(int(jt->second));
      
      lumiPairListArray.push_back(lumiPairArray);
    }
    json_spirit::Pair runPair(boost::lexical_cast<std::string>(runnum), lumiPairListArray);
    jsonTree.push_back(runPair);
  } 

  std::ofstream os(filepath.c_str());
  json_spirit::write(jsonTree,os);
 
}

//--------------------------------------------------------------------------------------------------
void mithep::RunLumiRangeMap::FillRunLumiSet(const RunLumiSet &rlSet)
{
  fMap.clear();
  const RunLumiSet::SetType &theset = rlSet.runLumiSet();

  UInt_t firstlumi = 0;
  for (RunLumiSet::SetType::const_iterator it = theset.begin(); it!=theset.end(); ++it) {

    if (firstlumi==0) firstlumi = it->second;
    MapType::mapped_type &lumiPairList = fMap[it->first];

    RunLumiSet::SetType::const_iterator itnext = it;
    ++itnext;

    if ( itnext==theset.end() || itnext->first!=it->first || itnext->second!=(it->second+1) ) {
      lumiPairList.push_back(std::pair<UInt_t,UInt_t>(firstlumi,it->second));
      firstlumi = 0;
    }
    
  }
}
