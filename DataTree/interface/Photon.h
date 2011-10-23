//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.41 2011/10/08 18:21:02 bendavid Exp $
//
// Photon
//
// This class holds the reconstructed photon quantities.
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PHOTON_H
#define MITANA_DATATREE_PHOTON_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class Photon : public Particle
  {
    public:
      Photon() : 
        fR9(0),fHadOverEm(0),fHcalDepth1OverEcal(0),
        fHcalDepth2OverEcal(0), fMaxEnergyXtal(0), fE15(0), fE25(0), fE33(0),
        fE55(0), fCovEtaEta(0), fCoviEtaiEta(0),
        fEcalRecHitIso(0),fHcalRecHitIso(0), fHcalTowerSumEtDr04(0),
        fHcalDepth1TowerSumEtDr04(0), fHcalDepth2TowerSumEtDr04(0), fSolidConeTrkIso(0),
        fHollowConeTrkIso(0),fSolidConeNTrk(0),fHollowConeNTrk(0), fEcalRecHitIsoDr03(0),
        fHcalTowerSumEtDr03(0), fHcalDepth1TowerSumEtDr03(0), fHcalDepth2TowerSumEtDr03(0),
        fSolidConeTrkIsoDr03(0), fHollowConeTrkIsoDr03(0),fSolidConeNTrkDr03(0),
        fHollowConeNTrkDr03(0), fPFChargedHadronIso(0), fPFNeutralHadronIso(0), fPFPhotonIso(0),
        fHasPixelSeed(0), fIsEB(0), fIsEE(0), fIsEBGap(0),
        fIsEEGap(0),fIsEBEEGap(0), fIsLooseEM(0),fIsLoosePhoton(0), fIsTightPhoton(0),
        fIsConverted(0), fEnergyErr(-99.), fEnergyErrSmeared(-99.), fEnergySmearing(0.),
        fEnergyRegr(0.), fEnergyErrRegr(0.), fEnergyPhoFix(0.), fEnergyErrPhoFix(0.) {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) :    
        fMom(FourVector(px,py,pz,e)), 
        fR9(0),fHadOverEm(0),fHcalDepth1OverEcal(0),
        fHcalDepth2OverEcal(0), fMaxEnergyXtal(0), fE15(0), fE25(0), fE33(0),
        fE55(0), fCovEtaEta(0), fCoviEtaiEta(0),
        fEcalRecHitIso(0),fHcalRecHitIso(0), fHcalTowerSumEtDr04(0),
        fHcalDepth1TowerSumEtDr04(0), fHcalDepth2TowerSumEtDr04(0), fSolidConeTrkIso(0),
        fHollowConeTrkIso(0),fSolidConeNTrk(0),fHollowConeNTrk(0), fEcalRecHitIsoDr03(0),
        fHcalTowerSumEtDr03(0), fHcalDepth1TowerSumEtDr03(0), fHcalDepth2TowerSumEtDr03(0),
        fSolidConeTrkIsoDr03(0), fHollowConeTrkIsoDr03(0),fSolidConeNTrkDr03(0),
        fHollowConeNTrkDr03(0), fPFChargedHadronIso(0), fPFNeutralHadronIso(0), fPFPhotonIso(0),
        fHasPixelSeed(0), fIsEB(0), fIsEE(0), fIsEBGap(0),
        fIsEEGap(0),fIsEBEEGap(0), fIsLooseEM(0),fIsLoosePhoton(0), fIsTightPhoton(0),
        fIsConverted(0), fEnergyErr(-99.), fEnergyErrSmeared(-99.), fEnergySmearing(0.),
        fEnergyRegr(0.), fEnergyErrRegr(0.), fEnergyPhoFix(0.), fEnergyErrPhoFix(0.) {}

      const Conversion    *ConvCand(UInt_t i)         const { return fConversions.At(i);  }
      Double_t             EcalRecHitIsoDr03()        const { return fEcalRecHitIsoDr03;  }
      Double_t             EcalRecHitIsoDr04()        const { return fEcalRecHitIso;      }
      Double_t             EnergyErr()                const { return fEnergyErr;          }
      Double_t             EnergyErrSmeared()         const { return fEnergyErrSmeared;   }      
      Double_t             EnergySmearing()           const { return fEnergySmearing;     }      
      Double_t             EnergyRegr()               const { return fEnergyRegr;         }
      Double_t             EnergyErrRegr()            const { return fEnergyErrRegr;      }
      Double_t             EnergyPhoFix()             const { return fEnergyPhoFix;       }
      Double_t             EnergyErrPhoFix()          const { return fEnergyErrPhoFix;    }      
      Double_t             HadOverEm()                const { return fHadOverEm;          }
      Double_t             HcalDepth1OverEcal()       const { return fHcalDepth1OverEcal; }
      Double_t             HcalDepth2OverEcal()       const { return fHcalDepth2OverEcal; }
      Double_t             MaxEnergyXtal()            const { return fMaxEnergyXtal;      }
      Double_t             E15()                      const { return fE15;                }
      Double_t             E25()                      const { return fE25;                }
      Double_t             E33()                      const { return fE33;                }      
      Double_t             E55()                      const { return fE55;                }      
      ThreeVectorC         CaloPos()                  const;
      Double_t             CovEtaEta()                const { return fCovEtaEta;          }
      Double_t             CoviEtaiEta()              const { return fCoviEtaiEta;        }         
      Bool_t               HasPixelSeed()             const { return fHasPixelSeed;       }
      Double_t             HcalDepth1TowerSumEtDr03() const { return fHcalDepth1TowerSumEtDr03; }
      Double_t             HcalDepth1TowerSumEtDr04() const { return fHcalDepth1TowerSumEtDr04; }
      Double_t             HcalDepth2TowerSumEtDr03() const { return fHcalDepth2TowerSumEtDr03; }
      Double_t             HcalDepth2TowerSumEtDr04() const { return fHcalDepth2TowerSumEtDr04; }
      Double_t             HcalRecHitIso()            const { return fHcalRecHitIso;         } // *DEPRECATED*
      Double_t             HcalTowerSumEtDr03()       const { return fHcalTowerSumEtDr03;    }
      Double_t             HcalTowerSumEtDr04()       const { return fHcalTowerSumEtDr04;    }
      UShort_t             HollowConeNTrkDr03()       const { return fHollowConeNTrkDr03;    }
      UShort_t             HollowConeNTrkDr04()       const { return fHollowConeNTrk;        }
      Double_t             HollowConeTrkIsoDr03()     const { return fHollowConeTrkIsoDr03;  }
      Double_t             HollowConeTrkIsoDr04()     const { return fHollowConeTrkIso;      }
      Double_t             PFChargedHadronIso()       const { return fPFChargedHadronIso;    }
      Double_t             PFNeutralHadronIso()       const { return fPFNeutralHadronIso;    }
      Double_t             PFPhotonIso()              const { return fPFPhotonIso;           }      
      Bool_t               IsEB()                     const { return fIsEB;                  }
      Bool_t               IsEE()                     const { return fIsEE;                  }
      Bool_t               IsEBGap()                  const { return fIsEBGap;               }
      Bool_t               IsEEGap()                  const { return fIsEEGap;               }
      Bool_t               IsEBEEGap()                const { return fIsEBEEGap;             }
      Bool_t               IsLooseEM()                const { return fIsLooseEM;             } // *DEPRECATED*
      Bool_t               IsLoosePhoton()            const { return fIsLoosePhoton;         }
      Bool_t               IsTightPhoton()            const { return fIsTightPhoton;         }
      Bool_t               IsConverted()              const { return fIsConverted;           }
      ThreeVector          Mom3(const ThreeVector &v) const { return E()*(ThreeVector(CaloPos()) - v).Unit(); }
      FourVectorM          MomVtx(const ThreeVector &vtx)  const;
      UInt_t               NConversions()             const { return fConversions.Entries(); }
      EObjType             ObjType()                  const { return kPhoton;                }
      Double_t             R9()                       const { return fR9;                    }
      const SuperCluster  *SCluster()                 const { return fSuperClusterRef.Obj(); }
      Double_t             SolidConeTrkIsoDr03()      const { return fSolidConeTrkIsoDr03;   }
      Double_t             SolidConeTrkIsoDr04()      const { return fSolidConeTrkIso;       }
      UShort_t             SolidConeNTrkDr03()        const { return fSolidConeNTrkDr03;     }
      UShort_t             SolidConeNTrkDr04()        const { return fSolidConeNTrk;         }

      void                 AddConversion(const Conversion *c)      { fConversions.Add(c);    }
      void                 SetEnergyErr(Double_t x)                { fEnergyErr                = x; }
      void                 SetEnergyErrSmeared(Double_t x)         { fEnergyErrSmeared         = x; }
      void                 SetEnergySmearing(Double_t x)           { fEnergySmearing           = x; }
      void                 SetEnergyRegr(Double_t x)               { fEnergyRegr               = x; }
      void                 SetEnergyErrRegr(Double_t x)            { fEnergyErrRegr            = x; }
      void                 SetEnergyPhoFix(Double_t x)             { fEnergyPhoFix             = x; }
      void                 SetEnergyErrPhoFix(Double_t x)          { fEnergyErrPhoFix          = x; }      
      void                 SetIsConverted(Bool_t b)                { fIsConverted              = b; }
      void                 SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                 SetSuperCluster(const SuperCluster* sc) { fSuperClusterRef = sc; }
      void                 SetR9(Double_t x)                       { fR9                       = x; }
      void                 SetHadOverEm(Double_t x)                { fHadOverEm                = x; }
      void                 SetHcalDepth1OverEcal(Double_t x)       { fHcalDepth1OverEcal       = x; }
      void                 SetHcalDepth2OverEcal(Double_t x)       { fHcalDepth2OverEcal       = x; } 
      void                 SetMaxEnergyXtal(Double_t x)            { fMaxEnergyXtal            = x; }
      void                 SetE15(Double_t x)                      { fE15                      = x; }
      void                 SetE25(Double_t x)                      { fE25                      = x; }
      void                 SetE33(Double_t x)                      { fE33                      = x; }      
      void                 SetE55(Double_t x)                      { fE55                      = x; }      
      void                 SetCovEtaEta(Double_t x)                { fCovEtaEta                = x; }
      void                 SetCoviEtaiEta(Double_t x)              { fCoviEtaiEta              = x; }      
      void                 SetHasPixelSeed(Bool_t x)               { fHasPixelSeed             = x; }
      void                 SetEcalRecHitIsoDr04(Double_t x)        { fEcalRecHitIso            = x; }
      void                 SetHcalTowerSumEtDr04(Double_t x)       { fHcalTowerSumEtDr04       = x; }
      void                 SetHcalDepth1TowerSumEtDr04(Double_t x) { fHcalDepth1TowerSumEtDr04 = x; }
      void                 SetHcalDepth2TowerSumEtDr04(Double_t x) { fHcalDepth2TowerSumEtDr04 = x; }
      void                 SetSolidConeTrkIsoDr04(Double_t x)      { fSolidConeTrkIso          = x; }
      void                 SetHollowConeTrkIsoDr04(Double_t x)     { fHollowConeTrkIso         = x; }
      void                 SetSolidConeNTrkDr04(UShort_t x)        { fSolidConeNTrk            = x; }
      void                 SetHollowConeNTrkDr04(UShort_t x)       { fHollowConeNTrk           = x; }
      void                 SetEcalRecHitIsoDr03(Double_t x)        { fEcalRecHitIsoDr03        = x; }
      void                 SetHcalTowerSumEtDr03(Double_t x)       { fHcalTowerSumEtDr03       = x; }
      void                 SetHcalDepth1TowerSumEtDr03(Double_t x) { fHcalDepth1TowerSumEtDr03 = x; }
      void                 SetHcalDepth2TowerSumEtDr03(Double_t x) { fHcalDepth2TowerSumEtDr03 = x; }
      void                 SetSolidConeTrkIsoDr03(Double_t x)      { fSolidConeTrkIsoDr03      = x; }
      void                 SetHollowConeTrkIsoDr03(Double_t x)     { fHollowConeTrkIsoDr03     = x; }
      void                 SetSolidConeNTrkDr03(UShort_t x)        { fSolidConeNTrkDr03        = x; }
      void                 SetHollowConeNTrkDr03(UShort_t x)       { fHollowConeNTrkDr03       = x; }
      void                 SetPFChargedHadronIso(Double_t x)       { fPFChargedHadronIso       = x; }
      void                 SetPFNeutralHadronIso(Double_t x)       { fPFNeutralHadronIso       = x; }
      void                 SetPFPhotonIso(Double_t x)              { fPFPhotonIso              = x; }      
      void                 SetIsEB(Bool_t x)                       { fIsEB                     = x; }
      void                 SetIsEE(Bool_t x)                       { fIsEE                     = x; }
      void                 SetIsEBGap(Bool_t x)                    { fIsEBGap                  = x; }
      void                 SetIsEEGap(Bool_t x)                    { fIsEEGap                  = x; }
      void                 SetIsEBEEGap(Bool_t x)                  { fIsEBEEGap                = x; }
      void                 SetIsLooseEM(Bool_t x)                  { fIsLooseEM                = x; }
      void                 SetIsLoosePhoton(Bool_t x)              { fIsLoosePhoton            = x; }
      void                 SetIsTightPhoton(Bool_t x)              { fIsTightPhoton            = x; }
      void                 SetCaloPosXYZ(Double_t x, Double_t y, Double_t z) { fCaloPos.SetXYZ(x,y,z); }
      void                 SetPV(const Vertex *v)                  { fPVRef                    = v; }
      Bool_t               HasPV()                           const { return fPVRef.IsValid();       }
      const Vertex        *PV()                              const { return fPVRef.Obj();           }



    protected:
      void                 GetMom() const;

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
      Double32_t           fEcalRecHitIso;            //[0,0,14]ecal rechit based isolation dR 0.4 *RENAMING*
      Double32_t           fHcalRecHitIso;            //[0,0,14]hcal rechit based isolation dR 0.4 - *DEPRECATED*
      Double32_t           fHcalTowerSumEtDr04;       //[0,0,14]hcal tower based isolation dR 0.4
      Double32_t           fHcalDepth1TowerSumEtDr04; //[0,0,14]hcal depth1 tower based isolation dR 0.4
      Double32_t           fHcalDepth2TowerSumEtDr04; //[0,0,14]hcal depth2 tower based isolation dR 0.4
      Double32_t           fSolidConeTrkIso;          //[0,0,14]sum track pT in cone of dR 0.4 *RENAMING*
      Double32_t           fHollowConeTrkIso;         //[0,0,14]as above excluding the core, dR 0.4 *RENAMING*
      UShort_t             fSolidConeNTrk;            //number of tracks in a cone of dR 0.4 *RENAMING*
      UShort_t             fHollowConeNTrk;           //as above excluding the core, dR 0.4 *RENAMING*
      Double32_t           fEcalRecHitIsoDr03;        //[0,0,14]ecal rechit based isolation dR 0.3
      Double32_t           fHcalTowerSumEtDr03;       //[0,0,14] hcal tower based isolation dR 0.3
      Double32_t           fHcalDepth1TowerSumEtDr03; //[0,0,14]hcal depth1 tower based isolation dR 0.3
      Double32_t           fHcalDepth2TowerSumEtDr03; //[0,0,14]hcal depth2 tower based isolation dR 0.3
      Double32_t           fSolidConeTrkIsoDr03;      //[0,0,14]sum track pT in cone of dR 0.3
      Double32_t           fHollowConeTrkIsoDr03;     //[0,0,14]as above excluding the core, dR 0.3
      UShort_t             fSolidConeNTrkDr03;        //number of tracks in a cone of dR 0.3
      UShort_t             fHollowConeNTrkDr03;       //as above excluding the core, dR 0.3
      Double32_t           fPFChargedHadronIso;       //[0,0,14]pf isolation, charged hadrons
      Double32_t           fPFNeutralHadronIso;       //[0,0,14]pf isolation, neutral hadrons
      Double32_t           fPFPhotonIso;              //[0,0,14]pf isolation, photons
      Bool_t               fHasPixelSeed;             //=true if super cluster has matched seed
      Bool_t               fIsEB;                     //=true if photon is ECal barrel
      Bool_t               fIsEE;                     //=true if photon is ECAL endcap
      Bool_t               fIsEBGap;                  //=true photon is in ECAL barrel crystal gap
      Bool_t               fIsEEGap;                  //=true photon is in ECAL endcap crystal gap
      Bool_t               fIsEBEEGap;                //=true photon is in boundary between EB/EE
      Bool_t               fIsLooseEM;                //=true if loose em cuts are passed *DEPRECATED*
                                                      // LooseEM corresponds to supercluster preselection in 3_1_X
                                                      //so this variable is now always true for photon objects
      Bool_t               fIsLoosePhoton;            //=true if loose photon cuts are passed
      Bool_t               fIsTightPhoton;            //=true if tight photon cuts are passed
      Bool_t               fIsConverted;              //=true if photon converted
      RefArray<Conversion> fConversions;              //refs to associated conversion candidates
      Ref<SuperCluster>    fSuperClusterRef;          //ref to associated super cluster
      Ref<Vertex>          fPVRef;                    //ref to associated primary vertex
      Double32_t           fEnergyErr;                //[0,0,14]uncertainty on energy measurement (in GeV), eg from variance regression
      Double32_t           fEnergyErrSmeared;         //[0,0,14]uncertainty on energy measurement (in GeV), eg from variance regression with added smearing
      Double32_t           fEnergySmearing;           //[0,0,14]additional energy smearing applied or required wrt MC
      Double32_t           fEnergyRegr;               //[0,0,14]regression energy (computed at filler time)
      Double32_t           fEnergyErrRegr;            //[0,0,14]regression energy uncertainty (computed at filler time)
      Double32_t           fEnergyPhoFix;             //[0,0,14]PhotonFix energy (computed at filler time)
      Double32_t           fEnergyErrPhoFix;          //[0,0,14]PhotonFix energy uncertainty (computed at filler time)

    ClassDef(Photon,10) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline mithep::ThreeVectorC mithep::Photon::CaloPos() const
{
  // Get caloposition
  mithep::ThreeVectorC calopos = fCaloPos.V();
  if (calopos.Rho()>1.0) {
    return calopos;
  }
  else {
    return SCluster()->Point();
  }
  
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set momentum vector.

  fMom.SetXYZT(px, py, pz, e);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline mithep::FourVectorM mithep::Photon::MomVtx(const ThreeVector &vtx) const
{
  // Get momentum values from stored values.
  ThreeVector momv = Mom3(vtx);
  FourVectorM newmom;
  
  newmom.SetCoordinates(momv.Rho(),momv.Eta(),momv.Phi(),0.); 
  
  return newmom;
}

#endif
