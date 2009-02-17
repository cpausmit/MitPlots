//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.5 2008/12/09 17:46:59 loizides Exp $
//
// DaughterData
//
// Daughter decay information: Keep reference to original particle.
// 
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DAUGHTERDATA_H
#define MITANA_DATATREE_DAUGHTERDATA_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class DaughterData : public Particle
  {
    public:
      DaughterData() {}
      DaughterData(const Particle *orig) : fOriginal(orig) {}
      ~DaughterData() {}

      Double_t             Charge()                       const { return Original()->Charge();    }
      Bool_t               HasOriginal()                  const { return fOriginal.IsValid();     }
      Bool_t               HasOriginal(const Particle *p) const { return fOriginal.RefsObject(p); }
      EObjType             ObjType()                      const { return kDaughterData;           }
      const Particle      *Original()                     const { return fOriginal.Obj();         }

    protected:
      Ref<Particle>        fOriginal; //reference to original particle

    ClassDef(DaughterData, 1) // Daughter data class
  };
}
#endif
