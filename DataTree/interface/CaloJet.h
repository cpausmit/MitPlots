//--------------------------------------------------------------------------------------------------
// $Id: CaloJet.h,v 1.7 2012/03/28 12:15:34 paus Exp $
//
// CaloJet
//
// This class holds information about reconstructed jet based on calorimeter towers.
//
// Authors: S.Xie, C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CALOJET_H
#define MITANA_DATATREE_CALOJET_H
 
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/CaloTower.h"

namespace mithep 
{
  class CaloJet : public Jet
  {
    public:
      CaloJet() : fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0),
                  fEnergyFractionEm(0), fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0),
                  fHadEnergyInHF(0), fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0),
                  fTowersArea(0), fHPD(0), fRBX(0), fN90Hits(0), fSubDetector1(0), fSubDetector2(0),
                  fSubDetector3(0), fSubDetector4(0), fRestrictedEMF(0), fNHCalTowers(0),
                  fNECalTowers(0), fApproximatefHPD(0), fApproximatefRBX(0), fHitsInN90(0),
                  fNHits2RPC(0), fNHits3RPC(0), fNHitsRPC(0) {}
      CaloJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Jet(px,py,pz,e),
                  fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0),
                  fEnergyFractionEm(0), fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0),
                  fHadEnergyInHF(0), fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0),
                  fTowersArea(0), fHPD(0), fRBX(0), fN90Hits(0), fSubDetector1(0), fSubDetector2(0),
                  fSubDetector3(0), fSubDetector4(0), fRestrictedEMF(0), fNHCalTowers(0),
                  fNECalTowers(0), fApproximatefHPD(0), fApproximatefRBX(0), fHitsInN90(0),
                  fNHits2RPC(0), fNHits3RPC(0), fNHitsRPC(0) {}

      void                AddTower(const CaloTower *t)        { fTowers.Add(t);                  }
      Bool_t              HasTower(const CaloTower *t)  const { return fTowers.HasObject(t);     }
      UInt_t              NTowers()                     const { return fTowers.Entries();        }
      const CaloTower    *Tower(UInt_t i)               const { return fTowers.At(i);            }
      UInt_t              NConstituents()               const { return NTowers();                }
      EObjType            ObjType()                     const { return kCaloJet;                 }  
      Double_t            EmEnergyInEB()                const { return fEmEnergyInEB;            } 
      Double_t            EmEnergyInEE()                const { return fEmEnergyInEE;            } 
      Double_t            EmEnergyInHF()                const { return fEmEnergyInHF;            } 
      Double_t            EnergyFractionH()             const { return fEnergyFractionH;         }
      Double_t            EnergyFractionEm()            const { return fEnergyFractionEm;        }
      Double_t            HadEnergyInHO()               const { return fHadEnergyInHO;           } 
      Double_t            HadEnergyInHB()               const { return fHadEnergyInHB;           } 
      Double_t            HadEnergyInHF()               const { return fHadEnergyInHF;           } 
      Double_t            HadEnergyInHE()               const { return fHadEnergyInHE;           }
      Jet                *MakeCopy()                    const { return new CaloJet(*this);       }
      Double_t            MaxEInEmTowers()              const { return fMaxEInEmTowers;          }
      Double_t            MaxEInHadTowers()             const { return fMaxEInHadTowers;         }
      void                SetEmEnergyInEB(Double_t val)       { fEmEnergyInEB     = val;         } 
      void                SetEmEnergyInEE(Double_t val)       { fEmEnergyInEE     = val;         } 
      void                SetEmEnergyInHF(Double_t val)       { fEmEnergyInHF     = val;         } 
      void                SetEnergyFractionH(Double_t val)    { fEnergyFractionH  = val;         }
      void                SetEnergyFractionEm(Double_t val)   { fEnergyFractionEm = val;         }
      void                SetHadEnergyInHO(Double_t val)      { fHadEnergyInHO    = val;         } 
      void                SetHadEnergyInHB(Double_t val)      { fHadEnergyInHB    = val;         } 
      void                SetHadEnergyInHF(Double_t val)      { fHadEnergyInHF    = val;         } 
      void                SetHadEnergyInHE(Double_t val)      { fHadEnergyInHE    = val;         } 
      void                SetMaxEInEmTowers(Double_t val)     { fMaxEInEmTowers   = val;         }
      void                SetMaxEInHadTowers(Double_t val)    { fMaxEInHadTowers  = val;         }
      void                SetTowersArea(Double_t val)         { fTowersArea       = val;         }
      void                SetFHPD(Double_t val)               { fHPD = val;                      }
      void                SetFRBX(Double_t val)               { fRBX = val;                      }
      void                SetN90Hits(Int_t val)               { fN90Hits = val;                  }
      void                SetFSubDetector1(Double_t val)      { fSubDetector1 = val;             }
      void                SetFSubDetector2(Double_t val)      { fSubDetector2 = val;             }
      void                SetFSubDetector3(Double_t val)      { fSubDetector3 = val;             }
      void                SetFSubDetector4(Double_t val)      { fSubDetector4 = val;             }
      void                SetRestrictedEMF(Double_t val)      { fRestrictedEMF = val;            }
      void                SetNHCalTowers(Int_t val)           { fNHCalTowers = val;              }
      void                SetNECalTowers(Int_t val)           { fNECalTowers = val;              }
      void                SetApproximatefHPD(Double_t val)    { fApproximatefHPD = val;          }
      void                SetApproximatefRBX(Double_t val)    { fApproximatefRBX = val;          }
      void                SetHitsInN90(Int_t val)             { fHitsInN90 = val;                }
      void                SetNHits2RPC(Int_t val)             { fNHits2RPC = val;                }
      void                SetNHits3RPC(Int_t val)             { fNHits3RPC = val;                }
      void                SetNHitsRPC(Int_t val)              { fNHitsRPC = val;                 }
      Double_t            TowersArea()                  const { return fTowersArea;              }
      Double_t            FHPD()                        const { return fHPD;                     }
      Double_t            FRBX()                        const { return fRBX;                     }
      UInt_t              N90Hits()                     const { return fN90Hits;                 }
      Double_t            FSubDetector1()               const { return fSubDetector1;            }
      Double_t            FSubDetector2()               const { return fSubDetector2;            }
      Double_t            FSubDetector3()               const { return fSubDetector3;            }
      Double_t            FSubDetector4()               const { return fSubDetector4;            }
      Double_t            RestrictedEMF()               const { return fRestrictedEMF;           }
      UInt_t              NHCalTowers()                 const { return fNHCalTowers;             }
      UInt_t              NECalTowers()                 const { return fNECalTowers;             }
      Double_t            ApproximatefHPD()             const { return fApproximatefHPD;         }
      Double_t            ApproximatefRBX()             const { return fApproximatefRBX;         }
      UInt_t              HitsInN90()                   const { return fHitsInN90;               }
      UInt_t              NHits2RPC()                   const { return fNHits2RPC;               }
      UInt_t              NHits3RPC()                   const { return fNHits3RPC;               }
      UInt_t              NHitsRPC()                    const { return fNHitsRPC;                }

      // Some structural tools
      void                Mark(UInt_t i = 1)            const;

    protected:

      Double32_t          fMaxEInEmTowers;    //[0,0,14]maximum energy in EM towers
      Double32_t          fMaxEInHadTowers;   //[0,0,14]maximum energy in HCAL towers
      Double32_t          fEnergyFractionH;   //[0,0,14]hadronic energy fraction
      Double32_t          fEnergyFractionEm;  //[0,0,14]electromagnetic energy fraction
      Double32_t          fHadEnergyInHB;     //[0,0,14]hadronic energy in HB
      Double32_t          fHadEnergyInHO;     //[0,0,14]hadronic energy in HO
      Double32_t          fHadEnergyInHE;     //[0,0,14]hadronic energy in HE
      Double32_t          fHadEnergyInHF;     //[0,0,14]hadronic energy in HF
      Double32_t          fEmEnergyInEB;      //[0,0,14]electromagnetic energy in EB
      Double32_t          fEmEnergyInEE;      //[0,0,14]electromagnetic energy in EE
      Double32_t          fEmEnergyInHF;      //[0,0,14]electromagnetic energy extracted from HF
      Double32_t          fTowersArea;        //[0,0,14]area of contributing towers
      Double32_t          fHPD;               //[0,0,14]energy from hottest hpd
      Double32_t          fRBX;               //[0,0,14]energy fraction from hottest rbx
      Int_t               fN90Hits;           //number of hits comprising 90 percent of the energy
      Double32_t          fSubDetector1;      //[0,0,14]
      Double32_t          fSubDetector2;      //[0,0,14]
      Double32_t          fSubDetector3;      //[0,0,14]
      Double32_t          fSubDetector4;      //[0,0,14]
      Double32_t          fRestrictedEMF;     //[0,0,14]
      Int_t               fNHCalTowers;
      Int_t               fNECalTowers;
      Double32_t          fApproximatefHPD;   //[0,0,14]
      Double32_t          fApproximatefRBX;   //[0,0,14]
      Int_t               fHitsInN90;
      Int_t               fNHits2RPC;
      Int_t               fNHits3RPC;
      Int_t               fNHitsRPC;
      RefArray<CaloTower> fTowers;            //calotowers in jet

    ClassDef(CaloJet, 2) // CaloJet class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CaloJet::Mark(UInt_t i) const
{
  // mark myself
  mithep::DataObject::Mark(i);
  // mark my dependencies if they are there
  fTowers.Mark(i);
}

#endif
