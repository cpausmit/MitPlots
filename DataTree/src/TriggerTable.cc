// $Id: TriggerTable.cc,v 1.1 2009/03/24 16:10:16 loizides Exp $

#include "MitAna/DataTree/interface/TriggerTable.h"
#include <TObjArray.h>

ClassImp(mithep::TriggerTable)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerTable::Print(Option_t *opt) const
{
  // Print trigger table content (not ordered!)

  TObjArray sorter;
  TIter iter(MakeIterator());
  const TriggerName *tn = dynamic_cast<const TriggerName*>(iter.Next());
  while (tn) {
    sorter.Add(const_cast<TriggerName*>(tn));
    tn = dynamic_cast<const TriggerName*>(iter.Next());
  }
  sorter.Sort();
  for(Int_t i = 0; i<sorter.GetEntriesFast(); ++i)
    sorter.At(i)->Print();
}
