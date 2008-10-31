// $Id: RefArray.cc,v 1.1 2008/07/29 10:36:21 loizides Exp $

#include "MitAna/DataCont/interface/ProcIDRef.h"

ClassImp(mithep::ProcIDRef)

//--------------------------------------------------------------------------------------------------
void mithep::ProcIDRef::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    //UInt_t sv, cv;
    //b.ReadVersion(&sv, &cv);
    //TObject::Streamer(b);
    UShort_t pidf;
    b >> pidf;
    pidf += b.GetPidOffset();
    fProcID = b.ReadProcessID(pidf);
    //b.CheckByteCount(sv, cv, ProcIDRef::IsA());
  } else { /*writing*/
    //UInt_t cv;
    //cv = b.WriteVersion(ProcIDRef::IsA(), kTRUE);
    //TObject::Streamer(b);
    UShort_t pidf;
    pidf = b.WriteProcessID(fProcID);
    b << pidf;
    //b.SetByteCount(cv, kTRUE);
  }
}
