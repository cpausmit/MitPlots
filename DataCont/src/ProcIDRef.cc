// $Id: ProcIDRef.cc,v 1.1 2008/10/31 18:56:14 bendavid Exp $

#include "MitAna/DataCont/interface/ProcIDRef.h"

ClassImp(mithep::ProcIDRef)

//--------------------------------------------------------------------------------------------------
void mithep::ProcIDRef::Streamer(TBuffer &b)
{
   // Custom streamer for the process id.

  if (b.IsReading()) {
    UShort_t pidf;
    b >> pidf;
    pidf += b.GetPidOffset();
    fProcID = b.ReadProcessID(pidf);
  } else { /*writing*/
    UShort_t pidf;
    pidf = b.WriteProcessID(fProcID);
    b << pidf;
  }
}
