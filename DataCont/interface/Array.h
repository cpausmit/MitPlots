//--------------------------------------------------------------------------------------------------
// $Id: Array.h,v 1.13 2008/07/14 20:55:19 loizides Exp $
//
// Array
//
// Implementation of Collection interface using TClonesArray class. 
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_ARRAY_H
#define DATATREE_ARRAY_H

#include <TClonesArray.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class Array : public Collection<ArrayElement> 
  {
    public:
      Array(UInt_t size=0, const char *name=0);
      ~Array() {}

      ArrayElement        *AddNew();
      ArrayElement        *Allocate();
      const TClonesArray  &Arr()                                const { return fArray; }
      TClonesArray        &Arr()                                      { return fArray; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                       const;
      void                 Clear(Option_t */*opt*/="")                { fArray.~TClonesArray(); }
      UInt_t               Entries()                            const { return fNumEntries; }
      UInt_t               GetEntries()                         const { return fNumEntries; }
      const char          *GetName()                            const { return fArray.GetName(); }
      Bool_t               IsOwner()                            const { return kTRUE; }
      TIterator           *Iterator(Bool_t dir = kIterForward)  const;
      Bool_t               MustClear()                          const { return this->TestBit(14); }
      Bool_t               MustDelete()                         const { return this->TestBit(15); }
      void                 Reset();
      void                 Trim()                                     { fArray.Compress(); }
      void                 SetMustClearBit()                          { this->SetBit(14); }
      void                 SetMustDeleteBit()                         { this->SetBit(15); }
      void                 SetName(const char *name)                  { fArray.SetName(name); }
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)              const;

      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)               const;

    protected:
      TClonesArray         fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      Array(const Array &a);

    ClassDefT(Array,1) // Wrapper around TClonesArray class
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::Array<ArrayElement>::Array(UInt_t size, const char *name) : 
  fArray(ArrayElement::Class_Name(),size), 
  fNumEntries(0)
{
   // Default constructor.

  fArray.BypassStreamer(kTRUE);

  if (name) 
    fArray.SetName(name);

  ArrayElement test;
  if (test.MustClear())
    SetMustClearBit();
  if (test.MustDelete())
    SetMustDeleteBit();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::AddNew()
{
  // Add new entry and return pointer to it.

  return new(Allocate()) ArrayElement(); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::Allocate()
{
   // Allocate a slot in the array, *only* to be used in placement new operator.
   
   return static_cast<ArrayElement*>(fArray[fNumEntries++]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));

  ArrayElement tmp;
  Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
        idx, fNumEntries, this->GetName(), tmp.GetName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::Array<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));

  ArrayElement tmp;
  Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
        idx, fNumEntries, this->GetName(), tmp.GetName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TIterator *mithep::Array<ArrayElement>::Iterator(Bool_t dir) const 
{ 
  // Return ROOT collection iterator.

  return fArray.MakeIterator(dir); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::Array<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::Reset()
{
  // ROOT implementation for clearing the array.

  if (this->MustDelete())
    fArray.Delete();   //will call destructor for every element
  else if (this->MustClear())
    fArray.Clear("C"); //will call clear for every element
  else 
    fArray.Clear();

  fNumEntries = 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::Array<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));
}
#endif
