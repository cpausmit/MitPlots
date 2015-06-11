//--------------------------------------------------------------------------------------------------
// MCRunInfo
//
// This class holds run-wide MC information. It is stored in the run tree.
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

    EObjType ObjType() const override { return kMCRunInfo; }
    
    Bool_t HasLHEInfo() const { return fHasLHEInfo; }
    Double_t BeamEnergy() const { return fBeamEnergy; }
    Int_t PdfGroup() const { return fPdfGroup; }
    Int_t PdfId() const { return fPdfId; }
    Int_t WeightMode() const { return fWeightMode; }
    UInt_t NProcesses() const { return fNProcesses; }
    Double_t ProcessXSec(UInt_t iP) const { return iP < fNProcesses ? fProcessXSec[iP] : -1.; }
    Double_t ProcessXSecError(UInt_t iP) const { return iP < fNProcesses ? fProcessXSecError[iP] : 0.; }
    Double_t ProcessXSecMax(UInt_t iP) const { return iP < fNProcesses ? fProcessXSecMax[iP] : 0.; }
    Int_t ProcessId(UInt_t iP) const { return iP < fNProcesses ? fProcessId[iP] : -1; }
    UInt_t NHeaderBlocks() const { return fNHeaderBlocks; }
    char const* HeaderBlockTag(UInt_t iB) { return iB < fNHeaderBlocks ? fHeaderBlockTag[iB].Data() : ""; }
    char const* HeaderBlockContent(UInt_t iB) { return iB < fNHeaderBlocks ? fHeaderBlockContent[iB].Data() : ""; }
    UInt_t NWeightGroups() const { return fNWeightGroups; }
    char const* WeightGroupCombination(UInt_t iG) const { return iG < fNWeightGroups ? fWeightGroupCombination[iG].Data() : ""; }
    char const* WeightGroupType(UInt_t iG) const { return iG < fNWeightGroups ? fWeightGroupType[iG].Data() : ""; }
    UInt_t NWeights(UInt_t iG) const { return iG < fNWeightGroups ? fWeightData[iG].size() : 0; }
    char const* WeightId(UInt_t iG, UInt_t iW) const { return iG < fNWeightGroups ? fWeightData[iG].at(iW).first : ""; };
    char const* WeightData(UInt_t iG, UInt_t iW) const { return iG < fNWeightGroups ? fWeightData[iG].at(iW).second : ""; }
    char const* WeightData(UInt_t, char const*) const;
    UShort_t WeightPositionInEvent(UInt_t iG, UInt_t iW) const { return iG < fNWeightGroups ? fWeightPositionInEvent[iG].at(iW) : -1; }
    UInt_t NLHECommentLines() const { return fLHEComments.size(); }
    char const* LHEComment(UInt_t iL) const { return fLHEComments.at(iL).Data(); }

    // Using HEPRUP speak
    Double_t EBMUP() const { return BeamEnergy(); }
    Int_t PDFGUP() const { return PdfGroup(); }
    Int_t PDFSUP() const { return PdfId(); }
    Int_t IdWTUP() const { return WeightMode(); }
    UInt_t NPRUP() const { return NProcesses(); }
    Double_t XSECUP(UInt_t iP) const { return ProcessXSec(iP); }
    Double_t XERRUP(UInt_t iP) const { return ProcessXSecError(iP); }
    Double_t XMAXUP(UInt_t iP) const { return ProcessXSecMax(iP); }
    Int_t LPRUP(UInt_t iP) const { return ProcessId(iP); }

    void SetHasLHEInfo(Bool_t f) { fHasLHEInfo = f; }
    void SetBeamEnergy(Double_t e) { fBeamEnergy = e; }
    void SetPdfGroup(Int_t g) { fPdfGroup = g; }
    void SetPdfId(Int_t i) { fPdfId = i; }
    void SetWeightMode(Int_t m) { fWeightMode = m; }
    void SetNProcesses(UInt_t);
    void SetProcessXSec(UInt_t iP, Double_t v) { fProcessXSec[iP] = v; }
    void SetProcessXSecError(UInt_t iP, Double_t v) { fProcessXSecError[iP] = v; }
    void SetProcessXSecMax(UInt_t iP, Double_t v) { fProcessXSecMax[iP] = v; }
    void SetProcessId(UInt_t iP, Int_t v) { fProcessId[iP] = v; }
    void SetNHeaderBlocks(UInt_t);
    void SetHeaderBlockTag(UInt_t iB, char const* s) { fHeaderBlockTag[iB] = s; }
    void SetHeaderBlockContent(UInt_t iB, char const* s) { fHeaderBlockContent[iB] = s; }
    void ClearWeightData();
    void SetNWeightGroups(UInt_t);
    void SetWeightGroupCombination(UInt_t iG, char const* s) { fWeightGroupCombination[iG] = s; }
    void SetWeightGroupType(UInt_t iG, char const* s) { fWeightGroupType[iG] = s; }
    void AddWeightData(UInt_t iG, char const* id, char const* d, UShort_t idx)
    { fWeightData[iG].push_back(IdValuePair(id, d)); fWeightPositionInEvent[iG].push_back(idx); }
    void ClearLHEComments() { fLHEComments.clear(); }
    void AddLHECommentLine(TString const& c) { fLHEComments.push_back(c); }

  protected:
    Bool_t fHasLHEInfo; // Everything below comes from LHE
    Double_t fBeamEnergy;
    Int_t fPdfGroup;
    Int_t fPdfId;
    Int_t fWeightMode;
    UInt_t fNProcesses;
    UInt_t fProcessesSize; //! to keep track of the array size
    Double_t* fProcessXSec; //[fNProcesses]
    Double_t* fProcessXSecError; //[fNProcesses]
    Double_t* fProcessXSecMax; //[fNProcesses]
    Int_t* fProcessId; //[fNProcesses]
    UInt_t fNHeaderBlocks;
    UInt_t fHeaderBlocksSize; //! to keep track of the array size
    TString* fHeaderBlockTag; //[fNHeaderBlocks]
    TString* fHeaderBlockContent; //[fNHeaderBlocks]
    UInt_t fNWeightGroups;
    UInt_t fWeightGroupsSize; //! to keep track of the array size
    TString* fWeightGroupCombination; //[fNWeightGroups]
    TString* fWeightGroupType; //[fNWeightGroups]
    IdValuePairVector* fWeightData; //[fNWeightGroups]
    std::vector<UShort_t>* fWeightPositionInEvent; //[fNWeightGroups] position of the reweighting factor in the events
    std::vector<TString> fLHEComments;

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
