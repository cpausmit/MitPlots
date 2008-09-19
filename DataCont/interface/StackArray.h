//--------------------------------------------------------------------------------------------------
// $Id: StackArray.h,v 1.2 2008/09/10 03:33:26 loizides Exp $
//
// StackArray
//
// Implementation of a TStackArray using stack (and not heap) memory.
// For various reasons, the array can not be written in split mode.
// Maximum size of references is set to 1024 (but this could be 
// changed if there is need for it).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_STACKARRAY
#define MITANA_DATACONT_STACKARRAY

#include <TObject.h>
#include <TError.h>
#include <TClass.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement, UInt_t N>
  class StackArray : public Collection<ArrayElement>
  {
    public:
      StackArray();
      ~StackArray() {}

      void                      AddCopy(const ArrayElement &ae);
      ArrayElement             *AddNew();
      ArrayElement             *Allocate();
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                    const;
      void                      Clear(Option_t */*opt*/="")             {}
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
      TClass                    *fClass;//! pointer to TClass object used by streamer
      UShort_t                  fSize;        //size of array
      ArrayElement              fArray[N];  //storage of uids of referenced objects

    private:
      StackArray(const StackArray &a);

    ClassDef(StackArray,1) // Implementation of our own TStackArray
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArray<ArrayElement, N>::StackArray() : 
  fSize(0)
{
   // Default constructor.
   fClass = TClass::GetClass(typeid(ArrayElement));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArray<ArrayElement, N>::AddCopy(const ArrayElement &ae)
{
  // Add a copy of an existing object.

  if(fSize>=N) {
    Fatal("Add", "Maximum number of references reached: To support more requires change in code!");
    return;
  }

  fArray[fSize] = ae;
  ++fSize;
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
   // Allocate a slot in the array, *only* to be used in placement new operator.

  if(fSize>=N) {
    Fatal("Add", "Maximum number of references reached: To support more requires change in code!");
    return 0;
  }

  ++fSize;
  return &fArray[fSize-1];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement *mithep::StackArray<ArrayElement, N>::At(UInt_t idx)
{
  // Return entry at given index.

  if(idx<fSize)  
     return static_cast<ArrayElement*>(&fArray[idx]);

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement *mithep::StackArray<ArrayElement, N>::At(UInt_t idx) const
{
  // Return entry at given index.

  if(idx<fSize)  
     return static_cast<const ArrayElement*>(&fArray[idx]);

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
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

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArray<ArrayElement, N>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    //UInt_t sv, cv;
    //b.ReadVersion(&sv, &cv);
    //TObject::Streamer(b);
    b >> fSize;
    if (fSize) {
      b.ReadFastArray(fArray,fClass,fSize);
    }
    //b.CheckByteCount(sv, cv, StackArray::IsA());
  } else { /*writing*/
    //UInt_t cv;
    //cv = b.WriteVersion(StackArray::IsA(), kTRUE);
    //TObject::Streamer(b);
    b << fSize;
    if (fSize) {
      b.WriteFastArray(fArray,fClass,fSize);
    }
    //b.SetByteCount(cv, kTRUE);
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
#endif
