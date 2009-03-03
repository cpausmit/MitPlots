//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.4 2008/11/05 10:46:48 bendavid Exp $
//
// Vect3C
//
// Implementation of our own ThreeVectorC32.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEDATA_VECT3C_H
#define MITANA_TREEDATA_VECT3C_H

#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Vect3C
  {
    public:
      Vect3C() : 
        fRho(0), fEta(0), fPhi(0) {}
      Vect3C(Double_t rho, Double_t eta, Double_t phi) : 
        fRho(rho), fEta(eta), fPhi(phi) {}
      Vect3C(const ThreeVector pos) :
        fRho(pos.Rho()), fEta(pos.Eta()), fPhi(pos.Phi()) {}
      Vect3C(const ThreeVectorC pos) :
        fRho(pos.Rho()), fEta(pos.Eta()), fPhi(pos.Phi()) {}

      Double_t            Eta()        const { return fEta; }
      Double_t            Phi()        const { return fPhi; }
      Double_t            Rho()        const { return fRho; }
      const ThreeVectorC  V()          const { return ThreeVectorC(fRho,fEta,fPhi); }
      void                SetXYZ(Double_t x, Double_t y, Double_t z);

    protected:
      Double32_t          fRho; //[0,0,12]
      Double32_t          fEta; //[0,0,10]
      Double32_t          fPhi; //[0,0,10]

    ClassDef(Vect3C, 1)
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Vect3C::SetXYZ(Double_t x, Double_t y, Double_t z)
{ 
  // Set four vector.

  ThreeVector tmp(x, y, z);
  fRho=tmp.Rho();
  fEta=tmp.Eta();
  fPhi=tmp.Phi();
}
#endif
