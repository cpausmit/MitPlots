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
    enum Algo {
      kHighEta,
      kLowEta,
      kRandom,
      kRandomLowEta,
      kFixedGridAll,
      kFixedGridFastjetAll,
      kFixedGridFastjetAllCalo,
      kFixedGridFastjetCentralCalo,
      kFixedGridFastjetCentralChargedPileUp,
      kFixedGridFastjetCentralNeutral,
      nAlgos
    };

    enum LegacyAlgo {
      kKt6CaloJets = nAlgos,
      kKt6CaloJetsCentral,
      kKt6PFJets,
      kKt6PFJetsCentralChargedPileUp,
      kKt6PFJetsCentralNeutral,
      kKt6PFJetsCentralNeutralTight,
      nAllAlgos,
      nLegacyAlgos = nAllAlgos - nAlgos
    };

    PileupEnergyDensity() :
      fRho{}
    {
    }

    Double_t RhoDefault() const { return Rho(kRandom); }
    Double_t Rho(UInt_t = kHighEta) const;

    void SetRho(Double_t, UInt_t = kHighEta);

    virtual PileupEnergyDensity *MakeCopy() const { return new PileupEnergyDensity(*this); }

    // backward compatibility
    Double_t RhoHighEta() const { return Rho(kHighEta); }
    Double_t RhoLowEta() const { return Rho(kLowEta); }
    Double_t RhoRandom() const { return Rho(kRandom); }
    Double_t RhoRandomLowEta() const { return Rho(kRandomLowEta); }
    Double_t RhoFixedGridAll() const { return Rho(kFixedGridAll); }
    Double_t RhoFixedGridFastjetAll() const { return Rho(kFixedGridFastjetAll); }
    Double_t RhoKt6CaloJets() const { return Rho(kKt6CaloJets); }
    Double_t RhoKt6CaloJetsCentral() const { return Rho(kKt6CaloJetsCentral); }
    Double_t RhoKt6PFJets() const { return Rho(kKt6PFJets); }
    Double_t RhoKt6PFJetsCentralChargedPileUp() const { return Rho(kKt6PFJetsCentralChargedPileUp); }
    Double_t RhoKt6PFJetsCentralNeutral() const { return Rho(kKt6PFJetsCentralNeutral); }
    Double_t RhoKt6PFJetsCentralNeutralTight() const { return Rho(kKt6PFJetsCentralNeutralTight); }

    static char const* AlgoName(UInt_t);
    static UInt_t AlgoIndex(char const*);
 
  protected:
    Double32_t fRho[nAlgos]; //rho from various fastjet algos
    Double_t   fRhoLegacy[nLegacyAlgos]; //! only for reading old files

    ClassDef(PileupEnergyDensity, 5) // Pileup Energy Density class
  };
}

inline
Double_t
mithep::PileupEnergyDensity::Rho(UInt_t a/* = mithep::PileupEnergyDensity::kHighEta*/) const
{
  if (a < nAlgos)
    return fRho[a];
  else if (a < nAllAlgos)
    return fRhoLegacy[a - nAlgos];
  else
    return 0.;
}

inline
void
mithep::PileupEnergyDensity::SetRho(Double_t r, UInt_t a/* = mithep::PileupEnergyDensity::kHighEta*/)
{
  if (a < nAlgos)
    fRho[a] = r;
  else if (a < nAllAlgos)
    fRhoLegacy[a - nAlgos] = r;
}

#endif
