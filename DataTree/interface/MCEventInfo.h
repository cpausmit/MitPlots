//--------------------------------------------------------------------------------------------------
// MCEventInfo
//
// This class holds monte-carle generation specific information, as for example stored
// in HepMC::PdfInfo and HepMC::GenEvent.
// 
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCEVENTINFO_H
#define MITANA_DATATREE_MCEVENTINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitCommon/DataFormats/interface/Types.h"
#include "MitAna/DataCont/interface/Types.h"

namespace mithep {

  class MCEventInfo : public DataBase {
  public:
    MCEventInfo();
    ~MCEventInfo();

    Int_t Id1() const { return fId1; }
    Int_t Id2() const { return fId2; }
    EObjType ObjType() const { return kMCEventInfo; } 
    Double_t Pdf1() const { return fPdf1; }
    Double_t Pdf2() const { return fPdf2; }
    Int_t ProcessId() const { return fProcessId; }
    Double_t Scale() const { return fScale; }
    Double_t ScalePdf() const { return fScalePdf; }
    Double_t X1() const { return fX1; }
    Double_t X2() const { return fX2; }
    Double_t Weight() const { return fWeight; }
    Int_t FlavorHistoryPath() const { return fFlavorHistoryPath; }
    Bool_t HasLHEInfo() const { return fHasLHEInfo; }
    UInt_t NReweightScaleFactors() const { return fReweightScaleFactors.GetEntries(); }
    Double_t ReweightScaleFactor(UInt_t idx) const { return fReweightScaleFactors.At(idx); }
    UInt_t NScales() const { return fScales.GetEntries(); }
    Double_t Scale(UInt_t idx) const { return fScales.At(idx); }
    UShort_t NPartonsLO() const { return fNPartonsLO; }
    UShort_t NPartonsNLO() const { return fNPartonsNLO; }
    UInt_t NPartons() const { return fNPartons; }
    Double_t AlphaQED() const { return fAlphaQED; }
    Double_t AlphaQCD() const { return fAlphaQCD; }
    Int_t PartonId(UInt_t iP) const { return iP < fNPartons ? fPartonId[iP] : 0; }
    Short_t PartonStatus(UInt_t iP) const { return iP < fNPartons ? fPartonStatus[iP] : -1; }
    UShort_t PartonMother1(UInt_t iP) const { return iP < fNPartons ? fPartonMother1[iP] : -1; }
    UShort_t PartonMother2(UInt_t iP) const { return iP < fNPartons ? fPartonMother2[iP] : -1; }
    Short_t PartonColor1(UInt_t iP) const { return iP < fNPartons ? fPartonColor1[iP] : 0; }
    Short_t PartonColor2(UInt_t iP) const { return iP < fNPartons ? fPartonColor2[iP] : 0; }
    mithep::FourVector const* PartonMom(UInt_t iP) const { return iP < fNPartons ? fPartonMom + iP : 0; }
    Double_t PartonCTau(UInt_t iP) const { return iP < fNPartons ? fPartonCTau[iP] : -1.; }
    Double_t PartonSpin(UInt_t iP) const { return iP < fNPartons ? fPartonSpin[iP] : 0.; }
    UInt_t NLHECommentLines() const { return fLHEComments.GetEntries(); }
    char const* LHEComment(UInt_t iL) const { return fLHEComments.At(iL)->GetName(); }

    // Using HEPEUP speak
    UInt_t NUP() const { return NPartons(); }
    Int_t IDPRUP() const { return ProcessId(); }
    Double_t XWGTUP() const { return Weight(); }
    Double_t SCALUP() const { return Scale(); }
    Double_t AQEDUP() const { return AlphaQED(); }
    Double_t AQCDUP() const { return AlphaQCD(); }
    Int_t IDUP(UInt_t iP) const { return PartonId(iP); }
    Short_t ISTUP(UInt_t iP) const { return PartonStatus(iP); }
    std::pair<UShort_t, UShort_t> MOTHUP(UInt_t iP) const { return std::make_pair(PartonMother1(iP), PartonMother2(iP)); }
    std::pair<Short_t, Short_t> ICOLUP(UInt_t iP) const { return std::make_pair(PartonColor1(iP), PartonColor2(iP)); }
    mithep::FourVector const* PUP(UInt_t iP) const { return PartonMom(iP); }
    Double_t VTIMUP(UInt_t iP) const { return PartonCTau(iP); }
    Double_t SPINUP(UInt_t iP) const { return PartonSpin(iP); }

    void SetId1(Int_t id) { fId1 = id; }
    void SetId2(Int_t id) { fId2 = id; }
    void SetPdf1(Double_t p) { fPdf1 = p; }
    void SetPdf2(Double_t p) { fPdf2 = p; }
    void SetProcessId(Int_t id) { fProcessId = id; }
    void SetScale(Double_t s) { fScale = s; }
    void SetScalePdf(Double_t s) { fScalePdf = s; }
    void SetWeight(Double_t w) { fWeight = w; }
    void SetX1(Double_t x) { fX1 = x; }
    void SetX2(Double_t x) { fX2 = x; }
    void SetFlavorHistoryPath(Int_t p) { fFlavorHistoryPath = p; }
    void SetHasLHEInfo(Bool_t b) { fHasLHEInfo = b; }
    void SetNReweightScaleFactors(UInt_t size) { fReweightScaleFactors.Resize(size); }
    void SetReweightScaleFactors(UInt_t iF, Double_t s) { fReweightScaleFactors.At(iF) = s; }
    void ClearScales() { fScales.Reset(); }
    void AddScale(Double_t s) { fScales.Add(s); }
    void SetNPartonsLO(UShort_t n) { fNPartonsLO = n; }
    void SetNPartonsNLO(UShort_t n) { fNPartonsNLO = n; }
    void SetNPartons(UInt_t);
    void SetAlphaQED(Double_t a) { fAlphaQED = a; }
    void SetAlphaQCD(Double_t a) { fAlphaQCD = a; }
    void SetPartonId(UShort_t iP, Int_t id) { fPartonId[iP] = id; }
    void SetPartonStatus(UShort_t iP, Short_t s) { fPartonStatus[iP] = s; }
    void SetPartonMother1(UShort_t iP, UShort_t m) { fPartonMother1[iP] = m; }
    void SetPartonMother2(UShort_t iP, UShort_t m) { fPartonMother2[iP] = m; }
    void SetPartonColor1(UShort_t iP, Short_t c) { fPartonColor1[iP] = c; }
    void SetPartonColor2(UShort_t iP, Short_t c) { fPartonColor2[iP] = c; }
    void SetPartonMom(UShort_t iP, Double_t x, Double_t y, Double_t z, Double_t e)
    { fPartonMom[iP].SetPxPyPzE(x, y, z, e); }
    void SetPartonCTau(UShort_t iP, Double_t c) { fPartonCTau[iP] = c; }
    void SetPartonSpin(UShort_t iP, Double_t s) { fPartonSpin[iP] = s; }
    void ClearLHEComments() { fLHEComments.Reset(); }
    void AddLHEComment(char const* c) { new (fLHEComments.Allocate()) TObjString(c); }

  protected:
    Int_t fProcessId; //process id
    Double32_t fScale; //scale
    Double32_t fWeight; //weight
    Int_t fId1; //pdg of first parton
    Int_t fId2; //pdg of second parton
    Double32_t fX1; //bjorken x1
    Double32_t fX2; //bjorken x2
    Double32_t fScalePdf; //scale (Q^2)
    Double32_t fPdf1; //pdf1/x1
    Double32_t fPdf2; //pdf2/x2
    Int_t fFlavorHistoryPath; //Number indicating flavor history
    // all data below are from LHE
    Bool_t fHasLHEInfo;
    FArrDouble32 fReweightScaleFactors; //|| alternative event weights normalized to original XWGTUP
    FArrDouble32 fScales; //|| scale value used to exclude EWK-produced partons from matching
    UShort_t fNPartonsLO; // number of partons for LO process (used to steer matching/merging)
    UShort_t fNPartonsNLO; // number of partons for NLO process (used to steer matching/merging)
    UInt_t fNPartons; // number of partons excluding the first two
    UShort_t fPartonsSize; //! only for bookkeeping array size
    Double32_t fAlphaQED; // value of QED coupling used in the event
    Double32_t fAlphaQCD; // value of QCD coupling used in the event
    Int_t* fPartonId; //[fNPartons] pdg id of the partons
    Short_t* fPartonStatus; //[fNPartons] status of the partons
    UShort_t* fPartonMother1; //[fNPartons] mother 1 of the partons
    UShort_t* fPartonMother2; //[fNPartons] mother 2 of the partons
    Short_t* fPartonColor1; //[fNPartons] color line 1 of the partons
    Short_t* fPartonColor2; //[fNPartons] color line 1 of the partons
    mithep::FourVector* fPartonMom; //[fNPartons] momentum of the partons
    Double32_t* fPartonCTau; //[fNPartons] ctau of the partons
    Double32_t* fPartonSpin; //[fNPartons] spin of the partons
    FArrObjString fLHEComments; //|| LHE event block comment lines

    ClassDef(MCEventInfo, 4) // Monte-Carlo event info class
  };

}
#endif
