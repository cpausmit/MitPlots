// $Id: Electron.h,v 1.3 2008/06/09 11:47:03 paus Exp $

#ifndef DATATREE_ELECTRON_H
#define DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

//--------------------------------------------------------------------------------------------------
//
// Electron
//
// Details to be worked out...
//
// Authors: C.Loizides, J. Bendavid
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Electron : public Lepton
  {
    public:
      Electron() {}
      Electron(Double_t px, Double_t py, Double_t pz, Double_t e) : Lepton(px,py,pz,e) {}
      ~Electron() {}
      
      ClassDef(Electron, 1) // Muon class
  };
}
#endif
