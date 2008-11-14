//--------------------------------------------------------------------------------------------------
// $Id: DecayData.h,v 1.2 2008/11/13 14:07:51 bendavid Exp $
//
// DecayData
//
// Additional information on a stable daughter which is specific to a particular decay
// 
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DECAYDATA_H
#define MITANA_DATATREE_DECAYDATA_H
 
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DecayData : public DaughterData
  {
    public:
      DecayData() {}
      DecayData(Particle *p, const FourVector &mom) :
        DaughterData(p),
        fMomAtVertex(mom) {}
      virtual ~DecayData() {}

      Double32_t             Px()   const { return fMomAtVertex.Px(); }
      Double32_t             Py()   const { return fMomAtVertex.Py(); }
      Double32_t             Pz()   const { return fMomAtVertex.Pz(); }
      Double32_t             P()    const { return fMomAtVertex.P(); }
      Double32_t             E()    const { return fMomAtVertex.E(); }
      FourVector           Mom()  const { return FourVector(fMomAtVertex); }
      void                 SetMom(Double32_t px, Double32_t y, Double32_t z, Double32_t e);
      void                 SetMom(const FourVector &mom) { fMomAtVertex = mom; }
      
      const ThreeVector32    RelativePosition() const;
      
      // Fitted Mass Error
      Double32_t             MassError() const { return fMassError; }
      void              SetMassError(Double32_t massError) { fMassError = massError;}
      // Lxy
      Double32_t             Lxy() const { return fLxy; }
      void              SetLxy(Double32_t lxy) { fLxy = lxy;}
      // Lxy Error
      Double32_t             LxyError() const { return fLxyError; }
      void              SetLxyError(Double32_t lxyError) { fLxyError = lxyError;}
      // Dxy (two dimensional impact parameter)
      Double32_t             Dxy() const { return fDxy; }
      void              SetDxy(Double32_t dxy) { fDxy = dxy;}
      // Dxy Error
      Double32_t             DxyError() const { return fDxyError; }
      void              SetDxyError(Double32_t dxyError) { fDxyError = dxyError;}
      // Lz
      Double32_t             Lz() const { return fLz; }
      void              SetLz(Double32_t lz) { fLz = lz;}
      // Lz Error
      Double32_t             LzError() const { return fLzError; }
      void              SetLzError(Double32_t lzError) { fLzError = lzError;}      

    protected:
      FourVectorM32        fMomAtVertex;      //fitted momentum at vertex
      Double32_t           fMassError;
      Double32_t           fLxy;
      Double32_t           fLxyError;
      Double32_t           fDxy;
      Double32_t           fDxyError;
      Double32_t           fLz;
      Double32_t           fLzError;

    ClassDef(DecayData, 1) // Stable daughter class
  };
}
//--------------------------------------------------------------------------------------------------
inline void mithep::DecayData::SetMom(Double32_t px, Double32_t py, Double32_t pz, Double32_t e)
{
  // Set four momentum.

  fMomAtVertex.SetXYZT(px, py, pz, e);
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector32 mithep::DecayData::RelativePosition() const
{
  //compute the position vector of the decay vertex relative to the parent decay vertex

  mithep::ThreeVector32 dz(0,0,fLz*TMath::Abs(fMomAtVertex.Pz())/fMomAtVertex.Pz());
  
  mithep::ThreeVector32 momPerp(fMomAtVertex.Px(),fMomAtVertex.Py(),0);
  mithep::ThreeVector32 zHat(0,0,1.0);
  
  mithep::ThreeVector32 dxy = -momPerp.Cross(zHat)*fDxy/momPerp.R();
  mithep::ThreeVector32 dlxy  = momPerp*fLxy/momPerp.R();
  
  return (dxy+dlxy+dz);
}
#endif
