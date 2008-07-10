//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.6 2008/07/02 21:45:17 loizides Exp $
//
// RefArray
//
// Wrapper for a std::vector with TRefs to TObjects or derived objects.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_REFARRAY_H
#define DATATREE_REFARRAY_H

#include <vector>
#include <TRef.h>
#include "MitAna/DataTree/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class RefArray : public Collection<ArrayElement> 
  {
    public:
      RefArray(const char *name=0, Int_t size=0);
      ~RefArray() {}

      void                      Add(ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                    const;
      UInt_t                    GetEntries()                      const { return fV.size(); }
      Bool_t                    IsOwner()                         const { return kTRUE; }
      void                      Reset()                                 { fV.clear(); }
      void                      Trim()                                  { fV.resize(fV.size());}
      ArrayElement             *UncheckedAt(UInt_t idx);                 
      const ArrayElement       *UncheckedAt(UInt_t idx)           const;
      const std::vector<TRef>  &Vect()                            const { return fV; }

      ArrayElement             *operator[](UInt_t idx);
      const ArrayElement       *operator[](UInt_t idx)            const;

    protected:
      std::vector<TRef>         fV;            //vector for storage

    private:
      RefArray(const RefArray &a);

    ClassDefT(RefArray,1) // Wrapper around std::vector class to hold TRef object pointers
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefArray<ArrayElement>::RefArray(const char */*name*/, Int_t size) : 
  fV(0)
{
   // Default constructor.

  fV.reserve(size);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefArray<ArrayElement>::Add(ArrayElement *ae)
{
  // Add new reference to object.

  fV.push_back(TRef(ae));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement* mithep::RefArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fV.at(idx).GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::RefArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fV.at(idx).GetObject());
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

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement* mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}
#endif
