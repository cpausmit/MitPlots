//--------------------------------------------------------------------------------------------------
// $Id: DecayData.h,v 1.9 2009/03/03 17:04:09 loizides Exp $
//
// DecayData
//
// Additional information on a stable daughter which is specific to a particular decay.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DECAYDATA_H
#define MITANA_DATATREE_DECAYDATA_H
 
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Types.h"
#include "MitCommon/DataFormats/interface/Vect4M.h"

namespace mithep 
{
  class DecayData : public DaughterData
  {
    public:
      DecayData() : fMassError(0), fLxy(0), fLxyError(0), 
                    fDxy(0), fDxyError(0), fLz(0), fLzError(0) {}
      DecayData(const Particle *p, const FourVector &mom) : DaughterData(p), fMomAtVertex(mom), 
        fMassError(0), fLxy(0), fLxyError(0), fDxy(0), fDxyError(0), fLz(0), fLzError(0) {}

      Double_t             Dxy()       const { return fDxy;                     }
      Double_t             DxyError()  const { return fDxyError;                }
      Double_t             Lxy()       const { return fLxy;                     }
      Double_t             LxyError()  const { return fLxyError;                }
      Double_t             Lz()        const { return fLz;                      }
      Double_t             LzError()   const { return fLzError;                 }
      Double_t             MassError() const { return fMassError;               }
      EObjType             ObjType()   const { return kDecayData;               }
      const ThreeVector32  RelativePosition() const;
      void                 SetDxy(Double_t dxy)             { fDxy = dxy;             }
      void                 SetDxyError(Double_t dxyError)   { fDxyError = dxyError;   }
      void                 SetLxy(Double_t lxy)             { fLxy = lxy;             }
      void                 SetLxyError(Double_t lxyError)   { fLxyError = lxyError;   }
      void                 SetLz(Double_t lz)               { fLz = lz;               }
      void                 SetLzError(Double_t lzError)     { fLzError = lzError;     }      
      void                 SetMom(Double_t px, Double_t y, Double_t z, Double_t e);
//      void                 SetMom(const FourVector &mom)    { fMomAtVertex = mom; ClearMom(); }
//      void                 SetMom(const FourVector &mom)    { fMomAtVertex = mom; ClearMom(); }
      void                 SetMassError(Double_t massError) { fMassError = massError;         }

    protected:
      void                 GetMom()    const;

      Vect4M               fMomAtVertex;      //fitted momentum at vertex
      Double32_t           fMassError;        //[0,0,14]fitted mass error
      Double32_t           fLxy;              //[0,0,14]fitted lxy
      Double32_t           fLxyError;         //[0,0,14]fitted lxy error
      Double32_t           fDxy;              //[0,0,14]fitted impact parameter
      Double32_t           fDxyError;         //[0,0,14]fitted impact parameter error
      Double32_t           fLz;               //[0,0,14]fitted lz
      Double32_t           fLzError;          //[0,0,14]fitted lz error

    ClassDef(DecayData, 1) // Decay data for stable daughter class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayData::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMomAtVertex.Pt(),fMomAtVertex.Eta(),
                            fMomAtVertex.Phi(),fMomAtVertex.M()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayData::SetMom(Double32_t px, Double32_t py, Double32_t pz, Double32_t e)
{
  // Set four momentum.

  fMomAtVertex.SetXYZT(px, py, pz, e);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector32 mithep::DecayData::RelativePosition() const
{
  // Compute the position vector of the decay vertex relative to the parent decay vertex.

  mithep::ThreeVector32 dz(0,0,fLz*TMath::Abs(Pz())/Pz());
  mithep::ThreeVector32 momPerp(Px(),Py(),0);
  mithep::ThreeVector32 zHat(0,0,1.0);
  mithep::ThreeVector32 dxy = -momPerp.Cross(zHat)*fDxy/momPerp.R();
  mithep::ThreeVector32 dlxy  = momPerp*fLxy/momPerp.R();
  return (dxy+dlxy+dz);
}
#endif
