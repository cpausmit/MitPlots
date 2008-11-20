//--------------------------------------------------------------------------------------------------
// $Id: ProcIDRef.h,v 1.1 2008/10/31 18:56:14 bendavid Exp $
//
// ProcIDRef
//
// Implementation of a process id that can be used in the
// StackArray (and then used in the RefArray).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_PROCIDREF
#define MITANA_DATACONT_PROCIDREF

#include <TObject.h>
#include <TProcessID.h>

namespace mithep 
{
  class ProcIDRef : public TObject
  {
    public:
      ProcIDRef() {};
      ProcIDRef(TProcessID *pid) : fProcID(pid) {}
      ~ProcIDRef() { fProcID = 0; }

      TProcessID        *Pid()                   const { return fProcID; }
      void               SetPid(TProcessID *pid)       { fProcID = pid; }
      
    protected:
      TProcessID        *fProcID; //!ptr to the Process Unique Identifier

    ClassDef(ProcIDRef,1) // Implementation of our own TProcIDRef
  };
}
#endif
