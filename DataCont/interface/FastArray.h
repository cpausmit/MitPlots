//--------------------------------------------------------------------------------------------------
// FastArray
//
// Implementation of a "fast" array on the heap: Memory is dynamically allocated, but there is an
// optimization in the read streamer similar to the TClonesArray where the heap memory of an
// existing object is reused.
//
// This class is meant to be used as a datamember for objects which are contained inside a
// TClonesArray. It is assumed that those classed do not use heap memory themselves.
//
// For various reasons, the array cannot be written in split mode.  Array is meant to store classes
// as opposed to FastArrayBasic which should be used to hold basic types.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATACONT_FASTARRAY_H
#define MITANA_DATACONT_FASTARRAY_H

#include <TObject.h>
#include <TClass.h>
#include <TStorage.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class FastArray : public Collection<ArrayElement>
  {
    public:
      FastArray();
      FastArray(const FastArray &a);
      ~FastArray() { Init(0); }

      void                      AddCopy(const ArrayElement &ae);
      ArrayElement             *AddNew();
      ArrayElement             *Allocate();
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                     const;
      void                      Clear(Option_t */*opt*/="")              { fSize=0; Init(0);    }
      UInt_t                    Entries()                          const { return fSize;        }
      UInt_t                    GetEntries()                       const { return fSize;        } 
      ArrayElement             *GetNew();
      UInt_t                    GetSize()                          const { return fCapacity;    }
      Bool_t                    HasObject(const ArrayElement *obj) const;
      Bool_t                    IsOwner()                          const { return kTRUE;        }
      TObject                  *ObjAt(UInt_t idx);
      const TObject            *ObjAt(UInt_t idx)                  const;
      void                      Resize(UInt_t);
      void                      Reset();
      void                      Trim()                                   { Expand(fSize);       }
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)            const;
      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)             const;

    protected:
      ArrayElement             *AddBlank();                      
      void                      Init(UShort_t s);
      void                      Expand(UShort_t s);
    
      UShort_t                  fSize;     //size of array
      const TClass             *fClass;    //!pointer to TClass object used by streamer
      UShort_t                  fCapacity; //!size of heap allocated
      UShort_t                  fNObjects; //!number of allocated objects
      ArrayElement             *fArray;    //!the array on the heap

    ClassDef(FastArray,1) // Array on heap for arbitrary classes
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::FastArray<ArrayElement>::FastArray() : 
  fSize(0),
  fClass(TClass::GetClass(typeid(ArrayElement))),
  fCapacity(0),
  fNObjects(0),
  fArray(0)
{
   // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::FastArray<ArrayElement>::FastArray(const FastArray &a) : 
  fSize(0),
  fClass(a.fClass),
  fCapacity(0),
  fNObjects(0),
  fArray(0)
{
   // Copy constructor. Copy only elements which are used.

   Init(a.fSize);
   for (UInt_t i=0; i<a.fSize; ++i)
     new(Allocate()) ArrayElement(a.fArray[i]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement* mithep::FastArray<ArrayElement>::AddBlank()
{
  // Construct additional blank objects for read streamer.

  if (fNObjects >= fCapacity)
    Expand(TMath::Max(16,2*fCapacity));
    
  ++fNObjects;
  return new(&fArray[fNObjects-1]) ArrayElement();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::FastArray<ArrayElement>::AddCopy(const ArrayElement &ae)
{
  // Add a copy of an existing object.

  if (fSize<fNObjects) {
    fArray[fSize] = ae;
    ++fSize;
    BaseCollection::Clear();
  }
  else
    new(Allocate()) ArrayElement(ae);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement* mithep::FastArray<ArrayElement>::AddNew()
{
  // Add new object.

  return new(Allocate()) ArrayElement(); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement* mithep::FastArray<ArrayElement>::Allocate()
{
  // Return next slot in the array, *only* to be used in placement new operator. 

  if (fSize >= fCapacity)
    Expand(TMath::Max(16,2*fCapacity));
  
  ++fSize;
  BaseCollection::Clear();
  fNObjects = TMath::Max(fNObjects,fSize);
  return &fArray[fSize-1];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::FastArray<ArrayElement>::At(UInt_t idx)
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
template<class ArrayElement>
inline const ArrayElement *mithep::FastArray<ArrayElement>::At(UInt_t idx) const
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
template<class ArrayElement>
inline void mithep::FastArray<ArrayElement>::Expand(UShort_t s)
{

  // Expand or shrink the array to the given number of elements.
  
  if (s < fSize) {
    TObject::Fatal("Expand", "Cannot shrink FastArray to less than fSize");
    return;
  }
  
  if (!fArray || s==0) {
    Init(s);
    return;
  }
      
  if (fCapacity == s)
    return;
    
  fArray = static_cast<ArrayElement*>(TStorage::ReAlloc(fArray, s * sizeof(ArrayElement),
                                                        fCapacity * sizeof(ArrayElement)));
  fCapacity = s;
  fNObjects = TMath::Min(fCapacity,fNObjects);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement* mithep::FastArray<ArrayElement>::GetNew()
{
  // Return next slot in the array, *only* to be used in placement new operator.

  if (fSize < fNObjects)
    return Allocate();
  else
    return AddNew();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline Bool_t mithep::FastArray<ArrayElement>::HasObject(const ArrayElement *obj) const
{
  // Check whether object is in array.

  for (UInt_t i=0; i<fSize; ++i) {
    if ( fArray[i].IsEqual(obj) )
      return true;
  }
  
  return false;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::FastArray<ArrayElement>::Init(UShort_t s)
{
  // Initialize heap array.
      
  if (fArray && fCapacity != s) {
    for (UInt_t i=0; i<fNObjects; ++i)
      fArray[i].~ArrayElement();
    TStorage::Dealloc(fArray);
    fArray    = 0;
    fNObjects = 0;
  }
  
  fCapacity = s;
  
  if ( !fArray && fCapacity > 0 )
    fArray = static_cast<ArrayElement*>(TStorage::Alloc(fCapacity*sizeof(ArrayElement))); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TObject *mithep::FastArray<ArrayElement>::ObjAt(UInt_t idx)
{
  // Return object at given index.

  return static_cast<TObject*>(At(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const TObject *mithep::FastArray<ArrayElement>::ObjAt(UInt_t idx) const
{
  // Return object at given index.

  return static_cast<const TObject*>(At(idx));
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::FastArray<ArrayElement>::Resize(UInt_t s)
{
  if (!fArray)
    Init(s);
  else {
    if (s < fSize) {
      for (UInt_t i = s; i != fSize; ++i)
        fArray[i].~ArrayElement();
    }

    fSize = s;

    if (fSize >= fCapacity)
      Expand(TMath::Max(16, 2 * fSize));

    BaseCollection::Clear();
    fNObjects = TMath::Max(fNObjects, fSize);
  }
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::FastArray<ArrayElement>::Reset()
{
  // Reset this array.

  fSize = 0;
  BaseCollection::Clear();
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::FastArray<ArrayElement>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    b >> fSize;
    if (fSize) {
      if (fSize > fCapacity)
        Expand(TMath::Max(static_cast<Int_t>(fSize),2*fCapacity));
      
      while (fNObjects < fSize)
        AddBlank();
      
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
template<class ArrayElement>
inline ArrayElement *mithep::FastArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(&fArray[idx]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::FastArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(&fArray[idx]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::FastArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::FastArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
