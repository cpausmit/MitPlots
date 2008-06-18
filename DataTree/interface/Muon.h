//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.5 2008/06/18 13:23:13 paus Exp $
//
// Muon
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_MUON_H
#define DATATREE_MUON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

namespace mithep 
{
  class Muon : public Lepton
  {
    public:
      Muon() {}
      Muon(Double_t px, Double_t py, Double_t pz, Double_t e) : Lepton(px,py,pz,e) {}
      ~Muon() {}
      
      ClassDef(Muon, 1) // Muon class
  };
}
#endif
