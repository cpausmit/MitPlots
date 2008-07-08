//--------------------------------------------------------------------------------------------------
// $Id: LAHeader.h,v 1.1 2008/06/24 14:01:41 loizides Exp $
//
// LAHeader
//
// Look-ahead header information in a very compressed way. Just enough information to figure
// out if the run ends.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_LAHEADER_H
#define DATATREE_LAHEADER_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class LAHeader
  {
    public:
      LAHeader() : fRunNum(0) {}
      LAHeader(UInt_t run) : fRunNum(run) {}
      virtual ~LAHeader() {}

      UInt_t              RunNum()       const { return fRunNum; }
      void                SetRunNum(UInt_t i)  { fRunNum=i; }

    protected:
      UInt_t              fRunNum;          //run number
      
    ClassDef(LAHeader, 1) // Look-ahead event header class
  };
}
#endif
