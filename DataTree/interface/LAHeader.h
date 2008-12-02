//--------------------------------------------------------------------------------------------------
// $Id: LAHeader.h,v 1.3 2008/09/10 03:33:26 loizides Exp $
//
// LAHeader
//
// Look-ahead header information in a very compressed way. Just enough information to figure
// out if the run ends. This class is stored in a dedicated tree.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_LAHEADER_H
#define MITANA_DATATREE_LAHEADER_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class LAHeader : public DataBase
  {
    public:
      LAHeader() : fRunNum(0) {}
      LAHeader(UInt_t run) : fRunNum(run) {}
      virtual ~LAHeader() {}

      UInt_t              RunNum()       const { return fRunNum; }
      void                SetRunNum(UInt_t i)  { fRunNum=i; }

    protected:
      UInt_t              fRunNum;          //run number
      
    ClassDef(LAHeader, 2) // Look-ahead event header class
  };
}
#endif
