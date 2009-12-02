// $Id: EventHeader.cc,v 1.2 2009/07/06 13:37:40 loizides Exp $

#include "MitAna/DataTree/interface/EventHeader.h"

ClassImp(mithep::EventHeader)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
EventHeader::EventHeader() : 
  fTimeStamp(0), fBunchCrossing(-1), fOrbitNumber(-1), fStoreNumber(-1),
  fRunNum(0), fEvtNum(0), fLumiSec(0), fRunEntry(-1), fWeight(1), 
  fExpType(0), fSkimmed(0), fIsMC(kTRUE), fIsPhysDec(kFALSE) 
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
EventHeader::EventHeader(UInt_t run, UInt_t evt, UInt_t lumi) : 
  fTimeStamp(0), fBunchCrossing(-1), fOrbitNumber(-1), fStoreNumber(-1),
  fRunNum(run), fEvtNum(evt), fLumiSec(lumi), fRunEntry(-1), fWeight(1), 
  fExpType(0), fSkimmed(0), fIsMC(kTRUE) , fIsPhysDec(kFALSE)
{
  // Constructor.
}
