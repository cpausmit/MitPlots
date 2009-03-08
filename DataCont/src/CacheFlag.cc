// $Id: CacheFlag.cc,v 1.2 2009/02/18 15:38:55 loizides Exp $

#include "MitAna/DataCont/interface/CacheFlag.h"

ClassImp(mithep::CacheFlag)

//--------------------------------------------------------------------------------------------------
void mithep::CacheFlag::Streamer(TBuffer &b)
{
   // Custom streamer for the cache flag. Nothing is actually read or written from/to the buffer,
   // but the cache flag is set to false in the read part of the streamer. This guarantees the 
   // default value is set even when an object containing the CacheFlag is read into a TClonesArray.

  if (b.IsReading())
    fIsValid = kFALSE;
}
