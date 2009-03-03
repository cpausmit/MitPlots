//--------------------------------------------------------------------------------------------------
// $Id: Jet.h,v 1.17 2009/02/26 20:28:59 bendavid Exp $
//
// Jet
//
// Jet class to hold reconstructed jet information.
//
// Authors: S.Xie, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_JET_H
#define MITANA_DATATREE_JET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/CaloTower.h"

namespace mithep 
{
  class Jet : public Particle
  {
    public:
      enum ECorr { 
        L1 = 0, 
        L2,
        L3,
        L4,
        L5,
        L6,
        L7,
        Custom
      };
    
      Jet() : 
        fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0), fEnergyFractionEm(0),
        fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0), fHadEnergyInHF(0),
        fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0), fTowersArea(0), fN(0), 
        fN60(0), fN90(0), fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fImpactParameterMVABJetTagsDisc(0),
        fTrackCountingHighEffBJetTagsDisc(0), fTrackCountingHighPurBJetTagsDisc(0),
        fSoftMuonBJetTagsDisc(0), fSoftMuonNoIPBJetTagsDisc(0),
        fSoftElectronBJetTagsDisc(0), fL2RelativeCorrectionScale(0),
        fL3AbsoluteCorrectionScale(0), fL4EMFCorrectionScale(0),
        fL5FlavorCorrectionScale(0), fL7PartonCorrectionScale(0) {}
      Jet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fRawMom(FourVector(px,py,pz,e)),
        fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0), fEnergyFractionEm(0),
        fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0), fHadEnergyInHF(0),
        fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0), fTowersArea(0), fN(0), 
        fN60(0), fN90(0), fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fImpactParameterMVABJetTagsDisc(0),
        fTrackCountingHighEffBJetTagsDisc(0), fTrackCountingHighPurBJetTagsDisc(0),
        fSoftMuonBJetTagsDisc(0), fSoftMuonNoIPBJetTagsDisc(0),
        fSoftElectronBJetTagsDisc(0), fL2RelativeCorrectionScale(0),
        fL3AbsoluteCorrectionScale(0), fL4EMFCorrectionScale(0),
        fL5FlavorCorrectionScale(0), fL7PartonCorrectionScale(0) {}

      Double_t   Alpha()                       const { return fAlpha;                        }
      Double_t   Beta()                        const { return fBeta;                         }
      Double_t   CombinedSecondaryVertexBJetTagsDisc()          const 
                   { return fCombinedSecondaryVertexBJetTagsDisc;    } 
      Double_t   CombinedSecondaryVertexMVABJetTagsDisc()       const 
                   { return fCombinedSecondaryVertexMVABJetTagsDisc; }
      Double_t   CustomCorrectionScale()       const { return fCustomCorrectionScale;        }
      void       DisableCorrection(ECorr c)          { fCorrections.ClearBit(c); ClearMom(); }
      void       DisableCorrections()                { fCorrections.Clear(); ClearMom();     }
      Double_t   EmEnergyInEB()                const { return fEmEnergyInEB;                 } 
      Double_t   EmEnergyInEE()                const { return fEmEnergyInEE;                 } 
      Double_t   EmEnergyInHF()                const { return fEmEnergyInHF;                 } 
      void       EnableCorrection(ECorr c)           { fCorrections.SetBit(c); ClearMom();   }
      Bool_t     CorrectionActive(ECorr c)     const { return fCorrections.TestBit(c);       }
      Double_t   EnergyFractionH()             const { return fEnergyFractionH;              }
      Double_t   EnergyFractionEm()            const { return fEnergyFractionEm;             }
      Double_t   HadEnergyInHO()               const { return fHadEnergyInHO;                } 
      Double_t   HadEnergyInHB()               const { return fHadEnergyInHB;                } 
      Double_t   HadEnergyInHF()               const { return fHadEnergyInHF;                } 
      Double_t   HadEnergyInHE()               const { return fHadEnergyInHE;                }
      Bool_t     HasTower(const CaloTower *t)  const { return fTowers.HasObject(t);          }
      Double_t   ImpactParameterMVABJetTagsDisc()               const 
                   { return fImpactParameterMVABJetTagsDisc; }
      Double_t   JetProbabilityBJetTagsDisc()                   const 
                   { return fJetProbabilityBJetTagsDisc;     }
      Double_t   JetBProbabilityBJetTagsDisc()                  const 
                   { return fJetBProbabilityBJetTagsDisc;    }
      Int_t      MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      Double_t   MaxEInEmTowers()              const { return fMaxEInEmTowers;            }
      Double_t   MaxEInHadTowers()             const { return fMaxEInHadTowers;           }
      UShort_t   N()                           const { return fN;                         }
      UShort_t   N60()                         const { return fN60;                       }
      UShort_t   N90()                         const { return fN90;                       }
      UInt_t     NTowers()                     const { return fTowers.GetEntries();       }
      Double_t   L2RelativeCorrectionScale()   const { return fL2RelativeCorrectionScale; }
      Double_t   L3AbsoluteCorrectionScale()   const { return fL3AbsoluteCorrectionScale; }
      Double_t   L4EMFCorrectionScale()        const { return fL4EMFCorrectionScale;      }
      Double_t   L5FlavorCorrectionScale()     const { return fL5FlavorCorrectionScale;   }
      Double_t   L7PartonCorrectionScale()     const { return fL7PartonCorrectionScale;   }
      EObjType   ObjType()                     const { return kJet;                       }      
      Double_t   SimpleSecondaryVertexBJetTagsDisc()            const 
                   { return fSimpleSecondaryVertexBJetTagsDisc; }
      Double_t   SoftMuonBJetTagsDisc()                         const 
                   { return fSoftMuonBJetTagsDisc;              }
      Double_t   SoftMuonNoIPBJetTagsDisc()                     const 
                   { return fSoftMuonNoIPBJetTagsDisc;          }
      Double_t   SoftElectronBJetTagsDisc()                     const 
                   { return fSoftElectronBJetTagsDisc;          }
      Double_t   TrackCountingHighEffBJetTagsDisc()             const 
                   { return fTrackCountingHighEffBJetTagsDisc;  }
      Double_t   TrackCountingHighPurBJetTagsDisc()             const 
                   { return fTrackCountingHighPurBJetTagsDisc;  }
      const CaloTower  
                *Tower(UInt_t i)               const { return fTowers.At(i);           }
      Double_t   TowersArea()                  const { return fTowersArea;             }
      void	 AddTower(const CaloTower *tower)  { fTowers.Add(tower);               }
      const FourVectorM &RawMom()              const { return fRawMom;                 }
      void       SetAlpha(Double_t val)            { fAlpha            = val;          }
      void       SetBeta(Double_t val)             { fBeta             = val;          } 
      void       SetCombinedSecondaryVertexBJetTagsDisc(Double_t d) 
                   { fCombinedSecondaryVertexBJetTagsDisc = d;    }
      void       SetCombinedSecondaryVertexMVABJetTagsDisc(Double_t d) 
                   { fCombinedSecondaryVertexMVABJetTagsDisc = d; }
      void       SetEmEnergyInEB(Double_t val)     { fEmEnergyInEB     = val;          } 
      void       SetEmEnergyInEE(Double_t val)     { fEmEnergyInEE     = val;          } 
      void       SetEmEnergyInHF(Double_t val)     { fEmEnergyInHF     = val;          } 
      void       SetEnergyFractionH(Double_t val)  { fEnergyFractionH  = val;          }
      void       SetEnergyFractionEm(Double_t val) { fEnergyFractionEm = val;          }
      void       SetHadEnergyInHO(Double_t val)    { fHadEnergyInHO    = val;          } 
      void       SetHadEnergyInHB(Double_t val)    { fHadEnergyInHB    = val;          } 
      void       SetHadEnergyInHF(Double_t val)    { fHadEnergyInHF    = val;          } 
      void       SetHadEnergyInHE(Double_t val)    { fHadEnergyInHE    = val;          } 
      void       SetImpactParameterMVABJetTagsDisc (Double_t d) 
                   { fImpactParameterMVABJetTagsDisc = d; }
      void       SetJetProbabilityBJetTagsDisc(Double_t d)  
                   { fJetProbabilityBJetTagsDisc = d;     }
      void       SetJetBProbabilityBJetTagsDisc(Double_t d) 
                   { fJetBProbabilityBJetTagsDisc = d;    }
      void       SetRawMom(const FourVectorM &mom) { fRawMom = mom; ClearMom();        }
      void       SetN(UShort_t n)                  { fN                = n;            }
      void       SetN60(UShort_t n)                { fN60              = n;            }
      void       SetN90(UShort_t n)                { fN90              = n;            }
      void       SetMatchedMCFlavor(Int_t flavor)  { fMatchedMCFlavor = flavor;        }
      void       SetMaxEInEmTowers(Double_t val)   { fMaxEInEmTowers   = val;          }
      void       SetMaxEInHadTowers(Double_t val)  { fMaxEInHadTowers  = val;          }
      void       SetL2RelativeCorrectionScale(Double_t s )   
                   { fL2RelativeCorrectionScale = s; ClearMom(); }
      void       SetL3AbsoluteCorrectionScale(Double_t s )   
                   { fL3AbsoluteCorrectionScale = s; ClearMom(); }
      void       SetL4EMFCorrectionScale(Double_t s )        
                   { fL4EMFCorrectionScale = s; ClearMom();    }
      void       SetL5FlavorCorrectionScale(Double_t s )     
                   { fL5FlavorCorrectionScale = s; ClearMom(); }
      void       SetL7PartonCorrectionScale(Double_t s )     
                   { fL7PartonCorrectionScale = s; ClearMom(); }
      void       SetCustomCorrectionScale(Double_t s)        
                   { fCustomCorrectionScale = s; ClearMom(); }
      void       SetSimpleSecondaryVertexBJetTagsDisc(Double_t d) 
                   { fSimpleSecondaryVertexBJetTagsDisc = d;     }
      void       SetSoftMuonBJetTagsDisc(Double_t d)         { fSoftMuonBJetTagsDisc = d;        }
      void       SetSoftMuonNoIPBJetTagsDisc(Double_t d)     { fSoftMuonNoIPBJetTagsDisc = d;    }
      void       SetSoftElectronBJetTagsDisc(Double_t d)     { fSoftElectronBJetTagsDisc = d;    }
      void       SetTowersArea(Double_t val)       { fTowersArea = val;                          } 
      void       SetTrackCountingHighEffBJetTagsDisc(Double_t d) 
                                                   { fTrackCountingHighEffBJetTagsDisc = d;      }
      void       SetTrackCountingHighPurBJetTagsDisc(Double_t d) 
                                                   { fTrackCountingHighPurBJetTagsDisc = d;      }

    protected:
      void          GetMom()                   const;

      FourVectorM32 fRawMom;              //uncorrected four momentum of jet
      Double32_t    fMaxEInEmTowers;      //maximum energy in EM towers
      Double32_t    fMaxEInHadTowers;     //maximum energy in HCAL towers
      Double32_t    fEnergyFractionH;     //hadronic energy fraction
      Double32_t    fEnergyFractionEm;    //electromagnetic energy fraction
      Double32_t    fHadEnergyInHB; 	  //hadronic energy in HB
      Double32_t    fHadEnergyInHO; 	  //hadronic energy in HO
      Double32_t    fHadEnergyInHE; 	  //hadronic energy in HE
      Double32_t    fHadEnergyInHF; 	  //hadronic energy in HF
      Double32_t    fEmEnergyInEB; 	  //electromagnetic energy in EB
      Double32_t    fEmEnergyInEE; 	  //electromagnetic energy in EE
      Double32_t    fEmEnergyInHF; 	  //electromagnetic energy extracted from HF
      Double32_t    fTowersArea;          //area of contributing towers
      UShort_t      fN;                   //number of constituents
      UShort_t      fN60;                 //number constituents with 60% of total energy
      UShort_t      fN90;                 //number constituents with 90% of total energy
      Double32_t    fAlpha;         	  //jet vertex association alpha variable
      Double32_t    fBeta;         	  //jet vertex association beta variable
      Int_t         fMatchedMCFlavor;     //pdg of the quark flavor that the jet matched to
      Double32_t    fJetProbabilityBJetTagsDisc;             //discriminants from b-tagging algos
      Double32_t    fJetBProbabilityBJetTagsDisc;            //discriminants from b-tagging algos
      Double32_t    fSimpleSecondaryVertexBJetTagsDisc;      //discriminants from b-tagging algos
      Double32_t    fCombinedSecondaryVertexBJetTagsDisc;    //discriminants from b-tagging algos
      Double32_t    fCombinedSecondaryVertexMVABJetTagsDisc; //discriminants from b-tagging algos
      Double32_t    fImpactParameterMVABJetTagsDisc;         //discriminants from b-tagging algos
      Double32_t    fTrackCountingHighEffBJetTagsDisc;       //discriminants from b-tagging algos
      Double32_t    fTrackCountingHighPurBJetTagsDisc;       //discriminants from b-tagging algos
      Double32_t    fSoftMuonBJetTagsDisc;                   //discriminants from b-tagging algos
      Double32_t    fSoftMuonNoIPBJetTagsDisc;               // discriminants from b-tagging algos
      Double32_t    fSoftElectronBJetTagsDisc;               //discriminants from b-tagging algos
      Double32_t          fL2RelativeCorrectionScale;        //L2 correction scale
      Double32_t          fL3AbsoluteCorrectionScale;        //L3 correction scale
      Double32_t          fL4EMFCorrectionScale;             //L4 correction scale
      Double32_t          fL5FlavorCorrectionScale;          //L5 correction scale
      Double32_t          fL7PartonCorrectionScale;          //L7 correction scale
      Double32_t          fCustomCorrectionScale;            //custom correction scale
      BitMask8            fCorrections;                      //mask of corrections to be applied
      RefArray<CaloTower> fTowers;                           //calo towers assigned to this jet

    ClassDef(Jet, 1) // Jet class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Jet::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom = fRawMom;
  
  if (CorrectionActive(L2))
    fCachedMom *= fL2RelativeCorrectionScale;
    
  if (CorrectionActive(L3))
    fCachedMom *= fL3AbsoluteCorrectionScale;
  
  if (CorrectionActive(L4))
    fCachedMom *= fL4EMFCorrectionScale;
    
  if (CorrectionActive(L5))
    fCachedMom *= fL5FlavorCorrectionScale;
    
  if (CorrectionActive(L7))
    fCachedMom *= fL7PartonCorrectionScale;
    
  if (CorrectionActive(Custom))
    fCachedMom *= fCustomCorrectionScale;
}
#endif
