//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.31 2009/03/20 18:44:17 bendavid Exp $
//
// Electron
//
// This class holds information about reconstructed electrons from CMSSW.
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
                   fDeltaPhiSeedClTrkAtCalo(0), fHadronicOverEm(0), fNumberOfClusters(0), fE33(0),
                   fE55(0), fCovEtaEta(0), fCoviEtaiEta(0), fCovEtaPhi(0), fCovPhiPhi(0),
                   fCaloIsolation(0), fCaloTowerIsolation(0), fTrackIsolation(0), 
                   fEcalJurassicIsolation(0), fHcalJurassicIsolation(0), fPassLooseID(0),
                   fPassTightID(0), fIDLikelihood(0), fPIn(0), fPOut(0),
                   fIsEnergyScaleCorrected(0), fIsMomentumCorrected(0), fClassification(0) {}

      const Track         *BestTrk()                const;
      Double_t             CaloIsolation()          const { return fCaloIsolation;                 }
      Double_t             CaloTowerIsolation()     const { return fCaloTowerIsolation;            }
      Int_t                Classification()         const { return fClassification;                }
      Double_t             CovEtaEta()              const { return fCovEtaEta;                     }
      Double_t             CovEtaPhi()              const { return fCovEtaPhi;                     }
      Double_t             CovPhiPhi()              const { return fCovPhiPhi;                     }
      Double_t             CoviEtaiEta()            const { return fCoviEtaiEta;                   }
      Double_t             DeltaEtaSuperClusterTrackAtVtx() const 
                             { return fDeltaEtaSuperClTrkAtVtx; }
      Double_t             DeltaEtaSeedClusterTrackAtCalo() const 
                             { return fDeltaEtaSeedClTrkAtCalo; }
      Double_t             DeltaPhiSuperClusterTrackAtVtx() const 
                             { return fDeltaPhiSuperClTrkAtVtx; }
      Double_t             DeltaPhiSeedClusterTrackAtCalo() const 
                             { return fDeltaPhiSeedClTrkAtCalo; }
      Double_t             E33()                    const { return fE33;                           }
      Double_t             E55()                    const { return fE55;                           }
      Double_t             EcalJurassicIsolation()  const { return fEcalJurassicIsolation;         }
      Double_t             ESuperClusterOverP()     const { return fESuperClusterOverP;            }
      Double_t             ESeedClusterOverPout()   const { return fESeedClusterOverPout;          }
      Double_t             ESeedClusterOverPIn()    const;
      Double_t             FBrem()                  const { return (PIn() - POut())/PIn();   }
      const Track         *GsfTrk()                 const { return fGsfTrackRef.Obj();             }
      Double_t             HadronicOverEm()         const { return fHadronicOverEm;                }
      Bool_t               HasGsfTrk()              const { return fGsfTrackRef.IsValid();         }
      Bool_t               HasTrackerTrk()          const { return fTrackerTrackRef.IsValid();     }
      Bool_t               HasSuperCluster()        const { return fSuperClusterRef.IsValid();     }
      Double_t             HcalIsolation()          const { return fHcalJurassicIsolation;         }
      Double_t             IDLikelihood()           const { return fIDLikelihood;                  }
      Bool_t               IsEnergyScaleCorrected() const { return fIsEnergyScaleCorrected;        }
      Bool_t               IsMomentumCorrected()    const { return fIsMomentumCorrected;           }
      Double_t             NumberOfClusters()       const { return fNumberOfClusters;              }
      EObjType             ObjType()                const { return kElectron;                      }
      Double_t             PassLooseID()            const { return fPassLooseID;                   }
      Double_t             PassTightID()            const { return fPassTightID;                   }
      Double_t             PIn()                    const { return fPIn;                           }
      Double_t             POut()                   const { return fPOut;                          }
      const SuperCluster  *SCluster()               const { return fSuperClusterRef.Obj();         }
      void                 SetCaloIsolation(Double_t caloiso)     { fCaloIsolation = caloiso;      }
      void                 SetCaloTowerIsolation(Double_t tiso)   { fCaloTowerIsolation = tiso;    }
      void                 SetClassification(Int_t x)             { fClassification = x;           }
      void                 SetCovEtaEta(Double_t CovEtaEta)       { fCovEtaEta = CovEtaEta;        }
      void                 SetCovEtaPhi(Double_t CovEtaPhi)       { fCovEtaPhi = CovEtaPhi;        }
      void                 SetCovPhiPhi(Double_t CovPhiPhi)       { fCovPhiPhi = CovPhiPhi;        }
      void                 SetCoviEtaiEta(Double_t CoviEtaiEta)   { fCoviEtaiEta = CoviEtaiEta;    }
      void                 SetDeltaEtaSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaEtaSuperClTrkAtVtx = x;   }
      void                 SetDeltaEtaSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaEtaSeedClTrkAtCalo = x;   }
      void                 SetDeltaPhiSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaPhiSuperClTrkAtVtx = x;   }
      void                 SetDeltaPhiSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaPhiSeedClTrkAtCalo = x;   }
      void                 SetE33(Double_t E33)                   { fE33 = E33;                    }
      void                 SetE55(Double_t E55)                   { fE55 = E55;                    }
      void                 SetESeedClusterOverPout(Double_t x)    { fESeedClusterOverPout = x;     }
      void                 SetESuperClusterOverP(Double_t x)      { fESuperClusterOverP = x;       }
      void                 SetEcalJurassicIso(Double_t iso )      { fEcalJurassicIsolation = iso;  }
      void	           SetGsfTrk(const Track* t)                     
                             { fGsfTrackRef = t; ClearCharge(); }
      void                 SetHadronicOverEm(Double_t x)          { fHadronicOverEm = x;           }
      void                 SetHcalIsolation(Double_t iso )        { fHcalJurassicIsolation = iso;  }
      void                 SetIDLikelihood(Double_t likelihood)   { fIDLikelihood = likelihood;    }
      void                 SetIsEnergyScaleCorrected(Bool_t x)    { fIsEnergyScaleCorrected = x;   }
      void                 SetIsMomentumCorrected(Bool_t x)       { fIsMomentumCorrected = x;      }
      void                 SetNumberOfClusters(Double_t x)        { fNumberOfClusters = x;         }
      void                 SetPIn(Double_t PIn)                   { fPIn = PIn;                    }
      void                 SetPOut(Double_t POut)                 { fPOut = POut;                  }
      void                 SetPassLooseID(Double_t passLooseID)   { fPassLooseID = passLooseID;    }
      void                 SetPassTightID(Double_t passTightID)   { fPassTightID = passTightID;    }
      void                 SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi);
      void	           SetSuperCluster(const SuperCluster* sc) 
                             { fSuperClusterRef = sc; }
      void	           SetTrackerTrk(const Track* t)                 
                             { fTrackerTrackRef = t; ClearCharge(); }
      void                 SetTrackIsolation(Double_t trkiso)     { fTrackIsolation = trkiso;      }
      const Track         *TrackerTrk()            const { return fTrackerTrackRef.Obj();          }
      Double_t             TrackIsolation()        const { return fTrackIsolation;                 }
      const Track         *Trk()                   const { return BestTrk();                       }

    protected:
      Double_t             GetMass()               const          { return 0.51099892e-3;          }
      void                 GetMom()                const;

      Vect3C               fMom;                       //stored three-momentum
      Ref<Track>           fGsfTrackRef;               //gsf track reference
      Ref<Track>           fTrackerTrackRef;           //tracker track reference
      Ref<SuperCluster>    fSuperClusterRef;           //reference to SuperCluster
      Double32_t           fESuperClusterOverP;        //[0,0,14]super cluster e over p ratio
      Double32_t           fESeedClusterOverPout;      //[0,0,14]seed cluster e over p mom
      Double32_t           fDeltaEtaSuperClTrkAtVtx;   //[0,0,14]delta eta of super cluster with trk
      Double32_t           fDeltaEtaSeedClTrkAtCalo;   //[0,0,14]delta eta of seeed cluster with trk
      Double32_t           fDeltaPhiSuperClTrkAtVtx;   //[0,0,14]delta phi of super cluster with trk
      Double32_t           fDeltaPhiSeedClTrkAtCalo;   //[0,0,14]delta phi of seeed cluster with trk
      Double32_t           fHadronicOverEm;            //[0,0,14]hadronic over em fraction
      Double32_t           fNumberOfClusters;          //[0,0,14]number of associated clusters
      Double32_t           fE33;                       //[0,0,14]3x3 crystal energy
      Double32_t           fE55;                       //[0,0,14]5x5 crystal energy
      Double32_t           fCovEtaEta;                 //[0,0,14]variance eta-eta
      Double32_t           fCoviEtaiEta;               //[0,0,14]covariance eta-eta (in crystals)
      Double32_t           fCovEtaPhi;                 //[0,0,14]covariance eta-phi
      Double32_t           fCovPhiPhi;                 //[0,0,14]covariance phi-phi
      Double32_t           fCaloIsolation;             //[0,0,14]isolation based on rechits
      Double32_t           fCaloTowerIsolation;        //[0,0,14]isolation based on calo towers
      Double32_t           fTrackIsolation;            //[0,0,14]isolation based on tracks
      Double32_t           fEcalJurassicIsolation;     //[0,0,14]ecal jura iso
      Double32_t           fHcalJurassicIsolation;     //[0,0,14]hcal jura iso
      Double32_t           fPassLooseID;               //[0,0,14]pass loose id
      Double32_t           fPassTightID;               //[0,0,14]pass tight id
      Double32_t           fIDLikelihood;              //[0,0,14]likelihood value
      Double32_t           fPIn;                       //[0,0,14]momentum at vtx
      Double32_t           fPOut;                      //[0,0,14]momentum at ecal surface
      Bool_t               fIsEnergyScaleCorrected;    //class dependent escale correction
      Bool_t               fIsMomentumCorrected;       //class dependent E-p combination 
      Int_t                fClassification;            //classification (see GsfElectron.h)

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
  // Get momentum of the electron. We use an explicitly stored three vector, with the pdg mass,
  // since the momentum vector may be computed non-trivially in cmssw

  fCachedMom.SetCoordinates(fMom.Rho(),fMom.Eta(),fMom.Phi(),GetMass());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::ESeedClusterOverPIn() const
{
  // Return energy of the SuperCluster seed divided by the magnitude 
  // of the track momentum at the vertex.
  
  return SCluster()->Seed()->Energy() / PIn();
}

//-------------------------------------------------------------------------------------------------
inline void mithep::Electron::SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi)
{
  // Set three-vector
  
  fMom.Set(pt,eta,phi);
  ClearMom();
}
#endif
