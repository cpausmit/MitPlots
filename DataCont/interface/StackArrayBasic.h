//--------------------------------------------------------------------------------------------------
// $Id: StackArrayBasic.h,v 1.1 2008/09/19 11:56:08 bendavid Exp $
//
// StackArrayBasic
//
// Implementation of a TStackArrayBasic using stack (and not heap) memory.
// For various reasons, the array can not be written in split mode.
// Maximum size of references is set to 1024 (but this could be 
// changed if there is need for it).
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_STACKARRAYBASIC
#define MITANA_DATACONT_STACKARRAYBASIC

#include <TObject.h>
#include <TError.h>
#include <TClass.h>
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
      Bool_t                    IsOwner()                         const { return kTRUE; }
      void                      Reset()                                 { fSize = 0; }
      void                      Trim()                                  {}
      ArrayElement              UncheckedAt(UInt_t idx);                 
      const ArrayElement        UncheckedAt(UInt_t idx)           const;

      ArrayElement              operator[](UInt_t idx);
      const ArrayElement        operator[](UInt_t idx)            const;

    protected:
      UShort_t                  fSize;        //size of array
      ArrayElement              fArray[N];  //storage of uids of referenced objects

    ClassDef(StackArrayBasic,1) // Implementation of our own TStackArrayBasic
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArrayBasic<ArrayElement, N>::StackArrayBasic() : 
  fSize(0)
{
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline mithep::StackArrayBasic<ArrayElement, N>::StackArrayBasic(const StackArrayBasic &a) : 
  fSize(a.fSize)
{
  //Copy constructor.  Copy only elements which are used.
  for (UInt_t i=0; i<fSize; ++i)
    fArray[i] = a.fArray[i];

}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArrayBasic<ArrayElement, N>::Add(const ArrayElement &ae)
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
inline ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::At(UInt_t idx)
{
  // Return entry at given index.

  if(idx<fSize)  
     return fArray[idx];

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return fArray[fSize];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::At(UInt_t idx) const
{
  // Return entry at given index.

  if(idx<fSize)  
     return fArray[idx];

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return fArray[fSize];
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

//-------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
void mithep::StackArrayBasic<ArrayElement, N>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

  if (b.IsReading()) {
    //UInt_t sv, cv;
    //b.ReadVersion(&sv, &cv);
    //TObject::Streamer(b);
    b >> fSize;
    if (fSize) {
      b.ReadFastArray(fArray,fSize);
    }
    //b.CheckByteCount(sv, cv, StackArrayBasic::IsA());
  } else { /*writing*/
    //UInt_t cv;
    //cv = b.WriteVersion(StackArrayBasic::IsA(), kTRUE);
    //TObject::Streamer(b);
    b << fSize;
    if (fSize) {
      b.WriteFastArray(fArray,fSize);
    }
    //b.SetByteCount(cv, kTRUE);
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return fArray[idx];
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement, UInt_t N>
inline const ArrayElement  mithep::StackArrayBasic<ArrayElement, N>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return fArray[idx];
}
#endif
