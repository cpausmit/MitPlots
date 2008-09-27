// $Id: TriggerObject.cc,v 1.1 2008/09/17 04:07:28 loizides Exp $

#include "MitAna/DataTree/interface/TriggerObject.h"

ClassImp(mithep::TriggerObjectRel)
ClassImp(mithep::TriggerObjectBase)
ClassImp(mithep::TriggerObject)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
void TriggerObject::Print(Option_t *opt) const
{
  printf("%03d: %s %2d %.2f %.2f %.2f (%s/%s)\n", 
         TrgId(), TrigName(), Int_t(Type()), Pt(), Eta(), Phi(), ModuleName(), FilterName());
}

//--------------------------------------------------------------------------------------------------
void TriggerObjectsTable::Print(Option_t *opt) const
{
  // Print trigger objects table content.

  TIterator *iter = MakeIterator();
  const TriggerObject *to = dynamic_cast<const TriggerObject *>(iter->Next());
  while (to) {
    to->Print();
    to = dynamic_cast<const TriggerObject *>(iter->Next());
  }
}
