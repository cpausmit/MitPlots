//--------------------------------------------------------------------------------------------------
// $Id: EvtSelData.h,v $
//
// EvtSelData
//
// Class to store event properties on which one may want to select clean events.  This may be needed
// for early collision data only.
//
// Authors: C.Loizides, L.Di Matteo
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATATREE_EVENTSELDATA_H
#define MITANA_DATATREE_EVENTSELDATA_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class EvtSelData : public DataBase
  {
    public:
      EvtSelData() : 
        fMetFiltersWord(0) {}
    //      EvtSelData(Int_t metFiltersWord) :
    //        fMetFiltersWord(metFiltersWord) {}
      ~EvtSelData() {}

      Int_t    metFiltersWord()           const { return fMetFiltersWord; }
      void     SetFiltersWord(Int_t word)       { fMetFiltersWord = word; }

    protected:
      Int_t    fMetFiltersWord;  // word containing the bit-values of the MET filters

    ClassDef(EvtSelData, 4) // Event selection data
  };
}
#endif
