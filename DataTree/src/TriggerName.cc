// $Id: TriggerName.cc,v 1.4 2008/12/08 16:42:53 loizides Exp $

#include "MitAna/DataTree/interface/TriggerName.h"

ClassImp(mithep::TriggerName)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerName::Print(Option_t *opt) const
{
  // Print trigger id and name.

  printf("%04d: %s\n", fId, fName.Data());
}
