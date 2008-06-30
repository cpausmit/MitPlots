//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.1 2008/06/30 13:09:21 loizides Exp $
//
// RefArray
//
// Wrapper for a TClonesArray with TRefs to TObjects or derived objects.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_REFARRAY_H
#define DATATREE_REFARRAY_H

#include <TClonesArray.h>
#include <TRef.h>
#include "MitAna/DataTree/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class RefArray : public Collection<ArrayElement> {
    public:
      RefArray(const char *name=0, Int_t size=0);
      ~RefArray() {}

      void                 Add(ArrayElement *ae);
      const TClonesArray  &Arr()                                   const { return fArray; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                          const;
      UInt_t               GetEntries()                            const { return fNumEntries; }
      const char*          GetName()                               const { return fArray.GetName(); }
      Bool_t               IsOwner()                               const { return kTRUE; }
      TIterator           *MakeIterator(Bool_t dir = kIterForward) const { return fArray.MakeIterator(dir); }
      void                 Reset()                                       { Clear(); }
      void                 Trim()                                        { fArray.Compress();}
      void                 SetName(const char* name)                     { fArray.SetName(name); }
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)                 const;

      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)                  const;

    protected:
      TRef                *Allocate();
      void                 Clear(Option_t *opt="");

      TClonesArray         fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      //RefArray(const RefArray &a);

    ClassDefT(RefArray,1) // Wrapper around TClonesArray class to hold TRef object pointers
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefArray<ArrayElement>::RefArray(const char *name, Int_t size) : 
  fArray("TRef",size), 
  fNumEntries(0)
{
   // Default constructor.

  fArray.BypassStreamer(kFALSE);

  if (name) 
    fArray.SetName(name);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefArray<ArrayElement>::Add(ArrayElement *ae)
{
  // Add new reference to object.

  new(Allocate()) TRef(ae); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TRef *mithep::RefArray<ArrayElement>::Allocate()
{
   // Allocate a slot in the array, *only* to be used in placement new operator.
   
   return static_cast<TRef*>(fArray[fNumEntries++]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::RefArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(static_cast<TRef*>(fArray.At(idx))->GetObject());

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), RefArray::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::RefArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(static_cast<TRef*>(fArray.At(idx))->GetObject());

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), RefArray::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefArray<ArrayElement>::Clear(Option_t *opt)
{
   // Default implementation for clearing the array.

   fArray.Clear(opt); //TClonesArray with opt=="C" will call clear for every entry
                      //(TObjArray would delete objects if owner)

   fNumEntries = 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::RefArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::RefArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(static_cast<TRef*>(fArray.At(idx))->GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(static_cast<TRef*>(fArray.At(idx))->GetObject());
}
#endif
