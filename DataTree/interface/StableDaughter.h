//--------------------------------------------------------------------------------------------------
// $Id: StableDaughter.h,v 1.1 2008/07/29 13:32:49 bendavid Exp $
//
// StableDaughter
//
// Stable particle to be used as part of a decay tree.
// Explicitly stores the three momentum at the decay vertex as well as the link to the mother.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_STABLEDAUGHTER_H
#define DATATREE_STABLEDAUGHTER_H
 
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class StableDaughter : public StableParticle
  {
    public:
      StableDaughter() : StableParticle() {}
      StableDaughter(UInt_t absPdgId, Track *track) : StableParticle(absPdgId, track) {}
      StableDaughter(UInt_t absPdgId, Track *track, Double_t px, Double_t py, Double_t pz) :
        StableParticle(absPdgId, track),
        fMomentumAtVertex(px,py,pz) {}
      ~StableDaughter() {}

      Double_t             Eta()       const { return fMomentumAtVertex.Eta(); }
      const Particle      *Mother()    const;
      Double_t             Phi()       const { return fMomentumAtVertex.Phi(); }
      Double_t             P()         const { return fMomentumAtVertex.R();  }
      Double_t             Pt()        const { return fMomentumAtVertex.Rho(); }
      Double_t             Px()        const { return fMomentumAtVertex.X(); }
      Double_t             Py()        const { return fMomentumAtVertex.Y(); }
      Double_t             Pz()        const { return fMomentumAtVertex.Z(); }
      void                 SetThreeMom(Double_t px, Double_t y, Double_t z);
      const ThreeVector   &ThreeMom()  const { return fMomentumAtVertex; }

    protected:
      ThreeVector          fMomentumAtVertex;
      TRef	           fMother; //tracker track reference

    ClassDef(StableDaughter, 1) // StableDaughter class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Particle *mithep::StableDaughter::Mother() const
{
  // Return decay mother.

  return static_cast<const Particle*>(fMother.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StableDaughter::SetThreeMom(Double_t px, Double_t py, Double_t pz)
{
  // Set three momentum.

  fMomentumAtVertex.SetXYZ(px, py, pz);
}
#endif
