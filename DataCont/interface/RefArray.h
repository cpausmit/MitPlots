//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.10 2008/12/10 11:26:52 loizides Exp $
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
#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/StackArray.h"
#include "MitAna/DataCont/interface/StackArrayBasic.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"

namespace mithep 
{
  template<class ArrayElement, UInt_t N>
  class RefArray /*: public Collection<ArrayElement> TODO to be enabled for Mit_008*/
  {
    public:
      RefArray();
      virtual ~RefArray() {}

      void                      Add(const ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)               const;
      void                      Clear(Option_t */*opt*/="")        {}
      UInt_t                    Entries()                    const { return GetEntries(); }
      UInt_t                    GetEntries()                 const { return fUIDs.GetEntries(); }
      UInt_t                    GetSize()                    const { return N; }
      Bool_t                    IsOwner()                    const { return kTRUE; }
      TObject                  *ObjAt(UInt_t idx);       
      const TObject            *ObjAt(UInt_t idx)            const;
      void                      Reset();
      void                      Trim()                             {}
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)      const;
      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)       const;

    protected:
      TObject                  *GetObject(UInt_t idx)        const;
      UInt_t                    GetUID(UInt_t idx)           const;
    
      StackArray<ProcIDRef,N>      fPIDs;//|| process ids of referenced objects
      StackArrayBasic<UInt_t,N>    fUIDs;//|| unique ids of referenced objects

    ClassDef(RefArray, 2) // Implementation of our own TRefArray
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::RefArray<ArrayElement,N>::RefArray()
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::RefArray<ArrayElement,N>::Add(const ArrayElement *ae)
{
  // Add new reference to object.

  if (GetEntries()>=N) {
    Fatal("Add", "Maximum number of slots reached (%d>=%d): "
          "To support more requires a different template!", GetEntries(), N);
    return;
  }

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
        fPIDs.Allocate()->SetPid(fPIDs.At(0)->Pid());
        
      fPIDs.Allocate()->SetPid(pid);
    }    
  }
  else
    fPIDs.Allocate()->SetPid(pid);
  
  fUIDs.Add(uid);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::RefArray<ArrayElement,N>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<GetEntries())  
     return static_cast<ArrayElement*>(GetObject(idx));

  Fatal("At", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::RefArray<ArrayElement,N>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<GetEntries())  
     return static_cast<const ArrayElement*>(GetObject(idx));

  Fatal("At", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
TObject *mithep::RefArray<ArrayElement,N>::GetObject(UInt_t idx) const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  TProcessID *pid=0; 
  if (fPIDs.GetEntries()>1)
    pid = fPIDs.At(idx)->Pid();
  else
    pid = fPIDs.At(0)->Pid();
  
  if (!pid) {
    Fatal("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject","Process id is invalid!");
    return 0;
  }

  UInt_t uid = GetUID(idx);

  //the reference may be in the TRefTable
  TRefTable *table = TRefTable::GetRefTable();
  if (table) {
    table->SetUID(uid, pid);
    table->Notify();
  }

  //try to find the object from the table of the corresponding PID
  TObject *obj = pid->GetObjectWithID(uid);
  return obj;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline UInt_t mithep::RefArray<ArrayElement,N>::GetUID(UInt_t idx) const
{
  // Return uid corresponding to idx.

  return fUIDs.At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
TObject *mithep::RefArray<ArrayElement,N>::ObjAt(UInt_t idx)
{
  // Return object at given index.

  if (idx<GetEntries())  
     return GetObject(idx);

  Fatal("ObjAt", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement,UInt_t N>
const TObject *mithep::RefArray<ArrayElement,N>::ObjAt(UInt_t idx) const
{
  // Return object at given index.

  if (idx<GetEntries())  
    return static_cast<const TObject*>(GetObject(idx));

  Fatal("ObjAt", "Given index (%u) is larger than array size (%u)", idx, GetEntries());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline void mithep::RefArray<ArrayElement,N>::Reset()
{
  fUIDs.Reset();
  fPIDs.Reset();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::RefArray<ArrayElement,N>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(GetObject(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::RefArray<ArrayElement,N>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(GetObject(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::RefArray<ArrayElement,N>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::RefArray<ArrayElement,N>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
