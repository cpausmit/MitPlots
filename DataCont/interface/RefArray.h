//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.14 2009/02/17 21:54:35 bendavid Exp $
//
// RefArray
//
// Implementation of a TRefArray using stack (and not heap) memory.
// The maximum number of references is left as a template parameter.
// Since all of the stack allocation is handled by the StackArrays
// the RefArray itself can now actually be split.
//
// RefArray now supports objects from multiple PIDs, but only a single PID will be stored as long
// as only objects from a single PID are added.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_REFARRAY
#define MITANA_DATACONT_REFARRAY

#include <TObject.h>
#include <TRefArray.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include <TError.h>
#include "MitAna/TAM/interface/TAMSelector.h"
#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/FastArray.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"

namespace mithep 
{
  template<class ArrayElement>
  class RefArray /*: public Collection<ArrayElement> TODO to be enabled for Mit_008*/
  {
    public:
      RefArray();
      virtual ~RefArray() {}

      void                      Add(const ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)               const;
      void                      Clear(Option_t */*opt*/="")        { fPIDs.Clear(); fUIDs.Clear(); }
      UInt_t                    Entries()                    const { return GetEntries(); }
      UInt_t                    GetEntries()                 const { return fUIDs.GetEntries(); }
      UInt_t                    GetSize()                    const { return fUIDs.GetSize(); }
      Bool_t                    HasObject(const ArrayElement *obj) const;
      Bool_t                    IsOwner()                    const { return kTRUE; }
      TObject                  *ObjAt(UInt_t idx);       
      const TObject            *ObjAt(UInt_t idx)            const;
      void                      Reset();
      void                      Trim()                             { fPIDs.Trim(); fUIDs.Trim(); }
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)      const;
      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)       const;

    protected:
      TObject                  *GetObject(UInt_t idx)        const;
      TProcessID               *GetPID(UInt_t idx)           const;
      UInt_t                    GetUID(UInt_t idx)           const;
    
      FastArray<ProcIDRef>      fPIDs;//|| process ids of referenced objects
      FastArrayBasic<UInt_t>    fUIDs;//|| unique ids of referenced objects

    ClassDef(RefArray, 2) // Implementation of our own TRefArray
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefArray<ArrayElement>::RefArray()
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::RefArray<ArrayElement>::Add(const ArrayElement *ae)
{
  // Add new reference to object.

  // check if the object can belong here and assign or get its uid
  if (ae->TestBit(kHasUUID)) {
    Fatal("Add", "Object can not be added as it has not UUID!");
    return;
  }

  UInt_t uid = 0;
  TProcessID *pid = 0;
  if (ae->TestBit(kIsReferenced)) {
    uid = ae->GetUniqueID();
    pid = TProcessID::GetProcessWithUID(uid, const_cast<ArrayElement*>(ae));
  } else {
    pid = TProcessID::GetSessionProcessID();
    uid = TProcessID::AssignID(const_cast<ArrayElement*>(ae));
  }

  // If RefArray contains one and only one PID reference, then only add another if the added object
  // has a different PID.  When this occurs all of the extra spaces which had been left empty get
  // filled in with the original PID
  if (fPIDs.GetEntries()==1) {
    if (pid != fPIDs.At(0)->Pid() ) {
      while (fPIDs.GetEntries()<GetEntries())
        fPIDs.GetNew()->SetPid(fPIDs.At(0)->Pid());
        
      fPIDs.GetNew()->SetPid(pid);
    }    
  }
  else
    fPIDs.GetNew()->SetPid(pid);
  
  fUIDs.Add(uid);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<GetEntries())  
     return static_cast<ArrayElement*>(GetObject(idx));

  Fatal("At", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<GetEntries())  
     return static_cast<const ArrayElement*>(GetObject(idx));

  Fatal("At", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::RefArray<ArrayElement>::GetObject(UInt_t idx) const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  TProcessID *pid = GetPID(idx); 
  
  if (!pid) {
    Fatal("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject","Process id is invalid!");
    return 0;
  }

  UInt_t uid = GetUID(idx);

  //try to autoload from TAM
  TAMSelector *tSel = TAMSelector::GetEvtSelector();
  if (tSel) {
    return tSel->GetObjectWithID(uid,pid);
  }
  
  //no TAM proxy present, fall back to standard Root calls
  
  //the reference may be in the TRefTable
  TRefTable *table = TRefTable::GetRefTable();
  if (table) {
    table->SetUID(uid, pid);
    table->Notify();
  }

  return pid->GetObjectWithID(uid);

}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TProcessID *mithep::RefArray<ArrayElement>::GetPID(UInt_t idx) const
{
  // Return pid corresponding to idx.

  TProcessID *pid = 0;
  if (fPIDs.GetEntries()>1)
    pid = fPIDs.UncheckedAt(idx)->Pid();
  else
    pid = fPIDs.UncheckedAt(0)->Pid();
    
  return pid;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline UInt_t mithep::RefArray<ArrayElement>::GetUID(UInt_t idx) const
{
  // Return uid corresponding to idx.

  return fUIDs.UncheckedAt(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
Bool_t mithep::RefArray<ArrayElement>::HasObject(const ArrayElement *obj) const
{
  // check whether RefArray contains a given object

  if (!obj->TestBit(kIsReferenced))
    return kFALSE;
  
  UInt_t oUid = obj->GetUniqueID();
  TProcessID *oPid = TProcessID::GetProcessWithUID(oUid, const_cast<ArrayElement*>(obj));
  
  for (UInt_t i=0; i<GetEntries(); ++i) {
    if ( (GetUID(i)&0xffffff)==(oUid&0xffffff) && GetPID(i)->GetUniqueID()==oPid->GetUniqueID())
      return kTRUE;
  }
  
  return kFALSE;
  
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::RefArray<ArrayElement>::ObjAt(UInt_t idx)
{
  // Return object at given index.

  if (idx<GetEntries())  
     return GetObject(idx);

  Fatal("ObjAt", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
const TObject *mithep::RefArray<ArrayElement>::ObjAt(UInt_t idx) const
{
  // Return object at given index.

  if (idx<GetEntries())  
    return static_cast<const TObject*>(GetObject(idx));

  Fatal("ObjAt", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefArray<ArrayElement>::Reset()
{
  fUIDs.Reset();
  fPIDs.Reset();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(GetObject(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(GetObject(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
