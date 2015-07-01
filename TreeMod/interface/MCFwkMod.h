//--------------------------------------------------------------------------------------------------
// MCFwkMod
//
// This TAM module reads the MC event information and supplements it with MC run information.
//
// Authors: Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_MCFWKMOD_H
#define MITANA_TREEMOD_MCFWKMOD_H

#include <string>
#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/MCReweightFactorCol.h"

namespace mithep 
{
  class MCFwkMod : public BaseMod {
  public:
    MCFwkMod(const char *name="MCFwkMod", const char *title="MC framework module");
    ~MCFwkMod();

    char const* ReweightFactorPub() const { return fReweightFactors->GetName(); }
    char const* EventInfoName() const { return fEventInfoName; }

    void SetReweightFactorName(char const* n) { fReweightFactors->SetName(n); }
    void SetEventInfoName(char const* n) { fEventInfoName = n; }

  protected:
    void BeginRun() override;
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fEventInfoName; //Input MCEventInfo branch name
    mithep::MCEventInfo const* fEventInfo; //!event info branch
    mithep::MCReweightFactorArr* fReweightFactors;

    std::vector<TString> fWeightGroupCombination; //! reverse mapping position -> comb
    std::vector<TString> fWeightGroupType; //! reverse mapping position -> type
    std::vector<TString> fWeightId; //! reverse mapping position -> id
    std::vector<TString> fWeightDef; //! reverse mapping position -> def

    ClassDef(MCFwkMod, 1) // MC framework TAM module
  };
}
#endif
