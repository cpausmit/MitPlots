#ifndef MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H
#define MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ PileupEnergyDensityCol
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

// below onfile.LowEta is filled to kHighEta - this is not a typo!
#pragma read \
    sourceClass="mithep::PileupEnergyDensity" \
    version="[-4]" \
    source="Double32_t fRho; Double32_t fRhoHighEta; Double32_t fRhoRandom;\
            Double32_t fRhoRandomLowEta; Double32_t fRhoFixedGridAll;\
            Double32_t fRhoFixedGridFastjetAll;" \
    targetClass="mithep::PileupEnergyDensity" \
    target="fRho" \
    code="{ fRho[mithep::PileupEnergyDensity::kHighEta] = onfile.fRho;\
      fRho[mithep::PileupEnergyDensity::kLowEta] = onfile.fRhoHighEta;\
      fRho[mithep::PileupEnergyDensity::kRandom] = onfile.fRhoRandom;\
      fRho[mithep::PileupEnergyDensity::kRandomLowEta] = onfile.fRhoRandomLowEta;\
      fRho[mithep::PileupEnergyDensity::kFixedGridAll] = onfile.fRhoFixedGridAll;\
      fRho[mithep::PileupEnergyDensity::kFixedGridFastjetAll] = onfile.fRhoFixedGridFastjetAll; }" \

#pragma read \
    sourceClass="mithep::PileupEnergyDensity" \
    version="[-4]" \
    source="Double32_t fRhoKt6CaloJets;\
            Double32_t fRhoKt6CaloJetsCentral; Double32_t fRhoKt6PFJets;\
            Double32_t fRhoKt6PFJetsCentralChargedPileUp; Double32_t fRhoKt6PFJetsCentralNeutral;\
            Double32_t fRhoKt6PFJetsCentralNeutralTight;" \
    targetClass="mithep::PileupEnergyDensity" \
    target="fRhoLegacy" \
    code="{ unsigned const aOffset = mithep::PileupEnergyDensity::nAlgos;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6CaloJets - aOffset] = onfile.fRhoKt6CaloJets;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6CaloJetsCentral - aOffset] = onfile.fRhoKt6CaloJetsCentral;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6PFJets - aOffset] = onfile.fRhoKt6PFJets;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6PFJetsCentralChargedPileUp - aOffset] = onfile.fRhoKt6PFJetsCentralChargedPileUp;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6PFJetsCentralNeutral - aOffset] = onfile.fRhoKt6PFJetsCentralNeutral;\
      fRhoLegacy[mithep::PileupEnergyDensity::kKt6PFJetsCentralNeutralTight - aOffset] = onfile.fRhoKt6PFJetsCentralNeutralTight; }" \

#pragma link C++ class mithep::PileupEnergyDensity+;
#pragma link C++ enum mithep::PileupEnergyDensity::Algo;
#pragma link C++ class mithep::Collection<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Array<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::ObjArray<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Ref<mithep::PileupEnergyDensity>+;
#pragma link C++ typedef mithep::PileupEnergyDensityCol;
#pragma link C++ typedef mithep::PileupEnergyDensityArr;
#endif
