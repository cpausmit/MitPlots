//--------------------------------------------------------------------------------------------------
// $Id: ObjArray.h,v 1.4 2008/10/23 18:21:57 loizides Exp $
//
// ObjArray
//
// Implementation of Collection interface using TObjArray class. 
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_OBJARRAY_H
#define MITANA_DATACONT_OBJARRAY_H

#include <TObjArray.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class ObjArray : public Collection<ArrayElement> 
  {
    public:
      ObjArray(UInt_t size=0, const char *name=0);
      ~ObjArray() {}

      void                 Add(ArrayElement *ae)                       { AddLast(ae); }
      void                 Add(const TCollection *col);
      const TObjArray     &Arr()                                 const { return fArray; }
      TObjArray           &Arr()                                       { return fArray; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                        const;
      void                 Clear(Option_t */*opt*/="")                 { fArray.~TObjArray(); }
      UInt_t               Entries()                             const { return fNumEntries; }
      UInt_t               GetEntries()                          const { return fNumEntries; }
      const char*          GetName()                             const { return fArray.GetName(); }
      UInt_t               GetSize()                            const { return fArray.GetSize(); }
      const ArrayElement  *Find(const char *name)                const;
      ArrayElement        *Find(const char *name);
      void                 Print(Option_t *opt="")              const;
      void                 Remove(UInt_t idx);
      void                 Remove(const char *name);
      void                 Remove(ArrayElement *ae);
      Bool_t               IsOwner()                             const { return fArray.IsOwner(); }
      TIterator           *Iterator(Bool_t dir = kIterForward)   const;
      void                 Reset();
      void                 SetName(const char* name)                   { fArray.SetName(name); }
      void                 SetOwner(Bool_t o)                          { fArray.SetOwner(o); }
      void                 Sort()                                      { fArray.Sort(); }
      void                 Trim()                                      { fArray.Compress();}
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)               const;
      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)                const;

    protected:
      void                 AddLast(ArrayElement *e);

      TObjArray            fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      ObjArray(const ObjArray &a);

    ClassDefT(ObjArray,1) // Wrapper around TClonesArray class
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::ObjArray<ArrayElement>::ObjArray(UInt_t size, const char *name) : 
  fArray(size), 
  fNumEntries(0)
{
   // Default constructor.

  if (name) 
    fArray.SetName(name);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Add(const TCollection *col)
{
  // Add objects from collection to array.

  if (!col)
    return;

  if (IsOwner()) {
    TObject::Error("Add","Can not add collection since IsOwner() returns kTRUE.");
    return;
  }

  TIterator *iter = col->MakeIterator();
  if (iter) {
    ArrayElement *to = dynamic_cast<ArrayElement *>(iter->Next());
    while (to) {
      AddLast(to);
      to = dynamic_cast<ArrayElement *>(iter->Next());
    }
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::AddLast(ArrayElement *ae)
{
  // Add new entry at the end of array.

  fArray.AddLast(ae); 
  fNumEntries++; 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::ObjArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));

  TObject::Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::ObjArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));

  TObject::Fatal("At","Index too large: (%ud < %ud violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::ObjArray<ArrayElement>::Find(const char *name) const
{
  // Find object by name.

  return static_cast<const ArrayElement*>(fArray.FindObject(name));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::ObjArray<ArrayElement>::Find(const char *name)
{
  // Find object by name.

  return static_cast<ArrayElement*>(fArray.FindObject(name));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Remove(UInt_t idx)
{
  // Remove object at given index from array. You probably want to call Trim as well.

  fArray.RemoveAt(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Remove(const char *name)
{
  // Remove object from array. You probably want to call Trim as well.

  TObject *obj = fArray.FindObject(name);
  if (obj) fArray.Remove(obj);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Remove(ArrayElement *ae)
{
  fArray.Remove(ae);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::ObjArray<ArrayElement>::Reset()
{
  // Default implementation for clearing the array.

  fArray.Clear(); //will delete objects if owner

  fNumEntries = 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TIterator *mithep::ObjArray<ArrayElement>::Iterator(Bool_t dir) const 
{ 
  // Return ROOT collection iterator.

  return fArray.MakeIterator(dir); 
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::ObjArray<ArrayElement>::Print(Option_t *opt) const
{
  // Print out elements of array.

  printf("%s: Contains %d (out of %d) objs of name %s\n",
         GetName(), GetEntries(), GetSize(), ArrayElement::Class_Name());

  const UInt_t N = GetEntries();
  for (UInt_t i=0; i<N; ++i) {
    printf("%4d: ",i);
    At(i)->Print(opt);
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::ObjArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::ObjArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::ObjArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::ObjArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
