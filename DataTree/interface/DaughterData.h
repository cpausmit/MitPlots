//--------------------------------------------------------------------------------------------------
// $Id: DaughterData.h,v 1.5 2008/09/10 03:33:27 loizides Exp $
//
// DaughterData
//
// Additional information on a decay daughter which is specific to a particular decay
// 
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DAUGHTERDATA_H
#define MITANA_DATATREE_DAUGHTERDATA_H
 
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DaughterData
  {
    public:
      DaughterData() {}
      DaughterData(const FourVector &mom) : fMomAtVertex(mom) {}
      virtual ~DaughterData() {}

      void                 SetMom(Double_t px, Double_t y, Double_t z, Double_t e);
      void                 SetMom(const FourVector &mom) { fMomAtVertex = mom; }
      const FourVector    &Mom()       const { return fMomAtVertex; }

    protected:
      FourVector           fMomAtVertex;      //fitted momentum at vertex

    ClassDef(DaughterData, 1) // Stable daughter class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DaughterData::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{
  // Set four momentum.

  fMomAtVertex.SetXYZT(px, py, pz, e);
}
#endif
