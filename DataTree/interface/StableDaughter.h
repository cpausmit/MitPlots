//--------------------------------------------------------------------------------------------------
// $Id: StableDaughter.h,v 1.6 2008/12/09 17:47:00 loizides Exp $
//
// StableDaughter
//
// Stable particle to be used as part of a decay tree. Explicitly stores the three momentum at 
// the decay vertex as well as the link to the mother.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_STABLEDAUGHTER_H
#define MITANA_DATATREE_STABLEDAUGHTER_H
 
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class StableDaughter : public StableParticle
  {
    public:
      StableDaughter() {}
      StableDaughter(UInt_t absPdgId, Track *track) : StableParticle(absPdgId, track) {}
      StableDaughter(UInt_t absPdgId, Track *track, Double_t px, Double_t py, Double_t pz) :
        StableParticle(absPdgId, track), fMomAtVertex(px,py,pz) {}
      ~StableDaughter() {}

      Double_t             Eta()       const { return fMomAtVertex.Eta(); }
      const Particle      *Mother()    const { return fMother.Obj();      }
      EObjType             ObjType()   const { return kStableDaughter;    }      
      Double_t             Phi()       const { return fMomAtVertex.Phi(); }
      Double_t             P()         const { return fMomAtVertex.R();   }
      Double_t             Pt()        const { return fMomAtVertex.Rho(); }
      Double_t             Px()        const { return fMomAtVertex.X();   }
      Double_t             Py()        const { return fMomAtVertex.Y();   }
      Double_t             Pz()        const { return fMomAtVertex.Z();   }
      const ThreeVector   &ThreeMom()  const { return fMomAtVertex;       }
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);

    protected:
      ThreeVector          fMomAtVertex;      //fitted momentum at vertex
      Ref<Particle>        fMother;           //decay mother reference

    ClassDef(StableDaughter, 1) // Stable daughter class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableDaughter::SetThreeMom(Double_t px, Double_t py, Double_t pz)
{
  // Set three momentum.

  fMomAtVertex.SetXYZ(px, py, pz);
}
#endif
