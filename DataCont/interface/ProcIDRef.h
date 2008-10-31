//--------------------------------------------------------------------------------------------------
// $Id: ProcIDRef.h,v 1.5 2008/10/02 14:00:02 bendavid Exp $
//
// ProcIDRef
//
// Implementation of a TProcIDRef using stack (and not heap) memory.
// For various reasons, the array can not be written in split mode.
// Maximum size of references is set to 1024 (but this could be 
// changed if there is need for it).
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
      ProcIDRef();
      ProcIDRef(TProcessID *pid) : fProcID(pid) {}
      ~ProcIDRef() { fProcID = 0; }

      TProcessID               *Pid()                   const { return fProcID; }
      void                      SetPid(TProcessID *pid)       { fProcID = pid; }
      
    protected:
      TProcessID               *fProcID;      //!ptr to Process Unique Identifier

    ClassDef(ProcIDRef,1) // Implementation of our own TProcIDRef
  };
}

//--------------------------------------------------------------------------------------------------
inline mithep::ProcIDRef::ProcIDRef()
{
   // Default constructor.
}
#endif
