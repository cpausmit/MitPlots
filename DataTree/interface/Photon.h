//--------------------------------------------------------------------------------------------------
// $Id: Photon.h,v 1.23 2009/03/03 18:03:06 bendavid Exp $
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
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataCont/interface/RefArray.h"

namespace mithep 
{
  class Photon : public Particle
  {
    public:
      Photon() : fR9(0),fHadOverEm(0),fEcalRecHitIso(0),fHcalRecHitIso(0),fSolidConeTrkIso(0),
                 fHollowConeTrkIso(0),fSolidConeNTrk(0),fHollowConeNTrk(0),fHasPixelSeed(0),
                 fIsEBGap(0),fIsEEGap(0),fIsEBEEGap(0),fIsLooseEM(0),fIsLoosePhoton(0),
                 fIsTightPhoton(0),fIsConverted(0) {}
      Photon(Double_t px, Double_t py, Double_t pz, Double_t e) :    
        fMom(FourVector(px,py,pz,e)), 
        fR9(0),fHadOverEm(0),fEcalRecHitIso(0),fHcalRecHitIso(0),fSolidConeTrkIso(0),
        fHollowConeTrkIso(0),fSolidConeNTrk(0),fHollowConeNTrk(0),fHasPixelSeed(0),
        fIsEBGap(0),fIsEEGap(0),fIsEBEEGap(0),fIsLooseEM(0),fIsLoosePhoton(0),
        fIsTightPhoton(0),fIsConverted(0) {}

      const Conversion         *ConvCand(UInt_t i)      const { return fConversions.At(i); }
      Double_t                  EcalRecHitIso()         const { return fEcalRecHitIso;     }
      Double_t                  HadOverEm()             const { return fHadOverEm;         }
      Bool_t                    HasPixelSeed()          const { return fHasPixelSeed;      }
      Double_t                  HcalRecHitIso()         const { return fHcalRecHitIso;     }
      UShort_t                  HollowConeNTrk()        const { return fHollowConeNTrk;    }
      Double_t                  HollowConeTrkIso()      const { return fHollowConeTrkIso;  }
      Bool_t                    IsEBGap()               const { return fIsEBGap;           }
      Bool_t                    IsEEGap()               const { return fIsEEGap;           }
      Bool_t                    IsEBEEGap()             const { return fIsEBEEGap;         }
      Bool_t                    IsLooseEM()             const { return fIsLooseEM;         }
      Bool_t                    IsLoosePhoton()         const { return fIsLoosePhoton;     }
      Bool_t                    IsTightPhoton()         const { return fIsTightPhoton;     }
      Bool_t                    IsConverted()           const { return fIsConverted;       }
      UInt_t                    NConversions()          const { return fConversions.Entries();   }
      EObjType                  ObjType()               const { return kPhoton;                  }
      Double_t                  R9()                    const { return fR9;                      }
      const SuperCluster       *SCluster()              const { return fSuperClusterRef.Obj();   }
      Double_t                  SolidConeTrkIso()       const { return fSolidConeTrkIso;         }
      UShort_t                  SolidConeNTrk()         const { return fSolidConeNTrk;           }
      void                      AddConversion(const Conversion *c)      { fConversions.Add(c);   }  
      void                      SetIsConverted(Bool_t isConv)           { fIsConverted = isConv; }
      void                      SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                      SetSuperCluster(const SuperCluster* sc) { fSuperClusterRef = sc; }
      void                      SetR9(Double_t x)                 { fR9 = x;               }
      void                      SetHadOverEm(Double_t x)          { fHadOverEm = x;        }
      void                      SetHasPixelSeed(Bool_t x)         { fHasPixelSeed = x;     }
      void                      SetEcalRecHitIso(Double_t x)      { fEcalRecHitIso = x;    }
      void                      SetHcalRecHitIso(Double_t x)      { fHcalRecHitIso = x;    }
      void                      SetSolidConeTrkIso(Double_t x)    { fSolidConeTrkIso = x;  }
      void                      SetHollowConeTrkIso(Double_t x)   { fHollowConeTrkIso = x; }
      void                      SetSolidConeNTrk(UShort_t x)      { fSolidConeNTrk = x;    }
      void                      SetHollowConeNTrk(UShort_t x)     { fHollowConeNTrk = x;   }
      void                      SetIsEBGap(Bool_t x)              { fIsEBGap = x;          }
      void                      SetIsEEGap(Bool_t x)              { fIsEEGap = x;          }
      void                      SetIsEBEEGap(Bool_t x)            { fIsEBEEGap = x;        }
      void                      SetIsLooseEM(Bool_t x)            { fIsLooseEM = x;        }
      void                      SetIsLoosePhoton(Bool_t x)        { fIsLoosePhoton = x;    }
      void                      SetIsTightPhoton(Bool_t x)        { fIsTightPhoton = x;    }

    protected:
      void                      GetMom()                const;

      Vect4M                    fMom;               //four momentum vector
      Double32_t                fR9;                //[0,0,14]r9=e3x3/etotal variable
      Double32_t                fHadOverEm;         //[0,0,14]hadronic over em fraction
      Double32_t                fEcalRecHitIso;     //[0,0,14]ecal rechit based isolation
      Double32_t                fHcalRecHitIso;     //[0,0,14]hcal rechit based isolation
      Double32_t                fSolidConeTrkIso;   //[0,0,14]sum track pT in cone of dR
      Double32_t                fHollowConeTrkIso;  //[0,0,14]as above excluding the core
      UShort_t                  fSolidConeNTrk;     //number of tracks in a cone of dR
      UShort_t                  fHollowConeNTrk;    //as above excluding the core
      Bool_t                    fHasPixelSeed;      //=true if super cluster has matched seed
      Bool_t                    fIsEBGap;           //=true photon is in ECAL barrel
      Bool_t                    fIsEEGap;           //=true photon is in ECAL endcap
      Bool_t                    fIsEBEEGap;         //=true photon is in boundary between EB/EE
      Bool_t                    fIsLooseEM;         //=true if loose em cuts are passed
      Bool_t                    fIsLoosePhoton;     //=true if loose photon cuts are passed
      Bool_t                    fIsTightPhoton;     //=true if tight photon cuts are passed
      Bool_t                    fIsConverted;       //=true if photon converted
      RefArray<Conversion>      fConversions;       //refs to associated conversion candidates
      Ref<SuperCluster>         fSuperClusterRef;   //ref to associated super cluster
	
    ClassDef(Photon,1) // Photon class
  };
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
#endif
