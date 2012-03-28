//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.8 2009/07/13 11:00:25 loizides Exp $
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
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class DaughterData : public Particle
  {
    public:
      DaughterData() {}
      DaughterData(const Particle *orig) : fOriginal(orig) {}

      Double_t             Charge()                       const { return Original()->Charge();    }
      Bool_t               HasOriginal()                  const { return fOriginal.IsValid();     }
      Bool_t               HasOriginal(const Particle *p) const { return fOriginal.RefsObject(p); }
      EObjType             ObjType()                      const { return kDaughterData;           }
      const Particle      *Original()                     const { return fOriginal.Obj();         }

      // Some structural tools
      void                 Mark()                         const;

    protected:
      Ref<Particle>        fOriginal; //reference to original particle

    ClassDef(DaughterData, 1) // Daughter data class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DaughterData::Mark() const
{
  // mark myself
  mithep::DataObject::Mark();
  // mark my dependencies if they are there
  Original()->Mark();
}
#endif
