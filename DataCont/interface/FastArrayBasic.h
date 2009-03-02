//--------------------------------------------------------------------------------------------------
// $Id: FastArrayBasic.h,v 1.3 2009/03/02 12:34:00 loizides Exp $
//
// FastArrayBasic
//
// Implementation of a "fast" array on the heap: Memory is dynamically allocated, 
// but there is an optimization in the read streamer similar to the TClonesArray
// where the heap memory of an existing object is reused.  
// This class is meant to be used as a datamember for objects which are contained 
// inside a TClonesArray. 
// For various reasons, the array can not be written in split mode. 
// Array is meant to store basic data types as opposed to FastArray 
// which can hold arbitrary (non-heap using) classes.
// Since it stores basic types it can not derive from the Collection<ArrayElement>
// interface, or else the At() member functions would have to return pointers to
// basic elements. Something we did not want to do.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_FASTARRAYBASIC_H
#define MITANA_DATACONT_FASTARRAYBASIC_H

#include <TObject.h>
#include <TClass.h>
#include <TStorage.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement, class DE=Float_t>
  class FastArrayBasic : public BaseCollection
  {
    public:
      FastArrayBasic(UShort_t icap=0);
      FastArrayBasic(const FastArrayBasic &a);
      ~FastArrayBasic() { Init(0); }

      void                      Add(const ArrayElement &ae);
      ArrayElement              At(UInt_t idx);
      const ArrayElement        At(UInt_t idx)                     const;
      void                      Clear(Option_t */*opt*/="")              { fSize=0; Init(0);    }
      UInt_t                    Entries()                          const { return fSize;        }
      UInt_t                    GetEntries()                       const { return Entries();    }
      UInt_t                    GetSize()                          const { return fCapacity;    }
      Bool_t                    IsOwner()                          const { return kTRUE;        }
      TObject                  *ObjAt(UInt_t idx)                        { return 0;            }
      const TObject            *ObjAt(UInt_t idx)                 const  { return 0;            }
      void                      Reset()                                  { fSize = 0;           }
      void                      Trim()                                   { Expand(fSize);       }
      ArrayElement              UncheckedAt(UInt_t idx);                 
      const ArrayElement        UncheckedAt(UInt_t idx)            const;
      ArrayElement              operator[](UInt_t idx);
      const ArrayElement        operator[](UInt_t idx)             const;

    protected:
      void                      Init(UShort_t s);
      void                      Expand(UShort_t s);
    
      UShort_t                  fSize;     //size of array
      UShort_t                  fCapacity; //!size of heap allocated
      ArrayElement             *fArray;    //!heap storage for objects

    ClassDef(FastArrayBasic,1) // Fast array for basic types
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline mithep::FastArrayBasic<ArrayElement, DE>::FastArrayBasic(UShort_t icap) : 
  fSize(0),
  fCapacity(0),
  fArray(0)
{
   // Default constructor.

  if (icap)
    Init(icap);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline mithep::FastArrayBasic<ArrayElement, DE>::FastArrayBasic(const FastArrayBasic &a) : 
  fSize(0),
  fCapacity(0),
  fArray(0)
{
   // Copy constructor. Copy only elements which are used.

   Init(a.fSize);
   for (UInt_t i=0; i<a.fSize; ++i)
     Add(a.fArray[i]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
void mithep::FastArrayBasic<ArrayElement, DE>::Add(const ArrayElement &ae)
{
  // Add a copy of an existing object.
  
  if (fSize >= fCapacity)
    Expand(TMath::Max(16,2*fCapacity));
   
  ++fSize; 
  fArray[fSize-1] = ae;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::At(UInt_t idx)
{
  // Return entry at given index. 

  if (idx<fSize)  
     return fArray[idx];

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fSize, this->GetName(), typeid(tmp).name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fSize)  
     return fArray[idx];

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fSize, this->GetName(), typeid(tmp).name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline void mithep::FastArrayBasic<ArrayElement, DE>::Expand(UShort_t s)
{

  // Expand or shrink the array to given number of elements.
  
  if (s < fSize) {
    TObject::Fatal("Expand", "Cannot shrink FastArrayBasic to less than fSize");
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
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline void mithep::FastArrayBasic<ArrayElement, DE>::Init(UShort_t s)
{

  // Initialize the array the heap.
  
  if (fArray && fCapacity != s) {
    TStorage::Dealloc(fArray);
    fArray = 0;
  }
  
  fCapacity = s;
  
  if (!fArray && fCapacity > 0)
    fArray = static_cast<ArrayElement*>(TStorage::Alloc(fCapacity*sizeof(ArrayElement)));
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
void mithep::FastArrayBasic<ArrayElement, DE>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    b >> fSize;
    if (fSize) {
      if (fSize > fCapacity)
        Expand(TMath::Max(static_cast<Int_t>(fSize),2*fCapacity));
        
      b.ReadFastArray(fArray,fSize);
    }
  } else { /*writing*/
    b << fSize;
    if (fSize) {
      b.WriteFastArray(fArray,fSize);
    }
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, class DE>
inline ArrayElement mithep::FastArrayBasic<ArrayElement, DE>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
