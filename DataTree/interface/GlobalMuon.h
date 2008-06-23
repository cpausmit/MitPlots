//--------------------------------------------------------------------------------------------------
// $Id: GlobalMuon.h,v 1.2 2008/06/18 19:08:14 loizides Exp $
//
// GlobalMuon
//
// Global muons are muons which have been reconstructed using a combination of as many as possible
// detector elements.
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_GLOBALMUON_H
#define DATATREE_GLOBALMUON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

namespace mithep 
{
  class GlobalMuon : public Lepton
  {
    public:
      GlobalMuon() {}
      GlobalMuon(Double_t px, Double_t py, Double_t pz, Double_t e) : Lepton(px,py,pz,e) {}
      ~GlobalMuon() {}
      
      ClassDef(GlobalMuon,1)
  };
}
#endif
