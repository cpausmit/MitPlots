//--------------------------------------------------------------------------------------------------
// $Id: PileupEnergyDensity.h,v 1.4 2011/10/08 17:53:57 bendavid Exp $
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
    PileupEnergyDensity() :
      fRho                             (0),
      fRhoHighEta                      (0),
      fRhoRandom                       (0),
      fRhoRandomLowEta                 (0),
      fRhoFixedGridAll                 (0),
      fRhoFixedGridFastjetAll          (0),
      fRhoKt6CaloJets                  (0),
      fRhoKt6CaloJetsCentral           (0),
      fRhoKt6PFJets                    (0),
      fRhoKt6PFJetsCentralChargedPileUp(0),
      fRhoKt6PFJetsCentralNeutral      (0),
      fRhoKt6PFJetsCentralNeutralTight (0)
        {}

    Double_t  RhoDefault()                       const { return fRhoRandom; }

    Double_t  Rho()                              const { return fRho; }
    Double_t  RhoHighEta()                       const { return fRho; }
    Double_t  RhoLowEta()                        const { return fRhoHighEta; }
    Double_t  RhoRandom()                        const { return fRhoRandom; }
    Double_t  RhoRandomLowEta()                  const { return fRhoRandomLowEta; }
    Double_t  RhoFixedGridAll()                  const { return fRhoFixedGridAll; }
    Double_t  RhoFixedGridFastjetAll()           const { return fRhoFixedGridFastjetAll; }
    Double_t  RhoKt6CaloJets()                   const { return fRhoKt6CaloJets; }
    Double_t  RhoKt6CaloJetsCentral()            const { return fRhoKt6CaloJetsCentral; }
    Double_t  RhoKt6PFJets()                     const { return fRhoKt6PFJets; }
    Double_t  RhoKt6PFJetsCentralChargedPileUp() const { return fRhoKt6PFJetsCentralChargedPileUp; }
    Double_t  RhoKt6PFJetsCentralNeutral()       const { return fRhoKt6PFJetsCentralNeutral; }
    Double_t  RhoKt6PFJetsCentralNeutralTight()  const { return fRhoKt6PFJetsCentralNeutralTight; }
    
    virtual PileupEnergyDensity *MakeCopy()      const { return new PileupEnergyDensity(*this);   }
    
    void      SetRho                             (Double_t r) { fRho = r; }
    void      SetRhoLowEta                       (Double_t r) { fRhoHighEta = r; }
    void      SetRhoRandom                       (Double_t r) { fRhoRandom = r; }
    void      SetRhoRandomLowEta                 (Double_t r) { fRhoRandomLowEta = r; }
    void      SetRhoFixedGridAll                 (Double_t r) { fRhoFixedGridAll = r; }
    void      SetRhoFixedGridFastjetAll          (Double_t r) { fRhoFixedGridFastjetAll = r; }
    void      SetRhoKt6CaloJets                  (Double_t r) { fRhoKt6CaloJets = r; }
    void      SetRhoKt6CaloJetsCentral           (Double_t r) { fRhoKt6CaloJetsCentral = r; }
    void      SetRhoKt6PFJets                    (Double_t r) { fRhoKt6PFJets = r; }
    void      SetRhoKt6PFJetsCentralChargedPileUp(Double_t r) { fRhoKt6PFJetsCentralChargedPileUp = r; }
    void      SetRhoKt6PFJetsCentralNeutral      (Double_t r) { fRhoKt6PFJetsCentralNeutral = r; }
    void      SetRhoKt6PFJetsCentralNeutralTight (Double_t r) { fRhoKt6PFJetsCentralNeutralTight = r; }
    
    
  protected:
    Double32_t          fRho;                    //rho from various fastjet algos
    Double32_t          fRhoHighEta;             //  ..
    Double32_t          fRhoRandom;
    Double32_t          fRhoRandomLowEta;
    Double32_t          fRhoFixedGridAll;
    Double32_t          fRhoFixedGridFastjetAll;
    Double32_t          fRhoKt6CaloJets;
    Double32_t          fRhoKt6CaloJetsCentral;
    Double32_t          fRhoKt6PFJets;
    Double32_t          fRhoKt6PFJetsCentralChargedPileUp;
    Double32_t          fRhoKt6PFJetsCentralNeutral;
    Double32_t          fRhoKt6PFJetsCentralNeutralTight;

    ClassDef(PileupEnergyDensity, 2)             // Pileup Energy Density class
  };
}
#endif
