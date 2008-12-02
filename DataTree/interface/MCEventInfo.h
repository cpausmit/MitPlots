//--------------------------------------------------------------------------------------------------
// $Id: MCEventInfo.h,v 1.3 2008/09/17 04:21:17 loizides Exp $
//
// MCEventInfo
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCEVENTINFO_H
#define MITANA_DATATREE_MCEVENTINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class MCEventInfo : public DataBase
  {
    public:
      MCEventInfo(Double_t w=0) : fWeight(w)  {}
      virtual ~MCEventInfo() {}

      Double_t            Weight()              const { return fWeight; }
      void                SetWeight(Double_t w)       { fWeight=w; }

    protected:
      Double32_t          fWeight;              //event weight
      
    ClassDef(MCEventInfo, 1) // Monte-Carlo event info class
  };
}
#endif
