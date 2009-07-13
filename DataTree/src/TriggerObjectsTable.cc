// $Id: TriggerObject.cc,v 1.4 2008/12/08 16:42:53 loizides Exp $

#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#include "MitAna/DataTree/interface/TriggerObject.h"

ClassImp(mithep::TriggerObjectsTable)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerObjectsTable::Print(Option_t *opt) const
{
  // Print trigger objects table content.

  TIter iter(MakeIterator());
  const TriggerObject *to = dynamic_cast<const TriggerObject*>(iter.Next());
  while (to) {
    to->Print();
    to = dynamic_cast<const TriggerObject*>(iter.Next());
  }
}
