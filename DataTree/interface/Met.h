//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.9 2009/02/18 15:38:54 loizides Exp $
//
// Met
//
// Class to store missing transverse energy information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MET_H
#define MITANA_DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() :
        fMex(0), fMey(0), fSumEt(0), fMetSig(0), fElongit(0), 
        fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) { SetClearBit(); }
      Met(Double_t mex, Double_t mey) : 
        fMex(mex), fMey(mey), fSumEt(0), fMetSig(0), fElongit(0), 
        fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) { SetClearBit(); }

      Double_t                     CaloSumEtInpHF()     const { return fCaloSumEtInpHF;         }
      Double_t                     CaloSumEtInmHF()     const { return fCaloSumEtInmHF;         }  
      Double_t                     CaloMetInpHF()       const { return fCaloMetInpHF;           }
      Double_t                     CaloMetInmHF()       const { return fCaloMetInmHF;           }
      Double_t                     CaloMetPhiInpHF()    const { return fCaloMetPhiInpHF;        }
      Double_t                     CaloMetPhiInmHF()    const { return fCaloMetPhiInmHF;        }
      const FArrDouble32          &Dmex()               const { return fDmex;                   }
      const FArrDouble32          &Dmey()               const { return fDmey;                   }
      const FArrDouble32          &DSumEt()             const { return fDSumEt;                 }
      Double_t                     EmEtFraction()       const { return fEmEtFraction;           }
      Double_t                     EmEtInEB()           const { return fEmEtInEB;               }
      Double_t                     EmEtInEE()           const { return fEmEtInEE;               }
      Double_t                     EmEtInHF()           const { return fEmEtInHF;               }
      Double_t                     Elongitudinal()      const { return fElongit;                }
      Double_t                     EtFractionHadronic() const { return fEtFractionHadronic;     }
      Double_t                     HadEtInHB()          const { return fHadEtInHB;              }
      Double_t                     HadEtInHO()          const { return fHadEtInHO;              }  
      Double_t                     HadEtInHE()          const { return fHadEtInHE;              }
      Double_t                     HadEtInHF()          const { return fHadEtInHF;              }
      Double_t                     MaxEtInEmTowers()    const { return fMaxEtInEmTowers;        }
      Double_t                     MaxEtInHadTowers()   const { return fMaxEtInHadTowers;       }
      Double_t                     MetSig()             const { return fMetSig;                 }
      EObjType                     ObjType()            const { return kMet;                    }
      Double_t                     SumEt()              const { return fSumEt;                  }
      void                         PushCorrectionX(Double_t x)       { fDmex.Add(x);            }
      void                         PushCorrectionY(Double_t x)       { fDmey.Add(x);            }
      void                         PushCorrectionSumEt(Double_t x)   { fDSumEt.Add(x);          }
      void                         SetCaloSumEtInpHF(Double_t x)     { fCaloSumEtInpHF = x;     }
      void                         SetCaloSumEtInmHF(Double_t x)     { fCaloSumEtInmHF = x;     }
      void                         SetCaloMetInpHF(Double_t x)       { fCaloMetInpHF = x;       }
      void                         SetCaloMetInmHF(Double_t x)       { fCaloMetInmHF = x;       }
      void                         SetCaloMetPhiInpHF(Double_t x)    { fCaloMetPhiInpHF = x;    }
      void                         SetCaloMetPhiInmHF(Double_t x)    { fCaloMetPhiInmHF = x;    }
      void                         SetEmEtFraction(Double_t x)       { fEmEtFraction = x;       }
      void                         SetElongitudinal(Double_t x)      { fElongit = x;            }
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
      void                         SetMetSig(Double_t x)             { fMetSig = x;             }
      void                         SetSumEt(Double_t x)              { fSumEt = x;              }
      
    protected:
      void                         Clear(Option_t * /*option*/ ="");
      void	                   GetMom()             const;

      Double32_t                   fMex;                 //x-component
      Double32_t                   fMey;                 //y-component              
      Double32_t                   fSumEt;               //scalar sum of ET over all objects
      Double32_t                   fMetSig;              //MET Significance = MET / sqrt(SumET)
      Double32_t                   fElongit;             //z-comp. of vector E sum over all inputs
      FArrDouble32                 fDmex;                //array of all corr. applied to MEx
      FArrDouble32                 fDmey;                //array of all corr. applied to MEy
      FArrDouble32                 fDSumEt;              //array of all corr. applied to SumET
      Double32_t                   fMaxEtInEmTowers;     //max ET deposited in ECAL towers
      Double32_t                   fMaxEtInHadTowers;    //max ET deposited in HCAL towers
      Double32_t                   fEtFractionHadronic;  //event hadronic scaler ET fraction
      Double32_t                   fEmEtFraction;        //event em scalar ET fraction
      Double32_t                   fHadEtInHB;           //event hadronic scalar ET in HB
      Double32_t                   fHadEtInHO;           //event hadronic scalar ET in HO
      Double32_t                   fHadEtInHE;           //event hadronic scalar ET in HE
      Double32_t                   fHadEtInHF;           //event hadronic scalar ET in HF
      Double32_t                   fEmEtInEB;            //event electromagnetic scalar ET in EB
      Double32_t                   fEmEtInEE;            //event electromagnetic scalar ET in EE
      Double32_t                   fEmEtInHF;            //event electromagnetic scalar ET from HF
      Double32_t                   fCaloSumEtInpHF;      //SumET in HF+
      Double32_t                   fCaloSumEtInmHF;      //SumET in HF-
      Double32_t                   fCaloMetInpHF;        //MET in HF+
      Double32_t                   fCaloMetInmHF;        //MET in HF-
      Double32_t                   fCaloMetPhiInpHF;     //MET-phi in HF+
      Double32_t                   fCaloMetPhiInmHF;     //MET-phi in HF-
    
    ClassDef(Met, 1) // Missing transverse energy class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::Clear(Option_t *)
{ 
  // Clear by deleting the std::vectors.
  
  fDmex.Clear();
  fDmey.Clear();
  fDSumEt.Clear();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::GetMom() const
{
  // Get momentum values from stored values.

  Double_t pt = TMath::Sqrt(fMex*fMex+fMey*fMey);
  Double_t phi = TMath::ATan2(fMey,fMex);
  fCachedMom.SetCoordinates(pt,0,phi,0);
}
#endif
