#include "MitAna/TreeMod/interface/MCFwkMod.h"

#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitAna/DataTree/interface/Names.h"

ClassImp(mithep::MCFwkMod)

mithep::MCFwkMod::MCFwkMod(char const* name, char const* title) :
  BaseMod(name, title),
  fEventInfoName(mithep::Names::gkMCEvtInfoBrn),
  fReweightFactors(new mithep::MCReweightFactorArr)
{
  fReweightFactors->SetName("MCReweightFactors");
}

mithep::MCFwkMod::~MCFwkMod()
{
  delete fReweightFactors;
}

void
mithep::MCFwkMod::BeginRun()
{
  mithep::MCRunInfo const* runInfo = GetMCRunInfo();

  if (!runInfo)
    return;

  fWeightGroupCombination.resize(runInfo->NWeights());
  fWeightGroupType.resize(runInfo->NWeights());
  fWeightId.resize(runInfo->NWeights());
  fWeightDef.resize(runInfo->NWeights());

  for (unsigned iW = 0; iW != runInfo->NWeights(); ++iW) {
    unsigned iG = runInfo->WeightGroup(iW);
    unsigned pos = runInfo->WeightPositionInEvent(iW);

    fWeightGroupCombination[pos] = runInfo->WeightGroupCombination(iG);
    fWeightGroupType[pos] = runInfo->WeightGroupType(iG);
    fWeightId[pos] = runInfo->WeightId(iW);
    fWeightDef[pos] = runInfo->WeightDefinition(iW);
  }
}

void
mithep::MCFwkMod::Process()
{
  if (!GetEventHeader()->IsMC())
    return;

  fReweightFactors->Reset();

  auto* eventInfo = GetObject<mithep::MCEventInfo>(fEventInfoName);

  for (unsigned iW = 0; iW != eventInfo->NReweightScaleFactors(); ++iW) {
    auto* outFactor = fReweightFactors->AddNew();

    outFactor->SetId(fWeightId[iW].Data());
    outFactor->SetWeightGroupCombination(fWeightGroupCombination[iW].Data());
    outFactor->SetWeightGroupType(fWeightGroupType[iW].Data());
    outFactor->SetWeightDefinition(fWeightDef[iW].Data());
    outFactor->SetScaleFactor(eventInfo->ReweightScaleFactor(iW));
  }
}

void
mithep::MCFwkMod::SlaveBegin()
{
  if (!PublishObj(fReweightFactors)) {
    SendError(kAbortAnalysis, "SlaveBegin", 
              "Could not publish MC reweight objects array with name %s.", fReweightFactors->GetName());
    return;
  }
}

void
mithep::MCFwkMod::SlaveTerminate()
{
  RetractObj(fReweightFactors->GetName());
}
