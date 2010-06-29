//--------------------------------------------------------------------------------------------------
// $Id: RunLumiRangeMap.h,v 1.1 2010/05/29 18:10:14 bendavid Exp $
//
// RunLumiRangeMap
//
// Stores a list of map of run numbers to lists of lumi section ranges
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_RUNLUMIRANGEMAP_H
#define MITANA_DATACONT_RUNLUMIRANGEMAP_H

#include <string>
#include <vector>
#include <map>
#include <TObject.h>
#include "MitAna/DataCont/interface/RunLumiSet.h"

namespace mithep 
{
  class RunLumiRangeMap : public TObject 
  { 
    public:
      typedef std::pair<UInt_t,UInt_t> RunLumiPairType;
      typedef std::map<UInt_t,std::vector<RunLumiPairType> > MapType;
      
      RunLumiRangeMap() {}
      RunLumiRangeMap(const RunLumiSet &rlset) { FillRunLumiSet(rlset); }

      void                         AddJSONFile(const std::string &filepath);
      void                         DumpJSONFile(const std::string &filepath);
      Bool_t                       HasRunLumi(const RunLumiPairType &runLumi) const;

    protected:
      void                         FillRunLumiSet(const RunLumiSet &rlSet);

      MapType                      fMap; //mapped run-lumi ranges to accept

    ClassDef(RunLumiRangeMap, 1) // Base class of all our collections
  };
}
#endif
