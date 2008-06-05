// $Id: Muon.h,v 1.1 2008/06/04 09:08:36 loizides Exp $

#ifndef DATATREE_ELECTRON_H
#define DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

//--------------------------------------------------------------------------------------------------
//
// Muon
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
      ~Electron() {}
      
      Electron(Double_t x, Double_t y, Double_t z, Double_t t) {fFourVector.SetXYZT(x,y,z,t);}
      
      ClassDef(Electron, 1) // Muon class
  };
   
} /*namespace mithep*/

#endif /*DATATREE_MUON_H*/
