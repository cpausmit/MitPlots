//--------------------------------------------------------------------------------------------------
// $Id: Vector.h,v 1.8 2009/03/12 18:19:48 loizides Exp $
//
// Vector
//
// Implementation of Collection interface using std:vector class. 
//
// Note, in case you one to store pointers to allocated objects on heap, 
// you should use the class PVector.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_VECTOR_H
#define MITANA_DATACONT_VECTOR_H
 
#include <vector>
#include <Rtypes.h>
#include <TClass.h>
#include <TObject.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class Vector : public Collection<ArrayElement>
  {
    public:
      Vector(UInt_t rsv=0) : fV(0) { fV.reserve(rsv); }
      Vector(std::vector<ArrayElement> &v) : fV(v) {}

      void                             AddCopy(const ArrayElement &ae)     
                                         { BaseCollection::Clear(); fV.push_back(ae);  }
      void                             AddCopy(const ArrayElement *ae)     
                                         { BaseCollection::Clear(); fV.push_back(*ae); }
      ArrayElement                    *At(UInt_t idx)                      { return &fV.at(idx); }
      const ArrayElement              *At(UInt_t idx)                const { return &fV.at(idx); }
      void                             Clear(Option_t *opt="");
      UInt_t                           Entries()                     const { return fV.size(); }
      UInt_t                           GetEntries()                  const { return fV.size(); }
      UInt_t                           GetSize()                     const { return fV.capacity(); }
      Bool_t                           HasObject(const ArrayElement *obj) const;
      Bool_t                           IsOwner()                     const { return kTRUE; }
      TObject                         *ObjAt(UInt_t idx)                   { return &fV.at(idx); }
      const TObject                   *ObjAt(UInt_t idx)             const { return &fV.at(idx); }
      ArrayElement                    &Ref(UInt_t idx)                     { return fV.at(idx); }
      const ArrayElement              &Ref(UInt_t idx)               const { return fV.at(idx); }
      void                             Reset();
      void                             Trim();
      ArrayElement                    *UncheckedAt(UInt_t idx)             { return &fV[idx]; }
      const ArrayElement              *UncheckedAt(UInt_t idx)       const { return &fV[idx]; }
      const std::vector<ArrayElement> &Vect()                        const { return fV; }
      std::vector<ArrayElement>       &Vect()                              { return fV; }
      ArrayElement                    *operator[](UInt_t idx)              { return &fV.at(idx); }
      const ArrayElement              *operator[](UInt_t idx)        const { return &fV.at(idx); }

    protected:
      std::vector<ArrayElement>        fV; //std::vector

    private:
      Vector(const Vector &v);

    ClassDef(Vector, 1) // Wrapper around std::vector class
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Vector<ArrayElement>::Clear(Option_t */*opt*/)
{
  // Destruct container.

  using namespace std;
  fV.~vector<ArrayElement>();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline Bool_t mithep::Vector<ArrayElement>::HasObject(const ArrayElement *obj) const
{
  // Check whether object is in array, using the isEqual function for the comparison.

  const TObject *tobj = 0;
  if (TClass::GetClass(typeid(ArrayElement))->IsTObject())
    tobj = reinterpret_cast<const TObject*>(obj);

  for (UInt_t i=0; i<fV.size(); ++i) {
    if ( fV.at(i).IsEqual(obj) )
      return kTRUE;
  }
  
  return kFALSE;
}


//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Vector<ArrayElement>::Reset()
{
  // Reset container.

  fV.clear();
  BaseCollection::Clear();
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::Vector<ArrayElement>::Trim()
{
  // Trim vector to minimal needed size.

  std::vector<ArrayElement>(fV).swap(fV);
}
#endif
