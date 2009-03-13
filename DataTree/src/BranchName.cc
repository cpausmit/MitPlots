// $Id: TriggerName.cc,v 1.4 2008/12/08 16:42:53 loizides Exp $

#include "MitAna/DataTree/interface/BranchName.h"

ClassImp(mithep::BranchName)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void BranchName::Print(Option_t *opt) const
{
  // Print trigger id and name.

//  printf("%03d: %s\n", fId, fName.Data());
}

#if 0
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
#endif
