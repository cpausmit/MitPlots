//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.9 2012/03/28 12:15:34 paus Exp $
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
      void                 Mark(UInt_t i=1)               const;

    protected:
      Ref<Particle>        fOriginal; //reference to original particle

    ClassDef(DaughterData, 1) // Daughter data class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DaughterData::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fOriginal.IsValid())
    fOriginal.Obj()->Mark(ib);
}
#endif
