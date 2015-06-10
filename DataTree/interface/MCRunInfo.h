//--------------------------------------------------------------------------------------------------
// MCRunInfo
//
// This class holds LHE reweighting definitions. It is stored in the run tree.
//
// Authors: Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCRUNINFO_H
#define MITANA_DATATREE_MCRUNINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep {

  class MCRunInfo : public DataBase {
  public:
    typedef std::pair<TString, TString> IdValuePair;
    typedef std::vector<IdValuePair> IdValuePairVector;

    MCRunInfo();
    virtual ~MCRunInfo();
    
    UInt_t NWeightGroups() const { return fNWeightGroups; }
    char const* WeightGroupCombination(UInt_t iG) const { return iG < fNWeightGroups ? fWeightGroupCombination[iG].Data() : ""; }
    char const* WeightGroupType(UInt_t iG) const { return iG < fNWeightGroups ? fWeightGroupType[iG].Data() : ""; }
    UInt_t NWeights(UInt_t iG) const { return iG < fNWeightGroups ? fWeightData[iG].size() : 0; }
    char const* WeightId(UInt_t iG, UInt_t iW) const { return iG < fNWeightGroups ? fWeightData[iG].at(iW).first : ""; };
    char const* WeightData(UInt_t iG, UInt_t iW) const { return iG < fNWeightGroups ? fWeightData[iG].at(iW).second : ""; }
    char const* WeightData(UInt_t, char const*) const;

    void SetNWeightGroups(UInt_t);
    void SetWeightGroupCombination(UInt_t iG, char const* s) { fWeightGroupCombination[iG] = s; }
    void SetWeightGroupType(UInt_t iG, char const* s) { fWeightGroupType[iG] = s; }
    void AddWeightData(UInt_t iG, char const* id, char const* d) { fWeightData[iG].push_back(IdValuePair(id, d)); }
    void ClearWeightData();

  protected:
    UInt_t fNWeightGroups;
    UInt_t fWeightGroupsSize; //! to keep track of the array size
    TString* fWeightGroupCombination; //[fNWeightGroups]
    TString* fWeightGroupType; //[fNWeightGroups]
    IdValuePairVector* fWeightData; //[fNWeightGroups]

    ClassDef(MCRunInfo, 1) // MC Run info class
  };

}

inline
char const*
mithep::MCRunInfo::WeightData(UInt_t iG, char const* id) const
{
  if (iG >= fNWeightGroups)
    return "";

  for (IdValuePair& idValue : fWeightData[iG]) {
    if (idValue.first == id)
      return idValue.second;
  }

  return "";
}

#endif
