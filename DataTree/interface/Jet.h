//--------------------------------------------------------------------------------------------------
// $Id: Jet.h,v 1.20 2009/03/11 18:11:18 bendavid Exp $
//
// Jet
//
// Base jet class to hold reconstructed jet information.
//
// Authors: S.Xie, C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_JET_H
#define MITANA_DATATREE_JET_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

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
        fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fImpactParameterMVABJetTagsDisc(0),
        fTrackCountingHighEffBJetTagsDisc(0), fTrackCountingHighPurBJetTagsDisc(0),
        fSoftMuonBJetTagsDisc(0), fSoftMuonNoIPBJetTagsDisc(0),
        fSoftElectronBJetTagsDisc(0), fL2RelativeCorrectionScale(0),
        fL3AbsoluteCorrectionScale(0), fL4EMFCorrectionScale(0),
        fL5FlavorCorrectionScale(0), fL7PartonCorrectionScale(0),
        fCustomCorrectionScale(0) {}
      Jet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fRawMom(FourVector(px,py,pz,e)),
        fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fImpactParameterMVABJetTagsDisc(0),
        fTrackCountingHighEffBJetTagsDisc(0), fTrackCountingHighPurBJetTagsDisc(0),
        fSoftMuonBJetTagsDisc(0), fSoftMuonNoIPBJetTagsDisc(0),
        fSoftElectronBJetTagsDisc(0), fL2RelativeCorrectionScale(0),
        fL3AbsoluteCorrectionScale(0), fL4EMFCorrectionScale(0),
        fL5FlavorCorrectionScale(0), fL7PartonCorrectionScale(0),
        fCustomCorrectionScale(0) {}

      Double_t      Alpha()                       const { return fAlpha;                        }
      Double_t      Beta()                        const { return fBeta;                         }
      Double_t      CombinedSecondaryVertexBJetTagsDisc()          const 
                      { return fCombinedSecondaryVertexBJetTagsDisc;    } 
      Double_t      CombinedSecondaryVertexMVABJetTagsDisc()       const 
                      { return fCombinedSecondaryVertexMVABJetTagsDisc; }
      Double_t      CustomCorrectionScale()       const { return fCustomCorrectionScale;        }
      void          DisableCorrection(ECorr c)          { fCorrections.ClearBit(c); ClearMom(); }
      void          DisableCorrections()                { fCorrections.Clear(); ClearMom();     }
      void          EnableCorrection(ECorr c)           { fCorrections.SetBit(c); ClearMom();   }
      Bool_t        CorrectionActive(ECorr c)     const { return fCorrections.TestBit(c);       }
      Double_t      ImpactParameterMVABJetTagsDisc()               const 
                      { return fImpactParameterMVABJetTagsDisc; }
      Double_t      JetProbabilityBJetTagsDisc()                   const 
                      { return fJetProbabilityBJetTagsDisc;     }
      Double_t      JetBProbabilityBJetTagsDisc()                  const 
                      { return fJetBProbabilityBJetTagsDisc;    }
      Int_t         MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      virtual 
      UInt_t        NConstituents()               const { return 0;                          }
      UInt_t        N()                           const { return NConstituents();            }
      Double_t      L2RelativeCorrectionScale()   const { return fL2RelativeCorrectionScale; }
      Double_t      L3AbsoluteCorrectionScale()   const { return fL3AbsoluteCorrectionScale; }
      Double_t      L4EMFCorrectionScale()        const { return fL4EMFCorrectionScale;      }
      Double_t      L5FlavorCorrectionScale()     const { return fL5FlavorCorrectionScale;   }
      Double_t      L7PartonCorrectionScale()     const { return fL7PartonCorrectionScale;   }
      EObjType      ObjType()                     const { return kJet;                       }      
      Double_t      SimpleSecondaryVertexBJetTagsDisc()            const 
                      { return fSimpleSecondaryVertexBJetTagsDisc; }
      Double_t      SoftMuonBJetTagsDisc()                         const 
                      { return fSoftMuonBJetTagsDisc;              }
      Double_t      SoftMuonNoIPBJetTagsDisc()                     const 
                      { return fSoftMuonNoIPBJetTagsDisc;          }
      Double_t      SoftElectronBJetTagsDisc()                     const 
                      { return fSoftElectronBJetTagsDisc;          }
      Double_t      TrackCountingHighEffBJetTagsDisc()             const 
                      { return fTrackCountingHighEffBJetTagsDisc;  }
      Double_t      TrackCountingHighPurBJetTagsDisc()             const 
                      { return fTrackCountingHighPurBJetTagsDisc;  }
      FourVectorM   RawMom()                      const { return fRawMom.V();                }
      void          SetAlpha(Double_t val)              { fAlpha = val;                      }
      void          SetBeta(Double_t val)               { fBeta  = val;                      } 
      void          SetCombinedSecondaryVertexBJetTagsDisc(Double_t d) 
                      { fCombinedSecondaryVertexBJetTagsDisc = d;    }
      void          SetCombinedSecondaryVertexMVABJetTagsDisc(Double_t d) 
                      { fCombinedSecondaryVertexMVABJetTagsDisc = d; }
      void          SetImpactParameterMVABJetTagsDisc (Double_t d) 
                      { fImpactParameterMVABJetTagsDisc = d; }
      void          SetJetProbabilityBJetTagsDisc(Double_t d)  
                      { fJetProbabilityBJetTagsDisc = d;     }
      void          SetJetBProbabilityBJetTagsDisc(Double_t d) 
                      { fJetBProbabilityBJetTagsDisc = d;    }
      void          SetRawMom(const FourVectorM &mom) { fRawMom = mom; ClearMom();           }
      void          SetMatchedMCFlavor(Int_t flavor)  { fMatchedMCFlavor = flavor;           }
      void          SetL2RelativeCorrectionScale(Double_t s )   
                      { fL2RelativeCorrectionScale = s; ClearMom(); }
      void          SetL3AbsoluteCorrectionScale(Double_t s )   
                      { fL3AbsoluteCorrectionScale = s; ClearMom(); }
      void          SetL4EMFCorrectionScale(Double_t s )        
                      { fL4EMFCorrectionScale = s; ClearMom();      }
      void          SetL5FlavorCorrectionScale(Double_t s )     
                      { fL5FlavorCorrectionScale = s; ClearMom();   }
      void          SetL7PartonCorrectionScale(Double_t s )     
                      { fL7PartonCorrectionScale = s; ClearMom();   }
      void          SetCustomCorrectionScale(Double_t s)        
                      { fCustomCorrectionScale = s; ClearMom(); }
      void          SetSimpleSecondaryVertexBJetTagsDisc(Double_t d) 
                      { fSimpleSecondaryVertexBJetTagsDisc = d;     }
      void          SetSoftMuonBJetTagsDisc(Double_t d)     { fSoftMuonBJetTagsDisc = d;     }
      void          SetSoftMuonNoIPBJetTagsDisc(Double_t d) { fSoftMuonNoIPBJetTagsDisc = d; }
      void          SetSoftElectronBJetTagsDisc(Double_t d) { fSoftElectronBJetTagsDisc = d; }
      void          SetTrackCountingHighEffBJetTagsDisc(Double_t d) 
                      { fTrackCountingHighEffBJetTagsDisc = d;      }
      void          SetTrackCountingHighPurBJetTagsDisc(Double_t d) 
                      { fTrackCountingHighPurBJetTagsDisc = d;      }

    protected:
      void          GetMom()                   const;

      Vect4M        fRawMom;                                 //uncorrected four momentum of jet
      Double32_t    fAlpha;         	                     //[0,0,14]jet vertex alpha variable
      Double32_t    fBeta;         	                     //[0,0,14]jet vertex beta variable
      Int_t         fMatchedMCFlavor;                        //[0,0,14]pdg of matched quark flavor
      Double32_t    fJetProbabilityBJetTagsDisc;             //[0,0,14]discriminants b-tagging algos
      Double32_t    fJetBProbabilityBJetTagsDisc;            //[0,0,14]discriminants b-tagging algos
      Double32_t    fSimpleSecondaryVertexBJetTagsDisc;      //[0,0,14]discriminants b-tagging algos
      Double32_t    fCombinedSecondaryVertexBJetTagsDisc;    //[0,0,14]discriminants b-tagging algos
      Double32_t    fCombinedSecondaryVertexMVABJetTagsDisc; //[0,0,14]discriminants b-tagging algos
      Double32_t    fImpactParameterMVABJetTagsDisc;         //[0,0,14]discriminants b-tagging algos
      Double32_t    fTrackCountingHighEffBJetTagsDisc;       //[0,0,14]discriminants b-tagging algos
      Double32_t    fTrackCountingHighPurBJetTagsDisc;       //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftMuonBJetTagsDisc;                   //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftMuonNoIPBJetTagsDisc;               //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftElectronBJetTagsDisc;               //[0,0,14]discriminants b-tagging algos
      Double32_t    fL2RelativeCorrectionScale;              //[0,0,14]L2 correction scale
      Double32_t    fL3AbsoluteCorrectionScale;              //[0,0,14]L3 correction scale
      Double32_t    fL4EMFCorrectionScale;                   //[0,0,14]L4 correction scale
      Double32_t    fL5FlavorCorrectionScale;                //[0,0,14]L5 correction scale
      Double32_t    fL7PartonCorrectionScale;                //[0,0,14]L7 correction scale
      Double32_t    fCustomCorrectionScale;                  //[0,0,14]custom correction scale
      BitMask8      fCorrections;                            //mask of corrections to be applied

    ClassDef(Jet, 1) // Jet class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Jet::GetMom() const
{
  // Get raw momentum values from stored values and apply all enabled corrections.

  fCachedMom.SetCoordinates(fRawMom.Pt(),fRawMom.Eta(),fRawMom.Phi(),fRawMom.M()); 

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
