// $Id: DataObject.cc,v 1.1 2008/06/04 09:08:36 loizides Exp $

#include "MitAna/DataTree/interface/DataObject.h"

ClassImp(mithep::DataObject)

//--------------------------------------------------------------------------------------------------
void mithep::DataObject::Mark(UInt_t i) const
{
  if (i == 0)
    const_cast<DataObject*>(this)->SetBit(16,0);
  else
    const_cast<DataObject*>(this)->SetBit(16,1);
}
