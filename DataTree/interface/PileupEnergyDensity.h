//--------------------------------------------------------------------------------------------------
// $Id: PileupEnergyDensity.h,v 1.2 2011/03/23 19:03:46 mzanetti Exp $
//
// PileupEnergyDensity
//
// Class to store the pu energy density as computed by fastjet algorithm 
//
// Authors: M. Zanetti
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PILEUPENERGYDENSITY_H
#define MITANA_DATATREE_PILEUPENERGYDENSITY_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class PileupEnergyDensity : public DataBase
  {
  public:
    PileupEnergyDensity() : fRho(0), fRhoHighEta(0), fRhoRandom(0), fRhoRandomLowEta(0) {}
    
    Double_t  Rho()  const { return fRho; }
    Double_t  RhoHighEta()  const { return fRho; }
    Double_t  RhoLowEta()  const { return fRhoHighEta; }
    Double_t  RhoRandom() const { return fRhoRandom; }
    Double_t  RhoRandomLowEta() const { return fRhoRandomLowEta; }
    
    virtual PileupEnergyDensity  *MakeCopy()                 const { return new PileupEnergyDensity(*this);   }
    
    void      SetRho(Double_t r)   { fRho = r; }
    void      SetRhoLowEta(Double_t r)   { fRhoHighEta = r; }
    void      SetRhoRandom(Double_t r)   { fRhoRandom = r; }
    void      SetRhoRandomLowEta(Double_t r)   { fRhoRandomLowEta = r; }

    
  protected:
    Double32_t          fRho;      //rho from fastjet algo
    Double32_t          fRhoHighEta;      //rho from fastjet algo
    Double32_t          fRhoRandom;      //rho from fastjet algo
    Double32_t          fRhoRandomLowEta; //rho from fastjet algo

    
    ClassDef(PileupEnergyDensity, 2) // Pileup Energy Density class
      };
}
#endif
