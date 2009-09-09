//--------------------------------------------------------------------------------------------------
// $Id: CaloMet.h,v 1.4 2009/03/18 15:44:32 loizides Exp $
//
// CaloMet
//
// Class to hold CaloMet specific information based on caloremetric information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CALOMET_H
#define MITANA_DATATREE_CALOMET_H
 
#include "MitAna/DataTree/interface/Met.h"

namespace mithep 
{
  class CaloMet : public Met
  {
    public:
      CaloMet() :
        fCaloMetSig(0), fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInpHF(0), fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) {}
      CaloMet(Double_t mex, Double_t mey) : 
        Met(mex,mey),
        fCaloMetSig(0), fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInpHF(0), fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) {}

      Double_t                     CaloSumEtInpHF()     const { return fCaloSumEtInpHF;         }
      Double_t                     CaloSumEtInmHF()     const { return fCaloSumEtInmHF;         }  
      Double_t                     CaloMetInpHF()       const { return fCaloMetInpHF;           }
      Double_t                     CaloMetInmHF()       const { return fCaloMetInmHF;           }
      Double_t                     CaloMetPhiInpHF()    const { return fCaloMetPhiInpHF;        }
      Double_t                     CaloMetPhiInmHF()    const { return fCaloMetPhiInmHF;        }
      Double_t                     EmEtFraction()       const { return fEmEtFraction;           }
      Double_t                     EmEtInEB()           const { return fEmEtInEB;               }
      Double_t                     EmEtInEE()           const { return fEmEtInEE;               }
      Double_t                     EmEtInHF()           const { return fEmEtInHF;               }
      Double_t                     EtFractionHadronic() const { return fEtFractionHadronic;     }
      Double_t                     HadEtInHB()          const { return fHadEtInHB;              }
      Double_t                     HadEtInHO()          const { return fHadEtInHO;              }  
      Double_t                     HadEtInHE()          const { return fHadEtInHE;              }
      Double_t                     HadEtInHF()          const { return fHadEtInHF;              }
      Met                         *MakeCopy()           const { return new CaloMet(*this);      }
      Double_t                     MaxEtInEmTowers()    const { return fMaxEtInEmTowers;        }
      Double_t                     MaxEtInHadTowers()   const { return fMaxEtInHadTowers;       }
      Double_t                     CaloMetSig()         const { return fCaloMetSig;             }
      EObjType                     ObjType()            const { return kCaloMet;                }
      void                         SetCaloSumEtInpHF(Double_t x)     { fCaloSumEtInpHF = x;     }
      void                         SetCaloSumEtInmHF(Double_t x)     { fCaloSumEtInmHF = x;     }
      void                         SetCaloMetInpHF(Double_t x)       { fCaloMetInpHF = x;       }
      void                         SetCaloMetInmHF(Double_t x)       { fCaloMetInmHF = x;       }
      void                         SetCaloMetPhiInpHF(Double_t x)    { fCaloMetPhiInpHF = x;    }
      void                         SetCaloMetPhiInmHF(Double_t x)    { fCaloMetPhiInmHF = x;    }
      void                         SetEmEtFraction(Double_t x)       { fEmEtFraction = x;       }
      void                         SetEtFractionHadronic(Double_t x) { fEtFractionHadronic = x; }
      void                         SetHadEtInHB(Double_t x)          { fHadEtInHB = x;          }
      void                         SetHadEtInHO(Double_t x)          { fHadEtInHO = x;          }
      void                         SetHadEtInHE(Double_t x)          { fHadEtInHE = x;          }
      void                         SetHadEtInHF(Double_t x)          { fHadEtInHF = x;          }
      void                         SetEmEtInEB(Double_t x)           { fEmEtInEB = x;           }
      void                         SetEmEtInEE(Double_t x)           { fEmEtInEE = x;           }
      void                         SetEmEtInHF(Double_t x)           { fEmEtInHF = x;           }
      void                         SetMaxEtInEmTowers(Double_t x)    { fMaxEtInEmTowers = x;    }
      void                         SetMaxEtInHadTowers(Double_t x)   { fMaxEtInHadTowers = x;   }
      void                         SetCaloMetSig(Double_t x)         { fCaloMetSig = x;         }
      
    protected:

      Double32_t                   fCaloMetSig;          //[0,0,14]calo met significance
      Double32_t                   fMaxEtInEmTowers;     //[0,0,14]max ET deposited in ECAL towers
      Double32_t                   fMaxEtInHadTowers;    //[0,0,14]max ET deposited in HCAL towers
      Double32_t                   fEtFractionHadronic;  //[0,0,14]event hadronic scaler ET fraction
      Double32_t                   fEmEtFraction;        //[0,0,14]event em scalar ET fraction
      Double32_t                   fHadEtInHB;           //[0,0,14]event hadronic scalar ET in HB
      Double32_t                   fHadEtInHO;           //[0,0,14]event hadronic scalar ET in HO
      Double32_t                   fHadEtInHE;           //[0,0,14]event hadronic scalar ET in HE
      Double32_t                   fHadEtInHF;           //[0,0,14]event hadronic scalar ET in HF
      Double32_t                   fEmEtInEB;            //[0,0,14]event em scalar ET in EB
      Double32_t                   fEmEtInEE;            //[0,0,14]event em scalar ET in EE
      Double32_t                   fEmEtInHF;            //[0,0,14]event em scalar ET from HF
      Double32_t                   fCaloSumEtInpHF;      //[0,0,14]SumET in HF+
      Double32_t                   fCaloSumEtInmHF;      //[0,0,14]SumET in HF-
      Double32_t                   fCaloMetInpHF;        //[0,0,14]MET in HF+
      Double32_t                   fCaloMetInmHF;        //[0,0,14]MET in HF-
      Double32_t                   fCaloMetPhiInpHF;     //[0,0,14]MET-phi in HF+
      Double32_t                   fCaloMetPhiInmHF;     //[0,0,14]MET-phi in HF-
    
    ClassDef(CaloMet, 1) // Missing transverse energy class
  };
}
#endif
