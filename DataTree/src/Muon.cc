#include "MitAna/DataTree/interface/Muon.h"

ClassImp(mithep::Muon)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void Muon::Print(Option_t */*opt*/) const
{
  // Print particle kinematics.

  TString type("GlM");
  if (IsTrackerMuon())
    type = "TrM";
  else if (IsStandaloneMuon())
    type = "SaM";
  else if (IsCaloMuon())
    type = "CaM";

  printf("%s: pt=%.3f eta=%.3f phi=%.3f\n", type.Data(), Pt(), Eta(), Phi());
}
