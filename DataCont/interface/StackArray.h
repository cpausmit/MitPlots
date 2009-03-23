//--------------------------------------------------------------------------------------------------
// $Id: StackArray.h,v 1.13 2009/03/23 13:07:18 loizides Exp $
//
// StackArray
//
// Implementation of an array on the stack as opposed to on the heap 
// memory. For various reasons, the array cannot be written in split 
// mode. Maximum size is set by template parameter. Array is meant to 
// store classes as opposed to StackArrayBasic which should be used to 
// hold basic types.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_STACKARRAY_H
#define MITANA_DATACONT_STACKARRAY_H

#include <TObject.h>
#include <TClass.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement, UInt_t N>
  class StackArray : public Collection<ArrayElement>
  {
    public:
      StackArray();
      StackArray(const StackArray &a);

      void                      AddCopy(const ArrayElement &ae);
      ArrayElement             *AddNew();
      ArrayElement             *Allocate();
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                     const;
      void                      Clear(Option_t */*opt*/="")              {}
      UInt_t                    Entries()                          const { return fSize; }
      UInt_t                    GetEntries()                       const { return fSize; }
      UInt_t                    GetSize()                          const { return N;     }
      Bool_t                    HasObject(const ArrayElement *obj) const;
      Bool_t                    IsOwner()                          const { return kTRUE; }
      TObject                  *ObjAt(UInt_t idx);
      const TObject            *ObjAt(UInt_t idx)                  const;
      void                      Reset();
      void                      Trim()                                   {}
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)            const;
      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)             const;

    protected:
      TClass                   *fClass;    //!pointer to TClass object used by streamer
      UShort_t                  fSize;     //size of array
      ArrayElement              fArray[N]; //storage for objects

    ClassDef(StackArray,1) // Array on stack for arbitrary classes
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArray<ArrayElement, N>::StackArray() : 
  fClass(TClass::GetClass(typeid(ArrayElement))),
  fSize(0)
{
   // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArray<ArrayElement, N>::StackArray(const StackArray &a) : 
  fClass(a.fClass),
  fSize(a.fSize)
{
   // Copy constructor. Copy only elements which are used.

   for (UInt_t i=0; i<fSize; ++i)
    fArray[i] = a.fArray[i];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArray<ArrayElement, N>::AddCopy(const ArrayElement &ae)
{
  // Add a copy of an existing object.

  if (fSize>=N) {
    TObject::Fatal("AddCopy", "Maximum number of slots reached (%d>=%d): "
                   "To support more requires a different template!", fSize, N);
    return;
  }

  fArray[fSize] = ae;
  ++fSize;
  BaseCollection::Clear();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
ArrayElement* mithep::StackArray<ArrayElement, N>::AddNew()
{
  // Add new object.

  return new(Allocate()) ArrayElement(); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
ArrayElement* mithep::StackArray<ArrayElement, N>::Allocate()
{
  // Return next slot in the array, *only* to be used in placement new operator.

  if (fSize>=N) {
    TObject::Fatal("Allocate", "Maximum number of slots reached (%d>=%d): "
                   "To support more requires a different template!", fSize, N);
    return 0;
  }

  ++fSize;
  BaseCollection::Clear();
  return &fArray[fSize-1];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::StackArray<ArrayElement, N>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fSize)  
     return static_cast<ArrayElement*>(&fArray[idx]);

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fSize, this->GetName(), typeid(tmp).name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::StackArray<ArrayElement, N>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fSize)  
     return static_cast<const ArrayElement*>(&fArray[idx]);

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fSize, this->GetName(), typeid(tmp).name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline Bool_t mithep::StackArray<ArrayElement, N>::HasObject(const ArrayElement *obj) const
{
  // Check whether object is in array.

  for (UInt_t i=0; i<fSize; ++i) {
    if ( fArray[i].IsEqual(obj) )
      return true;
  }
  
  return false;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline TObject *mithep::StackArray<ArrayElement, N>::ObjAt(UInt_t idx)
{
  // Return object at given index.

  return static_cast<TObject*>(At(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const TObject *mithep::StackArray<ArrayElement, N>::ObjAt(UInt_t idx) const
{
  // Return object at given index.

  return static_cast<const TObject*>(At(idx));
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArray<ArrayElement, N>::Reset()
{
  // Reset this array.

  fSize = 0;
  BaseCollection::Clear();
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArray<ArrayElement, N>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    b >> fSize;
    if (fSize) {
      b.ReadFastArray(fArray,fClass,fSize);
    }
  } else { /*writing*/
    b << fSize;
    if (fSize) {
      b.WriteFastArray(fArray,fClass,fSize);
    }
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::StackArray<ArrayElement, N>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(&fArray[idx]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::StackArray<ArrayElement, N>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(&fArray[idx]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::StackArray<ArrayElement, N>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::StackArray<ArrayElement, N>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
