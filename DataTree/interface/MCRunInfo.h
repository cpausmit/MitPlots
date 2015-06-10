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
  class LHERunInfo;

  class MCRunInfo : public DataBase
  {
  public:
    struct ProcessData {
      Double_t xsec;
      Double_t xsecError;
      Double_t xsecMax;
      Short_t processID;
    };

    struct WeightGroupData {
      TString combine;
      TString type;
      std::map<TString, TString> weightInfo;
    };

    MCRunInfo();
    ~MCRunInfo();

    Double_t InternalXSec() const { return fInternalXSec; }
    Double_t InternalXSecErr() const { return fInternalXSecErr; }
    Double_t ExternalLOXSec() const { return fExternalLOXSec; }
    Double_t ExternalLOXSecErr() const { return fExternalLOXSecErr; }
    Double_t ExternalNLOXSec() const { return fExternalNLOXsec; }
    Double_t ExternalNLOXSecErr() const { return fExternalNLOXsecErr; }
    Bool_t HasLHEInfo() const { return fHasLHEInfo; }
    Double_t BeamEnergy() const { return fBeamEnergy; }
    Int_t PdfGroup() const { return fPdfGroup; }
    Int_t PdfID() const { return fPdfID; }
    Int_t WeightMode() const { return fWeightMode; }
    UInt_t NProcesses() const { return fProcesses.size(); }
    ProcessData const& Process(UInt_t iP) const { return fProcesses.at(iP); }
    ProcessData& Process(UInt_t iP) { return fProcesses.at(iP); }
    UInt_t NWeightGroups() const { return fWeightGroups.size(); }
    WeightGroupData const& WeightGroup(UInt_t iW) const { return fWeightGroups.at(iW); }
    WeightGroupData& WeightGroup(UInt_t iW) { return fWeightGroups.at(iW); }
    std::vector<TString> HeaderList() const;
    std::vector<TString> const& HeaderBlock(char const*) const;
    std::vector<TString>& HeaderBlock(char const* tag) { return fHeaders[tag]; };
    UInt_t NCommentLines() const { return fComments.size(); }
    char const* Comment(UInt_t iL) const { return fComments.at(iL).Data(); }

    // Using HEPRUP speak
    Double_t EBMUP() const { return fBeamEnergy; }
    Int_t PDFGUP() const { return fPdfGroup; }
    Int_t PDFSUP() const { return fPdfID; }
    Int_t IDWTUP() const { return fWeightMode; }
    UInt_t NPRUP() const { return fProcesses.size(); }
    Double_t XSECUP(UInt_t iP) const { return Process(iP).xsec; }
    Double_t XERRUP(UInt_t iP) const { return Process(iP).xsecError; }
    Double_t XMAXUP(UInt_t iP) const { return Process(iP).xsecMax; }
    Short_t LPRUP(UInt_t iP) const { return Process(iP).processID; }

    void SetInternalXSec(Double_t v) { fInternalXSec = v; }
    void SetInternalXSecErr(Double_t v) { fInternalXSecErr = v; }
    void SetExternalLOXSec(Double_t v) { fExternalLOXSec = v; }
    void SetExternalLOXSecErr(Double_t v) { fExternalLOXSecErr = v; }
    void SetExternalNLOXSec(Double_t v) { fExternalNLOXsec = v; }
    void SetExternalNLOXSecErr(Double_t v) { fExternalNLOXsecErr = v; }
    void SetHasLHEInfo(Bool_t f) { fHasLHEInfo = f; }
    void SetBeamEnergy(Double_t e) { fBeamEnergy = e; }
    void SetPdfGroup(Int_t g) { fPdfGroup = g; }
    void SetPdfID(Int_t i) { fPdfID = i; }
    void SetWeightMode(Int_t m) { fWeightMod = m; }
    void SetNProcesses(UInt_t n) { fProcesses.resize(n); }
    void SetNWeightGroups(UInt_t n) { fWeightGroups.resize(n); }
    void SetNCommentLines(UInt_t n) { fComments.resize(n); }
    void AddCommentLine(TString const& c) { fComments.push_back(c); }

  protected:
    Double_t fInternalXSec; // Internal = PYTHIA etc.
    Double_t fInternalXSecErr;
    Double_t fExternalLOXSec; // External = If the events come from LHE files etc.
    Double_t fExternalLOXSecErr;
    Double_t fExternalNLOXSec;
    Double_t fExternalNLOXSecErr;
    Bool_t fHasLHEInfo; // Everything below comes from LHE
    Double_t fBeamEnergy;
    Int_t fPdfGroup;
    Int_t fPdfID;
    Int_t fWeightMode;
    std::vector<ProcessData> fProcesses;
    std::vector<WeightGroupData> fWeightGroups;
    std::map<TString, std::vector<TString> > fHeaders;
    std::vector<TString> fComments;

    ClassDef(MCRunInfo, 1) // MC Run info class
  };

}
#endif
