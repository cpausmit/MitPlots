#ifndef MITANA_DATATREE_MCREWEIGHTFACTOR_H
#define MITANA_DATATREE_MCREWEIGHTFACTOR_H

#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep {

  class MCReweightFactor : public DataBase {
  public:
    MCReweightFactor();
    ~MCReweightFactor() {}

    char const* Id() const { return fId.Data(); }
    char const* WeightGroupCombination() const { return fWeightGroupCombination.Data(); }
    char const* WeightGroupType() const { return fWeightGroupType.Data(); }
    char const* WeightDefinition() const { return fWeightDefinition; }
    Double_t ScaleFactor() const { return fScaleFactor; }

    void SetId(char const* id) { fId = id; }
    void SetWeightGroupCombination(char const* comb) { fWeightGroupCombination = comb; }
    void SetWeightGroupType(char const* type) { fWeightGroupType = type; }
    void SetWeightDefinition(char const* def) { fWeightDefinition = def; }
    void SetScaleFactor(Double_t s) { fScaleFactor = s; }

  private:
    TString fId;
    TString fWeightGroupCombination;
    TString fWeightGroupType;
    TString fWeightDefinition;
    Double_t fScaleFactor;

    ClassDef(MCReweightFactor, 1)
  };

}

#endif
