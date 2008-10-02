//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.3 2008/10/01 18:37:48 bendavid Exp $
//
// RefArray
//
// Implementation of a TRefArray using stack (and not heap) memory.
// For various reasons, the array can not be written in split mode.
// Maximum size of references is set to 1024 (but this could be 
// changed if there is need for it).
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

namespace mithep 
{
  template<class ArrayElement>
  class RefArray : public Collection<ArrayElement>
  {
    public:
      RefArray();
      ~RefArray() { fProcID = 0; }

      void                      Add(ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                    const;
      void                      Clear(Option_t */*opt*/="")             { fProcID = 0;}
      UInt_t                    Entries()                         const { return GetEntries(); }
      UInt_t                    GetEntries()                      const { return fSize; }
      Bool_t                    IsOwner()                         const { return kTRUE; }
      void                      Reset()                                 { fSize = 0; }
      void                      Trim()                                  {}
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)           const;

      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)            const;

    protected:
      TObject                  *GetObject(UInt_t idx)             const;
      UInt_t                    GetUID(UInt_t idx)                const;
    
      TProcessID               *fProcID;      //!ptr to Process Unique Identifier
      UShort_t                  fSize;        //size of array
      UInt_t                    fUIDs[1024];  //storage of uids of referenced objects

    ClassDefT(RefArray,1) // Implementation of our own TRefArray
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefArray<ArrayElement>::RefArray() : 
  fProcID(0),
  fSize(0)
{
   // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::RefArray<ArrayElement>::Add(ArrayElement *ae)
{
  // Add new reference to object.

  if(fSize>=1024) {
    Fatal("Add", "Maximum number of references reached: To support more requires change in code!");
    return;
  }

  // check if the object can belong here and assign or get its uid
  UInt_t uid = 0;
  if (ae->TestBit(kHasUUID)) {
    Error("Add", "Object can not be added as it has not UUID!");
    return;
  }

  if (ae->TestBit(kIsReferenced)) {
    uid = ae->GetUniqueID();
    if (fSize==0)
      fProcID = TProcessID::GetProcessWithUID(uid,ae);
    if (fProcID != TProcessID::GetProcessWithUID(uid,ae)) {
      Error("Add", "Object can not be added as it has a different process id!");
      return;
    }
  } else {
    if (fSize==0)
      fProcID = TProcessID::GetSessionProcessID();
    if (fProcID != TProcessID::GetSessionProcessID()) {
      Error("Add", "Object can not be added as it has a different process id!");
      return;
    }
    uid = TProcessID::AssignID(ae);
  }

  fUIDs[fSize] = uid;
  ++fSize;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if(idx<fSize)  
     return static_cast<ArrayElement*>(GetObject(idx));

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if(idx<fSize)  
     return static_cast<const ArrayElement*>(GetObject(idx));

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::RefArray<ArrayElement>::GetObject(UInt_t idx) const
{
  // Return entry at given index. Code adapted from TRef::GetObject().
  
  if (!fProcID) {
    Error("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(fProcID)) {
    Error("GetObject","Process id is invalid!");
    return 0;
  }
  UInt_t uid = GetUID(idx);

  //the reference may be in the TRefTable
  TRefTable *table = TRefTable::GetRefTable();
  if (table) {
    table->SetUID(uid, fProcID);
    table->Notify();
  }

  //try to find the object from the table of the corresponding PID
  TObject *obj = fProcID->GetObjectWithID(uid);
  return obj;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline UInt_t mithep::RefArray<ArrayElement>::GetUID(UInt_t idx) const
{
  // Return uid corresponding to idx.

  return fUIDs[idx];
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

//-------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::RefArray<ArrayElement>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    //UInt_t sv, cv;
    //b.ReadVersion(&sv, &cv);
    //TObject::Streamer(b);
    b >> fSize;
    if (fSize) {
      UShort_t pidf;
      b >> pidf;
      pidf += b.GetPidOffset();
      fProcID = b.ReadProcessID(pidf);
      b.ReadFastArray(fUIDs,fSize);
    }
    //b.CheckByteCount(sv, cv, RefArray::IsA());
  } else { /*writing*/
    //UInt_t cv;
    //cv = b.WriteVersion(RefArray::IsA(), kTRUE);
    //TObject::Streamer(b);
    b << fSize;
    if (fSize) {
      UShort_t pidf;
      pidf = b.WriteProcessID(fProcID);
      b << pidf;
      b.WriteFastArray(fUIDs,fSize);
    }
    //b.SetByteCount(cv, kTRUE);
  }
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
#endif
