// $Id: TriggerName.cc,v 1.3 2008/12/01 17:30:01 loizides Exp $

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

  TIter iter(MakeIterator());
  const TriggerName *tn = dynamic_cast<const TriggerName*>(iter.Next());
  while (tn) {
    tn->Print();
    tn = dynamic_cast<const TriggerName*>(iter.Next());
  }
}
