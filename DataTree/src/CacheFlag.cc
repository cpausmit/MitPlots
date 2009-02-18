// $Id: CacheFlag.cc,v 1.1 2009/02/17 15:52:52 bendavid Exp $

#include "MitAna/DataTree/interface/CacheFlag.h"

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
