// $Id: BaseCollection.cc,v 1.1 2008/07/29 10:36:21 loizides Exp $

#include "MitAna/DataCont/interface/BaseCollection.h"
#include <TClass.h>

ClassImp(mithep::BaseCollection)

//--------------------------------------------------------------------------------------------------
namespace {
  class BaseCollectionIgnoreTObject {
    public:
      BaseCollectionIgnoreTObject() {
        TClass *cls = TClass::GetClass("mithep::BaseCollection");
        if (cls) 
          cls->IgnoreTObjectStreamer();
      }
  };
  //DataCollectionIgnoreTObject dummy; //TODO enable for MIT_008 production
}
