#include "MitAna/DataTree/interface/Jet.h"

ClassImp(mithep::Jet)

mithep::Jet::Jet() :
  fRawMom(),
  fAlpha(0.),
  fBeta(0.),
  fMatchedMCFlavor(0),
  fSigmaEta(0.),
  fSigmaPhi(0.),
  fBJetTagsDisc{},
  fCorrectionScale{},
  fJetArea(0.),
  fCorrections()
{
}

mithep::Jet::Jet(Double_t px, Double_t py, Double_t pz, Double_t e) :
  fRawMom(px, py, pz, e),
  fAlpha(0.),
  fBeta(0.),
  fMatchedMCFlavor(0),
  fSigmaEta(0.),
  fSigmaPhi(0.),
  fBJetTagsDisc{},
  fCorrectionScale{},
  fJetArea(0.),
  fCorrections()
{
}

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

void
mithep::Jet::SetBJetTagsDisc(Double_t d, UInt_t a)
{
  if (a < nBTagAlgos)
    fBJetTagsDisc[a] = d;
  else if (a < nAllBTagAlgos)
    fBJetTagsLegacyDisc[a - nBTagAlgos] = d;
}

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
