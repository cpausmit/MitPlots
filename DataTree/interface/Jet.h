//--------------------------------------------------------------------------------------------------
// Jet
//
// Base jet class to hold reconstructed jet information.
//
// Authors: S.Xie, C.Loizides, J.Bendavid, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_JET_H
#define MITANA_DATATREE_JET_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep {
  class Jet : public Particle {
  public:
    enum BTagAlgo {
      kJetProbability,
      kJetBProbability,
      kSimpleSecondaryVertexHighEff,
      kSimpleSecondaryVertexHighPur,
      kCombinedSecondaryVertex,
      kCombinedSecondaryVertexV2,
      kCombinedSecondaryVertexSoftLepton,
      kCombinedInclusiveSecondaryVertexV2,
      kCombinedMVA,
      kTrackCountingHighEff,
      kTrackCountingHighPur,
      nBTagAlgos
    };

    enum BTagLegacyAlgo {
      kSimpleSecondaryVertex = nBTagAlgos,
      kSoftMuon,
      kSoftMuonByIP3d,
      kSoftMuonByPt,
      kSoftElectronByIP3d,
      kSoftElectronByPt,
      kGhostTrack,
      nAllBTagAlgos,
      nBTagLegacyAlgos = nAllBTagAlgos - nBTagAlgos
    };

    enum ECorr { 
      L1 = 0, 
      L2,
      L3,
      L4,
      L5,
      L6,
      L7,
      Custom,
      nECorrs
    };
 
    Jet();

    FourVectorM RawMom() const { return fRawMom.V(); }
    Double_t Alpha() const { return fAlpha; }
    Double_t Beta() const { return fBeta; }
    Int_t MatchedMCFlavor() const { return fMatchedMCFlavor; }
    Double_t SigmaEta() const { return fSigmaEta; }
    Double_t SigmaPhi() const { return fSigmaPhi; }
    Double_t BJetTagsDisc(UInt_t) const;
    Double_t CombinedCorrectionScale() const;
    Double_t CorrectionScale(UInt_t c) const { return fCorrectionScale[c]; }
    Double_t L1OffsetCorrectionScale() const { return fCorrectionScale[L1]; }
    Double_t L2RelativeCorrectionScale() const { return fCorrectionScale[L2]; }
    Double_t L3AbsoluteCorrectionScale() const { return fCorrectionScale[L3]; }
    Double_t L4EMFCorrectionScale() const { return fCorrectionScale[L4]; }
    Double_t L5FlavorCorrectionScale() const { return fCorrectionScale[L5]; }
    Double_t L6LSBCorrectionScale() const { return fCorrectionScale[L6]; }
    Double_t L7PartonCorrectionScale() const { return fCorrectionScale[L7]; }
    Double_t CustomCorrectionScale() const { return fCorrectionScale[Custom]; }
    Double_t JetArea() const { return fJetArea; }

    BitMask8 const& Corrections() const { return fCorrections; }
    Bool_t CorrectionActive(UInt_t c) const { return fCorrections.TestBit(c); }
    Bool_t CorrectionAvailable(UInt_t c) const { return fCorrectionScale[c] >= 0.; }

    virtual UInt_t NConstituents() const { return 0; }
    UInt_t N() const { return NConstituents(); }

    void SetRawPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m)
    { fRawMom.Set(pt, eta, phi, m); ClearMom(); }
    void SetAlpha(Double_t val) { fAlpha = val; }
    void SetBeta(Double_t val) { fBeta = val; } 
    void SetMatchedMCFlavor(Int_t flavor) { fMatchedMCFlavor = flavor; }
    void SetSigmaEta(Double_t val) { fSigmaEta = val; }
    void SetSigmaPhi(Double_t val) { fSigmaPhi = val; }
    void SetBJetTagsDisc(Double_t, UInt_t);
    void SetCorrectionScale(Double_t s, UInt_t l) { fCorrectionScale[l] = s; ClearMom(); }
    void SetL1OffsetCorrectionScale(Double_t s) { fCorrectionScale[L1] = s; ClearMom(); }
    void SetL2RelativeCorrectionScale(Double_t s) { fCorrectionScale[L2] = s; ClearMom(); }
    void SetL3AbsoluteCorrectionScale(Double_t s) { fCorrectionScale[L3] = s; ClearMom(); }
    void SetL4EMFCorrectionScale(Double_t s) { fCorrectionScale[L4] = s; ClearMom(); }
    void SetL5FlavorCorrectionScale(Double_t s) { fCorrectionScale[L5] = s; ClearMom(); }
    void SetL6LSBCorrectionScale(Double_t s) { fCorrectionScale[L6] = s; ClearMom(); }
    void SetL7PartonCorrectionScale(Double_t s) { fCorrectionScale[L7] = s; ClearMom(); }
    void SetCustomCorrectionScale(Double_t s) { fCorrectionScale[Custom] = s; ClearMom(); }
    void SetJetArea(Double_t a) { fJetArea = a; }

    void SetCorrections(BitMask8 const& cor) { fCorrections = cor; }
    void DisableCorrection(UInt_t c) { fCorrections.ClearBit(c); ClearMom(); }
    void DisableCorrections() { fCorrections.Clear(); ClearMom(); }
    void EnableCorrection(UInt_t c) { fCorrections.SetBit(c); ClearMom(); }

    EObjType ObjType() const override { return kJet; } 
    virtual Jet* MakeCopy() const { return new Jet(*this); }

    // backward compatibility
    Double_t JetProbabilityBJetTagsDisc() const { return BJetTagsDisc(kJetProbability); }
    Double_t JetBProbabilityBJetTagsDisc() const { return BJetTagsDisc(kJetBProbability); }
    Double_t SimpleSecondaryVertexHighEffBJetTagsDisc() const { return BJetTagsDisc(kSimpleSecondaryVertexHighEff); }
    Double_t SimpleSecondaryVertexHighPurBJetTagsDisc() const { return BJetTagsDisc(kSimpleSecondaryVertexHighPur); } 
    Double_t CombinedSecondaryVertexBJetTagsDisc() const { return BJetTagsDisc(kCombinedSecondaryVertex); } 
    Double_t CombinedSecondaryVertexMVABJetTagsDisc() const { return BJetTagsDisc(kCombinedMVA); }
    Double_t TrackCountingHighEffBJetTagsDisc() const { return BJetTagsDisc(kTrackCountingHighEff); }
    Double_t TrackCountingHighPurBJetTagsDisc() const { return BJetTagsDisc(kTrackCountingHighPur); }
    Double_t SimpleSecondaryVertexBJetTagsDisc() const { return BJetTagsDisc(kSimpleSecondaryVertex); }
    Double_t SoftMuonBJetTagsDisc() const { return BJetTagsDisc(kSoftMuon); }
    Double_t SoftMuonByIP3dBJetTagsDisc() const { return BJetTagsDisc(kSoftMuonByIP3d); }
    Double_t SoftMuonByPtBJetTagsDisc() const { return BJetTagsDisc(kSoftMuonByPt); }
    Double_t SoftElectronByIP3dBJetTagsDisc() const { return BJetTagsDisc(kSoftElectronByIP3d); }
    Double_t SoftElectronByPtBJetTagsDisc() const { return BJetTagsDisc(kSoftElectronByPt); }
    Double_t GhostTrackBJetTagsDisc() const { return BJetTagsDisc(kGhostTrack); }
    void SetCombinedSecondaryVertexBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kCombinedSecondaryVertex); }
    void SetCombinedSecondaryVertexMVABJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kCombinedMVA); }
    void SetJetProbabilityBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kJetProbability); }
    void SetJetBProbabilityBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kJetBProbability); }
    void SetSimpleSecondaryVertexBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSimpleSecondaryVertex); }
    void SetSimpleSecondaryVertexHighEffBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSimpleSecondaryVertexHighEff); }
    void SetSimpleSecondaryVertexHighPurBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSimpleSecondaryVertexHighPur); }
    void SetSoftMuonBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSoftMuon); }
    void SetSoftMuonByIP3dBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSoftMuonByIP3d); }
    void SetSoftMuonByPtBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSoftMuonByPt); }
    void SetSoftElectronByIP3dBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSoftElectronByIP3d); }
    void SetSoftElectronByPtBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kSoftElectronByPt); }
    void SetTrackCountingHighEffBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kTrackCountingHighEff); }
    void SetTrackCountingHighPurBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kTrackCountingHighPur); }
    void SetGhostTrackBJetTagsDisc(Double_t d) { SetBJetTagsDisc(d, kGhostTrack); }

    static char const* BTagAlgoName(UInt_t);
    static UInt_t BTagAlgoIndex(char const*);

  protected:
    void GetMom() const override;

    Vect4M fRawMom; //uncorrected four momentum of jet
    Double32_t fAlpha; 	 //[0,0,14]jet vertex alpha variable
    Double32_t fBeta; 	 //[0,0,14]jet vertex beta variable
    Int_t fMatchedMCFlavor; //[0,0,14]pdg of matched quark flavor
    Double32_t fSigmaEta; //[0,0,14]sqrt(etaetaMoment)
    Double32_t fSigmaPhi; //[0,0,14]sqrt(phiphiMoment)
    Double32_t fBJetTagsDisc[nBTagAlgos]; //b-tag discriminators
    Double_t fBJetTagsLegacyDisc[nBTagLegacyAlgos]; //! legacy b-tag algos (only when reading old files)
    Double32_t fCorrectionScale[nECorrs]; //jet energy correction scales, default to -1
    Double32_t fJetArea; //[0,0,14]infrared safe jet area
    BitMask8 fCorrections; //mask of corrections to be applied

    ClassDef(Jet, 7) // Jet class
  };
}

inline
void
mithep::Jet::GetMom() const
{
  // Get raw momentum values from stored values and apply all enabled corrections.

  fCachedMom.SetCoordinates(fRawMom.Pt(),fRawMom.Eta(),fRawMom.Phi(),fRawMom.M()); 

  fCachedMom *= CombinedCorrectionScale();

}

inline
Double_t
mithep::Jet::BJetTagsDisc(UInt_t a) const
{
  if (a < nBTagAlgos)
    return fBJetTagsDisc[a];
  else if (a < nAllBTagAlgos)
    return fBJetTagsLegacyDisc[a - nBTagAlgos];
  else
    return -9999.;
}

inline
Double_t
mithep::Jet::CombinedCorrectionScale() const
{
  // compute combined correction scale from all enabled corrections
  Double_t scale = 1.0;

  for (unsigned iC = 0; iC != nECorrs; ++iC) {
    if (CorrectionActive(iC))
      scale *= fCorrectionScale[iC];
  }

  return scale;
}

inline
void
mithep::Jet::SetBJetTagsDisc(Double_t d, UInt_t a)
{
  if (a < nBTagAlgos)
    fBJetTagsDisc[a] = d;
  else if (a < nAllBTagAlgos)
    fBJetTagsLegacyDisc[a - nBTagAlgos] = d;
}

#endif
