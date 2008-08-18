//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.13 2008/08/08 11:17:13 sixie Exp $
//
// Electron
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid, S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_ELECTRON_H
#define DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"

namespace mithep 
{
  class Electron : public ChargedParticle
  {
    public:
      Electron() {}
      ~Electron() {}
      
      const Track         *BestTrk()               const;
      const Track         *GsfTrk()                const;
      const Track         *TrackerTrk()            const;
      const SuperCluster  *SCluster()              const;
      FourVector           Mom()                   const;
      const Track         *Trk()                   const { return BestTrk();                }
      Double_t             E()                     const {return SCluster()->Energy();      } 


      Double_t    Mass()                           const { return 0.51099892e-3;            }
      Double_t    ESuperClusterOverP()             const { return fESuperClusterOverP;      }
      Double_t    ESeedClusterOverPout()           const { return fESeedClusterOverPout;    }
      Double_t    DeltaEtaSuperClusterTrackAtVtx() const { return fDeltaEtaSuperClTrkAtVtx; }
      Double_t    DeltaEtaSeedClusterTrackAtCalo() const { return fDeltaEtaSeedClTrkAtCalo; }
      Double_t    DeltaPhiSuperClusterTrackAtVtx() const { return fDeltaPhiSuperClTrkAtVtx; }
      Double_t    DeltaPhiSeedClusterTrackAtCalo() const { return fDeltaPhiSeedClTrkAtCalo; }
      Double_t    HadronicOverEm()                 const { return fHadronicOverEm;          }
      Double_t    IsEnergyScaleCorrected()         const { return fIsEnergyScaleCorrected;  }
      Double_t    IsMomentumCorrected()            const { return fIsMomentumCorrected;     }
      Double_t    NumberOfClusters()               const { return fNumberOfClusters;        }
      Double_t    Classification()                 const { return fClassification;          }
      Double_t    E33()                            const { return fE33;                     }
      Double_t    E55()                            const { return fE55;                     }
      Double_t    CovEtaEta()                      const { return fCovEtaEta;               }
      Double_t    CovEtaPhi()                      const { return fCovEtaPhi;               }
      Double_t    CovPhiPhi()                      const { return fCovPhiPhi;               }
      Double_t    CaloIsolation()                  const { return fCaloIsolation;           }
      Double_t    TrackIsolation()                 const { return fTrackIsolation;          }
     
      Double_t    ComputeTrackIsolation   (  Double_t extRadius, Double_t intRadius, 
                                             Double_t ptLow, Double_t maxVtxZDist, 
                                             mithep::Collection<Track> *tracks              );
      Double_t    ComputeEcalIsolation    (  Double_t coneSize, Double_t etLow, 
                                             mithep::Collection<BasicCluster> *basicClusters);

      void	  SetGsfTrk(Track* t)                           { fGsfTrackRef = t;                }
      void	  SetTrackerTrk(Track* t)                       { fTrackerTrackRef = t;            }
      void	  SetSuperCluster(SuperCluster* sc)             { fSuperClusterRef = sc;           }
      void        SetESuperClusterOverP(Double_t x)             { fESuperClusterOverP = x;         }
      void        SetESeedClusterOverPout(Double_t x)           { fESeedClusterOverPout = x;       }
      void        SetDeltaEtaSuperClusterTrackAtVtx(Double_t x) { fDeltaEtaSuperClTrkAtVtx = x;    }
      void        SetDeltaEtaSeedClusterTrackAtCalo(Double_t x) { fDeltaEtaSeedClTrkAtCalo = x;    }
      void        SetDeltaPhiSuperClusterTrackAtVtx(Double_t x) { fDeltaPhiSuperClTrkAtVtx = x;    }
      void        SetDeltaPhiSeedClusterTrackAtCalo(Double_t x) { fDeltaPhiSeedClTrkAtCalo = x;    }
      void        SetHadronicOverEm(Double_t x)                 { fHadronicOverEm = x;             }
      void        SetIsEnergyScaleCorrected(Double_t x)         { fIsEnergyScaleCorrected = x;     }
      void        SetIsMomentumCorrected(Double_t x)            { fIsMomentumCorrected = x;        }
      void        SetNumberOfClusters(Double_t x)               { fNumberOfClusters = x;           }
      void        SetClassification(Double_t x)                 { fClassification = x;             }
      void        SetE33(Double_t E33)                          { fE33 = E33;                      }
      void        SetE55(Double_t E55)                          { fE55 = E55;                      }
      void        SetCovEtaEta(Double_t CovEtaEta)              { fCovEtaEta = CovEtaEta;          }
      void        SetCovEtaPhi(Double_t CovEtaPhi)              { fCovEtaPhi = CovEtaPhi;          }
      void        SetCovPhiPhi(Double_t CovPhiPhi)              { fCovPhiPhi = CovPhiPhi;          }
      void        SetCaloIsolation(Double_t CaloIsolation)      { fCaloIsolation = CaloIsolation;  }
      void        SetTrackIsolation(Double_t TrackIsolation)    { fTrackIsolation = TrackIsolation;}

    protected:
      TRef	           fGsfTrackRef;     //global combined track reference
      TRef	           fTrackerTrackRef; //tracker track reference
      TRef                 fSuperClusterRef; //superCluster

      Double_t             fESuperClusterOverP;
      Double_t             fESeedClusterOverPout;
      Double_t             fDeltaEtaSuperClTrkAtVtx;
      Double_t             fDeltaEtaSeedClTrkAtCalo;
      Double_t             fDeltaPhiSuperClTrkAtVtx;
      Double_t             fDeltaPhiSeedClTrkAtCalo;
      Double_t             fHadronicOverEm;
      Double_t             fIsEnergyScaleCorrected;
      Double_t             fIsMomentumCorrected;      
      Double_t             fNumberOfClusters;
      Double_t             fClassification;          
      Double_t             fSuperClusterPx;
      Double_t             fSuperClusterPy;
      Double_t             fSuperClusterPz;
      Double_t             fSuperClusterE;
      Double_t             fE33;
      Double_t             fE55;
      Double_t             fCovEtaEta;
      Double_t             fCovEtaPhi;
      Double_t             fCovPhiPhi;
      Double_t             fCaloIsolation;
      Double_t             fTrackIsolation;

    ClassDef(Electron, 1) // Electron class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::BestTrk() const
{
  // Return "best" track.

  if (GsfTrk())
    return GsfTrk();
  else if (TrackerTrk())
    return TrackerTrk();

  return 0;
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::GsfTrk() const
{
  // Return global combined track.

  return static_cast<const Track*>(fGsfTrackRef.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::TrackerTrk() const
{
  // Return tracker track.

  return static_cast<const Track*>(fTrackerTrackRef.GetObject());
}
//--------------------------------------------------------------------------------------------------
inline const mithep::SuperCluster *mithep::Electron::SCluster() const
{
  // Return Super cluster

  return static_cast<const SuperCluster*>(fSuperClusterRef.GetObject());
}

//-------------------------------------------------------------------------------------------------
inline mithep::FourVector mithep::Electron::Mom() const
{
  // Return Momentum of the electron. We use the direction of the
  // Track and the Energy of the Super Cluster

  double P = TMath::Sqrt( E()*E() - Mass()*Mass());
  return FourVector(P*sin(Trk()->Theta())*cos(Trk()->Phi()), 
                    P*sin(Trk()->Theta())*sin(Trk()->Phi()), P*cos(Trk()->Theta()), E());
}
#endif
