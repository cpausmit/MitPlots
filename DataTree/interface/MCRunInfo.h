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
#include "MitAna/DataCont/interface/Types.h"

namespace mithep {

  class MCRunInfo : public DataBase {
  public:
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
    UInt_t NWeights(UInt_t = -1) const;
    char const* WeightId(UInt_t iW) const { return iW < fNWeightDefinitions ? fWeightId[iW].Data() : ""; };
    char const* WeightDefinition(UInt_t iW) const { return iW < fNWeightDefinitions ? fWeightDefinition[iW].Data() : ""; }
    char const* WeightDefinition(char const*) const;
    UShort_t WeightGroup(UInt_t iW) const { return iW < fNWeightDefinitions ? fWeightGroup[iW] : -1; }
    UShort_t WeightPositionInEvent(UInt_t iW) const { return iW < fNWeightDefinitions ? fWeightPositionInEvent[iW] : -1; }
    UInt_t NLHECommentLines() const { return fLHEComments.GetEntries(); }
    char const* LHEComment(UInt_t iL) const { return fLHEComments.At(iL)->GetName(); }

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
    void SetNWeightGroups(UInt_t);
    void SetWeightGroupCombination(UInt_t iG, char const* s) { fWeightGroupCombination[iG] = s; }
    void SetWeightGroupType(UInt_t iG, char const* s) { fWeightGroupType[iG] = s; }
    void SetNWeightDefinitions(UInt_t);
    void AddWeightDefinition(char const* id, char const* def, UChar_t iG, UShort_t idx);
    void ClearLHEComments() { fLHEComments.Reset(); }
    void AddLHECommentLine(char const* c) { new (fLHEComments.Allocate()) TObjString(c); }

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
    UInt_t fNWeightDefinitions;
    UInt_t fWeightDefinitionsSize; //! to keep track of the array size
    TString* fWeightId; //[fNWeightDefinitions] ID of the weight
    TString* fWeightDefinition; //[fNWeightDefinitions] Definition of the weight
    UChar_t* fWeightGroup; //[fNWeightDefinitions] Group index the weight belongs to
    UShort_t* fWeightPositionInEvent; //[fNWeightDefinitions] position of the reweighting factor in the events
    FArrObjString fLHEComments; //|| LHE header comment lines

    ClassDef(MCRunInfo, 1) // MC Run info class
  };

}

inline
UInt_t
mithep::MCRunInfo::NWeights(UInt_t iG/* = -1*/) const
{
  if (iG > fNWeightGroups)
    return fNWeightDefinitions;
  else {
    UInt_t result = 0;
    for (UInt_t iD = 0; iD != fNWeightDefinitions; ++iD) {
      if (fWeightGroup[iD == iG])
        ++result;
    }
    return result;
  }
}

inline
char const*
mithep::MCRunInfo::WeightDefinition(char const* id) const
{
  for (UInt_t iD = 0; iD != fNWeightDefinitions; ++iD) {
    if (fWeightId[iD] == id)
      return fWeightDefinition[iD].Data();
  }

  return "";
}

#endif
