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

#pragma read \
    sourceClass="mithep::PileupEnergyDensity" \
    version="[-4]" \
    source="Double32_t fRho; Double32_t fRhoHighEta; Double32_t fRhoRandom;\
            Double32_t fRhoRandomLowEta; Double32_t fRhoFixedGridAll;\
            Double32_t fRhoFixedGridFastjetAll; Double32_t fRhoKt6CaloJets;\
            Double32_t fRhoKt6CaloJetsCentral; Double32_t fRhoKt6PFJets;\
            Double32_t fRhoKt6PFJetsCentralChargedPileUp; Double32_t fRhoKt6PFJetsCentralNeutral;\
            Double32_t fRhoKt6PFJetsCentralNeutralTight;" \
    targetClass="mithep::PileupEnergyDensity" \
    target="fRho" \
    code="{ fRho[kHighEta] = fRho; fRho[kLowEta] = fRhoHighEta; fRho[kRandom] = fRhoRandom;\
            fRho[kRandomLowEta] = fRhoRandomLowEta; fRho[kFixedGridAll] = fRhoFixedGridAll;\
            fRho[kFixedGridFastjetAll] = fRhoFixedGridFastjetAll; fRho[kKt6CaloJets] = fRhoKt6CaloJets;\
            fRho[kKt6CaloJetsCentral] = fRhoKt6CaloJetsCentral; fRho[kKt6PFJets] = fRhoKt6PFJets;\
            fRho[kKt6PFJetsCentralChargedPileUp] = fRhoKt6PFJetsCentralChargedPileUp;\
            fRho[kKt6PFJetsCentralNeutral] = fRhoKt6PFJetsCentralNeutral;\
            fRho[kKt6PFJetsCentralNeutralTight] = fRhoKt6PFJetsCentralNeutralTight; }" \

#pragma link C++ class mithep::PileupEnergyDensity+;
#pragma link C++ class mithep::Collection<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Array<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::ObjArray<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Ref<mithep::PileupEnergyDensity>+;
#pragma link C++ typedef mithep::PileupEnergyDensityCol;
#pragma link C++ typedef mithep::PileupEnergyDensityArr;
#endif
