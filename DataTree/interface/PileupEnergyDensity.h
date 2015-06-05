//--------------------------------------------------------------------------------------------------
// PileupEnergyDensity
//
// Class to store the pu energy density as computed by fastjet algorithm
// Versions <= 4 had a very strange mixup where fRhoHighEta is actually RhoLowEta and fRho
// is RhoHighEta. Fixed using schema evolution (see LinkDef file)
//
// Authors: C.Paus, A.Levin, M.Zanetti, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PILEUPENERGYDENSITY_H
#define MITANA_DATATREE_PILEUPENERGYDENSITY_H

#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep
{
  class PileupEnergyDensity : public DataBase {
  public:
    enum Type {
      kHighEta,
      kLowEta,
      kRandom,
      kRandomLowEta,
      kFixedGridAll,
      kFixedGridFastjetAll,
      kKt6CaloJets,
      kKt6CaloJetsCentral,
      kKt6PFJets,
      kKt6PFJetsCentralChargedPileUp,
      kKt6PFJetsCentralNeutralToken,
      kKt6PFJetsCentralNeutralTight,
      nTypes
    };

    PileupEnergyDensity() :
      fRho{}
    {
    }

    Double_t RhoDefault()                       const { return fRho[kRandom]; }

    Double_t Rho(Type t = kHighEta)             const { return fRho[t]; }
    Double_t RhoHighEta()                       const { return fRho[kHighEta]; }
    Double_t RhoLowEta()                        const { return fRho[kLowEta]; }
    Double_t RhoRandom()                        const { return fRho[kRandom]; }
    Double_t RhoRandomLowEta()                  const { return fRho[kRandomLowEta]]; }
    Double_t RhoFixedGridAll()                  const { return fRho[kFixedGridAll]; }
    Double_t RhoFixedGridFastjetAll()           const { return fRho[kFixedGridFastjetAll]; }
    Double_t RhoKt6CaloJets()                   const { return fRho[kKt6CaloJets]; }
    Double_t RhoKt6CaloJetsCentral()            const { return fRho[kKt6CaloJetsCentral]; }
    Double_t RhoKt6PFJets()                     const { return fRho[kKt6PFJets]; }
    Double_t RhoKt6PFJetsCentralChargedPileUp() const { return fRho[kKt6PFJetsCentralChargedPileUp]; }
    Double_t RhoKt6PFJetsCentralNeutral()       const { return fRho[kKt6PFJetsCentralNeutral]; }
    Double_t RhoKt6PFJetsCentralNeutralTight()  const { return fRho[kKt6PFJetsCentralNeutralTight]; }

    virtual PileupEnergyDensity *MakeCopy()      const { return new PileupEnergyDensity(*this);   }
    
    void SetRho(Double_t r, Type t = kHighEta) { fRho[t] = r; }
    void SetRhoHighEta(Double_t r) { fRho[kHighEta] = r; }
    void SetRhoLowEta(Double_t r) { fRho[kLowEta] = r; }
    void SetRhoRandom(Double_t r) { fRho[kRandom] = r; }
    void SetRhoRandomLowEta(Double_t r) { fRho[kRandomLowEta] = r; }
    void SetRhoFixedGridAll(Double_t r) { fRho[kFixedGridAll] = r; }
    void SetRhoFixedGridFastjetAll(Double_t r) { fRho[kFixedGridFastjetAll] = r; }
    void SetRhoKt6CaloJets(Double_t r) { fRho[kKt6CaloJets] = r; }
    void SetRhoKt6CaloJetsCentral(Double_t r) { fRho[kKt6CaloJetsCentral] = r; }
    void SetRhoKt6PFJets(Double_t r) { fRho[kKt6PFJets] = r; }
    void SetRhoKt6PFJetsCentralChargedPileUp(Double_t r) { fRho[kKt6PFJetsCentralChargedPileUp] = r; }
    void SetRhoKt6PFJetsCentralNeutral(Double_t r) { fRho[kKt6PFJetsCentralNeutral] = r; }
    void SetRhoKt6PFJetsCentralNeutralTight(Double_t r) { fRho[kKt6PFJetsCentralNeutralTight] = r; }
    
  protected:
    Double32_t fRho[nTypes]; //rho from various fastjet algos

    ClassDef(PileupEnergyDensity, 5) // Pileup Energy Density class
  };
}
#endif
