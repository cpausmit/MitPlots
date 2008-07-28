#include "MitAna/DataTree/interface/BasePart.h"

using namespace std;
using namespace mithep;

BasePart::BasePart(int pid) :
  pid_ (pid),
  mass_(0.0)           // need to have funtion to automatically get mass from database using the pid
{
}

BasePart::BasePart(int pid, double mass) :
  pid_ (pid),
  mass_(mass)
{
}

BasePart::BasePart(const BasePart &d) :
  pid_ (d.pid ()),
  mass_(d.mass())
{
}

void BasePart::print(ostream &os) const
{
  os << " BasePart::print - pid: " << pid_ << "  mass: " << mass_ << endl;
}

ClassImp(BasePart)
