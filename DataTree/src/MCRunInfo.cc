#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitCommon/Utils/interface/Utils.h"

ClassImp(mithep::MCRunInfo)

mithep::MCRunInfo::MCRunInfo() :
  fHasLHEInfo(false),
  fBeamEnergy(0.),
  fPdfGroup(0),
  fPdfId(0),
  fWeightMode(0),
  fNProcesses(0),
  fProcessesSize(16),
  fProcessXSec(new Double_t[fProcessesSize]),
  fProcessXSecError(new Double_t[fProcessesSize]),
  fProcessXSecMax(new Double_t[fProcessesSize]),
  fProcessId(new Int_t[fProcessesSize]),
  fNHeaderBlocks(0),
  fHeaderBlocksSize(16),
  fHeaderBlockTag(new TString[fHeaderBlocksSize]),
  fHeaderBlockContent(new TString[fHeaderBlocksSize]),
  fNWeightGroups(0),
  fWeightGroupsSize(8),
  fWeightGroupCombination(new TString[fWeightGroupsSize]),
  fWeightGroupType(new TString[fWeightGroupsSize]),
  fNWeightDefinitions(0),
  fWeightDefinitionsSize(64),
  fWeightId(new TString[fWeightDefinitionsSize]),
  fWeightDefinition(new TString[fWeightDefinitionsSize]),
  fWeightGroup(new UChar_t[fWeightDefinitionsSize]),
  fWeightPositionInEvent(new UShort_t[fWeightDefinitionsSize]),
  fLHEComments()
{
}

mithep::MCRunInfo::~MCRunInfo()
{
  delete [] fProcessXSec;
  delete [] fProcessXSecError;
  delete [] fProcessXSecMax;
  delete [] fProcessId;
  delete [] fHeaderBlockTag;
  delete [] fHeaderBlockContent;
  delete [] fWeightGroupCombination;
  delete [] fWeightGroupType;
  delete [] fWeightId;
  delete [] fWeightDefinition;
  delete [] fWeightGroup;
  delete [] fWeightPositionInEvent;
}

void
mithep::MCRunInfo::SetNProcesses(UInt_t n)
{
  if (n > fProcessesSize) {
    fProcessesSize = n * 2;

    mithep::Utils::Reallocate(fProcessXSec, fNProcesses, fProcessesSize);
    mithep::Utils::Reallocate(fProcessXSecError, fNProcesses, fProcessesSize);
    mithep::Utils::Reallocate(fProcessId, fNProcesses, fProcessesSize);
    mithep::Utils::Reallocate(fProcessXSecMax, fNProcesses, fProcessesSize);
    mithep::Utils::Reallocate(fProcessXSecError, fNProcesses, fProcessesSize);
  }

  fNProcesses = n;
}

void
mithep::MCRunInfo::SetNHeaderBlocks(UInt_t n)
{
  if (n > fHeaderBlocksSize) {
    fHeaderBlocksSize = n * 2;

    mithep::Utils::Reallocate(fHeaderBlockTag, fNHeaderBlocks, fHeaderBlocksSize);
    mithep::Utils::Reallocate(fHeaderBlockContent, fNHeaderBlocks, fHeaderBlocksSize);
  }

  fNHeaderBlocks = n;
}

void
mithep::MCRunInfo::SetNWeightGroups(UInt_t n)
{
  if (n > fWeightGroupsSize) {
    fWeightGroupsSize = n * 2;

    mithep::Utils::Reallocate(fWeightGroupCombination, fNWeightGroups, fWeightGroupsSize);
    mithep::Utils::Reallocate(fWeightGroupType, fNWeightGroups, fWeightGroupsSize);
  }

  fNWeightGroups = n;
}

void
mithep::MCRunInfo::SetNWeightDefinitions(UInt_t n)
{
  if (n > fWeightDefinitionsSize) {
    fWeightDefinitionsSize = n * 2;

    mithep::Utils::Reallocate(fWeightId, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightDefinition, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightGroup, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightPositionInEvent, fNWeightDefinitions, fWeightDefinitionsSize);
  }

  fNWeightDefinitions = n;
}

void
mithep::MCRunInfo::AddWeightDefinition(char const* id, char const* def, UChar_t iG, UShort_t idx)
{
  if (fNWeightDefinitions >= fWeightDefinitionsSize) {
    fWeightDefinitionsSize *= 2;

    mithep::Utils::Reallocate(fWeightId, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightDefinition, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightGroup, fNWeightDefinitions, fWeightDefinitionsSize);
    mithep::Utils::Reallocate(fWeightPositionInEvent, fNWeightDefinitions, fWeightDefinitionsSize);
  }

  fWeightId[fNWeightDefinitions] = id;
  fWeightDefinition[fNWeightDefinitions] = def;
  fWeightGroup[fNWeightDefinitions] = iG;
  fWeightPositionInEvent[fNWeightDefinitions] = idx;
  ++fNWeightDefinitions;
}

void
mithep::MCRunInfo::Streamer(TBuffer& buffer)
{
  if (buffer.IsReading()) {
    buffer.ReadClassBuffer(mithep::MCRunInfo::Class(), this);

    fProcessesSize = fNProcesses;
    fHeaderBlocksSize = fNHeaderBlocks;
    fWeightGroupsSize = fNWeightGroups;
  }
  else
    buffer.WriteClassBuffer(mithep::MCRunInfo::Class(), this);
}
