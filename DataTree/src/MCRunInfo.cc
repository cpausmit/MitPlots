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
  fWeightData(new IdValuePairVector[fWeightGroupsSize]),
  fWeightPositionInEvent(new std::vector<UShort_t>[fWeightGroupsSize]),
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
  delete [] fWeightData;
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
    mithep::Utils::Reallocate(fWeightData, fNWeightGroups, fWeightGroupsSize);
    mithep::Utils::Reallocate(fWeightPositionInEvent, fNWeightGroups, fWeightGroupsSize);
  }

  fNWeightGroups = n;
}

void
mithep::MCRunInfo::ClearWeightData()
{
  fNWeightGroups = 0;
  for (unsigned iD = 0; iD != fWeightGroupsSize; ++iD) {
    fWeightData[iD].clear();
    fWeightPositionInEvent[iD].clear();
  }
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
