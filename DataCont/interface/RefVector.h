//--------------------------------------------------------------------------------------------------
// $Id: RefVector.h,v 1.3 2008/10/23 18:22:27 loizides Exp $
//
// RefArray
//
// Wrapper for a std::vector with TRefs to TObjects or derived objects.
//
// Authors: C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_REFVECTOR_H
#define MITANA_DATACONT_REFVECTOR_H

#include <vector>
#include <TRef.h>
#include "MitAna/DataCont/interface/Collection.h"

namespace mithep 
{
  template<class ArrayElement>
  class RefVector : public Collection<ArrayElement> 
  {
    public:
      RefVector(UInt_t rsv=0);
      ~RefVector() {}

      void                      Add(ArrayElement *ae);
      ArrayElement             *At(UInt_t idx);
      const ArrayElement       *At(UInt_t idx)                    const;
      void                      Clear(Option_t */*opt*/="")             { fV.~vector<TRef>(); }
      UInt_t                    Entries()                         const { return fV.size(); }
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
      std::vector<TRef>         fV; //vector for storage

    private:
      RefVector(const RefVector &a);

    ClassDefT(RefVector,1) // Wrapper around std::vector class to hold TRef object pointers
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline mithep::RefVector<ArrayElement>::RefVector(UInt_t rsv) : 
  fV(0)
{
   // Default constructor.

  fV.reserve(rsv);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefVector<ArrayElement>::Add(ArrayElement *ae)
{
  // Add new reference to object.

  fV.push_back(TRef(ae));
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefVector<ArrayElement>::At(UInt_t idx)
{
  // Return entry at given index.

  if (idx<fV.size())
    return static_cast<const ArrayElement*>(fV[idx].GetObject());

  TObject::Fatal("At", "Index out of range: %ud < %ud", idx, fV.size());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefVector<ArrayElement>::At(UInt_t idx) const
{
  // Return entry at given index.

  if (idx<fV.size())
     return static_cast<const ArrayElement*>(fV[idx].GetObject());

  TObject::Fatal("At", "Index out of range: %ud < %ud", idx, fV.size());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline void mithep::RefVector<ArrayElement>::Trim()
{
  // Trim vector to minimal needed size.

  std::vector<TRef>(fV).swap(fV);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefVector<ArrayElement>::UncheckedAt(UInt_t idx)
{
  // Return entry at given index.

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefVector<ArrayElement>::UncheckedAt(UInt_t idx) const
{
  // Return entry at given index.

    return static_cast<const ArrayElement*>(fV[idx].GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline const ArrayElement *mithep::RefVector<ArrayElement>::operator[](UInt_t idx) const
{
  // Return entry at given index.

  return At(idx);
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
inline ArrayElement *mithep::RefVector<ArrayElement>::operator[](UInt_t idx)
{
  // Return entry at given index.

  return At(idx);
}
#endif
