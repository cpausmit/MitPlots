//--------------------------------------------------------------------------------------------------
// $Id: Jet.h,v 1.4 2008/07/16 10:00:58 bendavid Exp $
//
// Jet
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_JET_H
#define DATATREE_JET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

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

      FourVector	    Mom()                             const { return fMom; }

      Double_t              Charge()                          const { return 0; }
      Double_t              MaxEInEmTowers()                  const { return fMaxEInEmTowers; }
      Double_t              MaxEInHadTowers()                 const { return fMaxEInHadTowers; }
      Double_t              HadEnergyInHO()                   const { return fHadEnergyInHO; } 
      Double_t              HadEnergyInHB()                   const { return fHadEnergyInHB; } 
      Double_t              HadEnergyInHF()                   const { return fHadEnergyInHF; } 
      Double_t              HadEnergyInHE()                   const { return fHadEnergyInHE; } 
      Double_t              EmEnergyInEB()                    const { return fEmEnergyInEB; } 
      Double_t              EmEnergyInEE()                    const { return fEmEnergyInEE; } 
      Double_t              EmEnergyInHF()                    const { return fEmEnergyInHF; } 
      Double_t              EnergyFractionH()                 const { return fEnergyFractionH; }
      Double_t              EnergyFractionEm()                const { return fEnergyFractionEm; }
      Double_t              TowersArea()                      const { return fTowersArea; }
      UShort_t              N()                               const { return fN; }
      UShort_t              N60()                             const { return fN60; }
      UShort_t              N90()                             const { return fN90; }
      Int_t                 MatchedMCFlavor()                 const { return fMatchedMCFlavor; }

      void                  SetMaxEInEmTowers(Double_t val)    { fMaxEInEmTowers   = val;   }
      void                  SetMaxEInHadTowers(Double_t val)   { fMaxEInHadTowers  = val;   }
      void                  SetHadEnergyInHO(Double_t val)     { fHadEnergyInHO    = val;   } 
      void                  SetHadEnergyInHB(Double_t val)     { fHadEnergyInHB    = val;   } 
      void                  SetHadEnergyInHF(Double_t val)     { fHadEnergyInHF    = val;   } 
      void                  SetHadEnergyInHE(Double_t val)     { fHadEnergyInHE    = val;   } 
      void                  SetEmEnergyInEB(Double_t val)      { fEmEnergyInEB     = val;   } 
      void                  SetEmEnergyInEE(Double_t val)      { fEmEnergyInEE     = val;   } 
      void                  SetEmEnergyInHF(Double_t val)      { fEmEnergyInHF     = val;   } 
      void                  SetEnergyFractionH(Double_t val)   { fEnergyFractionH  = val;   }
      void                  SetEnergyFractionEm(Double_t val)  { fEnergyFractionEm = val;   }
      void                  SetTowersArea(Double_t val)        { fTowersArea       = val;   } 
      void                  SetN(UShort_t n)                   { fN = n;                    }
      void                  SetN60(UShort_t n)                 { fN60 = n;                  }
      void                  SetN90(UShort_t n)                 { fN90 = n;                  }
      void                  SetMatchedMCFlavor(Int_t flavor)   { fMatchedMCFlavor = flavor; }

    protected:
      FourVector fMom;                    //four momentum of jet
      Double32_t fMaxEInEmTowers;         //maximum energy in EM towers
      Double32_t fMaxEInHadTowers;        //maximum energy in HCAL towers
      Double32_t fEnergyFractionH;        //hadronic energy fraction
      Double32_t fEnergyFractionEm;       //electromagnetic energy fraction
      Double32_t fHadEnergyInHB; 	  //hadronic energy in HB
      Double32_t fHadEnergyInHO; 	  //hadronic energy in HO
      Double32_t fHadEnergyInHE; 	  //hadronic energy in HE
      Double32_t fHadEnergyInHF; 	  //hadronic energy in HF
      Double32_t fEmEnergyInEB; 	  //electromagnetic energy in EB
      Double32_t fEmEnergyInEE; 	  //electromagnetic energy in EE
      Double32_t fEmEnergyInHF; 	  //electromagnetic energy extracted from HF
      Double32_t fTowersArea;             //area of contributing towers
      UShort_t   fN;                      //number of constituents
      UShort_t   fN60;                    //number constituents with 60% of total energy
      UShort_t   fN90;                    //number constituents with 90% of total energy
      Int_t      fMatchedMCFlavor;         //pdgID of the quark flavor that the jet matched to

    ClassDef(Jet, 1) // Jet class
  };
}
#endif
