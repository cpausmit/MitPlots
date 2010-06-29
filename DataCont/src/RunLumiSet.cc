// $Id: RunLumiSet.cc,v 1.1 2010/05/29 18:10:14 bendavid Exp $

#include "MitAna/DataCont/interface/RunLumiSet.h"
#include "MitAna/DataCont/interface/RunLumiRangeMap.h"
#include <TClass.h>

ClassImp(mithep::RunLumiSet)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
mithep::RunLumiSet::RunLumiSet(const TGraph &graph)
{
  for (Int_t i=0; i<graph.GetN(); ++i) {
    Double_t run;
    Double_t lumi;
    graph.GetPoint(i,run,lumi);
    fSet.insert(RunLumiPairType(run,lumi));
  }
  
}

//--------------------------------------------------------------------------------------------------
Long64_t mithep::RunLumiSet::Merge(TCollection *list)
{
  Long64_t nmerged = 0;
  TIter iter(list);
  TObject *obj = 0;
  while( (obj=iter.Next()) ) {
    const RunLumiSet *mergeset = dynamic_cast<const RunLumiSet*>(obj);
    if (mergeset) {
      fSet.insert(mergeset->runLumiSet().begin(), mergeset->runLumiSet().end());
      nmerged++;
    }
  }

  return nmerged;

}

//--------------------------------------------------------------------------------------------------
void mithep::RunLumiSet::DumpJSONFile(const std::string &filepath) 
{

  RunLumiRangeMap rlmap(*this);
  rlmap.DumpJSONFile(filepath);

}
