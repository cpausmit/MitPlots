//--------------------------------------------------------------------------------------------------
// ProcIDRef
//
// Implementation of a process id that can be stored in the FastArray (and then used in the
// RefArray).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_PROCIDREF_H
#define MITANA_DATACONT_PROCIDREF_H

#include <TObject.h>
#include <TProcessID.h>

namespace mithep 
{
  class ProcIDRef : public TObject {
  public:
    ProcIDRef() : fProcID(0) {}
    ProcIDRef(ProcIDRef const& orig) : TObject(orig), fProcID(orig.fProcID) {}
    ProcIDRef(TProcessID *pid) : fProcID(pid) {}
    ~ProcIDRef() {}

    ProcIDRef& operator=(ProcIDRef const& rhs) {
      fProcID = rhs.fProcID;
      return *this;
    }

    TProcessID* Pid() const { return fProcID; }
    void SetPid(TProcessID* pid) { fProcID = pid;  }

  protected:
    TProcessID* fProcID; //!ptr to the Process Unique Identifier

    ClassDef(ProcIDRef, 1) // Implementation of our own TProcIDRef
  };
}
#endif
