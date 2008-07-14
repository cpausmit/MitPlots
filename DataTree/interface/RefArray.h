//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.8 2008/07/13 08:33:26 loizides Exp $
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
      RefArray(UInt_t rsv=0);
      ~RefArray() {}

      void                      Add(ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                    const;
      void                      Clear(Option_t */*option*/="")    {   fV.~vector<TRef>();  }
      UInt_t                    GetEntries()                      const { return fV.size(); }
      Bool_t                    IsOwner()                         const { return kTRUE; }
      void                      Reset()                                 { fV.clear(); }
      void                      Trim();
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
inline mithep::RefArray<ArrayElement>::RefArray(UInt_t rsv) : 
  fV(0)
{
   // Default constructor.

  fV.reserve(rsv);
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
inline ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fV.at(idx).GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  return static_cast<const ArrayElement*>(fV.at(idx).GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefArray<ArrayElement>::Trim()
{
  // Trim vector to minimal needed size.

  std::vector<TRef>(fV).swap(fV);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefArray<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}
#endif
