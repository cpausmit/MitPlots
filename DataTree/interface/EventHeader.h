//--------------------------------------------------------------------------------------------------
// $Id: EventHeader.h,v 1.4 2008/06/24 14:01:41 loizides Exp $
//
// EventHeader
//
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_EVENTHEADER_H
#define DATATREE_EVENTHEADER_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class EventHeader
  {
    public:
      EventHeader() : fRunNum(0), fEvtNum(0), fLumiSec(0) {}
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : 
        fRunNum(run), fEvtNum(evt), fLumiSec(lumi) {}
      virtual ~EventHeader() {}

      UInt_t              EvtNum()       const { return fEvtNum; }
      UInt_t              LumiSec()      const { return fLumiSec; }
      Int_t               RunEntry()     const { return fRunEntry; }
      UInt_t              RunNum()       const { return fRunNum; }

      void                SetEvtNum(UInt_t i)  { fEvtNum=i; }
      void                SetLumiSec(UInt_t i) { fLumiSec=i; }
      void                SetRunEntry(Int_t i) { fRunEntry=i; }
      void                SetRunNum(UInt_t i)  { fRunNum=i; }

    protected:
      UInt_t              fRunNum;          // run number
      UInt_t              fEvtNum;          // event number
      UInt_t              fLumiSec;         // luminosity block number
      Int_t               fRunEntry;        // entry for run block
      
    ClassDef(EventHeader, 1) // Event header class
  };
}
#endif
