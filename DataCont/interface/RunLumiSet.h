//--------------------------------------------------------------------------------------------------
// $Id: RunLumiSet.h,v 1.1 2010/05/29 18:10:14 bendavid Exp $
//
// RunLumiSet
//
// Set of run,lumi pairs
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_RUNLUMISET_H
#define MITANA_DATACONT_RUNLUMISET_H
 
#include <TNamed.h>
#include <TCollection.h>
#include <TGraph.h>
#include <set>

namespace mithep 
{
  class RunLumiSet : public TNamed 
  {
    public:
      typedef std::pair<UInt_t,UInt_t> RunLumiPairType;
      typedef std::set<RunLumiPairType> SetType;
    
      RunLumiSet() {}
      RunLumiSet(const TGraph &graph);

      void                         Add(const RunLumiPairType &runlumi)        { fSet.insert(runlumi); }
      void                         DumpJSONFile(const std::string &filepath);
      UInt_t                       GetEntries()                        const  { return fSet.size();   }
      const SetType               &runLumiSet()                        const  { return fSet;          }
      Long64_t                     Merge(TCollection *list);

    protected:
      SetType                      fSet;

    ClassDef(RunLumiSet, 1) // Base class of all our collections
  };
}
#endif
