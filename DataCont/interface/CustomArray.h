//--------------------------------------------------------------------------------------------------
// $Id: CustomArray.h,v 1.1 2008/07/29 10:36:20 loizides Exp $
//
// OwnArray
//
// Implementation of a TRefArray using stack (and not heap) memory.
// For various reasons, the array can not be written in split mode.
// Maximum size of references is set to 1024 (but this could be 
// changed if there is need for it).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_CUSTOMARRAY
#define MITANA_DATACONT_CUSTOMARRAY

#include <Rtypes.h>

namespace mithep 
{
  template<class T, UShort_t N>
  class OwnArray
  {
    public:
      OwnArray(UInt_t rsv=0);
      ~OwnArray() { ; }

      void                      Add(T &val);
      T                        &At(UInt_t idx);
      const T                  &At(UInt_t idx)                    const;
      UInt_t                    Entries()                         const { return fSize; }
      UInt_t                    GetEntries()                      const { return fSize; }
      void                      Trim()                                  {}
      T                        &UncheckedAt(UInt_t idx);                 
      const T                  &UncheckedAt(UInt_t idx)           const;
      T                        &operator[](UInt_t idx);
      const T                  &operator[](UInt_t idx)            const;

    protected:
      UShort_t                 fSSize;     //size of array on stack
      UInt_t                   fHSize;     //size of array on heap
      Bool_t                   fHasHeap;   //=true if memory on heap is allocated
      T                        fVals[N];   //array on stack
      T                       *fHeap;      //[fHSize]array on heap

    private:
      OwnArray(const OwnArray &a);

    ClassDefT(OwnArray,1) // 
  };
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
inline mithep::OwnArray<T>::OwnArray(UInt_t rsv) : 
  fSize(0),
  fSSize(0),
  fHSize(0),
  fHeap(0),
  fHasHeap(kFALSE)
{
   // Default constructor.

  memset(fUIDs,0,128*sizeof(UInt_t));
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
void mithep::OwnArray<T,N>::Add(const T &val)
{
  // Add new reference to object.

}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
inline T &mithep::OwnArray<T,N>::At(UInt_t idx)
{
  // Return entry at given index.

#if 0
  if(idx<fSize)  
     return static_cast<T*>(GetObject(idx));

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
#endif
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
inline const T &mithep::OwnArray<T,N>::At(UInt_t idx) const
{
  // Return entry at given index.
#if 0
  if(idx<fSize)  
     return static_cast<const T*>(GetObject(idx));

  Error("At", "Given index (%ud) is larger than array size (%ud)", idx, fSize);
  return 0;
#endif
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
template<class T>
inline const T *mithep::OwnArray<T,N>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
template<class T>
inline T *mithep::OwnArray<T,N>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//-------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
template<class T>
void mithep::OwnArray<T,N>::Streamer(TBuffer &b)
{
   // Stream all objects in the array to or from the I/O buffer.

#if 0
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
    //b.CheckByteCount(sv, cv, OwnArray::IsA());
  } else { /*writing*/
    //UInt_t cv;
    //cv = b.WriteVersion(OwnArray::IsA(), kTRUE);
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
#endif
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
inline T &mithep::OwnArray<T,N>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

//  return static_cast<T*>(GetObject(idx));
}

//--------------------------------------------------------------------------------------------------
template<class T, UShort_t N>
inline const T %mithep::OwnArray<T,N>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

//  return static_cast<const T*>(GetObject(idx));
}
#endif
