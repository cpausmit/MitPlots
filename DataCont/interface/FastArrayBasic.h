//--------------------------------------------------------------------------------------------------
// $Id: FastArrayBasic.h,v 1.1 2009/02/26 17:05:18 bendavid Exp $
//
// FastArrayBasic
//
// Implementation of an array on the heap.  Memory is dynamically allocated, 
// but there is an optimization in the read streamer similar to the TClonesArray
// where the heap memory of an existing object is reused.  This class is meant to be used
// as a datamember for objects which are contained inside a TClonesArray. 
// For various reasons, the array can not be written in split 
// mode. Array is meant to 
// store basic data types as opposed to StackArray which can hold 
// classes.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_FASTARRAYBASIC
#define MITANA_DATACONT_FASTARRAYBASIC

#include <TObject.h>
#include <TClass.h>
#include <TStorage.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class FastArrayBasic : public BaseCollection
  {
    public:
      FastArrayBasic();
      FastArrayBasic(const FastArrayBasic &a);
      ~FastArrayBasic() { Init(0); }

      void                      Add(const ArrayElement &ae);
      ArrayElement              At(UInt_t idx);
      const ArrayElement        At(UInt_t idx)                     const;
      void                      Clear(Option_t */*opt*/="")              { fSize=0; Init(0); }
      UInt_t                    Entries()                          const { return GetEntries(); }
      UInt_t                    GetEntries()                       const { return fSize;        }
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

    ClassDef(FastArrayBasic,1) // Array on stack for arbitrary classes
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::FastArrayBasic<ArrayElement>::FastArrayBasic() : 
  fSize(0),
  fCapacity(0),
  fArray(0)
{
   // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::FastArrayBasic<ArrayElement>::FastArrayBasic(const FastArrayBasic &a) : 
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
template<class ArrayElement>
void mithep::FastArrayBasic<ArrayElement>::Add(const ArrayElement &ae)
{
  // Add a copy of an existing object.
  
  if (fSize >= fCapacity)
    Expand(TMath::Max(16,2*fCapacity));
   
  ++fSize; 
  fArray[fSize-1] = ae;

}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement mithep::FastArrayBasic<ArrayElement>::At(UInt_t idx)
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
template<class ArrayElement>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement>::At(UInt_t idx) const
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
template<class ArrayElement>
inline void mithep::FastArrayBasic<ArrayElement>::Expand(UShort_t s)
{

  // Expand or shrink the array to s elements.
  
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
template<class ArrayElement>
inline void mithep::FastArrayBasic<ArrayElement>::Init(UShort_t s)
{

  // Initialize heap array
  
  if (fArray && fCapacity != s) {
    TStorage::Dealloc(fArray);
    fArray = 0;
  }
  
  fCapacity = s;
  
  if ( !fArray && fCapacity > 0 )
    fArray = static_cast<ArrayElement*>(TStorage::Alloc(fCapacity*sizeof(ArrayElement))); //new TObject* [fSize];
  //memset(fCont, 0, fSize*sizeof(TObject*));

}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::FastArrayBasic<ArrayElement>::Streamer(TBuffer &b)
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
template<class ArrayElement>
inline ArrayElement mithep::FastArrayBasic<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement mithep::FastArrayBasic<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement mithep::FastArrayBasic<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
