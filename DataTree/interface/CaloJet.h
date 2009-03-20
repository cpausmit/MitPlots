//--------------------------------------------------------------------------------------------------
// $Id: CaloJet.h,v 1.3 2009/03/18 15:44:31 loizides Exp $
//
// CaloJet
//
// This class holds information about reconstructed jet based on calorimeter towers.
//
// Authors: S.Xie, C.Loizides, J.Bendavid
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
                  fTowersArea(0) {}
      CaloJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Jet(px,py,pz,e),
                  fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0),
                  fEnergyFractionEm(0), fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0),
                  fHadEnergyInHF(0), fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0),
                  fTowersArea(0) {}

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
      Double_t            TowersArea()                  const { return fTowersArea;              }

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
      RefArray<CaloTower> fTowers;            //calotowers in jet

    ClassDef(CaloJet, 1) // CaloJet class
  };
}
#endif
