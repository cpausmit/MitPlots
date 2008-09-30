//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.1 2008/09/19 11:58:02 bendavid Exp $
//
// DaughterData
//
// Additional information on a daughter which is specific to a particular decay
// 
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
      DaughterData(Particle *orig) : fOriginal(orig) {}
      virtual ~DaughterData() {}

      Double_t             Charge()    const { return Original()->Charge(); }
      
      const Particle      *Original()  const;

    protected:
      TRef                 fOriginal; //TRef to original particle

    ClassDef(DaughterData, 1) // Stable daughter class
  };
}

inline const mithep::Particle *mithep::DaughterData::Original() const
{
  // Return global combined track.

  return static_cast<const Particle*>(fOriginal.GetObject());
}
#endif
