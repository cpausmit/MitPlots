//--------------------------------------------------------------------------------------------------
// $Id: PileupEnergyDensity.h,v 1.1 2011/03/01 14:23:05 mzanetti Exp $
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
    PileupEnergyDensity() : fRho(0), fRhoHighEta(0) {}
    PileupEnergyDensity(Double_t r) : fRho(r), fRhoHighEta(0)  {}
    PileupEnergyDensity(Double_t r, Double_t rHighEta) : fRho(r), fRhoHighEta(rHighEta)  {}
    
    Double_t  Rho()  const { return fRho; }
    Double_t  RhoHighEta()  const { return fRhoHighEta; }
    
    virtual PileupEnergyDensity  *MakeCopy()                 const { return new PileupEnergyDensity(*this);   }
    
    void      SetRho(Double_t r)   { fRho = r; }
    void      SetRhoHighEta(Double_t r)   { fRhoHighEta = r; }
    
  protected:
    Double32_t          fRho;      //rho from fastjet algo
    Double32_t          fRhoHighEta;      //rho from fastjet algo
    
    ClassDef(PileupEnergyDensity, 1) // Pileup Energy Density class
      };
}
#endif
