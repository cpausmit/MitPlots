#include "MitAna/DataTree/interface/BasePartAction.h"
#include "MitAna/DataTree/interface/DecayPart.h"

using namespace std;
using namespace mithep;

DecayPart::DecayPart(int pid, double mass) :
  BasePart        (pid,mass),
  decayType_      (Fast),
  prob_           (0),
  chi2_           (0),
  ndof_           (0),
  fittedMass_     (0),
  fittedMassError_(0),
  lxy_            (0),
  lxyError_       (0),
  lxyToPv_        (0),
  lxyToPvError_   (0),
  dxy_            (0),
  dxyError_       (0),
  dxyToPv_        (0),
  dxyToPvError_   (0),
  lz_             (0),
  lzError_        (0),
  lzToPv_         (0),
  lzToPvError_    (0),
  cTau_           (0),
  cTauError_      (0),
  pt_             (0),
  ptError_        (0),
  fourMomentum_   (0,0,0,0),
  position_       (0,0,0),
  error_          (3,0),
  bigError_       (7,0)
{
}

DecayPart::DecayPart(int pid, double mass, DecayType decayType) :
  BasePart        (pid,mass),
  decayType_      (decayType),
  prob_           (0),
  chi2_           (0),
  ndof_           (0),
  fittedMass_     (0),
  fittedMassError_(0),
  lxy_            (0),
  lxyError_       (0),
  lxyToPv_        (0),
  lxyToPvError_   (0),
  dxy_            (0),
  dxyError_       (0),
  dxyToPv_        (0),
  dxyToPvError_   (0),
  lz_             (0),
  lzError_        (0),
  lzToPv_         (0),
  lzToPvError_    (0),
  cTau_           (0),
  cTauError_      (0),
  pt_             (0),
  ptError_        (0),
  fourMomentum_   (0,0,0,0),
  position_       (0,0,0),
  error_          (3,0),
  bigError_       (7,0)
{
}

DecayPart::DecayPart(const DecayPart &d) :
  BasePart        (d.pid(),d.mass()),
  decayType_      (d.decayType      ()),
  prob_           (d.prob           ()),
  chi2_           (d.chi2           ()),
  ndof_           (d.ndof           ()),
  fittedMass_     (d.fittedMass     ()),
  fittedMassError_(d.fittedMassError()),
  lxy_            (d.lxy            ()),
  lxyError_       (d.lxyError       ()),
  lxyToPv_        (d.lxyToPv        ()),
  lxyToPvError_   (d.lxyToPvError   ()),
  dxy_            (d.dxy            ()),
  dxyError_       (d.dxyError       ()),
  dxyToPv_        (d.dxyToPv        ()),
  dxyToPvError_   (d.dxyToPvError   ()),
  lz_             (d.lz             ()),
  lzError_        (d.lzError        ()),
  lzToPv_         (d.lzToPv         ()),
  lzToPvError_    (d.lzToPvError    ()),
  cTau_           (d.cTau           ()),
  cTauError_      (d.cTauError      ()),
  pt_             (d.pt             ()),
  ptError_        (d.ptError        ()),
  fourMomentum_   (d.fourMomentum   ()),
  position_       (d.position       ()),
  error_          (d.error          ()),
  bigError_       (d.bigError       ())
{
}

void DecayPart::print(ostream &os) const
{
  os << " DecayPart::print - pid: " << pid_ << "  mass: " << mass_
     << "  decayType: " << decayType_ << endl
     <<  "  Decays to \n";
  for (ConstIter ip=children_.begin(); ip!=children_.end(); ip++) {
    os << "   "; (*ip)->print(os);    
  }
  os <<  "  -- end decays to -------\n";
  os <<  "  Vertex fit (c2,ndof,prob): " << chi2() << ",  " << ndof() << ",  " << prob() << "\n\n" ;
}

void DecayPart::doAction(BasePartAction *action) const
{

  if (action->getActionType() == BasePartAction::NonRecursive) {
    action->doAction(this);
    return;
  }

  if (action->getActionType() == BasePartAction::TopDown)
    action->doAction(this);
  
  for (ConstIter ip=children_.begin(); ip!=children_.end(); ip++) {
    action->incLevel(); (*ip)->doAction(action); action->decLevel();
  }

  if (action->getActionType() == BasePartAction::BottomUp)
    action->doAction(this);

  return;
}

ClassImp(DecayPart)
