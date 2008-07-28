#include "MitAna/DataTree/interface/BasePartAction.h"
#include "MitAna/DataTree/interface/StablePart.h"

using namespace std;
using namespace mithep;

StablePart::StablePart() :
  BasePart(),
  hits_(0),
  stat_(0),
  phi0_(0) ,phi0Err_(0),
  d0_  (0) ,d0Err_  (0),
  pt_  (0) ,ptErr_  (0),
  z0_  (0) ,z0Err_  (0),
  cotT_(0) ,cotTErr_(0)
{
}

StablePart::StablePart(int pid) :
  BasePart(pid),
  hits_(0),
  stat_(0),
  phi0_(0) ,phi0Err_(0),
  d0_  (0) ,d0Err_  (0),
  pt_  (0) ,ptErr_  (0),
  z0_  (0) ,z0Err_  (0),
  cotT_(0) ,cotTErr_(0)
{
}

StablePart::StablePart(int pid, double mass) :
  BasePart(pid,mass),
  hits_(0),
  stat_(0),
  phi0_(0) ,phi0Err_(0),
  d0_  (0) ,d0Err_  (0),
  pt_  (0) ,ptErr_  (0),
  z0_  (0) ,z0Err_  (0),
  cotT_(0) ,cotTErr_(0)
{
}

StablePart::StablePart(const StablePart &s) :
  BasePart(s),
  hits_(s.hits ()  ),
  stat_(s.stat ()  ),
  phi0_(s.phi0 ()  ), phi0Err_(s.phi0Err()),
  d0_  (s.d0Raw()  ), d0Err_  (s.d0Err  ()),
  pt_  (s.pt   ()  ), ptErr_  (s.ptErr  ()),
  z0_  (s.z0Raw()  ), z0Err_  (s.z0Err  ()),
  cotT_(s.cotT ()  ), cotTErr_(s.cotTErr())
{
}

void StablePart::print(ostream &os) const
{
  os << " StablePart::print - pid: " << pid_ << "  mass: " << mass_ << endl;
}

void StablePart::doAction(BasePartAction *action) const
{
  action->doAction(this);
  return;
}

ClassImp(StablePart)
