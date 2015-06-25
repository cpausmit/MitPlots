#include "MitAna/DataTree/interface/PFTau.h"

#include <cstring>

ClassImp(mithep::PFTau)

mithep::PFTau::PFTau() :
  Tau(),
  fCharge(0),
  fLeadPFCandSignD0Sig(0.),
  fHCalTotalEOverP(0.),
  fHCalMaxEOverP(0.),
  fHCal3x3EOverP(0.),
  fIsoChargedHadronPtSum(0.),
  fIsoGammaEtSum(0.),
  fMaxHCalPFClusterEt(0.),
  fEMFraction(0.),
  fECalStripSumEOverP(0.),
  fBremRecoveryEOverP(0.),
  fElectronPreIDOutput(0.),
  fCaloCompatibility(0.),
  fSegmentCompatibility(0.),
  fElectronPreIDDecision(kFALSE),
  fMuonDecision(kFALSE),
  fPFTauDiscriminator{},
  fPFTauLegacyDiscriminator{},
  fLeadPFCand(),
  fLeadChargedHadPFCand(),
  fLeadNeutralPFCand(),
  fPFJet(),
  fElectronTrack(),
  fSignalPFCands(),
  fSignalPFChargedHadrCands(),
  fSignalPFNeutrHadrCands(),
  fSignalPFGammaCands(),
  fIsoPFCands()
{
}

/*static*/
char const*
mithep::PFTau::PFTauDiscriminatorName(UInt_t idx)
{
  switch(idx) {
  case kDiscriminationByLooseElectronRejection:
    return "DiscriminationByLooseElectronRejection";
  case kDiscriminationByMediumElectronRejection:
    return "DiscriminationByMediumElectronRejection";
  case kDiscriminationByTightElectronRejection:
    return "DiscriminationByTightElectronRejection";
  case kDiscriminationByMVA5VLooseElectronRejection:
    return "DiscriminationByMVA5VLooseElectronRejection";
  case kDiscriminationByMVA5LooseElectronRejection:
    return "DiscriminationByMVA5LooseElectronRejection";
  case kDiscriminationByMVA5MediumElectronRejection:
    return "DiscriminationByMVA5MediumElectronRejection";
  case kDiscriminationByMVA5TightElectronRejection:
    return "DiscriminationByMVA5TightElectronRejection";
  case kDiscriminationByLooseMuonRejection:
    return "DiscriminationByLooseMuonRejection";
  case kDiscriminationByMediumMuonRejection:
    return "DiscriminationByMediumMuonRejection";
  case kDiscriminationByTightMuonRejection:
    return "DiscriminationByTightMuonRejection";
  case kDiscriminationByLooseMuonRejection2:
    return "DiscriminationByLooseMuonRejection2";
  case kDiscriminationByMediumMuonRejection2:
    return "DiscriminationByMediumMuonRejection2";
  case kDiscriminationByTightMuonRejection2:
    return "DiscriminationByTightMuonRejection2";
  case kDiscriminationByLooseMuonRejection3:
    return "DiscriminationByLooseMuonRejection3";
  case kDiscriminationByTightMuonRejection3:
    return "DiscriminationByTightMuonRejection3";
  case kDiscriminationByDecayModeFinding:
    return "DiscriminationByDecayModeFinding";
  case kDiscriminationByDecayModeFindingNewDMs:
    return "DiscriminationByDecayModeFindingNewDMs";
  case kDiscriminationByDecayModeFindingOldDMs:
    return "DiscriminationByDecayModeFindingOldDMs";
  case kDiscriminationByVLooseCombinedIsolationDBSumPtCorr:
    return "DiscriminationByVLooseCombinedIsolationDBSumPtCorr";
  case kDiscriminationByLooseCombinedIsolationDBSumPtCorr:
    return "DiscriminationByLooseCombinedIsolationDBSumPtCorr";
  case kDiscriminationByMediumCombinedIsolationDBSumPtCorr:
    return "DiscriminationByMediumCombinedIsolationDBSumPtCorr";
  case kDiscriminationByTightCombinedIsolationDBSumPtCorr:
    return "DiscriminationByTightCombinedIsolationDBSumPtCorr";
  case kDiscriminationByRawCombinedIsolationDBSumPtCorr:
    return "DiscriminationByRawCombinedIsolationDBSumPtCorr";
  case kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits:
    return "DiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits";
  case kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits:
    return "DiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits";
  case kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits:
    return "DiscriminationByTightCombinedIsolationDBSumPtCorr3Hits";
  case kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits:
    return "DiscriminationByRawCombinedIsolationDBSumPtCorr3Hits";
  case kMVA3IsolationChargedIsoPtSum:
    return "MVA3IsolationChargedIsoPtSum";
  case kMVA3IsolationNeutralIsoPtSum:
    return "MVA3IsolationNeutralIsoPtSum";
  case kMVA3IsolationPUcorrPtSum:
    return "MVA3IsolationPUcorrPtSum";
  default:
    return "";
  }
}

/*static*/
UInt_t
mithep::PFTau::PFTauDiscriminatorIndex(char const* name)
{
  for (unsigned idx = 0; idx != nDiscriminators; ++idx) {
    if (std::strcmp(name, PFTauDiscriminatorName(idx)) == 0)
      return idx;
  }
  return nDiscriminators;
}
