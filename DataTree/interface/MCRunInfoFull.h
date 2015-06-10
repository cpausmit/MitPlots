//--------------------------------------------------------------------------------------------------
// MCRunInfoFull
//
// This class holds run-wide MC information. It is stored in the run tree.
//
// Authors: Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCRUNINFOFULL_H
#define MITANA_DATATREE_MCRUNINFOFULL_H
 
#include "MitAna/DataTree/interface/MCRunInfo.h"

namespace mithep {

  class MCRunInfoFull : public MCRunInfo {
  public:
    MCRunInfoFull();
    ~MCRunInfoFull();

    Double_t InternalXSec() const { return fInternalXSec; }
    Double_t InternalXSecErr() const { return fInternalXSecErr; }
    Double_t ExternalXSecLO() const { return fExternalXSecLO; }
    Double_t ExternalXSecLOErr() const { return fExternalXSecLOErr; }
    Double_t ExternalXSecNLO() const { return fExternalXSecNLO; }
    Double_t ExternalXSecNLOErr() const { return fExternalXSecNLOErr; }
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
    UInt_t NCommentLines() const { return fComments.size(); }
    char const* Comment(UInt_t iL) const { return fComments.at(iL).Data(); }

    // Using HEPRUP speak
    Double_t EBMUP() const { return fBeamEnergy; }
    Int_t PDFGUP() const { return fPdfGroup; }
    Int_t PDFSUP() const { return fPdfId; }
    Int_t IdWTUP() const { return fWeightMode; }
    UInt_t NPRUP() const { return fNProcesses; }
    Double_t XSECUP(UInt_t iP) const { return ProcessXSec(iP); }
    Double_t XERRUP(UInt_t iP) const { return ProcessXSecError(iP); }
    Double_t XMAXUP(UInt_t iP) const { return ProcessXSecMax(iP); }
    Int_t LPRUP(UInt_t iP) const { return ProcessId(iP); }

    void SetInternalXSec(Double_t v) { fInternalXSec = v; }
    void SetInternalXSecErr(Double_t v) { fInternalXSecErr = v; }
    void SetExternalXSecLO(Double_t v) { fExternalXSecLO = v; }
    void SetExternalXSecLOErr(Double_t v) { fExternalXSecLOErr = v; }
    void SetExternalXSecNLO(Double_t v) { fExternalXSecNLO = v; }
    void SetExternalXSecNLOErr(Double_t v) { fExternalXSecNLOErr = v; }
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
    void ClearComments() { fComments.clear(); }
    void AddCommentLine(TString const& c) { fComments.push_back(c); }

  protected:
    Double_t fInternalXSec; // Internal = PYTHIA etc.
    Double_t fInternalXSecErr;
    Double_t fExternalXSecLO; // External = If the events come from LHE files etc.
    Double_t fExternalXSecLOErr;
    Double_t fExternalXSecNLO;
    Double_t fExternalXSecNLOErr;
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
    std::vector<TString> fComments;

    ClassDef(MCRunInfoFull, 1) // MC Run info class
  };

}
#endif
