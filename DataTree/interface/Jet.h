//--------------------------------------------------------------------------------------------------
// $Id: Jet.h,v 1.8 2008/09/10 03:33:26 loizides Exp $
//
// Jet
//
// Details to be worked out...
//
// Authors: C.Loizides
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
      Jet() : fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0), fEnergyFractionEm(0),
              fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0), fHadEnergyInHF(0),
              fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0), fTowersArea(0), fN(0), 
              fN60(0), fN90(0), fMatchedMCFlavor(0) {}
      Jet(Double_t px, Double_t py, Double_t pz, Double_t e) : fMom(px,py,pz,e),
              fMaxEInEmTowers(0), fMaxEInHadTowers(0), fEnergyFractionH(0), fEnergyFractionEm(0),
              fHadEnergyInHB(0), fHadEnergyInHO(0), fHadEnergyInHE(0), fHadEnergyInHF(0),
              fEmEnergyInEB(0), fEmEnergyInEE(0), fEmEnergyInHF(0), fTowersArea(0), fN(0), 
              fN60(0), fN90(0), fMatchedMCFlavor(0) {}
      ~Jet() {}

      FourVector	Mom()                         const { return fMom;                       }
      Double_t          Charge()                      const { return 0;                          }
      Double_t          MaxEInEmTowers()              const { return fMaxEInEmTowers;            }
      Double_t          MaxEInHadTowers()             const { return fMaxEInHadTowers;           }
      Double_t          HadEnergyInHO()               const { return fHadEnergyInHO;             } 
      Double_t          HadEnergyInHB()               const { return fHadEnergyInHB;             } 
      Double_t          HadEnergyInHF()               const { return fHadEnergyInHF;             } 
      Double_t          HadEnergyInHE()               const { return fHadEnergyInHE;             } 
      Double_t          EmEnergyInEB()                const { return fEmEnergyInEB;              } 
      Double_t          EmEnergyInEE()                const { return fEmEnergyInEE;              } 
      Double_t          EmEnergyInHF()                const { return fEmEnergyInHF;              } 
      Double_t          EnergyFractionH()             const { return fEnergyFractionH;           }
      Double_t          EnergyFractionEm()            const { return fEnergyFractionEm;          }
      const CaloTower  *Tower(UInt_t i)               const { return fTowers.At(i);              }
      Double_t          TowersArea()                  const { return fTowersArea;                }
      UShort_t          N()                           const { return fN;                         }
      UShort_t          N60()                         const { return fN60;                       }
      UShort_t          N90()                         const { return fN90;                       }
      Double_t          Alpha()                       const { return fAlpha;                     }
      Double_t          Beta()                        const { return fBeta;                      }
      UInt_t            NTowers()                     const { return fTowers.GetEntries();       }
      Int_t             MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      Double_t          L2RelativeCorrectionScale()   const { return fL2RelativeCorrectionScale; };
      Double_t          L3AbsoluteCorrectionScale()   const { return fL3AbsoluteCorrectionScale; };
      Double_t          L4EMFCorrectionScale()        const { return fL4EMFCorrectionScale;      };
      Double_t          L5FlavorCorrectionScale()     const { return fL5FlavorCorrectionScale;   };
      Double_t          L7PartonCorrectionScale()     const { return fL7PartonCorrectionScale;   };

      Double_t JetProbabilityBJetTagsDisc()                   const 
      { return fJetProbabilityBJetTagsDisc;             }
      Double_t JetBProbabilityBJetTagsDisc()                  const 
      { return fJetBProbabilityBJetTagsDisc;            }
      Double_t SimpleSecondaryVertexBJetTagsDisc()            const 
      { return fSimpleSecondaryVertexBJetTagsDisc;      }
      Double_t CombinedSecondaryVertexBJetTagsDisc()          const 
      { return fCombinedSecondaryVertexBJetTagsDisc;    } 
      Double_t CombinedSecondaryVertexMVABJetTagsDisc()       const 
      { return fCombinedSecondaryVertexMVABJetTagsDisc; }
      Double_t ImpactParameterMVABJetTagsDisc()               const 
      { return fImpactParameterMVABJetTagsDisc;         }
      Double_t TrackCountingHighEffBJetTagsDisc()             const 
      { return fTrackCountingHighEffBJetTagsDisc;       }
      Double_t TrackCountingHighPurBJetTagsDisc()             const 
      { return fTrackCountingHighPurBJetTagsDisc;       }
      Double_t SoftMuonBJetTagsDisc()                         const 
      { return fSoftMuonBJetTagsDisc;                   }
      Double_t SoftMuonNoIPBJetTagsDisc()                     const 
      { return fSoftMuonNoIPBJetTagsDisc;               }
      Double_t SoftElectronBJetTagsDisc()                     const 
      { return fSoftElectronBJetTagsDisc;               }

      void	 AddTower(CaloTower *tower)                    { fTowers.Add(tower);               }
      void       SetMaxEInEmTowers(Double_t val)               { fMaxEInEmTowers   = val;          }
      void       SetMaxEInHadTowers(Double_t val)              { fMaxEInHadTowers  = val;          }
      void       SetHadEnergyInHO(Double_t val)                { fHadEnergyInHO    = val;          } 
      void       SetHadEnergyInHB(Double_t val)                { fHadEnergyInHB    = val;          } 
      void       SetHadEnergyInHF(Double_t val)                { fHadEnergyInHF    = val;          } 
      void       SetHadEnergyInHE(Double_t val)                { fHadEnergyInHE    = val;          } 
      void       SetEmEnergyInEB(Double_t val)                 { fEmEnergyInEB     = val;          } 
      void       SetEmEnergyInEE(Double_t val)                 { fEmEnergyInEE     = val;          } 
      void       SetEmEnergyInHF(Double_t val)                 { fEmEnergyInHF     = val;          } 
      void       SetEnergyFractionH(Double_t val)              { fEnergyFractionH  = val;          }
      void       SetEnergyFractionEm(Double_t val)             { fEnergyFractionEm = val;          }
      void       SetTowersArea(Double_t val)                   { fTowersArea       = val;          } 
      void       SetN(UShort_t n)                              { fN                = n;            }
      void       SetN60(UShort_t n)                            { fN60              = n;            }
      void       SetN90(UShort_t n)                            { fN90              = n;            }
      void       SetAlpha(Double_t val)                        { fAlpha            = val;          }
      void       SetBeta(Double_t val)                         { fBeta             = val;          } 
      void       SetMatchedMCFlavor(Int_t flavor)              { fMatchedMCFlavor = flavor;        }
      void       SetJetProbabilityBJetTagsDisc ( Double_t d )  { fJetProbabilityBJetTagsDisc = d;  }
      void       SetJetBProbabilityBJetTagsDisc ( Double_t d ) { fJetBProbabilityBJetTagsDisc = d; }
      void       SetSimpleSecondaryVertexBJetTagsDisc ( Double_t d ) 
                                                   { fSimpleSecondaryVertexBJetTagsDisc = d;       }
      void       SetCombinedSecondaryVertexBJetTagsDisc ( Double_t d ) 
                                                   { fCombinedSecondaryVertexBJetTagsDisc = d;     }
      void       SetCombinedSecondaryVertexMVABJetTagsDisc ( Double_t d ) 
                                                   { fCombinedSecondaryVertexMVABJetTagsDisc = d;  }
      void       SetImpactParameterMVABJetTagsDisc ( Double_t d ) 
                                                   {   fImpactParameterMVABJetTagsDisc = d;        }
      void       SetTrackCountingHighEffBJetTagsDisc ( Double_t d ) 
                                                   { fTrackCountingHighEffBJetTagsDisc = d;        }
      void       SetTrackCountingHighPurBJetTagsDisc ( Double_t d ) 
                                                   { fTrackCountingHighPurBJetTagsDisc = d;        }
      void       SetSoftMuonBJetTagsDisc ( Double_t d )        { fSoftMuonBJetTagsDisc = d;        }
      void       SetSoftMuonNoIPBJetTagsDisc ( Double_t d )    { fSoftMuonNoIPBJetTagsDisc = d;    }
      void       SetSoftElectronBJetTagsDisc ( Double_t d )    { fSoftElectronBJetTagsDisc = d;    }
      void       SetL2RelativeCorrectionScale ( Double_t s )   { fL2RelativeCorrectionScale = s;   }
      void       SetL3AbsoluteCorrectionScale ( Double_t s )   { fL3AbsoluteCorrectionScale = s;   }
      void       SetL4EMFCorrectionScale ( Double_t s )        { fL4EMFCorrectionScale = s;        }
      void       SetL5FlavorCorrectionScale ( Double_t s )     { fL5FlavorCorrectionScale = s;     }
      void       SetL7PartonCorrectionScale ( Double_t s )     { fL7PartonCorrectionScale = s;     }

    protected:
      FourVector fMom;                    //four momentum of jet
      Double_t   fMaxEInEmTowers;         //maximum energy in EM towers
      Double_t   fMaxEInHadTowers;        //maximum energy in HCAL towers
      Double_t   fEnergyFractionH;        //hadronic energy fraction
      Double_t   fEnergyFractionEm;       //electromagnetic energy fraction
      Double_t   fHadEnergyInHB; 	  //hadronic energy in HB
      Double_t   fHadEnergyInHO; 	  //hadronic energy in HO
      Double_t   fHadEnergyInHE; 	  //hadronic energy in HE
      Double_t   fHadEnergyInHF; 	  //hadronic energy in HF
      Double_t   fEmEnergyInEB; 	  //electromagnetic energy in EB
      Double_t   fEmEnergyInEE; 	  //electromagnetic energy in EE
      Double_t   fEmEnergyInHF; 	  //electromagnetic energy extracted from HF
      Double_t   fTowersArea;             //area of contributing towers
      UShort_t   fN;                      //number of constituents
      UShort_t   fN60;                    //number constituents with 60% of total energy
      UShort_t   fN90;                    //number constituents with 90% of total energy
      Double_t   fAlpha;         	  //jet vertex association alpha variable
      Double_t   fBeta;         	  //jet vertex association beta variable

      Int_t      fMatchedMCFlavor;        //pdgID of the quark flavor that the jet matched to
      Double_t   fJetProbabilityBJetTagsDisc;              //Discriminants for various b-tagging
      Double_t   fJetBProbabilityBJetTagsDisc;             //algorithms
      Double_t   fSimpleSecondaryVertexBJetTagsDisc;
      Double_t   fCombinedSecondaryVertexBJetTagsDisc;
      Double_t   fCombinedSecondaryVertexMVABJetTagsDisc;
      Double_t   fImpactParameterMVABJetTagsDisc;
      Double_t   fTrackCountingHighEffBJetTagsDisc;
      Double_t   fTrackCountingHighPurBJetTagsDisc;
      Double_t   fSoftMuonBJetTagsDisc;
      Double_t   fSoftMuonNoIPBJetTagsDisc;
      Double_t   fSoftElectronBJetTagsDisc;
      Double_t   fL2RelativeCorrectionScale;
      Double_t   fL3AbsoluteCorrectionScale;
      Double_t   fL4EMFCorrectionScale;
      Double_t   fL5FlavorCorrectionScale;
      Double_t   fL7PartonCorrectionScale;

      RefArray<CaloTower> fTowers;        //||CaloTowers in this jet

    ClassDef(Jet, 1) // Jet class
  };
}
#endif
