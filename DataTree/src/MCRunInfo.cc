#include "MitAna/DataTree/interface/MCRunInfo.h"

ClassImp(mithep::MCRunInfo)

mithep::MCRunInfo::MCRunInfo() :
  fNWeightGroups(0),
  fWeightGroupsSize(64),
  fWeightGroupCombination(new TString[fWeightGroupsSize]),
  fWeightGroupType(new TString[fWeightGroupsSize]),
  fWeightData(new IdValuePairVector[fWeightGroupsSize])
{
}

mithep::MCRunInfo::~MCRunInfo()
{
  delete [] fWeightGroupCombination;
  delete [] fWeightGroupType;
  delete [] fWeightData;
}

void
mithep::MCRunInfo::SetNWeightGroups(UInt_t n)
{
  if (n > fWeightGroupsSize) {
    fWeightGroupsSize = n * 2;
    
    auto tmp1 = new TString[fWeightGroupsSize];
    std::copy(fWeightGroupCombination, fWeightGroupCombination + fNWeightGroups, tmp1);
    delete [] fWeightGroupCombination;
    fWeightGroupCombination = tmp1;

    auto tmp2 = new TString[fWeightGroupsSize];
    std::copy(fWeightGroupType, fWeightGroupType + fNWeightGroups, tmp2);
    delete [] fWeightGroupType;
    fWeightGroupType = tmp2;

    auto tmp3 = new IdValuePairVector[fWeightGroupsSize];
    std::copy(fWeightData, fWeightData + fNWeightGroups, tmp3);
    delete [] fWeightData;
    fWeightData = tmp3;
  }

  fNWeightGroups = n;
}

void
mithep::MCRunInfo::ClearWeightData()
{
  fNWeightGroups = 0;
  for (unsigned iD = 0; iD != fWeightGroupsSize; ++iD)
    fWeightData[iD].clear();
}

void
mithep::MCRunInfo::Streamer(TBuffer& buffer)
{
  if (buffer.IsReading()) {
    buffer.ReadClassBuffer(mithep::MCRunInfo::Class(), this);

    fWeightGroupsSize = fNWeightGroups;
  }
  else
    buffer.WriteClassBuffer(mithep::MCRunInfo::Class(), this);
}
