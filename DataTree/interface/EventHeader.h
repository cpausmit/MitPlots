//--------------------------------------------------------------------------------------------------
// $Id: EventHeader.h,v 1.12 2009/02/18 15:38:54 loizides Exp $
//
// EventHeader
//
// Class to hold event specific information. If IsRemoved() returns kTRUE then the event
// content has been removed from events tree, and only meta information for book keeping
// purposes have been kept. This is used in conjunction with skimming.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_EVENTHEADER_H
#define MITANA_DATATREE_EVENTHEADER_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class EventHeader : public DataBase
  {
    public:
      EventHeader() : fRunNum(0), fEvtNum(0), fLumiSec(0), fRunEntry(-1), fSkimmed(0) {}
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : 
        fRunNum(run), fEvtNum(evt), fLumiSec(lumi), fRunEntry(-1), fSkimmed(0)        {}

      UInt_t              EvtNum()          const { return fEvtNum;      }
      UChar_t             Skimmed()         const { return fSkimmed;     }
      UInt_t              LumiSec()         const { return fLumiSec;     }
      EObjType            ObjType()         const { return kEventHeader; }
      Int_t               RunEntry()        const { return fRunEntry;    }
      UInt_t              RunNum()          const { return fRunNum;      }
      void                SetEvtNum(UInt_t i)     { fEvtNum=i;           }
      void                SetSkimmed(UChar_t s)   { fSkimmed = s;        }
      void                SetLumiSec(UInt_t i)    { fLumiSec=i;          }
      void                SetRunEntry(Int_t i)    { fRunEntry=i;         }
      void                SetRunNum(UInt_t i)     { fRunNum=i;           }

    protected:
      UInt_t              fRunNum;          //run number
      UInt_t              fEvtNum;          //event number
      UInt_t              fLumiSec;         //luminosity block number
      Int_t               fRunEntry;        //entry for run block
      UChar_t             fSkimmed;         //level of skimming (0 == non-skimmed)

    ClassDef(EventHeader, 1) // Event header class
  };
}
#endif
