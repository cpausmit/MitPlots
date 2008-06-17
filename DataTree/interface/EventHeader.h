// $Id: DataObject.h,v 1.2 2008/06/11 13:48:37 loizides Exp $

#ifndef DATATREE_EVENTHEADER_H
#define DATATREE_EVENTHEADER_H
 
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// EventHeader
//
// 
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class EventHeader
  {
    public:
      EventHeader() : fRunNum(0), fEvtNum(0), fLumiSec(0) {}
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : fRunNum(run), fEvtNum(evt), fLumiSec(lumi) {}
      virtual ~EventHeader() {}

      UInt_t              EvtNum()       const { return fEvtNum; }
      UInt_t              LumiSec()      const { return fLumiSec; }
      UInt_t              RunNum()       const { return fRunNum; }

    protected:
      UInt_t              fRunNum;          // run number
      UInt_t              fEvtNum;          // event number
      UInt_t              fLumiSec;         // luminosity block number

      ClassDef(EventHeader, 1) // Event header class
  };
}
#endif
