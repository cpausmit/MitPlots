// $Id: BaseCollection.cc,v 1.3 2009/03/02 12:34:00 loizides Exp $

#include "MitAna/DataCont/interface/RunLumiRangeMap.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
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

  //read json file into boost property tree
  boost::property_tree::ptree jsonTree;
  
  //loop through map and fill boost property tree
  for (MapType::const_iterator it = fMap.begin(); it!=fMap.end(); ++it) {
    UInt_t runnum  = it->first;
    //jsonTree.put(boost::lexical_cast<string>(runnum));
    //check lumis
    const MapType::mapped_type &lumiPairList = it->second;
    for (MapType::mapped_type::const_iterator jt = lumiPairList.begin(); jt<lumiPairList.end(); ++jt) {
      ;
    }
  }
  
  //write file
  boost::property_tree::write_json(filepath,jsonTree);

}