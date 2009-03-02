// $Id: BaseCollection.cc,v 1.2 2008/12/10 11:25:30 loizides Exp $

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
  BaseCollectionIgnoreTObject dummy;
}
