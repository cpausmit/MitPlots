// $Id: Vector.h,v 1.3 2008/06/01 10:03:39 loizides Exp $

#ifndef DATATREE_VECTOR_H
#define DATATREE_VECTOR_H
 
#include <vector>
#include "MitAna/DataTree/interface/Collection.h"

//--------------------------------------------------------------------------------------------------
//
// Vector
//
// Implementation of Collection interface using std:vector class. 
// Note, in case you one to store pointers to allocated objects on heap, 
// you should use the class PVector.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  template<class ArrayElement>
  class Vector : public Collection<ArrayElement>
  {
    public:
      Vector(UInt_t rsv=0) : fV(0) { fV.reserve(rsv); }
      Vector(std::vector<ArrayElement> &v) : fV(v) {}
      ~Vector() { fV.clear(); }

      void                             Add(const ArrayElement &ae)          { fV.push_back(ae); }
      ArrayElement                    &At(const UInt_t idx)                 { return fV.at(idx); }
      const ArrayElement              &At(const UInt_t idx)           const { return fV.at(idx); }
      UInt_t                           GetEntries()                   const { return fV.size(); }
      void                             Reset()                              { fV.clear(); }
      void                             Trim()                               { fV.resize(fV.size()); }
      ArrayElement                    &UncheckedAt(const UInt_t idx)        { return fV[idx]; }
      const ArrayElement              &UncheckedAt(const UInt_t idx)  const { return fV[idx]; }
      const std::vector<ArrayElement> &Vect() const { return fV; }
      std::vector<ArrayElement>       &Vect()       { return fV; }

      ArrayElement                    &operator[](const UInt_t idx)         { return fV.at(idx); }
      const ArrayElement              &operator[](const UInt_t idx)   const { return fV.at(idx); }

    protected:
      std::vector<ArrayElement>        fV;      //std::vector

      ClassDefT(Vector, 1) // Wrapper around std::vector class
  };

} /*namespace mithep*/

#endif /*DATATREE_VECTOR_H*/
