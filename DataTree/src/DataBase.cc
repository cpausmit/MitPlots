// $Id: DataBase.cc,v 1.1 2008/12/02 09:30:11 loizides Exp $

#include "MitAna/DataTree/interface/DataBase.h"
#include <TClass.h>

ClassImp(mithep::DataBase)

//--------------------------------------------------------------------------------------------------
namespace {
  class DataBaseIgnoreTObject {
    public:
      DataBaseIgnoreTObject() {
        TClass *cls = TClass::GetClass("mithep::DataBase");
        if (cls) 
          cls->IgnoreTObjectStreamer();
      }
  };
  DataBaseIgnoreTObject dummy;
}
