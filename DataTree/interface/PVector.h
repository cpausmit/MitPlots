// $Id: PVector.h,v 1.2 2008/06/03 10:04:27 loizides Exp $

#ifndef DATATREE_PVECTOR_H
#define DATATREE_PVECTOR_H
 
#include <vector>
#include "MitAna/DataTree/interface/Collection.h"

//--------------------------------------------------------------------------------------------------
//
// PVector
//
// Implementation of Collection interface using std:vector class
// for pointers to objects. Persistency not tested, like to not
// work, ask Constantin for a solution.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  template<class ArrayElement>
  class PVector : public Collection<ArrayElement>
  {
    public:
      PVector(UInt_t rsv=0) : fV(0) { fV.reserve(rsv); }
      PVector(std::vector<ArrayElement> &v) : fV(v) {}
      ~PVector() { Delete(); }

      void                             Add(const ArrayElement &ae)          { fV.push_back(ae); }
      void                             Add(const ArrayElement *ae)          { fV.push_back(*ae); }
      ArrayElement                    *At(const UInt_t idx)                 { return &fV.at(idx); }
      const ArrayElement              *At(const UInt_t idx)           const { return &fV.at(idx); }
      void                             Delete();
      UInt_t                           GetEntries()                   const { return fV.size(); }
      void                             Reset()                              { Delete(); }
      ArrayElement                    &Ref(const UInt_t idx)                { return fV.at(idx); }
      const ArrayElement              &Ref(const UInt_t idx)          const { return fV.at(idx); }
      void                             Trim()                               { fV.resize(fV.size()); }
      ArrayElement                    *UncheckedAt(const UInt_t idx)        { return &fV[idx]; }
      const ArrayElement              *UncheckedAt(const UInt_t idx)  const { return &fV[idx]; }
      const std::vector<ArrayElement> &Vect() const { return fV; }
      std::vector<ArrayElement>       &Vect()       { return fV; }

      ArrayElement                    *operator[](const UInt_t idx)         { return &fV.at(idx); }
      const ArrayElement              *operator[](const UInt_t idx)   const { return &fV.at(idx); }

    protected:
      std::vector<ArrayElement>        fV;      //std::vector

      ClassDefT(PVector, 1) // Wrapper around std::vector class
  };

} /*namespace mithep*/

//__________________________________________________________________________________________________
template<class ArrayElement>
inline void mithep::PVector<ArrayElement>::Delete()
{
  for (UInt_t i=0;i<GetEntries();++i) {
    delete fV.at(i);
  }
  fV.clear();
}

#endif /*DATATREE_PVECTOR_H*/
