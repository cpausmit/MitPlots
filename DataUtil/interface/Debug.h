//--------------------------------------------------------------------------------------------------
// $Id: Debug.h,v 1.7 2008/07/08 05:51:29 loizides Exp $
//
// Debug - detailed logging / debug scheme
//
// This class defines the debuging masks (EDebugMask), which are used with the MDB (MIT DeBug) 
// macro together with the log levels to control the verbosity. For example you can do in 
// your code:
//
//  MDB(kAnalysis, 2)
//    Info("AddFile", "Added %s to list of files.", pname);
// 
// This will printout the Info message provided that the gDebugLevel is >=2 (and provided
// the gDebugMask contains the kAnalysis bit.
//
// As a rule of thumb:
//    level 1 and 2 should not be used in (event) loops, level 3 and 4 might be used in loops.
//
// Please, do not introduce more levels!
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATAUTIL_DEBUG_H
#define MITANA_DATAUTIL_DEBUG_H

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
