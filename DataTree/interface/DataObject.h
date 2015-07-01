//--------------------------------------------------------------------------------------------------
// DataObject
//
// This is the common base class for all objects in the tree that do require the TObject bits to be
// written out (as opposed to DataBase). Typically these are all objects that can be persistently
// linked.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATATREE_DATAOBJECT_H
#define MITANA_DATATREE_DATAOBJECT_H
 
#include "MitAna/DataCont/interface/CacheFlag.h"
#include "MitAna/DataTree/interface/ObjTypes.h"
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

    Bool_t               Is(EObjType t)   const { return (ObjType()==t); }
    Bool_t               IsCached()       const { return TestBit(23); }
    Bool_t               MustClear()      const { return TestBit(14); }
    Bool_t               MustDelete()     const { return TestBit(15); }
    virtual Int_t        ObjId()          const { return ObjType()*1000; }
    virtual EObjType     ObjType()        const { return kDataObject; }
    template <class Col> 
    Col const*           ParentCol()      const;

    // Object marking
    Bool_t               IsMarked()       const { return fMarker == 1; }
    virtual void         Mark(UInt_t i=1) const;
    void                 UnmarkMe()       const { fMarker = 0; }

  protected:
    void                 ResetCacheBit()        { SetBit(23,0); }
    void                 SetCacheBit()          { SetBit(23); }
    void                 SetClearBit()          { SetBit(14); }
    void                 SetDeleteBit()         { SetBit(15); }

    mutable UInt_t       fMarker = 0;             //!  marker uses custom streamer

    ClassDef(DataObject, 1) // Common base for objects that do get referenced
  };
}

//--------------------------------------------------------------------------------------------------
template <class Col>
Col const*
mithep::DataObject::ParentCol() const
{
  // Return pointer to parent collection. SLOW, but faster than looping over collections!
  // Also note this function will only work for objects which were referenced prior to being 
  // written. Otherwise a null pointer will be returned.
  
  if (!this->TestBit(kIsReferenced))
    return 0;
  
  TRefTable *table = TRefTable::GetRefTable();
  if (!table)
    return 0;
    
  UInt_t uid = this->GetUniqueID();
  //cast away const is a hack, this is fixed in newer ROOT versions
  TProcessID *pid = TProcessID::GetProcessWithUID(uid, const_cast<DataObject*>(this));
  if (!pid) 
    return 0;
  table->SetUID(uid, pid);
  table->Notify(); 

  TBranchElement *trackParent = 
    static_cast<TBranchElement*>(table->GetParent(uid, pid));
  if (!trackParent)
    return 0;

  Col const* colObj=0;

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
