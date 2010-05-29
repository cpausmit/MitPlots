//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.5 2009/03/12 18:19:47 loizides Exp $
//
// RunLumiSet
//
// Set of run,lumi pairs
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_RUNLUMISET_H
#define MITANA_DATACONT_RUNLUMISET_H
 
#include <TObject.h>
#include <set>

namespace mithep 
{
  class RunLumiSet : public TObject 
  {
    public:
      typedef std::pair<UInt_t,UInt_t> RunLumiPairType;
      typedef std::set<RunLumiPairType> SetType;
    
      RunLumiSet() {}

      void                         Add(const RunLumiPairType &runlumi)        { fSet.insert(runlumi); }
      UInt_t                       GetEntries()                        const  { return fSet.size();   }

    protected:
      SetType                      fSet;

    ClassDef(RunLumiSet, 1) // Base class of all our collections
  };
}
#endif
