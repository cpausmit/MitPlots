//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.35 2009/07/21 16:34:46 bendavid Exp $
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
      Electron() : 
        fESuperClusterOverP(0), fESeedClusterOverPout(0), fDeltaEtaSuperClTrkAtVtx(0),
        fDeltaEtaSeedClTrkAtCalo(0), fDeltaPhiSuperClTrkAtVtx(0), 
        fDeltaPhiSeedClTrkAtCalo(0), fFBrem(0), fHadronicOverEm(0), fHcalDepth1OverEcal(0),
        fHcalDepth2OverEcal(0), fNumberOfClusters(0), fE15(0), fE25Max(0),
        fE55(0), fCovEtaEta(0), fCoviEtaiEta(0),
        fCaloIsolation(0), fHcalJurassicIsolation(0),
        fHcalDepth1TowerSumEtDr04(0), fHcalDepth2TowerSumEtDr04(0),
        fEcalJurassicIsolation(0), fTrackIsolationDr04(0), fCaloTowerIsolation(0),
        fHcalDepth1TowerSumEtDr03(0), fHcalDepth2TowerSumEtDr03(0),
        fEcalRecHitSumEtDr03(0), fTrackIsolation(0), fPassLooseID(0),
        fPassTightID(0), fIDLikelihood(0), fPIn(0), fPOut(0), fFracSharedHits(0),
        fMva(0), fIsEnergyScaleCorrected(0), fIsMomentumCorrected(0),
        fClassification(0), fIsEB(), fIsEE(0), fIsEBEEGap(0), fIsEBEtaGap(0),
        fIsEBPhiGap(0), fIsEEDeeGap(0), fIsEERingGap(0),
        fIsEcalDriven(0), fIsTrackerDriven(0) {}

      const Track         *BestTrk()                const;
      Double_t             CaloIsolation()          const { return fCaloIsolation;       } // *DEPRECATED*
      Int_t                Classification()         const { return fClassification;      }
      Double_t             CovEtaEta()              const { return fCovEtaEta;           }
      Double_t             CoviEtaiEta()            const { return fCoviEtaiEta;         }
      Double_t             DeltaEtaSuperClusterTrackAtVtx() const 
                             { return fDeltaEtaSuperClTrkAtVtx; }
      Double_t             DeltaEtaSeedClusterTrackAtCalo() const 
                             { return fDeltaEtaSeedClTrkAtCalo; }
      Double_t             DeltaPhiSuperClusterTrackAtVtx() const 
                             { return fDeltaPhiSuperClTrkAtVtx; }
      Double_t             DeltaPhiSeedClusterTrackAtCalo() const 
                             { return fDeltaPhiSeedClTrkAtCalo; }
      Double_t             E15()                    const { return fE15;                }
      Double_t             E25Max()                 const { return fE25Max;             }
      Double_t             E55()                    const { return fE55;                }
      Double_t             ESuperClusterOverP()     const { return fESuperClusterOverP;            }
      Double_t             ESeedClusterOverPout()   const { return fESeedClusterOverPout;          }
      Double_t             ESeedClusterOverPIn()    const;
      Double_t             FBrem()                  const { return fFBrem;                         }
      Double_t             FBremOld()               const { return (PIn() - POut())/PIn();         }
      Double_t             FracSharedHits()         const { return fFracSharedHits;                }
      const Track         *GsfTrk()                 const { return fGsfTrackRef.Obj();             }
      Double_t             HadronicOverEm()         const { return fHadronicOverEm;                }
      Double_t             HcalDepth1OverEcal()     const { return fHcalDepth1OverEcal;            }
      Double_t             HcalDepth2OverEcal()     const { return fHcalDepth2OverEcal;            }
      Bool_t               HasGsfTrk()              const { return fGsfTrackRef.IsValid();         }
      Bool_t               HasTrackerTrk()          const { return fTrackerTrackRef.IsValid();     }
      Bool_t               HasSuperCluster()        const { return fSuperClusterRef.IsValid();     }
      Double_t             HcalIsolation()          const { return fHcalJurassicIsolation;         } // *DEPRECATED*
      Double_t             IDLikelihood()           const { return fIDLikelihood;                  }
      Bool_t               IsEnergyScaleCorrected() const { return fIsEnergyScaleCorrected;        }
      Bool_t               IsMomentumCorrected()    const { return fIsMomentumCorrected;           }
      Bool_t               IsEB()                   const { return fIsEB;                          }
      Bool_t               IsEE()                   const { return fIsEE;                          }
      Bool_t               IsEBEEGap()              const { return fIsEBEEGap;                     }
      Bool_t               IsEBEtaGap()             const { return fIsEBEtaGap;                    }
      Bool_t               IsEBPhiGap()             const { return fIsEBPhiGap;                    }
      Bool_t               IsEEDeeGap()             const { return fIsEEDeeGap;                    }
      Bool_t               IsEERingGap()            const { return fIsEERingGap;                   }
      Bool_t               IsEcalDriven()           const { return fIsEcalDriven;                  }
      Bool_t               IsTrackerDriven()        const { return fIsTrackerDriven;               }
      Double_t             Mva()                    const { return fMva;                           }
      Double_t             NumberOfClusters()       const { return fNumberOfClusters;              }
      EObjType             ObjType()                const { return kElectron;                      }
      Double_t             PassLooseID()            const { return fPassLooseID;                   }
      Double_t             PassTightID()            const { return fPassTightID;                   }
      Double_t             PIn()                    const { return fPIn;                           }
      Double_t             POut()                   const { return fPOut;                          }
      const SuperCluster  *SCluster()               const { return fSuperClusterRef.Obj();         }
      
      Double_t             EcalRecHitIsoDr04()      const { return fEcalJurassicIsolation;         }
      Double_t             HcalTowerSumEtDr04()     const { return HcalDepth1TowerSumEtDr04() +
                                                                   HcalDepth2TowerSumEtDr04();     }
      Double_t             HcalDepth1TowerSumEtDr04() const { return fHcalDepth1TowerSumEtDr04;    }
      Double_t             HcalDepth2TowerSumEtDr04() const { return fHcalDepth2TowerSumEtDr04;    }
      Double_t             TrackIsolationDr04()     const { return fTrackIsolationDr04;            }
      Double_t             EcalRecHitIsoDr03()      const { return fEcalRecHitSumEtDr03;           }
      Double_t             HcalTowerSumEtDr03()     const { return fCaloTowerIsolation;            }
      Double_t             HcalDepth1TowerSumEtDr03() const { return fHcalDepth1TowerSumEtDr03;    }
      Double_t             HcalDepth2TowerSumEtDr03() const { return fHcalDepth2TowerSumEtDr03;    }
      Double_t             TrackIsolationDr03()     const { return fTrackIsolation;                }
      
      
      void                 SetClassification(Int_t x)             { fClassification = x;           }
      void                 SetCovEtaEta(Double_t CovEtaEta)       { fCovEtaEta = CovEtaEta;        }
      void                 SetCoviEtaiEta(Double_t CoviEtaiEta)   { fCoviEtaiEta = CoviEtaiEta;    }
      void                 SetDeltaEtaSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaEtaSuperClTrkAtVtx = x;   }
      void                 SetDeltaEtaSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaEtaSeedClTrkAtCalo = x;   }
      void                 SetDeltaPhiSuperClusterTrackAtVtx(Double_t x)  
                             { fDeltaPhiSuperClTrkAtVtx = x;   }
      void                 SetDeltaPhiSeedClusterTrackAtCalo(Double_t x)  
                             { fDeltaPhiSeedClTrkAtCalo = x;   }
      void                 SetE15(Double_t x)                     { fE15 = x;                      }
      void                 SetE25Max(Double_t x)                  { fE25Max = x;                   }
      void                 SetE55(Double_t x)                     { fE55 = x;                      }
      void                 SetESeedClusterOverPout(Double_t x)    { fESeedClusterOverPout = x;     }
      void                 SetESuperClusterOverP(Double_t x)      { fESuperClusterOverP = x;       }
      void                 SetFBrem(Double_t x)                   { fFBrem = x;                    }
      void                 SetFracSharedHits(Double_t x)          { fFracSharedHits = x;           }
      void	           SetGsfTrk(const Track* t)                     
                             { fGsfTrackRef = t; ClearCharge(); }
      void                 SetHadronicOverEm(Double_t x)          { fHadronicOverEm = x;           }
      void                 SetHcalDepth1OverEcal(Double_t x)      { fHcalDepth1OverEcal = x;       }
      void                 SetHcalDepth2OverEcal(Double_t x)      { fHcalDepth2OverEcal = x;       }
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
      void                 SetEcalRecHitIsoDr04(Double_t x)        { fEcalJurassicIsolation = x;    }
      void                 SetHcalDepth1TowerSumEtDr04(Double_t x) { fHcalDepth1TowerSumEtDr04 = x; }
      void                 SetHcalDepth2TowerSumEtDr04(Double_t x) { fHcalDepth2TowerSumEtDr04 = x; }
      void                 SetTrackIsolationDr04(Double_t x)       { fTrackIsolationDr04 = x;       }
      void                 SetEcalRecHitIsoDr03(Double_t x)        { fEcalRecHitSumEtDr03 = x;      }
      void                 SetHcalTowerSumEtDr03(Double_t x)       { fCaloTowerIsolation = x;       }
      void                 SetHcalDepth1TowerSumEtDr03(Double_t x) { fHcalDepth1TowerSumEtDr03 = x; }
      void                 SetHcalDepth2TowerSumEtDr03(Double_t x) { fHcalDepth2TowerSumEtDr03 = x; }
      void                 SetTrackIsolationDr03(Double_t x)       { fTrackIsolation = x;   }
      void                 SetMva(Double_t x)                      { fMva = x;              }
      void                 SetIsEB(Bool_t b)                       { fIsEB = b;             }
      void                 SetIsEE(Bool_t b)                       { fIsEE = b;             }
      void                 SetIsEBEEGap(Bool_t b)                  { fIsEBEEGap = b;        }
      void                 SetIsEBEtaGap(Bool_t b)                 { fIsEBEtaGap = b;       }
      void                 SetIsEBPhiGap(Bool_t b)                 { fIsEBPhiGap = b;       }
      void                 SetIsEEDeeGap(Bool_t b)                 { fIsEEDeeGap = b;       }
      void                 SetIsEERingGap(Bool_t b)                { fIsEERingGap = b;      }
      void                 SetIsEcalDriven(Bool_t b)               { fIsEcalDriven = b;     }
      void                 SetIsTrackerDriven(Bool_t b)            { fIsTrackerDriven = b;  }
      
     
      const Track         *TrackerTrk()            const { return fTrackerTrackRef.Obj();   }
      const Track         *Trk()                   const { return BestTrk();                }

    protected:
      Double_t             GetMass()               const { return 0.51099892e-3;            }
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
      Double32_t           fFBrem;                     //[0,0,14]brem fraction
      Double32_t           fHadronicOverEm;            //[0,0,14]hadronic over em fraction *DEPRECATED*
      Double32_t           fHcalDepth1OverEcal;        //[0,0,14]hadronic over em fraction depth1
      Double32_t           fHcalDepth2OverEcal;        //[0,0,14]hadronic over em fraction depth2
      Double32_t           fNumberOfClusters;          //[0,0,14]number of associated clusters
      Double32_t           fE15;                       //[0,0,14]1x5 crystal energy
      Double32_t           fE25Max;                    //[0,0,14]2x5 crystal energy (max of two possible sums)
      Double32_t           fE55;                       //[0,0,14]5x5 crystal energy
      Double32_t           fCovEtaEta;                 //[0,0,14]variance eta-eta
      Double32_t           fCoviEtaiEta;               //[0,0,14]covariance eta-eta (in crystals)
      Double32_t           fCaloIsolation;             //[0,0,14](non-jura) ecal isolation based on rechits dR 0.3 *DEPRECATED*
      Double32_t           fHcalJurassicIsolation;     //[0,0,14]hcal jura iso dR 0.4 *DEPRECATED*
      Double32_t           fHcalDepth1TowerSumEtDr04;  //[0,0,14]hcal depth1 tower based isolation dR 0.4
      Double32_t           fHcalDepth2TowerSumEtDr04;  //[0,0,14]hcal depth2 tower based isolation dR 0.4
      Double32_t           fEcalJurassicIsolation;     //[0,0,14]ecal jura iso dR 0.4 *RENAMING*
      Double32_t           fTrackIsolationDr04;        //[0,0,14]isolation based on tracks dR 0.4
      Double32_t           fCaloTowerIsolation;        //[0,0,14]hcal tower based isolation dR 0.3 *DEPRECATED*
      Double32_t           fHcalDepth1TowerSumEtDr03;  //[0,0,14]hcal depth1 tower based isolation dR 0.3
      Double32_t           fHcalDepth2TowerSumEtDr03;  //[0,0,14]hcal depth2 tower based isolation dR 0.3
      Double32_t           fEcalRecHitSumEtDr03;       //[0,0,14]ecal jura iso dR 0.3
      Double32_t           fTrackIsolation;            //[0,0,14]isolation based on tracks dR 0.3 *RENAMING*
      Double32_t           fPassLooseID;               //[0,0,14]pass loose id
      Double32_t           fPassTightID;               //[0,0,14]pass tight id
      Double32_t           fIDLikelihood;              //[0,0,14]likelihood value
      Double32_t           fPIn;                       //[0,0,14]momentum at vtx
      Double32_t           fPOut;                      //[0,0,14]momentum at ecal surface
      Double32_t           fFracSharedHits;            //[0,0,14]fraction of shared hits btw gsf and std. track
      Double32_t           fMva;                       //[0,0,14] pflow mva output
      Bool_t               fIsEnergyScaleCorrected;    //class dependent escale correction
      Bool_t               fIsMomentumCorrected;       //class dependent E-p combination 
      Int_t                fClassification;            //classification (see GsfElectron.h)
      Bool_t               fIsEB;                      //is ECAL barrel
      Bool_t               fIsEE;                      //is ECAL Endcap
      Bool_t               fIsEBEEGap;                 //is in barrel-endcap gap
      Bool_t               fIsEBEtaGap;                //is in EB eta module gap
      Bool_t               fIsEBPhiGap;                //is in EB phi module gap
      Bool_t               fIsEEDeeGap;                //is in EE dee gap
      Bool_t               fIsEERingGap;               //is in EE ring gap
      Bool_t               fIsEcalDriven;              //is std. egamma electron
      Bool_t               fIsTrackerDriven;           //is pflow track-seeded electron

    ClassDef(Electron, 2) // Electron class
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
