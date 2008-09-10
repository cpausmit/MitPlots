//--------------------------------------------------------------------------------------------------
// $Id: RunInfo.h,v 1.4 2008/07/08 14:41:01 loizides Exp $
//
// RunInfo
//
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_RUNINFO_H
#define MITANA_DATATREE_RUNINFO_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class RunInfo
  {
    public:
      RunInfo() : fRunNum(0) {}
      RunInfo(UInt_t run) : fRunNum(run) {}
      virtual ~RunInfo() {}

      UInt_t              RunNum()       const { return fRunNum; }
      void                SetRunNum(UInt_t i)  { fRunNum=i; }

    protected:
      UInt_t              fRunNum; //run number
      
    ClassDef(RunInfo, 1) // Run info class
  };
}
#endif
