// $Id: DataObject.cc,v 1.1 2008/06/04 09:08:36 loizides Exp $

#include "MitAna/DataTree/interface/DataBase.h"
#include <TClass.h>

ClassImp(mithep::DataBase)


//--------------------------------------------------------------------------------------------------
namespace {
  class DataBaseIgnoreTObject {
    public:
      DataBaseIgnoreTObject() {
        TClass *cls = TClass::GetClass("mithep::DataBase");
        cls->IgnoreTObjectStreamer();
      }
  };
  DataBaseIgnoreTObject dummy;
}
