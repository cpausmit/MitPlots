//--------------------------------------------------------------------------------------------------
// Array
//
// Implementation of Collection interface using TClonesArray class. 
//
// Authors: L.DiMatteo, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_ARRAY_H
#define MITANA_DATACONT_ARRAY_H

#include <TClonesArray.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class Array : public Collection<ArrayElement> 
  {
    public:
      Array(UInt_t size=0, const char *name=0);

      ArrayElement        *AddNew();
      ArrayElement        *Allocate();
      const TClonesArray  &Arr()                                const { return fArray; }
      TClonesArray        &Arr()                                      { return fArray; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                       const;
      void                 Clear(Option_t */*opt*/="")                { fArray.~TClonesArray(); }
      void                 Delete(Option_t *opt="");
      UInt_t               Entries()                            const { return fNumEntries; }
      UInt_t               GetEntries()                         const { return fNumEntries; }
      const char          *GetName()                            const { return fArray.GetName(); }
      UInt_t               GetSize()                            const { return fArray.GetSize(); }
      Bool_t               HasObject(const ArrayElement *obj)   const;
      Bool_t               IsOwner()                            const { return kTRUE; }
      TIterator           *Iterator(Bool_t dir = kIterForward)  const;
      Bool_t               MustClear()                          const { return this->TestBit(14); }
      Bool_t               MustDelete()                         const { return this->TestBit(15); }
      TObject             *ObjAt(UInt_t idx);
      const TObject       *ObjAt(UInt_t idx)                    const;
      void                 Print(Option_t *opt="")              const;
      void                 Reset();
      void                 SetMustClearBit()                          { this->SetBit(14); }
      void                 SetMustDeleteBit()                         { this->SetBit(15); }
      void                 SetName(const char *name)                  { fArray.SetName(name); }
      void                 Sort()                                     { fArray.Sort(); }
      void                 Trim()                                     { fArray.Compress(); }
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)              const;
      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)               const;

    protected:
      TClonesArray         fArray;        //array for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      Array(const Array &a);

    ClassDef(Array, 1) // Wrapper around TClonesArray class
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
   
  BaseCollection::Clear();
  return static_cast<ArrayElement*>(fArray[fNumEntries++]);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::Array<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<ArrayElement*>(fArray.UncheckedAt(idx));

  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::Array<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fNumEntries)
    return static_cast<const ArrayElement*>(fArray.UncheckedAt(idx));

  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
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
inline Bool_t mithep::Array<ArrayElement>::HasObject(const ArrayElement *obj) const
{
  // Check whether object is in array.

  return fArray.FindObject(obj);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::Array<ArrayElement>::Print(Option_t *opt) const
{
  // Print out elements of array.

  printf("%s: Contains %d (out of %d) objs of name %s\n",
         GetName(), Entries(), GetSize(), ArrayElement::Class_Name());

  if (opt && opt[0]=='l') {
    const UInt_t N = Entries();
    for (UInt_t i=0; i<N; ++i) {
      printf("%4d: ",i);
      At(i)->Print(opt);
    }
  }
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline TObject *mithep::Array<ArrayElement>::ObjAt(UInt_t idx)
{
  // Return object at given index.

  if (idx<fNumEntries)
    return fArray.UncheckedAt(idx);

  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
const TObject *mithep::Array<ArrayElement>::ObjAt(UInt_t idx) const
{
  // Return object at given index.

  if (idx<fNumEntries)
    return static_cast<const TObject*>(fArray.UncheckedAt(idx));

  TObject::Fatal("At","Index too large: (%u < %u violated) for %s containing %s",
                 idx, fNumEntries, GetName(), ArrayElement::Class_Name()); 
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::Reset()
{
  // ROOT-like implementation for clearing the array.

  if (MustDelete())
    fArray.Delete();   //will call destructor for every element
  else if (MustClear())
    fArray.Clear("C"); //will call clear for every element
  else 
    fArray.Clear();

  fNumEntries = 0;
  BaseCollection::Clear();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Array<ArrayElement>::Delete(Option_t *opt)
{
  // ROOT implementation for clearing the array, deleting all objects inside

  fArray.Delete();   // will call destructor for every element
  fNumEntries = 0;
  BaseCollection::Clear();

  if (opt && opt[0] != 0) {
    TObject::Warning("Delete",
		     "Delete option for Array class not implemented, using default implementation.");     
  }
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
#endif
