// $Id: LAHeader.cc,v 1.1 2008/06/24 14:01:41 loizides Exp $

#include "MitAna/DataTree/interface/TriggerName.h"

ClassImp(mithep::TriggerName)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerName::Print(Option_t *opt) const
{
  printf("%03d: %s\n", fId, fName.Data());
}
