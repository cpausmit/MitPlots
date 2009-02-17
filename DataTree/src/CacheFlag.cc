// $Id: ProcIDRef.cc,v 1.2 2008/11/20 17:49:16 loizides Exp $

#include "MitAna/DataTree/interface/CacheFlag.h"

ClassImp(mithep::CacheFlag)

//--------------------------------------------------------------------------------------------------
void mithep::CacheFlag::Streamer(TBuffer &b)
{
   // Custom streamer for the cache flag.
   // Nothing is actually read or written from/to the buffer
   // but the bool is set to false in the read part of the streamer to guarantee this default value
   // is set even when an object containing the CacheFlag is read into a TClonesArray

  if (b.IsReading()) {
    fIsValid = kFALSE;
  } else { /*writing (do nothing in this case) */
    ;
  }
}
