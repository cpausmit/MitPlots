// $Id: TriggerName.cc,v 1.2 2008/09/27 06:06:36 loizides Exp $

#include "MitAna/DataTree/interface/TriggerName.h"

ClassImp(mithep::TriggerName)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerName::Print(Option_t *opt) const
{
  // Print trigger id and name.

  printf("%03d: %s\n", fId, fName.Data());
}

//--------------------------------------------------------------------------------------------------
void TriggerTable::Print(Option_t *opt) const
{
  // Print trigger table content (not ordered!)

  TIterator *iter = MakeIterator();
  const TriggerName *tn = dynamic_cast<const TriggerName*>(iter->Next());
  while (tn) {
    tn->Print();
    tn = dynamic_cast<const TriggerName*>(iter->Next());
  }
}
