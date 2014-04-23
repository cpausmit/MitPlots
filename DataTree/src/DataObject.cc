#include "MitAna/DataTree/interface/DataObject.h"

ClassImp(mithep::DataObject)

//--------------------------------------------------------------------------------------------------
void mithep::DataObject::Mark(UInt_t i) const
{
  //if (i == 0)
  //  const_cast<DataObject*>(this)->SetBit(17,0);
  //else
  //  const_cast<DataObject*>(this)->SetBit(17,1);
  if (i == 0)
    fMarker = 0;
  else
    fMarker = 1;
}
