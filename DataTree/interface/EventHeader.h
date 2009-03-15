//--------------------------------------------------------------------------------------------------
// $Id: EventHeader.h,v 1.13 2009/03/11 10:00:51 loizides Exp $
//
// EventHeader
//
// Class to hold event specific information. If Skimmed() returns value > 0 then the event
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
      EventHeader() : fRunNum(0), fEvtNum(0), fLumiSec(0), fRunEntry(-1), 
                      fWeight(1), fSkimmed(0), fIsMC(kTRUE) {}
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : 
        fRunNum(run), fEvtNum(evt), fLumiSec(lumi), fRunEntry(-1),
        fWeight(1), fSkimmed(0), fIsMC(kTRUE) {}

      UInt_t              EvtNum()          const { return fEvtNum;      }
      Bool_t              IsMC()              const { return fIsMC;      }
      UInt_t              LumiSec()         const { return fLumiSec;     }
      EObjType            ObjType()         const { return kEventHeader; }
      Int_t               RunEntry()        const { return fRunEntry;    }
      UInt_t              RunNum()          const { return fRunNum;      }
      UChar_t             Skimmed()         const { return fSkimmed;     }
      Double_t            Weight()          const { return fWeight;      }
      void                SetEvtNum(UInt_t i)     { fEvtNum=i;           }
      void                SetIsMC(Bool_t b)       {  fIsMC=b;            }
      void                SetLumiSec(UInt_t i)    { fLumiSec=i;          }
      void                SetRunEntry(Int_t i)    { fRunEntry=i;         }
      void                SetRunNum(UInt_t i)     { fRunNum=i;           }
      void                SetSkimmed(UChar_t s)   { fSkimmed = s;        }
      void                SetWeight(Double_t w)   { fWeight=w;           }
      Bool_t              operator!=(const EventHeader &other) const;
      Bool_t              operator==(const EventHeader &other) const;    
    
    protected:
      UInt_t              fRunNum;          //run number
      UInt_t              fEvtNum;          //event number
      UInt_t              fLumiSec;         //luminosity block number
      Int_t               fRunEntry;        //entry for run block
      Double32_t          fWeight;          //event weight
      UChar_t             fSkimmed;         //level of skimming (0 == non-skimmed)
      Bool_t              fIsMC;            //==true for MC data 

    ClassDef(EventHeader, 1) // Event header class
  };
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::EventHeader::operator!=(const mithep::EventHeader &other) const
{
  // Unequal operator.

  if (fEvtNum != other.EvtNum())
    return kTRUE;
  if (fLumiSec != other.LumiSec())
    return kTRUE;
  if (fRunNum != other.RunNum())
    return kTRUE;
  if(fIsMC != other.IsMC())
    return kTRUE;

  return kFALSE;
}    

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::EventHeader::operator==(const mithep::EventHeader &other) const
{
  // Equal operator.

  if (fEvtNum != other.EvtNum())
    return kFALSE;
  if (fLumiSec != other.LumiSec())
    return kFALSE;
  if (fRunNum != other.RunNum())
    return kFALSE;
  if(fIsMC != other.IsMC())
    return kFALSE;

  return kTRUE;
}    
#endif
