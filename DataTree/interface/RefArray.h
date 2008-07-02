//--------------------------------------------------------------------------------------------------
// $Id: RefArray.h,v 1.3 2008/07/01 08:52:01 loizides Exp $
//
// RefArray
//
// Wrapper for a TClonesArray with TRefs to TObjects or derived objects.
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

      void                 Add(ArrayElement *ae);
      const std::vector<TRef>  &Arr()                                   const { return fV; }
      ArrayElement        *At(UInt_t idx);
      const ArrayElement  *At(UInt_t idx)                          const;
      UInt_t               GetEntries()                            const { return fV.size(); }
      Bool_t               IsOwner()                               const { return kTRUE; }
      void                 Reset()                                       { fV.clear(); }
      void                 Trim()                                        { fV.resize(fV.size());}
      ArrayElement        *UncheckedAt(UInt_t idx);                 
      const ArrayElement  *UncheckedAt(UInt_t idx)                 const;

      ArrayElement        *operator[](UInt_t idx);
      const ArrayElement  *operator[](UInt_t idx)                  const;

    protected:
      std::vector<TRef>    fV;        //vector for storage
      UInt_t               fNumEntries;   //number of entries in the array

    private:
      RefArray(const RefArray &a);

    ClassDefT(RefArray,1) // Wrapper around TClonesArray class to hold TRef object pointers
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefArray<ArrayElement>::RefArray(const char *name, Int_t size)
{
   // Default constructor.

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
