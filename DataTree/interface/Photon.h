//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.15 2008/10/31 18:56:42 bendavid Exp $
//
// Photon
//
// Details to be worked out...
//
// Authors: J.Bendavid, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PHOTON_H
#define MITANA_DATATREE_PHOTON_H
 
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class Photon : public Particle
  {
    public:
      Photon() {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fFourVector(px,py,pz,e) {}
      ~Photon() {}

      void                      AddConversion(Conversion *c)  { fConversions.Add(c);       }
      Double_t                  Charge()                const { return 0;                  }
      Double_t                  R9()                    const { return fR9;                }
      Double_t                  R19()                   const { return fR19;               }
      Double_t                  E5x5()                  const { return fE5x5;              }
      Double_t                  HadOverEm()             const { return fHadOverEm;         }
      Double_t                  HasPixelSeed()          const { return fHasPixelSeed;      }
      Double_t                  EcalRecHitIso()         const { return fEcalRecHitIso;     }
      Double_t                  HcalRecHitIso()         const { return fHcalRecHitIso;     }
      Double_t                  SolidConeTrkIso()       const { return fSolidConeTrkIso;   }
      Double_t                  HollowConeTrkIso()      const { return fHollowConeTrkIso;  }
      Int_t                     SolidConeNTrk()         const { return fSolidConeNTrk;     }
      Int_t                     HollowConeNTrk()        const { return fHollowConeNTrk;    }
      Bool_t                    IsEBGap()               const { return fIsEBGap;           }
      Bool_t                    IsEEGap()               const { return fIsEEGap;           }
      Bool_t                    IsEBEEGap()             const { return fIsEBEEGap;         }
      Bool_t                    IsLooseEM()             const { return fIsLooseEM;         }
      Bool_t                    IsLoosePhoton()         const { return fIsLoosePhoton;     }
      Bool_t                    IsTightPhoton()         const { return fIsTightPhoton;     }
      Bool_t                    IsConverted()           const { return fIsConverted;       }
      const Conversion         *ConvCand(UInt_t i)      const { return fConversions.At(i); }
      UInt_t                    NConversions()          const { return fConversions.GetEntries(); }
      const SuperCluster       *SCluster()              const;
      FourVector 	        Mom()                   const { return fFourVector; }
      void                      Clear(Option_t *opt="")       { fConversions.Clear(opt);   }
      void                      SetIsConverted(Bool_t isConv) { fIsConverted = isConv; }
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                      SetSuperCluster(SuperCluster* sc) { fSuperClusterRef = sc; }
      void                      SetR9(Double_t x)                 { fR9 = x;               }
      void                      SetR19(Double_t x)                { fR19 = x;              }
      void                      SetE5x5(Double_t x)               { fE5x5 = x;             }
      void                      SetHadOverEm(Double_t x)          { fHadOverEm = x;        }
      void                      SetHasPixelSeed(Double_t x)       { fHasPixelSeed = x;     }
      void                      SetEcalRecHitIso(Double_t x)      { fEcalRecHitIso = x;    }
      void                      SetHcalRecHitIso(Double_t x)      { fHcalRecHitIso = x;    }
      void                      SetSolidConeTrkIso(Double_t x)    { fSolidConeTrkIso = x;  }
      void                      SetHollowConeTrkIso(Double_t x)   { fHollowConeTrkIso = x; }
      void                      SetSolidConeNTrk(Int_t x)         { fSolidConeNTrk = x;    }
      void                      SetHollowConeNTrk(Int_t x)        { fHollowConeNTrk = x;   }
      void                      SetIsEBGap(Bool_t x)              { fIsEBGap = x;          }
      void                      SetIsEEGap(Bool_t x)              { fIsEEGap = x;          }
      void                      SetIsEBEEGap(Bool_t x)            { fIsEBEEGap = x;        }
      void                      SetIsLooseEM(Bool_t x)            { fIsLooseEM = x;        }
      void                      SetIsLoosePhoton(Bool_t x)        { fIsLoosePhoton = x;    }
      void                      SetIsTightPhoton(Bool_t x)        { fIsTightPhoton = x;    }

    protected:
      FourVector                fFourVector;  //four momentum vector
      Double32_t                fR9;
      Double32_t                fR19;
      Double32_t                fE5x5;
      Double32_t                fHadOverEm;
      Double32_t                fHasPixelSeed;
      Double32_t                fEcalRecHitIso;
      Double32_t                fHcalRecHitIso;
      Double32_t                fSolidConeTrkIso;
      Double32_t                fHollowConeTrkIso;
      Int_t                     fSolidConeNTrk;
      Int_t                     fHollowConeNTrk;
      Bool_t                    fIsEBGap;
      Bool_t                    fIsEEGap;
      Bool_t                    fIsEBEEGap;
      Bool_t                    fIsLooseEM;
      Bool_t                    fIsLoosePhoton;
      Bool_t                    fIsTightPhoton;
      RefArray<Conversion,128>  fConversions; //references to associated conversion candidates
      Bool_t                    fIsConverted; //conversion flag
      TRef                      fSuperClusterRef; //superCluster
	
    ClassDef(Photon,1) // Photon class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Photon::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set four vector.

  fFourVector.SetXYZT(px, py, pz, e);
}

//--------------------------------------------------------------------------------------------------
inline const mithep::SuperCluster *mithep::Photon::SCluster() const
{
  // Return Super cluster

  return static_cast<const SuperCluster*>(fSuperClusterRef.GetObject());
}
#endif
