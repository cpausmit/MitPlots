//--------------------------------------------------------------------------------------------------
// $Id: Ref.h,v 1.4 2009/03/16 19:58:40 loizides Exp $
//
// Ref
//
// Templated implimentation of our own TRef.
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
  class Ref
  {
    public:
      Ref() : fPID(0), fUID(0)    {}
      Ref(const ArrayElement *ae) { SetObject(ae); }
      virtual ~Ref()              {}

      Bool_t                       IsNull()        const { return fUID==0 ? kTRUE : kFALSE; }
      Bool_t                       IsValid()       const { return !IsNull();                }
      const ArrayElement          *Obj()           const;
      ArrayElement                *Obj();
      Bool_t                       RefsObject(const ArrayElement *ae) const;
      void                         SetObject(const ArrayElement *ae);
      
      void                         operator= (const ArrayElement *ae) { SetObject(ae);         }
      Bool_t                       operator==(const ArrayElement *ae) { return RefsObject(ae); }

    protected:
      TObject                     *GetObject()     const;

      ProcIDRef                    fPID;     //||process id corresponding to referenced object
      UInt_t                       fUID;     //unique id of the referenced object

    ClassDef(Ref, 1) // Templated implementation of our own TRef
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::Ref<ArrayElement>::GetObject() const
{
  // Return pointer to object. Code adapted from TRef::GetObject().

  if (IsNull())
    return 0;
  
  TProcessID *pid = fPID.Pid(); 
  if (!pid) {
    Fatal("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject","Process id is invalid!");
    return 0;
  }

  return RefResolver::GetObjectWithID(fUID,pid);
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
  // Check whether Ref points to given object.

  if (IsNull())
    return kFALSE;
  
  if (!ae->TestBit(kIsReferenced))
    return kFALSE;

  UInt_t oUid = ae->GetUniqueID();
  TProcessID *oPid = TProcessID::GetProcessWithUID(oUid, const_cast<ArrayElement*>(ae));
  if (!oPid)
    return kFALSE;

  if ( (fUID&0xffffff)!=(oUid&0xffffff) || fPID.Pid()->GetUniqueID()!=oPid->GetUniqueID())
    return kFALSE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::Ref<ArrayElement>::SetObject(const ArrayElement *ae)
{
  // Set reference to object.

  if (!ae)
    return;

  // check if the object can belong here and assign or get its uid
  if (ae->TestBit(kHasUUID)) {
    Fatal("Add", "Object cannot be added as it has not UUID!");
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
