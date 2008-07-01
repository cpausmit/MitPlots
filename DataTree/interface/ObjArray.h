//--------------------------------------------------------------------------------------------------
// $Id: ObjArray.h,v 1.4 2008/06/30 16:54:11 loizides Exp $
//
// ObjArray
//
// Implementation of Collection interface using TObjArray class. 
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_OBJARRAY_H
#define DATATREE_OBJARRAY_H

#include <TObjArray.h>
#include "MitAna/DataTree/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class ObjArray : public Collection<ArrayElement> 
  {
    public:
      ObjArray(const char *name=0, Int_t size=0);
      ~ObjArray() {}

      void                 Add(ArrayElement *ae);
      const TObjArray     &Arr()                                   const { return fArray; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                          const;
      UInt_t               GetEntries()                            const { return fNumEntries; }
      const char*          GetName()                               const { return fArray.GetName(); }
      Bool_t               IsOwner()                               const { return fArray.IsOwner(); }
      TIterator           *MakeIterator(Bool_t dir = kIterForward) const { return fArray.MakeIterator(dir); }
      void                 Reset()                                       { Clear(); }
      void                 Trim()                                        { fArray.Compress();}
      void                 SetName(const char* name)                     { fArray.SetName(name); }
      void                 SetOwner(Bool_t o)                            { fArray.SetOwner(o); }
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)                 const;

      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)                  const;

    protected:
      void                 AddLast(ArrayElement *e);
      void                 AddLast(const ArrayElement *e);
      void                 Clear(Option_t *opt="");

      TObjArray            fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      ObjArray(const ObjArray &a);

    ClassDefT(ObjArray,1) // Wrapper around TClonesArray class
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::ObjArray<ArrayElement>::ObjArray(const char *name, Int_t size) : 
  fArray(size), 
  fNumEntries(0)
{
   // Default constructor.

  if (name) 
    fArray.SetName(name);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Add(ArrayElement *ae)
{
  // Add new entry to array.

  AddLast(ae); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::AddLast(ArrayElement *e)
{
  // Add new entry at the end of array.

  fArray.AddLast(e); 
  fNumEntries++; 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::AddLast(const ArrayElement *e)
{ 
  // Add new entry at the end of array.

  AddLast(const_cast<ArrayElement*>(e)); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::ObjArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), ObjArray::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::ObjArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));

  Fatal("At","Index too large: (%ud < %ud violated) for %s with type %s",
        idx, fNumEntries, GetName(), ObjArray::ClassName()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Clear(Option_t *opt)
{
   // Default implementation for clearing the array.

   fArray.Clear(opt); //will delete objects if owner

   fNumEntries = 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::ObjArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::ObjArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::ObjArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::ObjArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));
}
#endif
