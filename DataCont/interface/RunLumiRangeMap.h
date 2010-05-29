//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.5 2009/03/12 18:19:47 loizides Exp $
//
// RunLumiRangeMap
//
// Stores a list of map of run numbers to lists of lumi section ranges
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_RUNLUMIRANGEMAP_H
#define MITANA_DATACONT_RUNLUMIRANGEMAP_H

#include <string>
#include <vector>
#include <map>
#include <TObject.h>

namespace mithep 
{
  class RunLumiRangeMap : public TObject 
  { 
    public:
      typedef std::pair<UInt_t,UInt_t> RunLumiPairType;
      typedef std::map<UInt_t,std::vector<RunLumiPairType> > MapType;
      
      RunLumiRangeMap() {}

      void                         AddJSONFile(const std::string &filepath);
      void                         DumpJSONFile(const std::string &filepath);
      Bool_t                       HasRunLumi(const RunLumiPairType &runLumi) const;

    protected:
      MapType                      fMap; //mapped run-lumi ranges to accept

    ClassDef(RunLumiRangeMap, 1) // Base class of all our collections
  };
}
#endif
