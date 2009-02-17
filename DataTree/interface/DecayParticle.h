//--------------------------------------------------------------------------------------------------
// $Id: DecayParticle.h,v 1.21 2009/01/22 14:21:32 loizides Exp $
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
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include <TDatabasePDG.h>
#include <TParticlePDG.h> 


namespace mithep 
{
  class DecayParticle : public Particle
  {
    public:
      DecayParticle() {}
      DecayParticle(Int_t absPdgId) : 
        fAbsPdgId(absPdgId), fChi2(0), fNdof(0), fMassError(0), fLxy(0), fLxyError(0), fDxy(0), 
        fDxyError(0), fLz(0), fLzError(0) {}
      ~DecayParticle() {}

      UInt_t                    AbsPdgId()            const { return fAbsPdgId;                  }
      Double_t                  Charge()              const;
      Double_t                  Chi2()                const { return fChi2;                      }
      const Particle           *Daughter(UInt_t i)    const { return DaughterDat(i)->Original(); }
      const DaughterData       *DaughterDat(UInt_t i) const { return fDaughterData.At(i);        }
      Double_t                  Dxy()                 const { return fDxy;                       }
      Double_t                  DxyError()            const { return fDxyError;                  }
      Bool_t                    HasDaughter(const Particle *p)            const;
      Bool_t                    HasCommonDaughter(const DecayParticle *p) const;
      Bool_t                    HasSameDaughters(const DecayParticle *p)  const;
      Bool_t                    HasPriVertex()        const { return fPriVertex.IsValid();       }
      Bool_t                    HasPriVertex(const Vertex *v) const { return fPriVertex.RefsObject(v); }
      Double_t                  Lxy()                 const { return fLxy;       }
      Double_t                  LxyError()            const { return fLxyError;  }
      Double_t                  MassError()           const { return fMassError; }
      UInt_t                    Ndof()                const { return fNdof;      }
      Double_t                  Lz()                  const { return fLz;        }
      Double_t                  LzError()             const { return fLzError;   }
      FourVector	        Mom()                 const { return FourVector(fMomentum);      }
      UInt_t                    NDaughters()          const { return fDaughterData.Entries();    }
      EObjType                  ObjType()             const { return kDecayParticle;             }
      TParticlePDG             *ParticlePdgEntry()    const;
      Double_t                  PdgMass()             const;
      Double_t                  Prob()                const { return TMath::Prob(fChi2,fNdof);   }
      const ThreeVector         Position()            const;
      const ThreeVector         RelativePosition()    const;
      const Vertex             *PriVertex()           const { return fPriVertex.Obj();           }
      void                      AddDaughterData(const DaughterData *dd) { fDaughterData.Add(dd); }
      void                      SetAbsPdgId(UInt_t apid) { fAbsPdgId=apid; }
      void                      SetChi2(Double_t chi2) { fChi2 = chi2;}
      void                      SetMassError(Double_t massError) { fMassError = massError;}
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                      SetMom(const FourVector &p) { fMomentum = p; }
      void                      SetNdof(UInt_t   ndof) { fNdof = ndof;}
      void                      SetDxy(Double_t dxy) { fDxy = dxy;}
      void                      SetDxyError(Double_t dxyError) { fDxyError = dxyError;}
      void                      SetLxy(Double_t lxy) { fLxy = lxy;}
      void                      SetLxyError(Double_t lxyError) { fLxyError = lxyError;}
      void                      SetLz(Double_t lz) { fLz = lz;}
      void                      SetLzError(Double_t lzError) { fLzError = lzError;}
      void                      SetPriVertex(const Vertex *v) { fPriVertex = v; }
      using TObject::Error;

    protected:
      UInt_t                    fAbsPdgId;     //absolute value of pid code
      Double32_t                fChi2;         //chi-squared of fit
      UInt_t                    fNdof;         //degrees of freedom for fit
      Double32_t                fMassError;    //fitted mass error
      Double32_t                fLxy;          //fitted lxy (decay length)
      Double32_t                fLxyError;     //fitted lxy error
      Double32_t                fDxy;          //fitted impact parameter
      Double32_t                fDxyError;     //fitted impact parameter error
      Double32_t                fLz;           //fitted lz (decay length)
      Double32_t                fLzError;      //fitted lz error
      FourVectorM32             fMomentum;     //momentum fourvector
      RefArray<DaughterData,32> fDaughterData; //momentum of daughters at vertex
      Ref<Vertex>               fPriVertex;    //reference to primary vertex
      
      ClassDef(DecayParticle, 1) // Decay particle class
  };
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
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector mithep::DecayParticle::Position() const
{
  // Return absolute position of decay.

  const mithep::Vertex *pv = PriVertex();
    
  if (pv)
    return ( pv->Position() + RelativePosition() );
  else
    return RelativePosition();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVector mithep::DecayParticle::RelativePosition() const
{
  // Compute the position vector of the decay vertex relative to the primary vertex.

  mithep::ThreeVector dz(0,0,fLz*TMath::Abs(fMomentum.Pz())/fMomentum.Pz());
  mithep::ThreeVector momPerp(fMomentum.Px(),fMomentum.Py(),0);
  mithep::ThreeVector zHat(0,0,1.0);
  mithep::ThreeVector dxy   = -momPerp.Cross(zHat)*fDxy/momPerp.R();
  mithep::ThreeVector dlxy  =  momPerp*fLxy/momPerp.R();
  return (dxy+dlxy+dz);
}

#endif
