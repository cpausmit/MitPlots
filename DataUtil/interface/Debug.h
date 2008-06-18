//--------------------------------------------------------------------------------------------------
// $Id: Debug.h,v 1.3 2008/06/11 13:27:48 loizides Exp $
//
// Debug
//
// Detailed logging / debug scheme:
//   This class defines the debuging masks (EDebugMask), which
//   are used with the MDB (MIT DeBug) macro together with
//   the log levels to control the verbosity.
//   As a rule of thumb:
//    level 1 and 2 should not be used in (event) loops,
//    level 3 and 4 might be used in loops.
//  Please, do not introduce more levels!
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

#ifndef DATAUTIL_DEBUG_H
#define DATAUTIL_DEBUG_H

#include <Rtypes.h>
#include <TError.h>

namespace mithep 
{
  class Debug 
  {
    public:
      enum EDebugMask {
        kNone          = 0,
        kGeneral       = 1,
        kTreeIO        = 2,
        kAnalysis      = 4,
        kModules       = 8,
        kAll           = 0xFFFFFFFF
      };
   private:
     Debug();
     virtual ~Debug() {}
     Debug(const Debug &cpy);

     ClassDef(Debug, 0) // Defines different debug masks

  }; 

}

R__EXTERN mithep::Debug::EDebugMask gDebugMask;
R__EXTERN Int_t gDebugLevel;

#define MDB(mask,level) \
   if ((mithep::Debug::mask & gDebugMask) && gDebugLevel >= (level))

#define MitAssert(f,e) \
        if (!(e)) Fatal(f, kAssertMsg, _QUOTE_(e), __LINE__, __FILE__)

#define MitAssertStatic(f,e) \
        if (!(e)) ::Fatal(f, kAssertMsg, _QUOTE_(e), __LINE__, __FILE__)

#endif
