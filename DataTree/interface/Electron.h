//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.5 2008/06/17 14:47:16 loizides Exp $
//
// Electron
//
// Details to be worked out...
//
// Authors: C.Loizides, J. Bendavid
//
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_ELECTRON_H
#define DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

namespace mithep 
{
  class Electron : public Lepton
  {
    public:
      Electron() {}
      Electron(Double_t px, Double_t py, Double_t pz, Double_t e) : Lepton(px,py,pz,e) {}
      ~Electron() {}
      
      ClassDef(Electron, 1) // Electron class
  };
}
#endif
