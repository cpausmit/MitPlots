//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.4 2008/12/03 17:37:46 loizides Exp $
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

namespace mithep 
{
  class DaughterData : public Particle
  {
    public:
      DaughterData() {}
      DaughterData(const Particle *orig) : fOriginal(const_cast<Particle*>(orig)) {}
      ~DaughterData() {}

      Double_t             Charge()    const { return Original()->Charge(); }
      EObjType             ObjType()   const { return kDaughterData;        }
      const Particle      *Original()  const;

    protected:
      TRef                 fOriginal; //reference to original particle

    ClassDef(DaughterData, 1) // Daughter data class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Particle *mithep::DaughterData::Original() const
{
  // Return original particle.

  return static_cast<const Particle*>(fOriginal.GetObject());
}
#endif
