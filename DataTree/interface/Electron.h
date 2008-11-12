//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.18 2008/09/12 12:44:57 bendavid Exp $
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
      Double_t             E()                     const;
      Double_t             P()                     const;
      Double_t             Pt()                    const;
      Double_t             Px()                    const;
      Double_t             Py()                    const;
      Double_t             Pz()                    const;

      Double_t    Mass()                           const { return 0.51099892e-3;            }
      Double_t    ESuperClusterOverP()             const { return fESuperClusterOverP;      }
      Double_t    ESeedClusterOverPout()           const { return fESeedClusterOverPout;    }
      Double_t    ESeedClusterOverPIn()            const;
      Double_t    PIn()                            const { return fPIn;                     }
      Double_t    POut()                           const { return fPOut;                    }
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
      Double_t    CoviEtaiEta()                    const { return fCoviEtaiEta;             }
      Double_t    CaloIsolation()                  const { return fCaloIsolation;           }
      Double_t    CaloTowerIsolation()             const { return fCaloTowerIsolation;      }
      Double_t    TrackIsolation()                 const { return fTrackIsolation;          }
      Double_t    EcalJurassicIsolation()          const { return fEcalJurassicIsolation;   }
      Double_t    HcalJurassicIsolation()          const { return fHcalJurassicIsolation;   }

      Double_t    PassLooseID()                    const { return fPassLooseID;             }
      Double_t    PassTightID()                    const { return fPassTightID;             }
      Double_t    IDLikelihood()                   const { return fIDLikelihood;            }

      void	  SetGsfTrk(Track* t)                           { fGsfTrackRef = t;                }
      void	  SetTrackerTrk(Track* t)                       { fTrackerTrackRef = t;            }
      void	  SetSuperCluster(SuperCluster* sc)             { fSuperClusterRef = sc;           }
      void        SetESuperClusterOverP(Double_t x)             { fESuperClusterOverP = x;         }
      void        SetESeedClusterOverPout(Double_t x)           { fESeedClusterOverPout = x;       }
      void        SetPIn(Double_t PIn)                          { fPIn = PIn;                      }
      void        SetPOut(Double_t POut)                        { fPOut = POut;                    }
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
      void        SetCoviEtaiEta(Double_t CoviEtaiEta)          { fCoviEtaiEta = CoviEtaiEta;      }
      void        SetCaloIsolation(Double_t CaloIsolation)      { fCaloIsolation = CaloIsolation;  }
      void        SetCaloTowerIsolation(Double_t TowerIso)      { fCaloTowerIsolation = TowerIso;  }
      void        SetTrackIsolation(Double_t TrackIsolation)    { fTrackIsolation = TrackIsolation;}
      void        SetEcalJurassicIsolation(Double_t iso )       { fEcalJurassicIsolation = iso;    }
      void        SetHcalJurassicIsolation(Double_t iso )       { fHcalJurassicIsolation = iso;    }
      void        SetPassLooseID(Double_t passLooseID)          { fPassLooseID = passLooseID;      }
      void        SetPassTightID(Double_t passTightID)          { fPassTightID = passTightID;      }
      void        SetIDLikelihood(Double_t likelihood)          { fIDLikelihood = likelihood;      }

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
      Double_t             fE33;
      Double_t             fE55;
      Double_t             fCovEtaEta;
      Double_t             fCoviEtaiEta;
      Double_t             fCovEtaPhi;
      Double_t             fCovPhiPhi;
      Double_t             fCaloIsolation;
      Double_t             fCaloTowerIsolation;
      Double_t             fTrackIsolation;
      Double_t             fEcalJurassicIsolation;
      Double_t             fHcalJurassicIsolation;
      Double_t             fPassLooseID;
      Double_t             fPassTightID;
      Double_t             fIDLikelihood;
      Double_t             fPIn;
      Double_t             fPOut;

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

  return FourVector(Px(), Py(), Pz(), E());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::ESeedClusterOverPIn() const
{
  // Return Energy of the SuperCluster Seed Divided by the magnitude 
  // of the track momentum at the vertex
  
  return SCluster()->Seed()->Energy() / PIn();
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::E() const
{
  // Return Energy of the SuperCluster if present
  // or else return energy derived from the track
  
  const mithep::SuperCluster *sc = SCluster();
  if (sc)
    return sc->Energy();
  else
    return TMath::Sqrt(Trk()->P()*Trk()->P() + Mass()*Mass());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::P() const
{
  // Return momentum derived from the SuperCluster if present
  // or else return momentum from the track
  
  const mithep::SuperCluster *sc = SCluster();
  if (sc)
    return TMath::Sqrt(sc->Energy()*sc->Energy() - Mass()*Mass());
  else
    return Trk()->P();
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::Px() const
{
  return Pt()*TMath::Cos(Trk()->Phi());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::Py() const
{
  return Pt()*TMath::Sin(Trk()->Phi());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::Pz() const
{
  return P()*TMath::Sin(Trk()->Lambda());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::Pt() const
{
  return TMath::Abs(P()*TMath::Cos(Trk()->Lambda()));
}
#endif
