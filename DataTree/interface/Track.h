//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.39 2009/03/20 18:23:27 loizides Exp $
//
// Track
//
// We store the CMSSW track parameterization
// Parameters associated to the 5D curvilinear covariance matrix:
// (qoverp, lambda, phi, dxy, dsz)
// defined as:
// qoverp = q / abs(p) = signed inverse of momentum [1/GeV]
// lambda = pi/2 - polar angle at the given point
// phi = azimuth angle at the given point
// dxy = -vx*sin(phi) + vy*cos(phi) [cm]
// dsz = vz*cos(lambda) - (vx*cos(phi)+vy*sin(phi))*sin(lambda) [cm]
// (See http://cmslxr.fnal.gov/lxr/source/DataFormats/TrackReco/interface/TrackBase.h)
//
// Format for fHits: (We do not use anything resembling reco::HitPattern from CMSSW because that
// data format requires 800 bits per track!)
// There is a one to one mapping between bits and tracker layers, where layers are enumerated
// seperately in the PXB, PXF, TIB, TID, TOB, TEC and r-phi and stereo modules are treated as
// seperate layers in those detectors which have them
// (TIB L1,L2, TID L1,L2,L3, TOB L1,L2, TEC L1,L2,L3,L4,L5,L6,L7,L8,L9).
// 
// A bit value of 1 indicates a hit in the corresponding layer, and 0 indicates no hit.
//
// Note that currently this only stores information about hits in the Tracker,
// but muon chamber information will likely be added as well.
//
// Bit-Layer assignments (starting from bit 0):
// Bit  0: PXB L1
// Bit  1: PXB L2
// Bit  2: PXB L3
// Bit  3: PXF L1
// Bit  4: PXF L2
// Bit  5: TIB L1 r-phi
// Bit  6: TIB L1 stereo
// Bit  7: TIB L2 r-phi
// Bit  8: TIB L2 stereo
// Bit  9: TIB L3 r-phi
// Bit 10: TIB L4 r-phi
// Bit 11: TID L1 r-phi
// Bit 12: TID L1 stereo
// Bit 13: TID L2 r-phi
// Bit 14: TID L2 stereo
// Bit 15: TID L3 r-phi
// Bit 16: TID L3 stereo
// Bit 17: TOB L1 r-phi
// Bit 18: TOB L1 stereo
// Bit 19: TOB L2 r-phi
// Bit 20: TOB L2 stereo
// Bit 21: TOB L3 r-phi
// Bit 22: TOB L4 r-phi
// Bit 23: TOB L5 r-phi
// Bit 24: TOB L6 r-phi
// Bit 25: TEC L1 r-phi
// Bit 26: TEC L1 stereo
// Bit 27: TEC L2 r-phi
// Bit 28: TEC L2 stereo
// Bit 29: TEC L3 r-phi
// Bit 30: TEC L3 stereo
// Bit 31: TEC L4 r-phi
// Bit 32: TEC L4 stereo
// Bit 33: TEC L5 r-phi
// Bit 34: TEC L5 stereo
// Bit 35: TEC L6 r-phi
// Bit 36: TEC L6 stereo
// Bit 37: TEC L7 r-phi
// Bit 38: TEC L7 stereo
// Bit 39: TEC L8 r-phi
// Bit 40: TEC L8 stereo
// Bit 41: TEC L9 r-phi
// Bit 42: TEC L9 stereo
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRACK_H
#define MITANA_DATATREE_TRACK_H
 
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataTree/interface/BaseVertex.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Track : public DataObject
  {
    public:
      enum EHitLayer { 
        PXB1, 
        PXB2,
        PXB3,
        PXF1,
        PXF2,
        TIB1,
        TIB1S,
        TIB2,
        TIB2S,
        TIB3,
        TIB4,
        TID1,
        TID1S,
        TID2,
        TID2S,
        TID3,
        TID3S,
        TOB1,
        TOB1S,
        TOB2,
        TOB2S,
        TOB3,
        TOB4,
        TOB5,
        TOB6,
        TEC1,
        TEC1S,
        TEC2,
        TEC2S,
        TEC3,
        TEC3S,
        TEC4,
        TEC4S,
        TEC5,
        TEC5S,
        TEC6,
        TEC6S,
        TEC7,
        TEC7S,
        TEC8,
        TEC8S,
        TEC9,
        TEC9S
      };

      Track() : fQOverP(0), fQOverPErr(0), fLambda(0), fLambdaErr(0),
                fPhi0(0), fPhi0Err(0), fDxy(0), fDxyErr(0), fDsz(0), fDszErr(0),
                fChi2(0), fNdof(0), fEtaEcal(0), fPhiEcal(0) {}
      Track(Double_t qOverP, Double_t lambda, Double_t phi0, Double_t dxy, Double_t dsz) :
	        fQOverP(qOverP), fQOverPErr(0), fLambda(lambda), fLambdaErr(0),
                fPhi0(phi0), fPhi0Err(0), fDxy(dxy), fDxyErr(0), fDsz(dsz), fDszErr(0),
                fChi2(0), fNdof(0), fEtaEcal(0), fPhiEcal(0) {}
      ~Track() {}

      Int_t                Charge()         const { return (fQOverP>0) ? 1 : -1;  }
      Double_t             Chi2()           const { return fChi2;                 }
      void                 ClearHit(EHitLayer l)  { fHits.ClearBit(l);            } 
      Double_t	           D0()             const { return -fDxy;                 }
      Double_t             D0Corrected(const BaseVertex &iVertex) const;
      Double_t	           D0Err()          const { return fDxyErr;               }
      Double_t             Dsz()            const { return fDsz;                  }
      Double_t             DszErr()         const { return fDszErr;               }
      Double_t             Dxy()            const { return fDxy;                  }
      Double_t             DxyErr()         const { return fDxyErr;               }
      Double_t             E(Double_t m)    const { return TMath::Sqrt(E2(m));    }
      Double_t             E2(Double_t m)   const { return P2()+m*m;              }
      Double_t             Eta()            const { return Mom().Eta();           }
      Double_t             EtaEcal()        const { return fEtaEcal;              }
      Bool_t               Hit(EHitLayer l) const { return fHits.TestBit(l);      }
      const BitMask48     &Hits()           const { return fHits;                 }
      Double_t             Lambda()         const { return fLambda;               }
      Double_t             LambdaErr()      const { return fLambdaErr;            }
      const MCParticle    *MCPart()         const { return fMCParticleRef.Obj();  }
      const ThreeVectorC  &Mom()            const;
      FourVectorM          Mom4(Double_t m) const { return FourVectorM(Pt(),Eta(),Phi(),E(m)); }
      UShort_t             Ndof()           const { return fNdof;                              }
      UInt_t               NHits()          const { return fHits.NBitsSet();                   }
      UInt_t               NStereoHits()    const { return StereoHits().NBitsSet();            }
      EObjType             ObjType()        const { return kTrack;                             }    
      Double_t             P2()             const { return 1./fQOverP/fQOverP;                 }
      Double_t             P()              const { return TMath::Abs(1./fQOverP);             }
      Double_t             Phi()            const { return fPhi0;                              }
      Double_t	           Phi0()           const { return fPhi0;                              }
      Double_t	           Phi0Err()        const { return fPhi0Err;                           }
      Double_t             PhiEcal()        const { return fPhiEcal;                           }
      Double_t             Prob()           const { return TMath::Prob(fChi2,fNdof);           }
      Double_t	           Pt()             const { return Mom().Rho();                        }
      Double_t             Px()             const { return Mom().X();                          } 
      Double_t             Py()             const { return Mom().Y();                          }
      Double_t             Pz()             const { return Mom().Z();                          }
      Double_t             QOverP()         const { return fQOverP;                            }
      Double_t             QOverPErr()      const { return fQOverPErr;                         }
      Double_t             RChi2()          const { return fChi2/(Double_t)fNdof; }
      Double_t             Theta()          const { return (TMath::PiOver2() - fLambda);       }
      const SuperCluster  *SCluster()       const { return fSuperClusterRef.Obj();             }
      const BitMask48      StereoHits()     const { return (fHits & StereoLayers());           }
      void                 SetChi2(Double_t chi2)              { fChi2 = chi2;                 }
      void	           SetErrors(Double_t qOverPErr, Double_t lambdaErr, Double_t phi0Err, 
                                     Double_t dXyErr, Double_t dSzErr);
      void                 SetEtaEcal(Double_t eta)            { fEtaEcal = eta;               }
      void                 SetHelix (Double_t qOverP, Double_t lambda, Double_t phi0, 
                                     Double_t dXy, Double_t dSz);
      void                 SetHit(EHitLayer l)                 { fHits.SetBit(l);              }
      void                 SetHits(const BitMask48 &hits)      { fHits = hits;                 }
      void                 SetNdof(UShort_t dof)               { fNdof = dof;                  }
      void	           SetMCPart(const MCParticle *p)      { fMCParticleRef = p;           }
      void                 SetPhiEcal(Double_t phi)            { fPhiEcal = phi;               }
      void	           SetSCluster(const SuperCluster* sc) { fSuperClusterRef = sc;        }
      Double_t             Z0()             const { return fDsz/TMath::Cos(fLambda);           }

      static 
      const BitMask48      StereoLayers();

    protected:
      void                 ClearMom()    const { fCacheMomFlag.ClearCache(); }
      void                 GetMom()      const;

      BitMask48            fHits;                //storage for mostly hit information
      Double32_t           fQOverP;              //[0,0,14]signed inverse of momentum [1/GeV]
      Double32_t           fQOverPErr;           //[0,0,14]error of q/p
      Double32_t           fLambda;              //[0,0,14]pi/2 - polar angle at the reference point
      Double32_t           fLambdaErr;           //[0,0,14]error of lambda
      Double32_t           fPhi0;                //[0,0,14]azimuth angle at the given point
      Double32_t           fPhi0Err;             //[0,0,14]error of azimuthal angle
      Double32_t           fDxy;                 //[0,0,14]trans. distance to reference point [cm]
      Double32_t           fDxyErr;              //[0,0,14]error of transverse distance
      Double32_t           fDsz;                 //[0,0,14]long. distance to reference point [cm]
      Double32_t           fDszErr;              //[0,0,14]error of longitudinal distance
      Double32_t           fChi2;                //[0,0,12]chi squared of track fit
      UShort_t             fNdof;                //degree-of-freedom of track fit
      Double32_t           fEtaEcal;             //[0,0,12]eta of track at Ecal front face
      Double32_t           fPhiEcal;             //[0,0,12]phi of track at Ecal front face
      Ref<SuperCluster>    fSuperClusterRef;     //superCluster crossed by track
      Ref<MCParticle>      fMCParticleRef;       //reference to sim particle (for monte carlo)
      mutable CacheFlag    fCacheMomFlag;        //||cache validity flag for momentum
      mutable ThreeVectorC fCachedMom;           //!cached momentum vector
	      
    ClassDef(Track, 1) // Track class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Track::GetMom() const
{
  // Compute three momentum.

  Double_t pt = TMath::Abs(TMath::Cos(fLambda)/fQOverP);
  Double_t eta = - TMath::Log(TMath::Tan(Theta()/2.));
  fCachedMom.SetCoordinates(pt,eta,Phi());
}

//--------------------------------------------------------------------------------------------------
inline const mithep::ThreeVectorC &mithep::Track::Mom() const
{
  // Return cached momentum value.

  if (!fCacheMomFlag.IsValid()) {
    GetMom();
    fCacheMomFlag.SetValid();
  }
  return fCachedMom;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Track::D0Corrected(const BaseVertex &iVertex) const
{
  // Return corrected d0 with respect to primary vertex or beamspot.

  Double_t lXM =  -TMath::Sin(Phi()) * D0();
  Double_t lYM =   TMath::Cos(Phi()) * D0();
  Double_t lDX = (lXM + iVertex.X());
  Double_t lDY = (lYM + iVertex.Y());
  Double_t d0Corr = (Px()*lDY - Py()*lDX)/Pt();
  
  return d0Corr;
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetHelix(Double_t qOverP, Double_t lambda, Double_t phi0, 
                             Double_t dxy, Double_t dsz)
{
  // Set helix parameters.

  fQOverP = qOverP;
  fLambda = lambda;
  fPhi0   = phi0;
  fDxy    = dxy;
  fDsz    = dsz;
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline
void mithep::Track::SetErrors(Double_t qOverPErr, Double_t lambdaErr, Double_t phi0Err, 
                              Double_t dxyErr, Double_t dszErr)
{
  // Set helix errors.

  fQOverPErr = qOverPErr;
  fLambdaErr = lambdaErr;
  fPhi0Err   = phi0Err;
  fDxyErr    = dxyErr;
  fDszErr    = dszErr;
}

//--------------------------------------------------------------------------------------------------
inline
const mithep::BitMask48 mithep::Track::StereoLayers()
{ 
  // Build and return BitMask of stereo layers.

  mithep::BitMask48 stereoLayers;
  stereoLayers.SetBit(mithep::Track::TIB1S);
  stereoLayers.SetBit(mithep::Track::TIB2S);
  stereoLayers.SetBit(mithep::Track::TID1S);
  stereoLayers.SetBit(mithep::Track::TID2S);
  stereoLayers.SetBit(mithep::Track::TID3S);
  stereoLayers.SetBit(mithep::Track::TOB1S);
  stereoLayers.SetBit(mithep::Track::TOB2S);
  stereoLayers.SetBit(mithep::Track::TEC1S);
  stereoLayers.SetBit(mithep::Track::TEC2S);
  stereoLayers.SetBit(mithep::Track::TEC3S);
  stereoLayers.SetBit(mithep::Track::TEC4S);
  stereoLayers.SetBit(mithep::Track::TEC5S);
  stereoLayers.SetBit(mithep::Track::TEC6S);
  stereoLayers.SetBit(mithep::Track::TEC7S);
  stereoLayers.SetBit(mithep::Track::TEC8S);
  stereoLayers.SetBit(mithep::Track::TEC9S);
  return stereoLayers;
}
#endif
