#include "MitAna/DataTree/interface/Jet.h"

#include <cstring>

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

/*static*/
char const*
mithep::Jet::BTagAlgoName(UInt_t idx)
{
  switch(idx) {
  case kJetProbability:
    return "JetProbability";
  case kJetBProbability:
    return "JetBProbability";
  case kSimpleSecondaryVertexHighEff:
    return "SimpleSecondaryVertexHighEff";
  case kSimpleSecondaryVertexHighPur:
    return "SimpleSecondaryVertexHighPur";
  case kCombinedSecondaryVertex:
    return "CombinedSecondaryVertex";
  case kCombinedSecondaryVertexV2:
    return "CombinedSecondaryVertexV2";
  case kCombinedSecondaryVertexSoftLepton:
    return "CombinedSecondaryVertexSoftLepton";
  case kCombinedInclusiveSecondaryVertexV2:
    return "CombinedInclusiveSecondaryVertexV2";
  case kCombinedMVA:
    return "CombinedMVA";
  case kTrackCountingHighEff:
    return "TrackCountingHighEff";
  case kTrackCountingHighPur:
    return "TrackCountingHighPur";
  default:
    return "";
  }
}

/*static*/
UInt_t
mithep::Jet::BTagAlgoIndex(char const* name)
{
  for (unsigned idx = 0; idx != nBTagAlgos; ++idx) {
    if (std::strcmp(name, BTagAlgoName(idx)) == 0)
      return idx;
  }
  return nBTagAlgos;
}
