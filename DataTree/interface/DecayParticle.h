//--------------------------------------------------------------------------------------------------
// $Id: DecayParticle.h,v 1.31 2011/02/17 13:44:14 bendavid Exp $
//
// DecayParticle
//
// The decay particle class is for use in vertexing based analyses. It
// stores vertex fit information (including four momentum) and links to daughters.
//
// Note that Charge() is still computed as a recursive loop over daughters, as inherited from
// CompositeParticle, but momentum is returned from the internally stored four vector.
//
// Authors: C.Paus, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DECAYPARTICLE_H
#define MITANA_DATATREE_DECAYPARTICLE_H
 
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/ConversionQuality.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class DecayParticle : public Particle
  {
    public:
      DecayParticle() :
        fAbsPdgId(0), fChi2(0), fNdof(0), fMassError(0), 
        fLxy(0), fLxyError(0), fDxy(0), fDxyError(0), fLz(0), fLzError(0), fDzBeamlineError(0), fNSharedHits(0) {}
      DecayParticle(Int_t absPdgId) : 
        fAbsPdgId(absPdgId), fChi2(0), fNdof(0), fMassError(0), 
        fLxy(0), fLxyError(0), fDxy(0), fDxyError(0), fLz(0), fLzError(0), fDzBeamlineError(0), fNSharedHits(0) {}

      void                      AddDaughterData(const DaughterData *dd) 
                                  { fDaughterData.Add(dd); ClearCharge(); }
      UInt_t                    AbsPdgId()            const { return fAbsPdgId;                    }
      Double_t                  Chi2()                const { return fChi2;                        }
      const Particle           *Daughter(UInt_t i)    const { return DaughterDat(i)->Original();   }
      const DaughterData       *DaughterDat(UInt_t i) const { return fDaughterData.At(i);          }
      Double_t                  Dxy()                 const { return fDxy;                         }
      Double_t                  DxyCorrected(const ThreeVector &v) const;
      Double_t                  DxyCorrected(const BaseVertex *v)  const;
      Double_t                  DxyError()            const { return fDxyError;                    }
      Double_t                  DzBeamlineError()     const { return fDzBeamlineError;             }
      Double_t                  DzCorrected(const ThreeVector &v) const;
      Double_t                  DzCorrected(const BaseVertex *v)  const;
      Bool_t                    HasDaughter(const Particle *p)            const;
      Bool_t                    HasCommonDaughter(const DecayParticle *p) const;
      Bool_t                    HasPriVertex()        const { return fPriVtx.IsValid();            }
      Bool_t                    HasPriVertex(const Vertex *v) 
                                                      const { return fPriVtx.RefsObject(v);        }
      Bool_t                    HasSameDaughters(const DecayParticle *p)  const;
      Double_t                  Lxy()                 const { return fLxy;                         }
      Double_t                  LxyError()            const { return fLxyError;                    }
      Double_t                  LxyCorrected(const BaseVertex *v)  const;
      Double_t                  Lz()                  const { return fLz;                          }
      Double_t                  LzError()             const { return fLzError;                     }
      Double_t                  MassError()           const { return fMassError;                   }
      UShort_t                  Ndof()                const { return fNdof;                        }
      UInt_t                    NDaughters()          const { return fDaughterData.Entries();      }
      EObjType                  ObjType()             const { return kDecayParticle;               }
      TParticlePDG             *ParticlePdgEntry()    const;
      Double_t                  PdgMass()             const;
      const Vertex             *PriVertex()           const { return fPriVtx.Obj();                }
      Double_t                  Prob()                const { return TMath::Prob(fChi2,fNdof);     }
      const ThreeVector        &Position()            const;
      const ConversionQuality  &Quality()             const { return fQuality;                     }
      ConversionQuality        &Quality()                   { return fQuality;                     }
      const ThreeVector         RelativePosition()    const;
      Bool_t                    SharedLayer(Track::EHitLayer l) const  { return fSharedLayers.TestBit(l); }
      const BitMask48          &SharedLayers()        const { return fSharedLayers;                }
      UInt_t                    NSharedLayers()       const { return fSharedLayers.NBitsSet();     }
      UInt_t                    NSharedHits()         const { return TMath::Max(UInt_t(fNSharedHits),NSharedLayers()); }      
      void                      SetAbsPdgId(UInt_t apid)                { fAbsPdgId=apid;          }
      void                      SetChi2(Double_t chi2)                  { fChi2 = chi2;            }
      void                      SetDxy(Double_t dxy)                    { fDxy = dxy; ClearPos();  }
      void                      SetDxyError(Double_t dxyError)          { fDxyError = dxyError;    }
      void                      SetDzBeamlineError(Double_t dzError)    { fDzBeamlineError = dzError; }
      void                      SetLxy(Double_t lxy)                    { fLxy = lxy; ClearPos();  }
      void                      SetLxyError(Double_t lxyError)          { fLxyError = lxyError;    }
      void                      SetLz(Double_t lz)                      { fLz = lz; ClearPos();    }
      void                      SetLzError(Double_t lzError)            { fLzError = lzError;      }
      void                      SetMassError(Double_t massError)        { fMassError = massError;  }
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                      SetMom(const FourVector &p)             
                                  { fMomentum = p; ClearMom(); ClearPos(); }
      void                      SetNdof(UShort_t ndof)                  { fNdof = ndof;            }
      void                      SetNSharedHits(UShort_t nhits)          { fNSharedHits = nhits;    }
      void                      SetPriVertex(const Vertex *v)           { fPriVtx = v; ClearPos(); }
      void                      SetSharedLayer(Track::EHitLayer l)      { fSharedLayers.SetBit(l); }
      void                      SetSharedLayers(const BitMask48 &layers) { fSharedLayers = layers; }
      using TObject::Error;

    protected:
      void                      ClearPos()            const { fCachePosFlag.ClearCache(); }
      Double_t                  GetCharge()           const;
      void	                GetMom()              const;
      void                      GetPos()              const;

      UInt_t                    fAbsPdgId;     //absolute value of pid code
      Double32_t                fChi2;         //[0,0,12]chi-squared of fit
      UShort_t                  fNdof;         //degrees of freedom for fit
      Double32_t                fMassError;    //[0,0,14]fitted mass error
      Double32_t                fLxy;          //[0,0,14]fitted lxy (decay length)
      Double32_t                fLxyError;     //[0,0,14]fitted lxy error
      Double32_t                fDxy;          //[0,0,14]fitted impact parameter
      Double32_t                fDxyError;     //[0,0,14]fitted impact parameter error
      Double32_t                fLz;           //[0,0,14]fitted lz (decay length)
      Double32_t                fLzError;      //[0,0,14]fitted lz error
      Double32_t                fDzBeamlineError; //[0,0,14]fitted deltaz error at beamline
      Vect4M                    fMomentum;     //momentum fourvector
      RefArray<DaughterData>    fDaughterData; //momentum of daughters at vertex
      Ref<Vertex>               fPriVtx;       //reference to primary vertex
      BitMask48                 fSharedLayers; //layer mask for shared hits from daughter particles
      UShort_t                  fNSharedHits;  //number of shared hits
      ConversionQuality         fQuality;      //conversion quality flags
      mutable CacheFlag         fCachePosFlag; //||cache validity flag for position
      mutable ThreeVector       fCachedPos;    //!cached momentum vector (filled by derived classes)
      
      ClassDef(DecayParticle, 4) // Decay particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::DecayParticle::GetCharge() const 
{
  // Return sum of charge of daughter particles.

  Double_t charge = 0;
  for (UInt_t i=0; i<NDaughters(); ++i)
    charge += DaughterDat(i)->Charge();
  
  return charge;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayParticle::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMomentum.Pt(), fMomentum.Eta(), fMomentum.Phi(), fMomentum.M());
}

//--------------------------------------------------------------------------------------------------
inline TParticlePDG *mithep::DecayParticle::ParticlePdgEntry() const 
{ 
  // Return entry to pdg database for the particle.

  return TDatabasePDG::Instance()->GetParticle(fAbsPdgId); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayParticle::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fMomentum.SetXYZT(px,py,pz,e);
  ClearMom();
  ClearPos();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector &mithep::DecayParticle::Position() const
{
  // Return cached momentum value.

  if (!fCachePosFlag.IsValid()) {
    GetPos();
    fCachePosFlag.SetValid();
  }

  return fCachedPos;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DecayParticle::GetPos() const
{
  // Return absolute position of decay.

  const mithep::Vertex *pv = PriVertex();
    
  if (pv)
    fCachedPos = pv->Position() + RelativePosition();
  else
    fCachedPos = RelativePosition();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector mithep::DecayParticle::RelativePosition() const
{
  // Compute the position vector of the decay vertex relative to the primary vertex.

  mithep::ThreeVector dz(0,0,fLz*TMath::Abs(Pz())/Pz());
  mithep::ThreeVector momPerp(Px(),Py(),0);
  mithep::ThreeVector zHat(0,0,1.0);
  mithep::ThreeVector dxy   = -momPerp.Cross(zHat)*fDxy/momPerp.R();
  mithep::ThreeVector dlxy  =  momPerp*fLxy/momPerp.R();
  return (dxy+dlxy+dz);
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::DecayParticle::DxyCorrected(const mithep::ThreeVector &v) const
{
  // Compute Dxy with respect to a given position
  mithep::ThreeVector momPerp(Px(),Py(),0);
  return momPerp.Cross(Position() - v).Z()/Pt();
  
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::DecayParticle::DxyCorrected(const mithep::BaseVertex *v) const
{
  // Compute Dxy with respect to a given beamspot/vertex
  return DxyCorrected(v->Position());
  
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::DecayParticle::DzCorrected(const mithep::ThreeVector &v) const
{
  // Compute Dxy with respect to a given position
  mithep::ThreeVector momPerp(Px(),Py(),0);
  mithep::ThreeVector posPerp(Position().X()-v.X(),Position().Y()-v.Y(),0);
  return Position().Z() - v.Z() - posPerp.Dot(momPerp)/Pt() * (Pz()/Pt());
  
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::DecayParticle::DzCorrected(const mithep::BaseVertex *v) const
{
  // Compute Dxy with respect to a given beamspot/vertex
  return DzCorrected(v->Position());
  
}

inline Double_t mithep::DecayParticle::LxyCorrected(const mithep::BaseVertex *v) const
{
  // Compute Dxy with respect to a given beamspot/vertex
  Double_t dx = Position().X() - v->X();
  Double_t dy = Position().Y() - v->Y();
  Double_t lxy = (dx*Px() + dy*Py())/Pt();
  return lxy;
  
}

#endif
