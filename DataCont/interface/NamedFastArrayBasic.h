//--------------------------------------------------------------------------------------------------
// NamedFastArrayBasic
//
// FastArrayBasic with a name so that it can be published / written to tree.
//
// Authors: Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_NAMEDFASTARRAYBASIC_H
#define MITANA_DATACONT_NAMEDFASTARRAYBASIC_H

#include "MitAna/DataCont/interface/FastArrayBasic.h"

namespace mithep {
  template<class ArrayElement, Bool_t IsDouble32 = kFALSE>
  class NamedFastArrayBasic : public FastArrayBasic<ArrayElement, IsDouble32> {
  public:
    NamedFastArrayBasic(UInt_t size = 0, char const* name = 0);
  
    char const* GetName() const override { return fName; }
    void SetName(char const* n) { fName = n; }

  protected:
    TString fName;

    ClassDef(NamedFastArrayBasic, 1)
  };
}

template<class ArrayElement, Bool_t IsDouble32>
mithep::NamedFastArrayBasic<ArrayElement, IsDouble32>::NamedFastArrayBasic(UInt_t size/* = 0*/, char const* name/* = 0*/) :
  FastArrayBasic<ArrayElement, IsDouble32>(size),
  fName(name)
{
}

template<class ArrayElement, Bool_t IsDouble32>
void
mithep::NamedFastArrayBasic<ArrayElement, IsDouble32>::Streamer(TBuffer& b)
{
  if (b.IsReading())
    b >> fName;
  else
    b << fName;

  FastArrayBasic<ArrayElement, IsDouble32>::Streamer(b);
}

#endif
