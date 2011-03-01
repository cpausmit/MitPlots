//--------------------------------------------------------------------------------------------------
// $Id: PileupEnergyDensity.h,v 1.5 2009/11/30 13:42:40 bendavid Exp $
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
    PileupEnergyDensity() : fRho(0) {}
    PileupEnergyDensity(Double_t r) : fRho(r) {}
    
    Double_t  Rho()  const { return fRho; }
    
    virtual PileupEnergyDensity  *MakeCopy()                 const { return new PileupEnergyDensity(*this);   }
    
    void      SetRho(Double_t r)   { fRho = r; }
    
  protected:
    Double32_t          fRho;      //rho from fastjet algo
    
    ClassDef(PileupEnergyDensity, 1) // Pileup Energy Density class
      };
}
#endif
