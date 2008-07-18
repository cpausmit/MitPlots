//--------------------------------------------------------------------------------------------------
// $Id: DataObject.h,v 1.10 2008/07/17 16:37:37 bendavid Exp $
//
// DataObject
//
// This is the common base class for all objects in the tree. 
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_DATAOBJECT_H
#define DATATREE_DATAOBJECT_H
 
#include <TObject.h>
#include <TROOT.h>
#include <TClass.h>
#include <TBranchElement.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class DataObject : public TObject
  {
    public:
      DataObject() {}
      ~DataObject() {}

      Bool_t               MustClear()   const { return TestBit(14); }
      Bool_t               MustDelete()  const { return TestBit(15); }
      Bool_t               IsCached()    const { return TestBit(23); }
      template <class Col> const Col* ParentCol() const;

    protected:
      void                 SetClearBit()       { SetBit(14); }
      void                 SetDeleteBit()      { SetBit(15); }
      void                 SetCacheBit()       { SetBit(23); }
      void                 ResetCacheBit()     { SetBit(23,0); }

    ClassDef(DataObject, 1) // Basic data object class
  };
}

//--------------------------------------------------------------------------------------------------
template <class Col>
const Col* mithep::DataObject::ParentCol() const
{
  // Return pointer to parent collection.  SLOW! (But faster than looping over collections.)
  // Also note this function will only work for objects which were reference prior to being written.
  // Otherwise a null pointer will be returned.
  
  const Col* colObj=0;
  TRefTable *table = TRefTable::GetRefTable();
  if (!table)
    return colObj;
  table->SetUID(this->GetUniqueID(), (TProcessID*)gROOT->GetUUIDs());
  table->Notify();
  //cast away const is a hack, this is fixed in newer root versions
  TProcessID* pID = TProcessID::GetProcessWithUID(this->GetUniqueID(),(void*)this); 
  TBranchElement *trackParent = (TBranchElement*)(table->GetParent(this->GetUniqueID(), pID));
  while (!colObj) {
    if (!trackParent)
      return colObj;
    colObj = dynamic_cast<Col*>((TObject*)((TBranchElement*)trackParent)->GetObject());
    if (!colObj)
      trackParent = dynamic_cast<TBranchElement*>(trackParent->GetMother());
  }
    return colObj;
}
#endif
