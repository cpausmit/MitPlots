//--------------------------------------------------------------------------------------------------
// Ref
//
// Templated implementation of our own TRef.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_REF_H
#define MITANA_DATACONT_REF_H

#include <TObject.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include <TError.h>
#include "MitAna/DataCont/interface/RefResolver.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
 
namespace mithep 
{
  template<class ArrayElement>
  class Ref {
  public:
    Ref() : fPID(0), fUID(0) {}
    Ref(Ref<ArrayElement> const& orig) : fPID(orig.fPID), fUID(orig.fUID) {}
    Ref(const ArrayElement *ae) { SetObject(ae); }
    virtual ~Ref() {}
  
    Ref<ArrayElement>& operator=(Ref<ArrayElement> const& rhs) {
      fPID = rhs.fPID;
      fUID = rhs.fUID;
      return *this;
    }
  
    Bool_t IsNull() const { return fUID==0 ? kTRUE : kFALSE; }
    Bool_t IsValid() const { return !IsNull(); }
    ArrayElement const* Obj() const;
    ArrayElement* Obj();
    Bool_t RefsObject(ArrayElement const*) const;
    void SetObject(ArrayElement const*);
    
    Ref<ArrayElement>& operator=(ArrayElement const* ae) { SetObject(ae); return *this; }
    Bool_t operator==(ArrayElement const* ae) { return RefsObject(ae); }
  
    protected:
    TObject* GetObject() const;
  
    ProcIDRef fPID;     //||process id corresponding to referenced object
    UInt_t fUID;     //unique id of the referenced object
  
    ClassDef(Ref, 1) // Templated implementation of our own TRef
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject*
mithep::Ref<ArrayElement>::GetObject() const
{
  // Return pointer to object. Code adapted from TRef::GetObject().

  if (IsNull())
    return 0;
  
  TProcessID* pid = fPID.Pid(); 
  if (!pid) {
    Fatal("GetObject", "Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject", "Process id is invalid!");
    return 0;
  }

  TObject* obj = RefResolver::GetObjectWithID(fUID, pid);
  if (!obj) {
    Fatal("Ref::GetObject","Null pointer for valid ref!");
  }
  
  return obj;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement const*
mithep::Ref<ArrayElement>::Obj() const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return static_cast<ArrayElement const*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement*
mithep::Ref<ArrayElement>::Obj()
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return static_cast<ArrayElement*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
Bool_t
mithep::Ref<ArrayElement>::RefsObject(ArrayElement const* ae) const
{
  // Check whether Ref points to given object.

  if (IsNull())
    return kFALSE;

  auto* oe = dynamic_cast<TObject const*>(ae);

  if (!oe || !oe->TestBit(kIsReferenced))
    return kFALSE;

  UInt_t oUid = oe->GetUniqueID();
  TProcessID *oPid = TProcessID::GetProcessWithUID(oUid, const_cast<TObject*>(oe));
  if (!oPid)
    return kFALSE;

  if ((fUID&0xffffff)!=(oUid&0xffffff) || fPID.Pid()->GetUniqueID()!=oPid->GetUniqueID())
    return kFALSE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void
mithep::Ref<ArrayElement>::SetObject(ArrayElement const* ae)
{
  // Set reference to object.

  if (!ae)
    return;

  auto* oe = dynamic_cast<TObject const*>(ae);

  if (!oe) {
    Fatal("Add", "Object cannot be added as it does not derive from TObject");
    return;
  }

  // check if the object can belong here and assign or get its uid
  if (oe->TestBit(kHasUUID)) {
    Fatal("Add", "Object cannot be added as it has a TUUID of its own");
    return;
  }

  if (oe->TestBit(kIsReferenced)) {
    fUID = oe->GetUniqueID();
    fPID.SetPid(TProcessID::GetProcessWithUID(fUID, const_cast<TObject*>(oe)));
  }
  else {
    fPID.SetPid(TProcessID::GetSessionProcessID());
    fUID = TProcessID::AssignID(const_cast<TObject*>(oe));
  }
}
#endif
