//--------------------------------------------------------------------------------------------------
// $Id: DataObject.h,v 1.15 2008/12/02 09:30:11 loizides Exp $
//
// DataObject
//
// This is the common base class for all objects in the tree that do require the TObject
// bits to be written out (as opposed to DataBase).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DATAOBJECT_H
#define MITANA_DATATREE_DATAOBJECT_H
 
#include "MitAna/DataTree/interface/Types.h"
#include <TObject.h>
#include <TROOT.h>
#include <TClass.h>
#include <TBranchElement.h>
#include <TRefTable.h>
#include <TProcessID.h>

namespace mithep
{
  class DataObject : public TObject
  {
    public:
      DataObject() {}
      ~DataObject() {}

      Bool_t               IsCached()    const { return TestBit(23); }
      Bool_t               MustClear()   const { return TestBit(14); }
      Bool_t               MustDelete()  const { return TestBit(15); }
      template <class Col> 
      const Col           *ParentCol()   const;

    protected:
      void                 ResetCacheBit()     { SetBit(23,0); }
      void                 SetCacheBit()       { SetBit(23);   }
      void                 SetClearBit()       { SetBit(14);   }
      void                 SetDeleteBit()      { SetBit(15);   }

    ClassDef(DataObject, 1)
  };
}

//--------------------------------------------------------------------------------------------------
template <class Col>
const Col* mithep::DataObject::ParentCol() const
{
  // Return pointer to parent collection. SLOW, but faster than looping over collections!
  // Also note this function will only work for objects which were referenced prior to being 
  // written. Otherwise a null pointer will be returned.
  
  const Col* colObj=0;
  
  if ( !this->TestBit(kIsReferenced) )
    return colObj;
  
  TRefTable *table = TRefTable::GetRefTable();
  if (!table)
    return colObj;
    
  UInt_t uid = this->GetUniqueID();
  //cast away const is a hack, this is fixed in newer root versions
  TProcessID *pid = TProcessID::GetProcessWithUID(uid, const_cast<DataObject*>(this));
  table->SetUID(uid, pid);
  table->Notify(); 
  TBranchElement *trackParent = 
    static_cast<TBranchElement*>(table->GetParent(uid, pid));
  while (!colObj) {
    if (!trackParent)
      return colObj;
    colObj = dynamic_cast<Col*>
      (reinterpret_cast<TObject*>(static_cast<TBranchElement*>(trackParent)->GetObject()));
    if (colObj)
      break;
    trackParent = static_cast<TBranchElement*>(trackParent->GetMother());
  }
  return colObj;
}
#endif
