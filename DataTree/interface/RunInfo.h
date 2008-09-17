//--------------------------------------------------------------------------------------------------
// $Id: RunInfo.h,v 1.5 2008/09/10 03:33:27 loizides Exp $
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
      RunInfo() : fRunNum(0), fL1Entry(0), fHltEntry(0) {}
      RunInfo(UInt_t run) : fRunNum(run) {}
      virtual ~RunInfo() {}

      Int_t               HltEntry()     const { return fHltEntry; }
      Int_t               L1Entry()      const { return fL1Entry; }
      UInt_t              RunNum()       const { return fRunNum; }
      void                SetL1Entry(Int_t i)  { fL1Entry=i; }
      void                SetHltEntry(Int_t i) { fHltEntry=i; }
      void                SetRunNum(UInt_t i)  { fRunNum=i; }

    protected:
      UInt_t              fRunNum;          //run number
      Int_t               fL1Entry;         //entry for L1 block
      Int_t               fHltEntry;        //entry for HLT block

    ClassDef(RunInfo, 1) // Run info class
  };
}
#endif

