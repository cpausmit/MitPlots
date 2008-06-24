//--------------------------------------------------------------------------------------------------
// $Id: Array.h,v 1.2 2008/06/18 19:08:13 loizides Exp $
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
#include "MitAna/DataTree/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class Array : public Collection<ArrayElement> {
    public:
      Array(const char *name=0, Int_t size=0);
      ~Array() {}

      ArrayElement        *Add();
      void                 AddCopy(const ArrayElement &ae);
      void                 AddCopy(const ArrayElement *ae);
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
      ArrayElement        *Allocate();
      void                 Clear(Option_t *opt="");

      TClonesArray         fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      Array(const Array &a);

    ClassDefT(Array,1) // Wrapper around TClonesArray class
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::Array<ArrayElement>::Array(const char *name, Int_t size) : 
  fArray(ArrayElement::Class_Name(),size), 
  fNumEntries(0)
{
   // Default constructor.

  fArray.BypassStreamer(kTRUE);

  if (name) 
    fArray.SetName(name);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::Add()
{
  // Add new entry and return pointer to it.

  return new(Allocate()) ArrayElement(); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::Allocate()
{
   // Allocate a slot in the array, *only* to be used in
   // placement new by derived classes.
   
   return static_cast<ArrayElement*>(fArray[fNumEntries++]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::AddCopy(const ArrayElement &ae)
{
  // Add new entry (by using copy constructor).

  new(Allocate()) ArrayElement(ae); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::AddCopy(const ArrayElement *ae)
{
  // Add new entry (by using copy constructor).

  new(Allocate()) ArrayElement(*ae); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::Array<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), Array::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::Array<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), Array::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::Clear(Option_t *opt)
{
   // Default implementation for clearing the array.

   fArray.Clear(opt); //TClonesArray with opt=="C" will call clear for every entry
                      //(TObjArray would delete objects if owner)

   fNumEntries = 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::Array<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::Array<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::Array<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.
  return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::Array<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));
}
#endif
