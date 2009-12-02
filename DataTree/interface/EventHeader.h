//--------------------------------------------------------------------------------------------------
// $Id: EventHeader.h,v 1.17 2009/07/13 11:00:29 loizides Exp $
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
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class EventHeader : public DataBase
  {
    public:
      EventHeader();
      EventHeader(UInt_t run, UInt_t evt, UInt_t lumi);

      Int_t               BunchCrossing()     const { return fBunchCrossing; }
      Int_t               ExpType()           const { return fExpType;       }
      UInt_t              EvtNum()            const { return fEvtNum;        }
      Bool_t              IsMC()              const { return fIsMC;          }
      Bool_t              IsPhysDec()         const { return fIsPhysDec;     }
      UInt_t              LumiSec()           const { return fLumiSec;       }
      EObjType            ObjType()           const { return kEventHeader;   }
      Int_t               OrbitNumber()       const { return fOrbitNumber;   }
      Int_t               RunEntry()          const { return fRunEntry;      }
      UInt_t              RunNum()            const { return fRunNum;        }
      UChar_t             Skimmed()           const { return fSkimmed;       }
      Int_t               StoreNumber()       const { return fStoreNumber;   }
      ULong64_t           TimeStamp()         const { return fTimeStamp;     }
      Double_t            Weight()            const { return fWeight;        }
      void                SetBunchCrossing(Int_t b) { fBunchCrossing = b;    }
      void                SetEvtNum(UInt_t i)       { fEvtNum        = i;    }
      void                SetExpType(Int_t e)       { fExpType       = e;    }
      void                SetIsMC(Bool_t b)         { fIsMC          = b;    }
      void                SetLumiSec(UInt_t i)      { fLumiSec       = i;    }
      void                SetOrbitNumber(Int_t o)   { fOrbitNumber   = o;    }
      void                SetIsPhysDec(Bool_t b)    { fIsPhysDec     = b;    }
      void                SetRunEntry(Int_t i)      { fRunEntry      = i;    }
      void                SetRunNum(UInt_t i)       { fRunNum        = i;    }
      void                SetSkimmed(UChar_t s)     { fSkimmed       = s;    }
      void                SetStoreNumber(Int_t s)   { fStoreNumber   = s;    } 
      void                SetTimeStamp(ULong64_t t) { fTimeStamp     = t;    }
      void                SetWeight(Double_t w)     { fWeight        = w;    }

      Bool_t              operator!=(const EventHeader &other) const;
      Bool_t              operator==(const EventHeader &other) const;    
    
    protected:

      ULong64_t           fTimeStamp;       //time stamp of event (h32 -> sec, l32 -> musec)
      Int_t               fBunchCrossing;   //bunch crossing
      Int_t               fOrbitNumber;     //orbit number
      Int_t               fStoreNumber;     //store number
      UInt_t              fRunNum;          //run number
      UInt_t              fEvtNum;          //event number
      UInt_t              fLumiSec;         //luminosity block number
      Int_t               fRunEntry;        //entry for run block
      Double32_t          fWeight;          //event weight
      UChar_t             fExpType;         //experiment type (as assigned in EventAuxiliary)
      UChar_t             fSkimmed;         //level of skimming (0 == non-skimmed)
      Bool_t              fIsMC;            //==true if MC and not real data 
      Bool_t              fIsPhysDec;       //==true if physics declared

    ClassDef(EventHeader, 3) // Event header class
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
