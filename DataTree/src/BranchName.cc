// $Id: BranchName.cc,v 1.1 2009/03/13 08:40:01 loizides Exp $

#include "MitAna/DataTree/interface/BranchName.h"

ClassImp(mithep::BranchName)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void BranchName::Print(Option_t *opt) const
{
  // Print branch names.

  printf("%s -> %s\n", fBrName.Data(), fBrDep.Data());
}
