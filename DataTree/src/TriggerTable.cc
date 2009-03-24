// $Id: TriggerName.cc,v 1.4 2008/12/08 16:42:53 loizides Exp $

#include "MitAna/DataTree/interface/TriggerTable.h"

ClassImp(mithep::TriggerTable)

using namespace mithep;

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
