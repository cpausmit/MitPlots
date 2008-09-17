//--------------------------------------------------------------------------------------------------
// $Id: MCEventInfo.h,v 1.2 2008/09/10 03:33:26 loizides Exp $
//
// MCEventInfo
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCEVENTINFO_H
#define MITANA_DATATREE_MCEVENTINFO_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class MCEventInfo
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
