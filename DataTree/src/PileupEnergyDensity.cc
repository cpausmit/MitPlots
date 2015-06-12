#include "MitAna/DataTree/interface/PileupEnergyDensity.h"

#include <cstring>

ClassImp(mithep::PileupEnergyDensity)

/*static*/
char const*
mithep::PileupEnergyDensity::AlgoName(UInt_t a)
{
  switch (a) {
  case kHighEta:
    return "HighEta";
  case kLowEta:
    return "LowEta";
  case kRandom:
    return "Random";
  case kRandomLowEta:
    return "RandomLowEta";
  case kFixedGridAll:
    return "FixedGridAll";
  case kFixedGridFastjetAll:
    return "FixedGridFastjetAll";
  case kFixedGridFastjetAllCalo:
    return "FixedGridFastjetAllCalo";
  case kFixedGridFastjetCentralCalo:
    return "FixedGridFastjetCentralCalo";
  case kFixedGridFastjetCentralChargedPileUp:
    return "FixedGridFastjetCentralChargedPileUp";
  case kFixedGridFastjetCentralNeutral:
    return "FixedGridFastjetCentralNeutral";
  case kKt6CaloJets:
    return "Kt6CaloJets";
  case kKt6CaloJetsCentral:
    return "Kt6CaloJetsCentral";
  case kKt6PFJets:
    return "Kt6PFJets";
  case kKt6PFJetsCentralChargedPileUp:
    return "Kt6PFJetsCentralChargedPileUp";
  case kKt6PFJetsCentralNeutral:
    return "Kt6PFJetsCentralNeutral";
  case kKt6PFJetsCentralNeutralTight:
    return "Kt6PFJetsCentralNeutralTight";
  default:
    return "";
  }
}

/*static*/
UInt_t
mithep::PileupEnergyDensity::AlgoIndex(char const* name)
{
  for (unsigned idx = 0; idx != nAllAlgos; ++idx) {
    if (std::strcmp(name, AlgoName(idx)) == 0)
      return idx;
  }
  return nAllAlgos;
}
