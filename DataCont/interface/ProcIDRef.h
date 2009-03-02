//--------------------------------------------------------------------------------------------------
// $Id: ProcIDRef.h,v 1.3 2008/12/10 11:26:52 loizides Exp $
//
// ProcIDRef
//
// Implementation of a process id that can be stored in the
// FastArray (and then used in the RefArray).
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
      ProcIDRef() : fProcID(0)                         {}
      ProcIDRef(TProcessID *pid) : fProcID(pid)        {}
      ~ProcIDRef()                                     { fProcID = 0;    }

      TProcessID        *Pid()                   const { return fProcID; }
      void               SetPid(TProcessID *pid)       { fProcID = pid;  }

    protected:
      TProcessID        *fProcID; //!ptr to the Process Unique Identifier

    ClassDef(ProcIDRef, 1) // Implementation of our own TProcIDRef
  };
}
#endif
