//--------------------------------------------------------------------------------------------------
// $Id: StackArrayBasic.h,v 1.1 2008/10/31 18:56:14 bendavid Exp $
//
// StackArrayBasic
//
// Implementation of an array on the stack as opposed to on the heap 
// memory. For various reasons, the array can not be written in split 
// mode. Maximum size is set by template parameter. Array is meant to 
// store basic data types as opposed to StackArray which can hold 
// classes.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_STACKARRAYBASIC
#define MITANA_DATACONT_STACKARRAYBASIC

#include <TObject.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement, UInt_t N>
  class StackArrayBasic : public TObject
  {
    public:
      StackArrayBasic();
      StackArrayBasic(const StackArrayBasic &a);
      ~StackArrayBasic() {}

      void                      Add(const ArrayElement &ae);
      ArrayElement              At(UInt_t idx);
      const ArrayElement        At(UInt_t idx)                    const;
      void                      Clear(Option_t */*opt*/="")             {}
      UInt_t                    Entries()                         const { return GetEntries(); }
      UInt_t                    GetEntries()                      const { return fSize; }
      UInt_t                    GetSize()                         const { return N; }
      Bool_t                    IsOwner()                         const { return kTRUE; }
      void                      Reset()                                 { fSize = 0; }
      void                      Trim()                                  {}
      ArrayElement              UncheckedAt(UInt_t idx);                 
      const ArrayElement        UncheckedAt(UInt_t idx)           const;
      ArrayElement              operator[](UInt_t idx);
      const ArrayElement        operator[](UInt_t idx)            const;

    protected:
      UShort_t                  fSize;      //size of array
      ArrayElement              fArray[N];  //storage for basic types

    ClassDef(StackArrayBasic,1) // Array on stack for basic types
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArrayBasic<ArrayElement, N>::StackArrayBasic() : 
  fSize(0)
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArrayBasic<ArrayElement, N>::StackArrayBasic(const StackArrayBasic &a) : 
  fSize(a.fSize)
{
  // Copy constructor. Copy only elements which are used.
  
  for (UInt_t i=0; i<fSize; ++i)
    fArray[i] = a.fArray[i];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArrayBasic<ArrayElement, N>::Add(const ArrayElement &ae)
{
  // Add element to array.

  if(fSize>=N) {
    TObject::Fatal("Add", "Maximum number of slots reached (%d>=%d): "
                   "To support more requires a different template!", fSize, N);
    return;
  }

  fArray[fSize] = ae;
  ++fSize;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement mithep::StackArrayBasic<ArrayElement, N>::At(UInt_t idx)
{
  // Return entry at given index.

  if(idx<fSize)  
     return fArray[idx];

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
                 idx, fSize, GetName(), typeid(tmp).name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::At(UInt_t idx) const
{
  // Return entry at given index.

  if(idx<fSize)  
     return fArray[idx];

  ArrayElement tmp;
  TObject::Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
                 idx, fSize, GetName(), typeid(tmp).name()); 
  return 0;
}

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArrayBasic<ArrayElement, N>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    b >> fSize;
    if (fSize) {
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
template<class ArrayElement, UInt_t N>
inline ArrayElement mithep::StackArrayBasic<ArrayElement, N>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement mithep::StackArrayBasic<ArrayElement, N>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
