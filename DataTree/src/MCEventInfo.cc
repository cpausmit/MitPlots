#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitCommon/Utils/interface/Utils.h"

ClassImp(mithep::MCEventInfo)

mithep::MCEventInfo::MCEventInfo() :
  fProcessId(0),
  fScale(0),
  fWeight(0),
  fId1(0),
  fId2(0), 
  fX1(0.),
  fX2(0.),
  fScalePdf(0.),
  fPdf1(0.),
  fPdf2(0.),
  fFlavorHistoryPath(0),
  fReweightScaleFactors(),
  fScales(),
  fNPartonsLO(0),
  fNPartonsNLO(0),
  fNPartons(0),
  fPartonsSize(64),
  fAlphaQED(0.),
  fAlphaQCD(0.),
  fPartonId(new Int_t[fPartonsSize]),
  fPartonStatus(new Short_t[fPartonsSize]),
  fPartonMother1(new UShort_t[fPartonsSize]),
  fPartonMother2(new UShort_t[fPartonsSize]),
  fPartonColor1(new Short_t[fPartonsSize]),
  fPartonColor2(new Short_t[fPartonsSize]),
  fPartonMom(new FourVector[fPartonsSize]),
  fPartonCTau(new Double32_t[fPartonsSize]),
  fPartonSpin(new Double32_t[fPartonsSize]),
  fLHEComments()
{
}

mithep::MCEventInfo::~MCEventInfo()
{
  delete [] fPartonId;
  delete [] fPartonStatus;
  delete [] fPartonMother1;
  delete [] fPartonMother2;
  delete [] fPartonColor1;
  delete [] fPartonColor2;
  delete [] fPartonMom;
  delete [] fPartonCTau;
  delete [] fPartonSpin;
}

void
mithep::MCEventInfo::SetNPartons(UShort_t n)
{
  if (n > fPartonsSize) {
    fPartonsSize = n * 2;

    mithep::Utils::Reallocate(fPartonId, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonStatus, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonMother1, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonMother2, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonColor1, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonColor2, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonMom, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonCTau, fNPartons, fPartonsSize);
    mithep::Utils::Reallocate(fPartonSpin, fNPartons, fPartonsSize);
  }

  fNPartons = n;
}
