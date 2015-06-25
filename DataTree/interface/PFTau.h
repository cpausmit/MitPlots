//--------------------------------------------------------------------------------------------------
// PFTau
//
// This class holds information about reconst* ucted tau based on PFCandidates.
//
// Authors: J.Bendavid, C.Paus, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PFTAU_H
#define MITANA_DATATREE_PFTAU_H

#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PFCandidate.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/PFJet.h"

namespace mithep {

  class PFTau : public Tau {
  public:
    enum Discriminator {
      kDiscriminationByLooseElectronRejection, // againstElectronLoose
      kDiscriminationByMediumElectronRejection, // againstElectronMedium
      kDiscriminationByTightElectronRejection, // againstElectronTight
      kDiscriminationByMVA5VLooseElectronRejection, // againstElectronVLooseMVA5
      kDiscriminationByMVA5LooseElectronRejection, // againstElectronLooseMVA5
      kDiscriminationByMVA5MediumElectronRejection, // againstElectronMediumMVA5
      kDiscriminationByMVA5TightElectronRejection, // againstElectronTightMVA5
      kDiscriminationByLooseMuonRejection, // againstMuonLoose
      kDiscriminationByMediumMuonRejection, // againstMuonMedium
      kDiscriminationByTightMuonRejection, // againstMuonTight
      kDiscriminationByLooseMuonRejection2, // againstMuonLoose2
      kDiscriminationByMediumMuonRejection2, // againstMuonMedium2
      kDiscriminationByTightMuonRejection2, // againstMuonTight2
      kDiscriminationByLooseMuonRejection3, // againstMuonLoose3
      kDiscriminationByTightMuonRejection3, // againstMuonTight3
      kDiscriminationByDecayModeFinding, // decayModeFinding
      kDiscriminationByDecayModeFindingNewDMs, // decayModeFindingNewDMs
      kDiscriminationByDecayModeFindingOldDMs, // decayModeFindingOldDMs
      kDiscriminationByVLooseCombinedIsolationDBSumPtCorr, // byVLooseCombinedIsolationDeltaBetaCorr
      kDiscriminationByLooseCombinedIsolationDBSumPtCorr, // byLooseCombinedIsolationDeltaBetaCorr
      kDiscriminationByMediumCombinedIsolationDBSumPtCorr, // byMediumCombinedIsolationDeltaBetaCorr
      kDiscriminationByTightCombinedIsolationDBSumPtCorr, // byTightCombinedIsolationDeltaBetaCorr
      kDiscriminationByRawCombinedIsolationDBSumPtCorr, // byCombinedIsolationDeltaBetaCorrRaw
      kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits, // byLooseCombinedIsolationDeltaBetaCorr3Hits
      kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits, // byMediumCombinedIsolationDeltaBetaCorr3Hits
      kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits, // byTightCombinedIsolationDeltaBetaCorr3Hits
      kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits, // byCombinedIsolationDeltaBetaCorrRaw3Hits
      kMVA3IsolationChargedIsoPtSum, // chargedIsoPtSum
      kMVA3IsolationNeutralIsoPtSum, // chargedIsoPtSum
      kMVA3IsolationPUcorrPtSum, // puCorrPtSum
      nDiscriminators
    };

    enum LegacyDiscriminator {
      kDiscriminationAgainstElectron = nDiscriminators,
      kDiscriminationAgainstMuon,
      kDiscriminationByMVAElectronRejection,
      kDiscriminationByVLooseIsolation,
      kDiscriminationByLooseIsolation,
      kDiscriminationByMediumIsolation,
      kDiscriminationByTightIsolation,
      kMVA2rawElectronRejection,
      kMVA2rawElectronRejectionCategory,
      kMVA2LooseElectronRejection,
      kMVA2MediumElectronRejection,
      kMVA2TightElectronRejection,
      kMVA3rawElectronRejection,
      kMVA3rawElectronRejectionCategory,
      kMVA3LooseElectronRejection,
      kMVA3MediumElectronRejection,
      kMVA3TightElectronRejection,
      kMVA3VTightElectronRejection,
      nAllDiscriminators,
      nLegacyDiscriminators = nAllDiscriminators - nDiscriminators
    };

    PFTau();

    Double_t LeadPFCandSignD0Sig() const { return fLeadPFCandSignD0Sig; }
    Double_t HCalTotalEOverP() const { return fHCalTotalEOverP; }
    Double_t HCalMaxEOverP() const { return fHCalMaxEOverP; }
    Double_t HCal3x3EOverP() const { return fHCal3x3EOverP; }
    Double_t IsoChargedHadronPtSum() const { return fIsoChargedHadronPtSum; }
    Double_t IsoGammaEtSum() const { return fIsoGammaEtSum; }
    Double_t MaxHCalPFClusterEt() const { return fMaxHCalPFClusterEt; }
    Double_t EMFraction() const { return fEMFraction; }
    Double_t ECalStripSumEOverP() const { return fECalStripSumEOverP; }
    Double_t BremRecoveryEOverP() const { return fBremRecoveryEOverP; }
    Double_t ElectronPreIDOutput() const { return fElectronPreIDOutput; }
    Double_t CaloCompatibility() const { return fCaloCompatibility; }
    Double_t SegmentCompatibility() const { return fSegmentCompatibility; }
    Bool_t ElectronPreIDDecision() const { return fElectronPreIDDecision; }
    Bool_t MuonDecision() const { return fMuonDecision; }
    Double_t PFTauDiscriminator(UInt_t) const;
    PFCandidate const* LeadPFCand() const { return fLeadPFCand.Obj(); }
    PFCandidate const* LeadChargedHadronPFCand() const { return fLeadChargedHadPFCand.Obj(); }
    PFCandidate const* LeadNeutralHadronPFCand() const { return fLeadNeutralPFCand.Obj(); }
    PFJet const* SourcePFJet() const { return fPFJet.Obj(); }
    Jet const* SourceJet() const override { return SourcePFJet(); }
    Track const* ElectronTrack() const { return fElectronTrack.Obj(); }
    PFCandidate const* SignalPFCand(UInt_t i) const { return fSignalPFCands.At(i); }
    PFCandidate const* SignalPFChargedHadrCand(UInt_t i) const { return fSignalPFChargedHadrCands.At(i); }
    PFCandidate const* SignalPFNeutrHadrCand(UInt_t i) const { return fSignalPFNeutrHadrCands.At(i); }
    PFCandidate const* SignalPFGammaCand(UInt_t i) const { return fSignalPFGammaCands.At(i); }
    PFCandidate const* IsoPFCand(UInt_t i) const { return fIsoPFCands.At(i); }

    UInt_t NSignalPFCands() const { return fSignalPFCands.Entries(); }
    UInt_t NSignalPFChargedHadrCands() const { return fSignalPFChargedHadrCands.Entries(); }
    UInt_t NSignalPFNeutrHadrCands() const { return fSignalPFNeutrHadrCands.Entries(); }
    UInt_t NSignalPFGammaCands() const { return fSignalPFGammaCands.Entries(); }
    UInt_t NIsoPFCands() const { return fIsoPFCands.Entries(); }

    EObjType ObjType() const override { return kPFTau; }

    void SetCharge(Char_t x) { fCharge = x; ClearCharge(); }
    void SetLeadPFCandSignD0Sig(Double_t x) { fLeadPFCandSignD0Sig = x; }
    void SetHCalTotalEOverP(Double_t x) { fHCalTotalEOverP = x; }
    void SetHCalMaxEOverP(Double_t x) { fHCalMaxEOverP = x; }
    void SetHCal3x3EOverP(Double_t x) { fHCal3x3EOverP = x; }
    void SetIsoChargedHadronPtSum(Double_t x){ fIsoChargedHadronPtSum = x; }
    void SetIsoGammaEtSum(Double_t x) { fIsoGammaEtSum = x; }
    void SetMaxHCalPFClusterEt(Double_t x) { fMaxHCalPFClusterEt = x; }
    void SetEMFraction(Double_t x) { fEMFraction = x; }
    void SetECalStripSumEOverP(Double_t x) { fECalStripSumEOverP = x; }
    void SetBremRecoveryEOverP(Double_t x) { fBremRecoveryEOverP = x; }
    void SetElectronPreIDOutput(Double_t x) { fElectronPreIDOutput = x; }
    void SetCaloCompatibility(Double_t x) { fCaloCompatibility = x; }
    void SetSegmentCompatibility(Double_t x) { fSegmentCompatibility = x; }
    void SetElectronPreIDDecision(Bool_t b) { fElectronPreIDDecision = b; }
    void SetMuonDecision(Bool_t b) { fMuonDecision = b; }
    void SetPFTauDiscriminator(Double_t, UInt_t);
    void SetLeadPFCand(PFCandidate const* p) { fLeadPFCand = p; }
    void SetLeadChargedHadronPFCand(PFCandidate const* p) { fLeadChargedHadPFCand = p; }
    void SetLeadNeutralPFCand(PFCandidate const* p) { fLeadNeutralPFCand = p; }
    void SetPFJet(PFJet const* j) { fPFJet = j; }
    void SetElectronTrack(Track const* t) { fElectronTrack = t; }
    void AddSignalPFCand(PFCandidate const* p) { ClearCharge(); fSignalPFCands.Add(p); }
    void AddSignalPFChargedHadrCand(PFCandidate const* p) { fSignalPFChargedHadrCands.Add(p); }
    void AddSignalPFNeutrHadrCand(PFCandidate const* p) { fSignalPFNeutrHadrCands.Add(p); }
    void AddSignalPFGammaCand(PFCandidate const* p) { fSignalPFGammaCands.Add(p); }
    void AddIsoPFCand(PFCandidate const* p) { fIsoPFCands.Add(p); }

    // Some structural tools
    void Mark(UInt_t i=1) const override;

    // backward compatibility
    Double_t DiscriminationAgainstElectron() const { return PFTauDiscriminator(kDiscriminationAgainstElectron); }
    Double_t DiscriminationAgainstMuon() const { return PFTauDiscriminator(kDiscriminationAgainstMuon); }
    Double_t DiscriminationByLooseElectronRejection() const { return PFTauDiscriminator(kDiscriminationByLooseElectronRejection); }
    Double_t DiscriminationByMediumElectronRejection() const { return PFTauDiscriminator(kDiscriminationByMediumElectronRejection); }
    Double_t DiscriminationByTightElectronRejection() const { return PFTauDiscriminator(kDiscriminationByTightElectronRejection); }
    Double_t DiscriminationByMVAElectronRejection() const { return PFTauDiscriminator(kDiscriminationByMVAElectronRejection); }
    Double_t DiscriminationByLooseMuonRejection() const { return PFTauDiscriminator(kDiscriminationByLooseMuonRejection); }
    Double_t DiscriminationByMediumMuonRejection() const { return PFTauDiscriminator(kDiscriminationByMediumMuonRejection); }
    Double_t DiscriminationByTightMuonRejection() const { return PFTauDiscriminator(kDiscriminationByTightMuonRejection); }
    Double_t DiscriminationByDecayModeFinding() const { return PFTauDiscriminator(kDiscriminationByDecayModeFinding); }
    Double_t DiscriminationByVLooseIsolation() const { return PFTauDiscriminator(kDiscriminationByVLooseIsolation); }
    Double_t DiscriminationByLooseIsolation() const { return PFTauDiscriminator(kDiscriminationByLooseIsolation); }
    Double_t DiscriminationByMediumIsolation() const { return PFTauDiscriminator(kDiscriminationByMediumIsolation); }
    Double_t DiscriminationByTightIsolation() const { return PFTauDiscriminator(kDiscriminationByTightIsolation); }
    Double_t DiscriminationByVLooseCombinedIsolationDBSumPtCorr() const { return PFTauDiscriminator(kDiscriminationByVLooseCombinedIsolationDBSumPtCorr); }
    Double_t DiscriminationByLooseCombinedIsolationDBSumPtCorr() const { return PFTauDiscriminator(kDiscriminationByLooseCombinedIsolationDBSumPtCorr); }
    Double_t DiscriminationByMediumCombinedIsolationDBSumPtCorr() const { return PFTauDiscriminator(kDiscriminationByMediumCombinedIsolationDBSumPtCorr); }
    Double_t DiscriminationByTightCombinedIsolationDBSumPtCorr() const { return PFTauDiscriminator(kDiscriminationByTightCombinedIsolationDBSumPtCorr); }
    Double_t DiscriminationByRawCombinedIsolationDBSumPtCorr() const { return PFTauDiscriminator(kDiscriminationByRawCombinedIsolationDBSumPtCorr); }
    Double_t MVA2rawElectronRejection() const { return PFTauDiscriminator(kMVA2rawElectronRejection); }
    Double_t MVA2rawElectronRejectionCategory() const { return PFTauDiscriminator(kMVA2rawElectronRejectionCategory); }
    Double_t MVA2LooseElectronRejection() const { return PFTauDiscriminator(kMVA2LooseElectronRejection); }
    Double_t MVA2MediumElectronRejection() const { return PFTauDiscriminator(kMVA2MediumElectronRejection); }
    Double_t MVA2TightElectronRejection() const { return PFTauDiscriminator(kMVA2TightElectronRejection); }
    Double_t MVA3rawElectronRejection() const { return PFTauDiscriminator(kMVA3rawElectronRejection); }
    Double_t MVA3rawElectronRejectionCategory() const { return PFTauDiscriminator(kMVA3rawElectronRejectionCategory); }
    Double_t MVA3LooseElectronRejection() const { return PFTauDiscriminator(kMVA3LooseElectronRejection); }
    Double_t MVA3MediumElectronRejection() const { return PFTauDiscriminator(kMVA3MediumElectronRejection); }
    Double_t MVA3TightElectronRejection() const { return PFTauDiscriminator(kMVA3TightElectronRejection); }
    Double_t MVA3VTightElectronRejection() const { return PFTauDiscriminator(kMVA3VTightElectronRejection); }
    Double_t LooseCombinedIsolationDBSumPtCorr3Hits() const { return PFTauDiscriminator(kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits); }
    Double_t MediumCombinedIsolationDBSumPtCorr3Hits() const { return PFTauDiscriminator(kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits); }
    Double_t TightCombinedIsolationDBSumPtCorr3Hits() const { return PFTauDiscriminator(kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits); }
    Double_t RawCombinedIsolationDBSumPtCorr3Hits() const { return PFTauDiscriminator(kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits); }
    Double_t LooseMuonRejection2() const { return PFTauDiscriminator(kDiscriminationByLooseMuonRejection2); }
    Double_t MediumMuonRejection2() const { return PFTauDiscriminator(kDiscriminationByMediumMuonRejection2); }
    Double_t TightMuonRejection2() const { return PFTauDiscriminator(kDiscriminationByTightMuonRejection2); }
    void SetDiscriminationAgainstElectron(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationAgainstElectron); }
    void SetDiscriminationAgainstMuon(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationAgainstMuon); }
    void SetDiscriminationByLooseElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseElectronRejection); }
    void SetDiscriminationByMediumElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumElectronRejection); }
    void SetDiscriminationByTightElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightElectronRejection); }
    void SetDiscriminationByMVAElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMVAElectronRejection); }
    void SetDiscriminationByLooseMuonRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseMuonRejection); }
    void SetDiscriminationByMediumMuonRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumMuonRejection); }
    void SetDiscriminationByTightMuonRejection(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightMuonRejection); }
    void SetDiscriminationByDecayModeFinding(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByDecayModeFinding); }
    void SetDiscriminationByVLooseIsolation(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByVLooseIsolation); }
    void SetDiscriminationByLooseIsolation(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseIsolation); }
    void SetDiscriminationByMediumIsolation(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumIsolation); }
    void SetDiscriminationByTightIsolation(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightIsolation); }
    void SetDiscriminationByVLooseCombinedIsolationDBSumPtCorr(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByVLooseCombinedIsolationDBSumPtCorr); }
    void SetDiscriminationByLooseCombinedIsolationDBSumPtCorr(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseCombinedIsolationDBSumPtCorr); }
    void SetDiscriminationByMediumCombinedIsolationDBSumPtCorr(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumCombinedIsolationDBSumPtCorr); }
    void SetDiscriminationByTightCombinedIsolationDBSumPtCorr(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightCombinedIsolationDBSumPtCorr); }
    void SetDiscriminationByRawCombinedIsolationDBSumPtCorr(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByRawCombinedIsolationDBSumPtCorr); }
    void SetMVA2rawElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA2rawElectronRejection); }
    void SetMVA2rawElectronRejectionCategory(Double_t x) { SetPFTauDiscriminator(x, kMVA2rawElectronRejectionCategory); }
    void SetMVA2LooseElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA2LooseElectronRejection); }
    void SetMVA2MediumElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA2MediumElectronRejection); }
    void SetMVA2TightElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA2TightElectronRejection); }
    void SetMVA3rawElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA3rawElectronRejection); }
    void SetMVA3rawElectronRejectionCategory(Double_t x) { SetPFTauDiscriminator(x, kMVA3rawElectronRejectionCategory); }
    void SetMVA3LooseElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA3LooseElectronRejection); }
    void SetMVA3MediumElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA3MediumElectronRejection); }
    void SetMVA3TightElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA3TightElectronRejection); }
    void SetMVA3VTightElectronRejection(Double_t x) { SetPFTauDiscriminator(x, kMVA3VTightElectronRejection); }
    void SetLooseCombinedIsolationDBSumPtCorr3Hits(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits); }
    void SetMediumCombinedIsolationDBSumPtCorr3Hits(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits); }
    void SetTightCombinedIsolationDBSumPtCorr3Hits(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits); }
    void SetRawCombinedIsolationDBSumPtCorr3Hits(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits); }
    void SetLooseMuonRejection2(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByLooseMuonRejection2); }
    void SetMediumMuonRejection2(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByMediumMuonRejection2); }
    void SetTightMuonRejection2(Double_t x) { SetPFTauDiscriminator(x, kDiscriminationByTightMuonRejection2); }

    static char const* PFTauDiscriminatorName(UInt_t);
    static UInt_t PFTauDiscriminatorIndex(char const*);

  protected:
    Double_t GetCharge() const override;

    Char_t fCharge; //stored charge
    Double32_t fLeadPFCandSignD0Sig; //[0,0,14]signed lead track D0 significance
    Double32_t fHCalTotalEOverP; //[0,0,14]total hcal e / lead ch had pfcand mom
    Double32_t fHCalMaxEOverP; //[0,0,14]max hcal e / lead ch had pfcand. mom
    Double32_t fHCal3x3EOverP; //[0,0,14]3x3 hcal e / lead ch hadron pfcand. mom
    Double32_t fIsoChargedHadronPtSum; //[0,0,14]sum pt of sel. ch had pfcands in iso cone
    Double32_t fIsoGammaEtSum; //[0,0,14]sum et of sel. photon pfcands in iso cone
    Double32_t fMaxHCalPFClusterEt; //[0,0,14]et of largest et hcal pfcluster
    Double32_t fEMFraction; //[0,0,14]em energy fraction
    Double32_t fECalStripSumEOverP; //[0,0,14]simple brem recovery e / lead ch had mom
    Double32_t fBremRecoveryEOverP; //[0,0,14]brem recovery E / lead charged hadron P
    Double32_t fElectronPreIDOutput; //[0,0,14]pfel pre id bdt output to be an el
    Double32_t fCaloCompatibility; //[0,0,14]calo comp. for this tau to be a muon
    Double32_t fSegmentCompatibility; //[0,0,14]segment comp. for this tau to be a muon
    Bool_t fElectronPreIDDecision; //pf electron pre id decision
    Bool_t fMuonDecision; //pf muon id decision
    Double32_t fPFTauDiscriminator[nDiscriminators];
    Double_t fPFTauLegacyDiscriminator[nLegacyDiscriminators]; //! only for reading old data

    Ref<PFCandidate> fLeadPFCand; //leading sig pf cand (charged or neutral)
    Ref<PFCandidate> fLeadChargedHadPFCand; //leading charged hadron signal pf cand
    Ref<PFCandidate> fLeadNeutralPFCand; //leading neutral signal pf cand
    Ref<PFJet> fPFJet; //original reconst* ucted pf jet
    Ref<Track> fElectronTrack; //track corresp. to pot. matching el cand
    RefArray<PFCandidate> fSignalPFCands; //selected pf candidates in signal cone
    RefArray<PFCandidate> fSignalPFChargedHadrCands; //signal pf charged hadron candidates
    RefArray<PFCandidate> fSignalPFNeutrHadrCands; //signal pf neutral hadron candidates
    RefArray<PFCandidate> fSignalPFGammaCands; //signal pf gamma candidates
    RefArray<PFCandidate> fIsoPFCands; //selected pf candidates in isolation annulus

    ClassDef(PFTau, 8) // PFTau class
  };
}

inline
Double_t
mithep::PFTau::PFTauDiscriminator(UInt_t d) const
{
  if (d < nDiscriminators)
    return fPFTauDiscriminator[d];
  else if (d < nAllDiscriminators)
    return fPFTauLegacyDiscriminator[d - nDiscriminators];
  else
    return 0.;
}

inline
void
mithep::PFTau::SetPFTauDiscriminator(Double_t v, UInt_t d)
{
  if (d < nDiscriminators)
    fPFTauDiscriminator[d] = v;
  else if (d < nAllDiscriminators)
    fPFTauLegacyDiscriminator[d - nDiscriminators] = v;
}

inline
void
mithep::PFTau::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fLeadPFCand .IsValid())
    fLeadPFCand .Obj()->Mark(ib);
  if (fLeadChargedHadPFCand.IsValid())
    fLeadChargedHadPFCand.Obj()->Mark(ib);
  if (fLeadNeutralPFCand .IsValid())
    fLeadNeutralPFCand .Obj()->Mark(ib);
  if (fPFJet .IsValid())
    fPFJet .Obj()->Mark(ib);
  if (fElectronTrack .IsValid())
    fElectronTrack .Obj()->Mark(ib);

  fSignalPFCands .Mark(ib);
  fSignalPFChargedHadrCands.Mark(ib);
  fSignalPFNeutrHadrCands .Mark(ib);
  fSignalPFGammaCands .Mark(ib);
  fIsoPFCands .Mark(ib);
}

inline
Double_t
mithep::PFTau::GetCharge() const
{
  return fCharge;
}


#endif
