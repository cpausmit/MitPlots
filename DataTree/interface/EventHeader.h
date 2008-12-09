//--------------------------------------------------------------------------------------------------
// $Id: EventHeader.h,v 1.9 2008/12/03 17:37:19 loizides Exp $
//
// EventHeader
//
// Class to hold event specific information. If IsRemoved() returns kTRUE then the event
// content has been removed from events tree, and only meta information for book keeping
// purposes have been kept. This is used in conjunction with skimming.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_EVENTHEADER_H
#define DATATREE_EVENTHEADER_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class EventHeader : public DataBase
  {
    public:
      EventHeader() : fRunNum(0), fEvtNum(0), fLumiSec(0), fRunEntry(-1), fIsRemoved(0) {}
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : 
        fRunNum(run), fEvtNum(evt), fLumiSec(lumi), fRunEntry(-1), fIsRemoved(0)        {}
      ~EventHeader() {}

      UInt_t              EvtNum()          const { return fEvtNum;      }
      Bool_t              IsRemoved()       const { return fIsRemoved;   }
      UInt_t              LumiSec()         const { return fLumiSec;     }
      EObjType            ObjType()         const { return kEventHeader; }
      Int_t               RunEntry()        const { return fRunEntry;    }
      UInt_t              RunNum()          const { return fRunNum;      }
      void                SetEvtNum(UInt_t i)     { fEvtNum=i;           }
      void                SetIsRemoved(Bool_t b)  { fIsRemoved = b;      }
      void                SetLumiSec(UInt_t i)    { fLumiSec=i;          }
      void                SetRunEntry(Int_t i)    { fRunEntry=i;         }
      void                SetRunNum(UInt_t i)     { fRunNum=i;           }

    protected:
      UInt_t              fRunNum;          //run number
      UInt_t              fEvtNum;          //event number
      UInt_t              fLumiSec;         //luminosity block number
      Int_t               fRunEntry;        //entry for run block
      Bool_t              fIsRemoved;       //=true if event content was removed (skimming) 

    ClassDef(EventHeader, 2) // Event header class
  };
}
#endif
