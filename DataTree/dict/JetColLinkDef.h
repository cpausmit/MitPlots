#ifndef MITANA_DATATREE_JETCOLLINKDEF_H
#define MITANA_DATATREE_JETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/JetCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ JetCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma read \
    sourceClass="mithep::Jet" \
    version="[-6]" \
    source="Double32_t fJetProbabilityBJetTagsDisc; \
            Double32_t fJetBProbabilityBJetTagsDisc; \
            Double32_t fSimpleSecondaryVertexHighEffBJetTagsDisc; \
            Double32_t fSimpleSecondaryVertexHighPurBJetTagsDisc; \
            Double32_t fCombinedSecondaryVertexBJetTagsDisc; \
            Double32_t fCombinedSecondaryVertexMVABJetTagsDisc; \
            Double32_t fTrackCountingHighEffBJetTagsDisc; \
            Double32_t fTrackCountingHighPurBJetTagsDisc;" \
    targetClass="mithep::Jet" \
    target="fBJetTagsDisc" \
    code="{ fBJetTagsDisc[mithep::Jet::kJetProbability] = onfile.fJetProbabilityBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kJetBProbability] = onfile.fJetBProbabilityBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kSimpleSecondaryVertexHighEff] = onfile.fSimpleSecondaryVertexHighEffBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kSimpleSecondaryVertexHighPur] = onfile.fSimpleSecondaryVertexHighPurBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kCombinedSecondaryVertex] = onfile.fCombinedSecondaryVertexBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kCombinedMVA] = onfile.fCombinedSecondaryVertexMVABJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kTrackCountingHighEff] = onfile.fTrackCountingHighEffBJetTagsDisc; \
      fBJetTagsDisc[mithep::Jet::kTrackCountingHighPur] = onfile.fTrackCountingHighPurBJetTagsDisc; }" \

#pragma read \
    sourceClass="mithep::Jet" \
    version="[-6]" \
    source="Double32_t fSimpleSecondaryVertexBJetTagsDisc; \
            Double32_t fSoftMuonBJetTagsDisc; \
            Double32_t fSoftMuonByIP3dBJetTagsDisc; \
            Double32_t fSoftMuonByPtBJetTagsDisc; \
            Double32_t fSoftElectronByIP3dBJetTagsDisc; \
            Double32_t fSoftElectronByPtBJetTagsDisc; \
            Double32_t fGhostTrackBJetTagsDisc;" \
    targetClass="mithep::Jet" \
    target="fBJetTagsLegacyDisc" \
    code="{ unsigned const aOffset = mithep::Jet::nBTagAlgos; \
      fBJetTagsLegacyDisc[mithep::Jet::kSimpleSecondaryVertex - aOffset] = onfile.fSimpleSecondaryVertexBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kSoftMuon - aOffset] = onfile.fSoftMuonBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kSoftMuonByIP3d - aOffset] = onfile.fSoftMuonByIP3dBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kSoftMuonByPt - aOffset] = onfile.fSoftMuonByPtBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kSoftElectronByIP3d - aOffset] = onfile.fSoftElectronByIP3dBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kSoftElectronByPt - aOffset] = onfile.fSoftElectronByPtBJetTagsDisc; \
      fBJetTagsLegacyDisc[mithep::Jet::kGhostTrack - aOffset] = onfile.fGhostTrackBJetTagsDisc; }" \

#pragma read \
    sourceClass="mithep::Jet" \
    version="[-6]" \
    source="Double32_t fL1OffsetCorrectionScale; \
            Double32_t fL2RelativeCorrectionScale; \
            Double32_t fL3AbsoluteCorrectionScale; \
            Double32_t fL4EMFCorrectionScale; \
            Double32_t fL5FlavorCorrectionScale; \
            Double32_t fL6LSBCorrectionScale; \
            Double32_t fL7PartonCorrectionScale; \
            Double32_t fCustomCorrectionScale;" \
    targetClass="mithep::Jet" \
    target="fCorrectionScale" \
    code="{ fCorrectionScale[mithep::Jet::L1] = onfile.fL1OffsetCorrectionScale; \
      fCorrectionScale[mithep::Jet::L2] = onfile.fL2RelativeCorrectionScale; \
      fCorrectionScale[mithep::Jet::L3] = onfile.fL3AbsoluteCorrectionScale; \
      fCorrectionScale[mithep::Jet::L4] = onfile.fL4EMFCorrectionScale; \
      fCorrectionScale[mithep::Jet::L5] = onfile.fL5FlavorCorrectionScale; \
      fCorrectionScale[mithep::Jet::L6] = onfile.fL6LSBCorrectionScale; \
      fCorrectionScale[mithep::Jet::L7] = onfile.fL7PartonCorrectionScale; \
      fCorrectionScale[mithep::Jet::Custom] = onfile.fCustomCorrectionScale; }" \

#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ class mithep::Ref<mithep::Jet>+;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::JetOArr;
#pragma link C++ enum mithep::Jet::BTagAlgo;
#pragma link C++ enum mithep::Jet::BTagLegacyAlgo;
#endif

