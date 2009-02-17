//--------------------------------------------------------------------------------------------------
// $Id: BaseCollection.h,v 1.3 2008/12/10 11:25:00 loizides Exp $
//
// Ref
//
// Templated reimplimentation of TRef
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_REF_H
#define MITANA_DATACONT_REF_H

#include <TObject.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include <TError.h>
#include "MitAna/DataCont/interface/ProcIDRef.h"
 
namespace mithep 
{
  template<class ArrayElement>
  class Ref
  {
    public:
      Ref() : fPID(0), fUID(0) {}
      Ref(const ArrayElement *ae) { SetObject(ae); }
      virtual ~Ref() {}

      Bool_t                       IsNull()        const { return fUID==0 ? kTRUE : kFALSE; }
      Bool_t                       IsValid()       const { return !IsNull(); }
      const ArrayElement          *Obj()           const;
      ArrayElement                *Obj();
      Bool_t                       RefsObject(const ArrayElement *ae) const;
      void                         SetObject(const ArrayElement *ae);
      
      void                         operator= (const ArrayElement *ae) { SetObject(ae); }
      Bool_t                       operator==(const ArrayElement *ae) { return RefsObject(ae); }

    protected:
      TObject                     *GetObject()     const;
    
      ProcIDRef                    fPID;//||
      UInt_t                       fUID;

    ClassDef(Ref, 1) // Base class of all our collections
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::Ref<ArrayElement>::GetObject() const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  if (IsNull())
    return 0;
  
  TProcessID *pid= fPID.Pid(); 
  
  if (!pid) {
    Fatal("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject","Process id is invalid!");
    return 0;
  }

  //try to find the object from the table of the corresponding PID
  TObject *obj = pid->GetObjectWithID(fUID);

  //We are now assuming that the object table is cleaned so that all unloaded objects have null
  //pointers in the object table
  //This guarantees that the check below is valid for determining whether we need to go to the
  //TRefTable
  if (obj)
    return obj;

  //the reference may be in the TRefTable
  TRefTable *table = TRefTable::GetRefTable();
  if (table) {
    table->SetUID(fUID, pid);
    table->Notify();
    obj = pid->GetObjectWithID(fUID);
  }

  return obj;
  
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
const ArrayElement *mithep::Ref<ArrayElement>::Obj() const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return static_cast<const ArrayElement*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement *mithep::Ref<ArrayElement>::Obj()
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return static_cast<ArrayElement*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
Bool_t mithep::Ref<ArrayElement>::RefsObject(const ArrayElement *ae) const
{
  // check whether RefArray contains a given object

  if (IsNull())
    return kFALSE;
  
  if (!ae->TestBit(kIsReferenced))
    return kFALSE;

  UInt_t oUid = ae->GetUniqueID();
  TProcessID *oPid = TProcessID::GetProcessWithUID(oUid, const_cast<ArrayElement*>(ae));

  if ( (fUID&0xffffff)==(oUid&0xffffff) && fPID.Pid()->GetUniqueID()==oPid->GetUniqueID())
    return kTRUE;
  else
    return kFALSE;

}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::Ref<ArrayElement>::SetObject(const ArrayElement *ae)
{
  // Add new reference to object.

  // check if the object can belong here and assign or get its uid
  if (ae->TestBit(kHasUUID)) {
    Fatal("Add", "Object can not be added as it has not UUID!");
    return;
  }

  if (ae->TestBit(kIsReferenced)) {
    fUID = ae->GetUniqueID();
    fPID.SetPid(TProcessID::GetProcessWithUID(fUID, const_cast<ArrayElement*>(ae)));
  } else {
    fPID.SetPid(TProcessID::GetSessionProcessID());
    fUID = TProcessID::AssignID(const_cast<ArrayElement*>(ae));
  }

}

#endif
