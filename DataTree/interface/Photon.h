//--------------------------------------------------------------------------------------------------
// Photon
//
// This class holds the reconstructed photon quantities.
//
// Authors: J.Bendavid, C.Loizides, C.Paus, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PHOTON_H
#define MITANA_DATATREE_PHOTON_H

#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/PFCandidate.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep
{
  class Photon : public Particle
  {
  public:
    Photon() {}

    // Contents of the Photons
    UInt_t               NConversionsD()              const { return fConversionsD.Entries(); }
    UInt_t               NConversionsS()              const { return fConversionsS.Entries(); }
    DecayParticle const* ConversionD(UInt_t i)        const { return fConversionsD.At(i); }
    DecayParticle const* ConversionS(UInt_t i)        const { return fConversionsS.At(i); }
    Double_t             EcalRecHitIsoDr03()          const { return fEcalRecHitIsoDr03;  }
    Double_t             EcalRecHitIsoDr04()          const { return fEcalRecHitIso;      }
    Double_t             EnergyErr()                  const { return fEnergyErr;          }
    Double_t             EnergyErrSmeared()           const { return fEnergyErrSmeared;   }
    Double_t             EnergySmearing()             const { return fEnergySmearing;     }
    Double_t             EnergyErrSmearing()          const { return fEnergyErrSmearing;  }
    Double_t             EnergyRegr()                 const { return fEnergyRegr;         }
    Double_t             EnergyErrRegr()              const { return fEnergyErrRegr;      }
    Double_t             EnergyPhoFix()               const { return fEnergyPhoFix;       }
    Double_t             EnergyErrPhoFix()            const { return fEnergyErrPhoFix;    }
    Double_t             EnergyScale()                const { return fEnergyScale;        }
    Double_t             HadOverEm()                  const { return fHadOverEm;          }
    Double_t             HcalDepth1OverEcal()         const { return fHcalDepth1OverEcal; }
    Double_t             HcalDepth2OverEcal()         const { return fHcalDepth2OverEcal; }
    Double_t             MaxEnergyXtal()              const { return fMaxEnergyXtal;      }
    Double_t             E15()                        const { return fE15;                }
    Double_t             E25()                        const { return fE25;                }
    Double_t             E33()                        const { return fE33;                }
    Double_t             E55()                        const { return fE55;                }
    ThreeVectorC         CaloPos()                    const;
    Double_t             CovEtaEta()                  const { return fCovEtaEta;          }
    Double_t             CoviEtaiEta(Bool_t force = kFALSE) const
    { return force || fCoviEtaiEta5x5 < 0. ? fCoviEtaiEta : fCoviEtaiEta5x5; }
    Double_t             CoviEtaiEta5x5()             const { return fCoviEtaiEta5x5;     }
    Bool_t               HasPixelSeed()               const { return fHasPixelSeed;       }
    Double_t             HcalDepth1TowerSumEtDr03()   const { return fHcalDepth1TowerSumEtDr03; }
    Double_t             HcalDepth1TowerSumEtDr04()   const { return fHcalDepth1TowerSumEtDr04; }
    Double_t             HcalDepth2TowerSumEtDr03()   const { return fHcalDepth2TowerSumEtDr03; }
    Double_t             HcalDepth2TowerSumEtDr04()   const { return fHcalDepth2TowerSumEtDr04; }
    Double_t             HcalTowerSumEtDr03()         const { return fHcalTowerSumEtDr03;    }
    Double_t             HcalTowerSumEtDr04()         const { return fHcalTowerSumEtDr04;    }
    UShort_t             HollowConeNTrkDr03()         const { return fHollowConeNTrkDr03;    }
    UShort_t             HollowConeNTrkDr04()         const { return fHollowConeNTrk;        }
    Double_t             HollowConeTrkIsoDr03()       const { return fHollowConeTrkIsoDr03;  }
    Double_t             HollowConeTrkIsoDr04()       const { return fHollowConeTrkIso;      }
    Double_t             PFChargedHadronIso()         const { return fPFChargedHadronIso;    }
    Double_t             PFNeutralHadronIso()         const { return fPFNeutralHadronIso;    }
    Double_t             PFPhotonIso()                const { return fPFPhotonIso;           }
    Bool_t               IsEB()                       const { return fIsEB;                  }
    Bool_t               IsEE()                       const { return fIsEE;                  }
    Bool_t               IsEBGap()                    const { return fIsEBGap;               }
    Bool_t               IsEEGap()                    const { return fIsEEGap;               }
    Bool_t               IsEBEEGap()                  const { return fIsEBEEGap;             }
    Bool_t               IsLoosePhoton()              const { return fIsLoosePhoton;         }
    Bool_t               IsTightPhoton()              const { return fIsTightPhoton;         }
    Bool_t               IsConverted()                const { return fIsConverted;           }
    ThreeVector          Mom3(ThreeVector const& v)   const
    { return E() * (ThreeVector(CaloPos()) - v).Unit(); }
    FourVectorM          MomVtx(ThreeVector const& v) const;
    EObjType             ObjType()                    const { return kPhoton;                }
    SuperCluster const*  ECALOnlySCluster()           const { return fPFSuperClusterRef.Obj(); }
    SuperCluster const*  PFSCluster()                 const { return ECALOnlySCluster(); } // backward compatibility
    UInt_t               NFootprintCandidates()       const { return fFootprintCandidates.Entries(); }
    PFCandidate const*   FootprintCandidate(UInt_t i) const { return fFootprintCandidates.At(i); }
    Bool_t               IsInFootprint(PFCandidate const* cand) const
    { return fFootprintCandidates.HasObject(cand); }
    Double_t             R9()                         const { return fR9;                    }
    SuperCluster const*  SCluster()                   const { return fSuperClusterRef.Obj(); }
    Double_t             SolidConeTrkIsoDr03()        const { return fSolidConeTrkIsoDr03;   }
    Double_t             SolidConeTrkIsoDr04()        const { return fSolidConeTrkIso;       }
    UShort_t             SolidConeNTrkDr03()          const { return fSolidConeNTrkDr03;     }
    UShort_t             SolidConeNTrkDr04()          const { return fSolidConeNTrk;         }
    Double_t             EtaWidth()                   const
    { return fEtaWidth >= 0. ? fEtaWidth : SCluster()->EtaWidth(); }
    Double_t             PhiWidth()                   const
    { return fPhiWidth >= 0. ? fPhiWidth : SCluster()->PhiWidth(); }
    Double_t             HadOverEmTow()               const { return fHadOverEmTow;       }
    Double_t             HcalIsoTowDr03()             const { return fHCalIsoTowDr03;    }
    Double_t             HcalIsoTowDr04()             const { return fHCalIsoTowDr04;    } 
    Double_t             S4Ratio()                    const
    { return fS4Ratio >= 0. ? fS4Ratio : SCluster()->Seed()->E2x2() / SCluster()->Seed()->E5x5(); }
    Double_t             EffSigmaRR()                 const
    { return fEffSigmaRR >= 0. ? fEffSigmaRR : sqrt(SCluster()->PsEffWidthSigmaXX() * SCluster()->PsEffWidthSigmaXX() + SCluster()->PsEffWidthSigmaYY() * SCluster()->PsEffWidthSigmaYY()); }
    Double_t             MipChi2()                    const { return fMipChi2;               }
    Double_t             MipTotEnergy()               const { return fMipTotEnergy;          }
    Double_t             MipSlope()                   const { return fMipSlope;              }
    Double_t             MipIntercept()               const { return fMipIntercept;          }
    Int_t                MipNhitCone()                const { return fMipNHitCone;           }
    Bool_t               MipIsHalo()                  const { return fMipIsHalo;             } 
    ThreeVector          MatchHePlusPos()             const { return fMatchHePlusPos.V();    }
    Double_t             MatchHePlusEn()              const { return fMatchHePlusEn;         }
    Double_t             MatchHePlusTime()            const { return fMatchHePlusTime;       }
    ThreeVector          MatchHeMinusPos()            const { return fMatchHeMinusPos.V();    }
    Double_t             MatchHeMinusEn()             const { return fMatchHeMinusEn;         }
    Double_t             MatchHeMinusTime()           const { return fMatchHeMinusTime;       }
    ThreeVector          MatchHePlusPosDR15()         const { return fMatchHePlusPosDR15.V(); }
    Double_t             MatchHePlusEnDR15()          const { return fMatchHePlusEnDR15;      }
    Double_t             MatchHePlusTimeDR15()        const { return fMatchHePlusTimeDR15;    }
    ThreeVector          MatchHeMinusPosDR15()        const { return fMatchHeMinusPosDR15.V();}
    Double_t             MatchHeMinusEnDR15()         const { return fMatchHeMinusEnDR15;     }
    Double_t             MatchHeMinusTimeDR15()       const { return fMatchHeMinusTimeDR15;   }
    Bool_t               HasPV()                      const { return fPVRef.IsValid();      }
    const Vertex        *PV()                         const { return fPVRef.Obj();          }
    Double_t             VtxProb()                    const { return fVtxProb;              }
    Double_t             IdMva()                      const { return fIdMva;                }
    // Some structural tools
    void                 Mark(UInt_t i=1)             const override;

    void                 SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi);
    void                 SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
    void                 AddConversionD(const DecayParticle *c)  { fConversionsD.Add(c); }
    void                 AddConversionS(const DecayParticle *c)  { fConversionsS.Add(c); }
    void                 SetEnergyErr(Double_t x)                { fEnergyErr               = x; }
    void                 SetEnergyErrSmeared(Double_t x)         { fEnergyErrSmeared        = x; }
    void                 SetEnergySmearing(Double_t x)           { fEnergySmearing          = x; }
    void                 SetEnergyErrSmearing(Double_t x)        { fEnergyErrSmearing       = x; }
    void                 SetEnergyRegr(Double_t x)               { fEnergyRegr              = x; }
    void                 SetEnergyErrRegr(Double_t x)            { fEnergyErrRegr           = x; }
    void                 SetEnergyPhoFix(Double_t x)             { fEnergyPhoFix            = x; }
    void                 SetEnergyErrPhoFix(Double_t x)          { fEnergyErrPhoFix         = x; }
    void                 SetEnergyScale(Double_t x)              { fEnergyScale             = x; }
    void                 SetIsConverted(Bool_t b)                { fIsConverted             = b; }
    void                 SetSuperCluster(const SuperCluster* s)  { fSuperClusterRef         = s; }
    void                 SetR9(Double_t x)                       { fR9                      = x; }
    void                 SetHadOverEm(Double_t x)                { fHadOverEm               = x; }
    void                 SetHcalDepth1OverEcal(Double_t x)       { fHcalDepth1OverEcal      = x; }
    void                 SetHcalDepth2OverEcal(Double_t x)       { fHcalDepth2OverEcal      = x; }
    void                 SetMaxEnergyXtal(Double_t x)            { fMaxEnergyXtal           = x; }
    void                 SetE15(Double_t x)                      { fE15                     = x; }
    void                 SetE25(Double_t x)                      { fE25                     = x; }
    void                 SetE33(Double_t x)                      { fE33                     = x; }
    void                 SetE55(Double_t x)                      { fE55                     = x; }
    void                 SetCovEtaEta(Double_t x)                { fCovEtaEta               = x; }
    void                 SetCoviEtaiEta(Double_t x)              { fCoviEtaiEta             = x; }
    void                 SetCoviEtaiEta5x5(Double_t x)           { fCoviEtaiEta5x5          = x; }
    void                 SetHasPixelSeed(Bool_t x)               { fHasPixelSeed            = x; }
    void                 SetEcalRecHitIsoDr04(Double_t x)        { fEcalRecHitIso           = x; }
    void                 SetHcalTowerSumEtDr04(Double_t x)       { fHcalTowerSumEtDr04      = x; }
    void                 SetHcalDepth1TowerSumEtDr04(Double_t x) { fHcalDepth1TowerSumEtDr04= x; }
    void                 SetHcalDepth2TowerSumEtDr04(Double_t x) { fHcalDepth2TowerSumEtDr04= x; }
    void                 SetSolidConeTrkIsoDr04(Double_t x)      { fSolidConeTrkIso         = x; }
    void                 SetHollowConeTrkIsoDr04(Double_t x)     { fHollowConeTrkIso        = x; }
    void                 SetSolidConeNTrkDr04(UShort_t x)        { fSolidConeNTrk           = x; }
    void                 SetHollowConeNTrkDr04(UShort_t x)       { fHollowConeNTrk          = x; }
    void                 SetEcalRecHitIsoDr03(Double_t x)        { fEcalRecHitIsoDr03       = x; }
    void                 SetHcalTowerSumEtDr03(Double_t x)       { fHcalTowerSumEtDr03      = x; }
    void                 SetHcalDepth1TowerSumEtDr03(Double_t x) { fHcalDepth1TowerSumEtDr03= x; }
    void                 SetHcalDepth2TowerSumEtDr03(Double_t x) { fHcalDepth2TowerSumEtDr03= x; }
    void                 SetSolidConeTrkIsoDr03(Double_t x)      { fSolidConeTrkIsoDr03     = x; }
    void                 SetHollowConeTrkIsoDr03(Double_t x)     { fHollowConeTrkIsoDr03    = x; }
    void                 SetSolidConeNTrkDr03(UShort_t x)        { fSolidConeNTrkDr03       = x; }
    void                 SetHollowConeNTrkDr03(UShort_t x)       { fHollowConeNTrkDr03      = x; }
    void                 SetPFChargedHadronIso(Double_t x)       { fPFChargedHadronIso      = x; }
    void                 SetPFNeutralHadronIso(Double_t x)       { fPFNeutralHadronIso      = x; }
    void                 SetPFPhotonIso(Double_t x)              { fPFPhotonIso             = x; }
    void                 SetIsEB(Bool_t x)                       { fIsEB                    = x; }
    void                 SetIsEE(Bool_t x)                       { fIsEE                    = x; }
    void                 SetIsEBGap(Bool_t x)                    { fIsEBGap                 = x; }
    void                 SetIsEEGap(Bool_t x)                    { fIsEEGap                 = x; }
    void                 SetIsEBEEGap(Bool_t x)                  { fIsEBEEGap               = x; }
    void                 SetIsLoosePhoton(Bool_t x)              { fIsLoosePhoton           = x; }
    void                 SetIsTightPhoton(Bool_t x)              { fIsTightPhoton           = x; }
    void                 SetCaloPosXYZ(Double_t x, Double_t y, Double_t z)
    { fCaloPos.SetXYZ(x,y,z); }
    void                 SetPV(Vertex const* v)                  { fPVRef                   = v; }
    void                 SetECALOnlySuperCluster(SuperCluster const* s)
    { fPFSuperClusterRef = s;      }
    void                 AddFootprintCandidate(PFCandidate const* c)
    { fFootprintCandidates.Add(c); }
    void                 SetVtxProb(Double_t x)                  { fVtxProb                 = x; }
    void                 SetIdMva(Double_t x)                    { fIdMva                   = x; }
    void                 SetEtaWidth(Double_t x)                 { fEtaWidth                = x; }
    void                 SetPhiWidth(Double_t x)                 { fPhiWidth                = x; }
    void                 SetHadOverEmTow(Double_t x)             { fHadOverEmTow = x;  }
    void                 SetHCalIsoTowDr03(Double_t x)           { fHCalIsoTowDr03 = x; }
    void                 SetHCalIsoTowDr04(Double_t x)           { fHCalIsoTowDr04 = x; } 
    void                 SetS4Ratio(Double_t x)                  { fS4Ratio = x;        }
    void                 SetEffSigmaRR(Double_t x)               { fEffSigmaRR = x;     }
    void                 SetMipChi2(Double_t x)                  { fMipChi2 = x;              }
    void                 SetMipTotEnergy(Double_t x)             { fMipTotEnergy = x;         }
    void                 SetMipSlope(Double_t x)                 { fMipSlope = x;             }
    void                 SetMipIntercept(Double_t x)             { fMipIntercept = x;         }
    void                 SetMipNhitCone(Int_t x)                 { fMipNHitCone = x;          }
    void                 SetMipIsHalo(Bool_t x)                  { fMipIsHalo = x;            } 
    void                 SetMatchHePlusPos(Double_t x, Double_t y, Double_t z)
    {  fMatchHePlusPos.SetXYZ(x,y,z);     }
    void                 SetMatchHePlusEn(Double_t x)            { fMatchHePlusEn = x;                }
    void                 SetMatchHePlusTime(Double_t x)          { fMatchHePlusTime = x;              }
    void                 SetMatchHeMinusPos(Double_t x, Double_t y, Double_t z)
    {  fMatchHeMinusPos.SetXYZ(x,y,z);    }
    void                 SetMatchHeMinusEn(Double_t x)           { fMatchHeMinusEn = x;               }
    void                 SetMatchHeMinusTime(Double_t x)         { fMatchHeMinusTime = x;             }
    void                 SetMatchHePlusPosDR15(Double_t x, Double_t y, Double_t z)
    {  fMatchHePlusPosDR15.SetXYZ(x,y,z); }
    void                 SetMatchHePlusEnDR15(Double_t x)        { fMatchHePlusEnDR15 = x;            }
    void                 SetMatchHePlusTimeDR15(Double_t x)      { fMatchHePlusTimeDR15 = x;          }
    void                 SetMatchHeMinusPosDR15(Double_t x, Double_t y, Double_t z)
    {  fMatchHeMinusPosDR15.SetXYZ(x,y,z);}
    void                 SetMatchHeMinusEnDR15(Double_t x)       { fMatchHeMinusEnDR15 = x;           }
    void                 SetMatchHeMinusTimeDR15(Double_t x)     { fMatchHeMinusTimeDR15 = x;         }

  protected:
    void                 GetMom() const override;

    Vect4M               fMom;                      //four momentum vector
    Vect3C               fCaloPos;                  //shower position
    Double32_t           fR9;                       //[0,0,14]r9=e3x3/etotal variable
    Double32_t           fHadOverEm;                //[0,0,14]hadronic over em fraction
    Double32_t           fHcalDepth1OverEcal;       //[0,0,14]hadronic over em fraction depth1
    Double32_t           fHcalDepth2OverEcal;       //[0,0,14]hadronic over em fraction depth2
    Double32_t           fMaxEnergyXtal;            //[0,0,14]maximum single crystal energy
    Double32_t           fE15;                      //[0,0,14]1x5 crystal energy
    Double32_t           fE25;                      //[0,0,14]2x5 crystal energy
    Double32_t           fE33;                      //[0,0,14]3x3 crystal energy
    Double32_t           fE55;                      //[0,0,14]5x5 crystal energy
    Double32_t           fCovEtaEta;                //[0,0,14]variance eta-eta
    Double32_t           fCoviEtaiEta;              //[0,0,14]covariance eta-eta (in crystals)
    Double32_t           fCoviEtaiEta5x5 = -1.;     //[0,0,14]"full 5x5" covariance eta-eta (in crystals)
    Double32_t           fEcalRecHitIso;            //[0,0,14]ecal rechit bsd isodR 0.4 *RENAME*
    Double32_t           fHcalTowerSumEtDr04;       //[0,0,14]hcal tower bsd isodR 0.4
    Double32_t           fHcalDepth1TowerSumEtDr04; //[0,0,14]hcal dp1 tw bsd isodR 0.4
    Double32_t           fHcalDepth2TowerSumEtDr04; //[0,0,14]hcal dp2 tw bsd isodR 0.4
    Double32_t           fSolidConeTrkIso;          //[0,0,14]sum track pT in cone dR 0.4 *RENAME*
    Double32_t           fHollowConeTrkIso;         //[0,0,14]as above excl. core, dR 0.4 *RENAME*
    UShort_t             fSolidConeNTrk;            //number of tracks in cone dR 0.4 *RENAME*
    UShort_t             fHollowConeNTrk;           //as above excl. core, dR 0.4 *RENAME*
    Double32_t           fEcalRecHitIsoDr03;        //[0,0,14]ecal rechit based iso dR 0.3
    Double32_t           fHcalTowerSumEtDr03;       //[0,0,14] hcal tower based iso dR 0.3
    Double32_t           fHcalDepth1TowerSumEtDr03; //[0,0,14]hcal depth1 tower based iso dR 0.3
    Double32_t           fHcalDepth2TowerSumEtDr03; //[0,0,14]hcal depth2 tower based iso dR 0.3
    Double32_t           fSolidConeTrkIsoDr03;      //[0,0,14]sum track pT in cone of dR 0.3
    Double32_t           fHollowConeTrkIsoDr03;     //[0,0,14]as above excluding the core, dR 0.3
    UShort_t             fSolidConeNTrkDr03;        //number of tracks in a cone of dR 0.3
    UShort_t             fHollowConeNTrkDr03;       //as above excluding the core, dR 0.3
    Double32_t           fPFChargedHadronIso;       //[0,0,14]pf iso, charged hadrons
    Double32_t           fPFNeutralHadronIso;       //[0,0,14]pf iso, neutral hadrons
    Double32_t           fPFPhotonIso;              //[0,0,14]pf iso, photons
    Bool_t               fHasPixelSeed = kFALSE;       //if super cluster has matched seed
    Bool_t               fIsEB = kFALSE;               //if photon is ECal barrel
    Bool_t               fIsEE = kFALSE;               //if photon is ECAL endcap
    Bool_t               fIsEBGap = kFALSE;            //photon is in ECAL barrel crystal gap
    Bool_t               fIsEEGap = kFALSE;            //photon is in ECAL endcap crystal gap
    Bool_t               fIsEBEEGap = kFALSE;          //photon is in boundary between EB/EE
    Bool_t               fIsLoosePhoton = kFALSE;      //if loose photon cuts are passed
    Bool_t               fIsTightPhoton = kFALSE;      //if tight photon cuts are passed
    Bool_t               fIsConverted = kFALSE;        //if photon converted
    Ref<SuperCluster>    fSuperClusterRef;    //ref to associated super cluster (refined unbiased PF supercluster in >= 7XY)
    Ref<Vertex>          fPVRef;              //ref to associated primary vertex
    Double32_t           fEnergyErr = -99.;          //[0,0,14]ene uncer. from var. regr.
    Double32_t           fEnergyErrSmeared = -99.;   //[0,0,14]ene uncer. from var. regr., smeared
    Double32_t           fEnergySmearing;     //[0,0,14]addit. ene smearing applied wrt MC
    Double32_t           fEnergyRegr;         //[0,0,14]regr. ene (filler time)
    Double32_t           fEnergyErrRegr;      //[0,0,14]regr. ene uncertainty (filler time)
    Double32_t           fEnergyPhoFix;       //[0,0,14]PhotonFix energy (filler time)
    Double32_t           fEnergyErrPhoFix;    //[0,0,14]PhotonFix energy uncertainty (filler time)
    Double32_t           fVtxProb;            //[0,0,14]Probability linked PV is correct
    Double32_t           fIdMva = -99.;              //[0,0,14]output of photon id mva
    Double32_t           fEtaWidth = -99.;           //[0,0,14]output of photon id mva
    Double32_t           fPhiWidth = -99.;           //[0,0,14]output of photon id mva
    Ref<SuperCluster>    fPFSuperClusterRef;  //ref to associated ECAL-only super cluster (PF cluster associated by geom in <=5XY, parentSuperCluster (ECAL-only PF mustache SC) in >=7XY) see below
    RefArray<PFCandidate> fFootprintCandidates; //ref to PF candidates in the footprint, association made by ParticleBasedIsolation algorithm
    Double32_t           fHadOverEmTow;       //[0,0,14]per-tower definition of hadronic/em energy fraction
    Double32_t           fHCalIsoTowDr03;     //[0,0,14]hcal isolation matched to per tower h/e definition
    Double32_t           fHCalIsoTowDr04;     //[0,0,14]hcal isolation matched to per tower h/e definition
    RefArray<DecayParticle> fConversionsD;        //refs to associated conversion candidates (using newer DecayParticle format)
    RefArray<DecayParticle> fConversionsS;        //refs to associated conversion candidates (using newer DecayParticle format) - single leg conversions
    Double32_t           fS4Ratio = -99.;           //[0,0,14]S4 ratio
    Double32_t           fEffSigmaRR = -99.;        //[0,0,14]preshower width variable
    Double32_t           fMipChi2 = -999.;               // mip fitted track chi2
    Double32_t           fMipTotEnergy = 999.;          // mip fitted track energy
    Double32_t           fMipSlope = 999.;              // mip fitted track slope
    Double32_t           fMipIntercept = 999.;          // mip fitted track intercept
    Int_t                fMipNHitCone = -1;           // mip fitted track nhits
    Bool_t               fMipIsHalo = kFALSE;             // mip fitted track is halo decision
    Vect3                fMatchHePlusPos;        // phi matched HBHE+ rechit pos
    Double32_t           fMatchHePlusEn = -1.;         // phi matched HBHE+ energy
    Double32_t           fMatchHePlusTime = -1000.;       // phi matched HBHE+ time
    Vect3                fMatchHeMinusPos;       // phi matched HBHE- rechit pos
    Double32_t           fMatchHeMinusEn = -1.;        // phi matched HBHE- energy
    Double32_t           fMatchHeMinusTime = -1000.;      // phi matched HBHE- time
    Vect3                fMatchHePlusPosDR15;    // phi matched HBHE+ rechit pos - 15 cm DR match window
    Double32_t           fMatchHePlusEnDR15 = -1.;     // phi matched HBHE+ energy - 15 cm DR match window
    Double32_t           fMatchHePlusTimeDR15 = -1000.;   // phi matched HBHE+ time - 15 cm DR match window
    Vect3                fMatchHeMinusPosDR15;   // phi matched HBHE- rechit pos - 15 cm DR match window
    Double32_t           fMatchHeMinusEnDR15 = -1.;    // phi matched HBHE- energy - 15 cm DR match window
    Double32_t           fMatchHeMinusTimeDR15 = -1000.;  // phi matched HBHE- time - 15 cm DR match window
    Double32_t           fEnergyErrSmearing;  //[0,0,14]addit. ene smearing applied to energy error wrt MC
    Double32_t           fEnergyScale = 1.;  //[0,0,14]Energy scale applied to photon

    // The following members are deprecated
    // (Cannot use pragma read for schema evolution when some members are missing? Causes seg fault at read..)
    //    RefArray<Conversion> fConversions;        //refs to associated conversion candidates
    //    Bool_t               fIsLooseEM;          //if loose em cuts are passed
    //    Double32_t           fHcalRecHitIso;      //[0,0,14]hcal rechit bsd isodR 0.4
    //    RefArray<PFCandidate> fPFPhotonsInMustache; //refs to photon-type PFCandidates inside of mustache region
    //    RefArray<PFCandidate> fPFPhotonsOutOfMustache; //refs to photon-type PFCandidates outside of mustache region
    // Accessors
    //    const Conversion    *ConvCand(UInt_t i)           const { return fConversions.At(i);  }
    //    Double_t             HcalRecHitIso()              const { return 0.;         }
    //    Bool_t               IsLooseEM()                  const { return true;             }
    //    UInt_t               NConversions()               const { return fConversions.Entries(); }
    //    UInt_t               NPFPhotonsInMustache()       const { return fPFPhotonsInMustache.Entries(); }
    //    UInt_t               NPFPhotonsOutOfMustache()    const { return fPFPhotonsOutOfMustache.Entries(); }
    //    const PFCandidate   *PFPhotonInMustache(UInt_t i) const { return fPFPhotonsInMustache.At(i); }
    //    const PFCandidate   *PFPhotonOutOfMustache(UInt_t i) const { return fPFPhotonsOutOfMustache.At(i); }
    //    void                 AddConversion(const Conversion *c)    { fConversions.Add(c); }
    //    void                 AddPFPhotonInMustache(const PFCandidate *c) { fPFPhotonsInMustache.Add(c); }
    //    void                 AddPFPhotonOutOfMustache(const PFCandidate *c) { fPFPhotonsOutOfMustache.Add(c); }
    //    void                 SetIsLooseEM(Bool_t x)                  { fIsLooseEM               = x; }

    // fPFSuperClusterRef: member object name is kept the same as <7XY so that old files can be read
    // Should in principle be possible to use schema evolution to convert it to something like fECALOnlySuperClusterRef
    // The problem is that process ID seems to be not set at the point where conversion rules are applied
    // which is strange since process ID is set in ProcIDRef::Streamer..

    ClassDef(Photon, 23) // Photon class
  };
}

inline
void
mithep::Photon::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fPVRef.IsValid())
    fPVRef.Obj()->Mark(ib);
  if (fSuperClusterRef.IsValid())
    fSuperClusterRef.Obj()->Mark(ib);
  if (fPFSuperClusterRef.IsValid())
    fPFSuperClusterRef.Obj()->Mark(ib);
  fConversionsD.Mark(ib);
  fConversionsS.Mark(ib);
  fFootprintCandidates.Mark(ib);
}

inline
mithep::ThreeVectorC
mithep::Photon::CaloPos() const
{
  // Get caloposition
  mithep::ThreeVectorC calopos = fCaloPos.V();
  if (calopos.Rho()>1.0)
    return calopos;
  else
    return SCluster()->Point();
}

inline
void
mithep::Photon::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M());
}

inline
void
mithep::Photon::SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi)
{
  fMom.Set(pt, eta, phi, 0.);
  ClearMom();
}

inline
void
mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{
  // Set momentum vector.

  fMom.SetXYZT(px, py, pz, e);
  ClearMom();
}

inline
mithep::FourVectorM
mithep::Photon::MomVtx(ThreeVector const& vtx) const
{
  // Get momentum values from stored values.
  ThreeVector momv = Mom3(vtx);
  FourVectorM newmom;

  newmom.SetCoordinates(momv.Rho(),momv.Eta(),momv.Phi(),0.);

  return newmom;
}

#endif
