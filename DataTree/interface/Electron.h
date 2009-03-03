//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.26 2009/02/26 17:06:24 bendavid Exp $
//
// Electron
//
// Details to be worked out... TODO: Needs description ala Muon class
//
// Authors: C.Loizides, J.Bendavid, S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_ELECTRON_H
#define MITANA_DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class Electron : public ChargedParticle
  {
    public:
      Electron() : fESuperClusterOverP(0), fESeedClusterOverPout(0), fDeltaEtaSuperClTrkAtVtx(0),
                   fDeltaEtaSeedClTrkAtCalo(0), fDeltaPhiSuperClTrkAtVtx(0), 
                   fDeltaPhiSeedClTrkAtCalo(0), fHadronicOverEm(0), fIsEnergyScaleCorrected(0),
                   fIsMomentumCorrected(0), fNumberOfClusters(0), fClassification(0), fE33(0),
                   fE55(0), fCovEtaEta(0), fCoviEtaiEta(0), fCovEtaPhi(0), fCovPhiPhi(0),
                   fCaloIsolation(0), fCaloTowerIsolation(0), fTrackIsolation(0), 
                   fEcalJurassicIsolation(0), fHcalJurassicIsolation(0), fPassLooseID(0),
                   fPassTightID(0), fIDLikelihood(0), fPIn(0), fPOut(0) {}
      
      const Track         *BestTrk()               const;
      const Track         *GsfTrk()                const { return fGsfTrackRef.Obj();          }
      const Track         *TrackerTrk()            const { return fTrackerTrackRef.Obj();      }
      const SuperCluster  *SCluster()              const { return fSuperClusterRef.Obj();      }
      const Track         *Trk()                   const { return BestTrk();                   }
      Double_t             CaloIsolation()         const { return fCaloIsolation;              }
      Double_t             CaloTowerIsolation()    const { return fCaloTowerIsolation;         }
      Double_t             Classification()        const { return fClassification;             }
      Double_t             CovEtaEta()             const { return fCovEtaEta;                  }
      Double_t             CovEtaPhi()             const { return fCovEtaPhi;                  }
      Double_t             CovPhiPhi()             const { return fCovPhiPhi;                  }
      Double_t             CoviEtaiEta()           const { return fCoviEtaiEta;                }
      Double_t             DeltaEtaSuperClusterTrackAtVtx() const 
                             { return fDeltaEtaSuperClTrkAtVtx; }
      Double_t             DeltaEtaSeedClusterTrackAtCalo() const 
                             { return fDeltaEtaSeedClTrkAtCalo; }
      Double_t             DeltaPhiSuperClusterTrackAtVtx() const 
                             { return fDeltaPhiSuperClTrkAtVtx; }
      Double_t             DeltaPhiSeedClusterTrackAtCalo() const 
                             { return fDeltaPhiSeedClTrkAtCalo; }
      Double_t             E33()                   const { return fE33;                        }
      Double_t             E55()                   const { return fE55;                        }
      Double_t             EcalJurassicIsolation() const { return fEcalJurassicIsolation;      }
      Double_t             ESuperClusterOverP()    const { return fESuperClusterOverP;         }
      Double_t             ESeedClusterOverPout()  const { return fESeedClusterOverPout;       }
      Double_t             ESeedClusterOverPIn()   const;
      Double_t             IDLikelihood()          const { return fIDLikelihood;               }
      Double_t             IsEnergyScaleCorrected()const { return fIsEnergyScaleCorrected;     }
      Double_t             IsMomentumCorrected()   const { return fIsMomentumCorrected;        }
      Double_t             HadronicOverEm()        const { return fHadronicOverEm;             }  
      Bool_t               HasGsfTrk()             const { return fGsfTrackRef.IsValid();      }
      Bool_t               HasTrackerTrk()         const { return fTrackerTrackRef.IsValid();  }
      Bool_t               HasSuperCluster()       const { return fSuperClusterRef.IsValid();  }
      Double_t             HcalIsolation()         const { return fHcalJurassicIsolation;      }
      Double_t             NumberOfClusters()      const { return fNumberOfClusters;           }
      EObjType             ObjType()               const { return kElectron;                   }
      Double_t             PassLooseID()           const { return fPassLooseID;                }
      Double_t             PassTightID()           const { return fPassTightID;                }
      Double_t             PIn()                   const { return fPIn;                        }
      Double_t             POut()                  const { return fPOut;                       }
      Double_t             TrackIsolation()        const { return fTrackIsolation;             }
      void	           SetGsfTrk(const Track* t)                     
                             { fGsfTrackRef = t;     ClearMom(); ClearCharge(); }
      void	           SetTrackerTrk(const Track* t)                 
                             { fTrackerTrackRef = t; ClearMom(); ClearCharge(); }
      void	           SetSuperCluster(const SuperCluster* sc)       
                             { fSuperClusterRef = sc; ClearMom(); }
      void                 SetCaloIsolation(Double_t caloiso)    { fCaloIsolation = caloiso;   }
      void                 SetCaloTowerIsolation(Double_t tiso)  { fCaloTowerIsolation = tiso; }
      void                 SetClassification(Double_t x)         { fClassification = x;        }
      void                 SetCovEtaEta(Double_t CovEtaEta)      { fCovEtaEta = CovEtaEta;     }
      void                 SetCovEtaPhi(Double_t CovEtaPhi)      { fCovEtaPhi = CovEtaPhi;     }
      void                 SetCovPhiPhi(Double_t CovPhiPhi)      { fCovPhiPhi = CovPhiPhi;     }
      void                 SetCoviEtaiEta(Double_t CoviEtaiEta)  { fCoviEtaiEta = CoviEtaiEta; }
      void                 SetDeltaEtaSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaEtaSuperClTrkAtVtx = x;   }
      void                 SetDeltaEtaSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaEtaSeedClTrkAtCalo = x;   }
      void                 SetDeltaPhiSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaPhiSuperClTrkAtVtx = x;   }
      void                 SetDeltaPhiSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaPhiSeedClTrkAtCalo = x;   }
      void                 SetE33(Double_t E33)                  { fE33 = E33;                     }
      void                 SetE55(Double_t E55)                  { fE55 = E55;                     }
      void                 SetEcalJurassicIso(Double_t iso )     { fEcalJurassicIsolation = iso;   }
      void                 SetESuperClusterOverP(Double_t x)     { fESuperClusterOverP = x;        }
      void                 SetESeedClusterOverPout(Double_t x)   { fESeedClusterOverPout = x;      }
      void                 SetHadronicOverEm(Double_t x)         { fHadronicOverEm = x;            }
      void                 SetIDLikelihood(Double_t likelihood)  { fIDLikelihood = likelihood;     }
      void                 SetIsEnergyScaleCorrected(Double_t x) { fIsEnergyScaleCorrected = x;    }
      void                 SetIsMomentumCorrected(Double_t x)    { fIsMomentumCorrected = x;       }
      void                 SetHcalIsolation(Double_t iso )       { fHcalJurassicIsolation = iso;   }
      void                 SetNumberOfClusters(Double_t x)       { fNumberOfClusters = x;          }
      void                 SetPassLooseID(Double_t passLooseID)  { fPassLooseID = passLooseID;     }
      void                 SetPassTightID(Double_t passTightID)  { fPassTightID = passTightID;     }
      void                 SetPIn(Double_t PIn)                  { fPIn = PIn;                     }
      void                 SetPOut(Double_t POut)                { fPOut = POut;                   }
      void                 SetTrackIsolation(Double_t trkiso)    { fTrackIsolation = trkiso;       }

    protected:
      Double_t             GetMass()               const         { return 0.51099892e-3;           }
      void                 GetMom()                const;

      Ref<Track>           fGsfTrackRef;               //gsf track reference
      Ref<Track>           fTrackerTrackRef;           //tracker track reference
      Ref<SuperCluster>    fSuperClusterRef;           //reference to SuperCluster
      Double32_t           fESuperClusterOverP;        //
      Double32_t           fESeedClusterOverPout;      //
      Double32_t           fDeltaEtaSuperClTrkAtVtx;   //
      Double32_t           fDeltaEtaSeedClTrkAtCalo;   //
      Double32_t           fDeltaPhiSuperClTrkAtVtx;   //
      Double32_t           fDeltaPhiSeedClTrkAtCalo;   //
      Double32_t           fHadronicOverEm;            //
      Double32_t           fIsEnergyScaleCorrected;    //
      Double32_t           fIsMomentumCorrected;       //
      Double32_t           fNumberOfClusters;          //
      Double32_t           fClassification;            //
      Double32_t           fE33;                       //
      Double32_t           fE55;                       //
      Double32_t           fCovEtaEta;                 //
      Double32_t           fCoviEtaiEta;               //
      Double32_t           fCovEtaPhi;                 //
      Double32_t           fCovPhiPhi;                 //
      Double32_t           fCaloIsolation;             //
      Double32_t           fCaloTowerIsolation;        //
      Double32_t           fTrackIsolation;            //
      Double32_t           fEcalJurassicIsolation;     //
      Double32_t           fHcalJurassicIsolation;     // 
      Double32_t           fPassLooseID;               //
      Double32_t           fPassTightID;               //
      Double32_t           fIDLikelihood;              //
      Double32_t           fPIn;                       //
      Double32_t           fPOut;                      //

    ClassDef(Electron, 1) // Electron class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::BestTrk() const
{
  // Return "best" track.

  if (HasGsfTrk())
    return GsfTrk();
  else if (HasTrackerTrk())
    return TrackerTrk();

  return 0;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Electron::GetMom() const
{
  // Get momentum of the electron. We use the direction of the
  // track and the energy of the SuperCluster.

  const mithep::Track *trk = Trk();

  if (!trk) {
    fCachedMom.SetCoordinates(0,0,0,0);
    return;
  }

  Double_t p = 0;
  Double_t mass = GetMass();

  const mithep::SuperCluster *sc = SCluster();
  if (sc)
    p = TMath::Sqrt(sc->Energy()*sc->Energy() - mass*mass);
  else
    p = trk->P();

  Double_t pt = TMath::Abs(p*TMath::Cos(trk->Lambda()));
  fCachedMom.SetCoordinates(pt,trk->Eta(),trk->Phi(),mass);
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::ESeedClusterOverPIn() const
{
  // Return energy of the SuperCluster seed divided by the magnitude 
  // of the track momentum at the vertex.
  
  return SCluster()->Seed()->Energy() / PIn();
}
#endif
