//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.3 2008/07/16 10:00:58 bendavid Exp $
//
// CaloMet
//
// Details to be worked out...
//
// Authors: K.Sung
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_CALOMET_H
#define DATATREE_CALOMET_H

#include "MitAna/DataTree/interface/Met.h"

namespace mithep
{
  class CaloMet : public Met
  {
    public:
      CaloMet() : Met(0,0) {}
      CaloMet(Double_t mex, Double_t mey) : Met(mex,mey) {}
      ~CaloMet() {}
      
      Double_t    MaxEtInEmTowers()    const { return fMaxEtInEmTowers; }
      Double_t    MaxEtInHadTowers()   const { return fMaxEtInHadTowers; }
      Double_t    EtFractionHadronic() const { return fEtFractionHadronic; }
      Double_t    EmEtFraction()       const { return fEmEtFraction; }
      Double_t    HadEtInHB()          const { return fHadEtInHB; }
      Double_t    HadEtInHO()          const { return fHadEtInHO; } 
      Double_t    HadEtInHE()          const { return fHadEtInHE; }
      Double_t    HadEtInHF()          const { return fHadEtInHF; }
      Double_t    EmEtInEB()           const { return fEmEtInEB; }
      Double_t    EmEtInEE()           const { return fEmEtInEE; }
      Double_t    EmEtInHF()           const { return fEmEtInHF; }
      Double_t    MetSignificance()    const { return fMetSignificance; }
      Double_t    CaloSumEtInpHF()     const { return fCaloSumEtInpHF; }
      Double_t    CaloSumEtInmHF()     const { return fCaloSumEtInmHF; }      
      Double_t    CaloMetInpHF()       const { return fCaloMetInpHF; }
      Double_t    CaloMetInmHF()       const { return fCaloMetInmHF; }
      Double_t    CaloMetPhiInpHF()    const { return fCaloMetPhiInpHF; }
      Double_t    CaloMetPhiInmHF()    const { return fCaloMetPhiInmHF; }
      
      void        SetMaxEtInEmTowers(Double_t x)    { fMaxEtInEmTowers = x; }
      void        SetMaxEtInHadTowers(Double_t x)   { fMaxEtInHadTowers = x; }
      void        SetEtFractionHadronic(Double_t x) { fEtFractionHadronic = x; }
      void        SetEmEtFraction(Double_t x)       { fEmEtFraction = x; }
      void        SetHadEtInHB(Double_t x)          { fHadEtInHB = x; }
      void        SetHadEtInHO(Double_t x)          { fHadEtInHO = x; }
      void        SetHadEtInHE(Double_t x)          { fHadEtInHE = x; }
      void        SetHadEtInHF(Double_t x)          { fHadEtInHF = x; }
      void        SetEmEtInEB(Double_t x)           { fEmEtInEB = x; }
      void        SetEmEtInEE(Double_t x)           { fEmEtInEE = x; }
      void        SetEmEtInHF(Double_t x)           { fEmEtInHF = x; }
      void        SetMetSignificance(Double_t x)    { fMetSignificance = x; }
      void        SetCaloSumEtInpHF(Double_t x)     { fCaloSumEtInpHF = x; }
      void        SetCaloSumEtInmHF(Double_t x)     { fCaloSumEtInmHF = x; }
      void        SetCaloMetInpHF(Double_t x)       { fCaloMetInpHF = x; }
      void        SetCaloMetInmHF(Double_t x)       { fCaloMetInmHF = x; }
      void        SetCaloMetPhiInpHF(Double_t x)    { fCaloMetPhiInpHF = x; }
      void        SetCaloMetPhiInmHF(Double_t x)    { fCaloMetPhiInmHF = x; }
      
    protected:
      Double_t    fMaxEtInEmTowers;       // max ET deposited in ECAL towers
      Double_t    fMaxEtInHadTowers;      // max ET deposited in HCAL towers
      Double_t    fEtFractionHadronic;    // event hadronic scaler ET fraction
      Double_t    fEmEtFraction;          // event electromagnetic scalar ET fraction
      Double_t    fHadEtInHB;             // event hadronic scalar ET in HB
      Double_t    fHadEtInHO;             // event hadronic scalar ET in HO
      Double_t    fHadEtInHE;             // event hadronic scalar ET in HE
      Double_t    fHadEtInHF;             // event hadronic scalar ET in HF
      Double_t    fEmEtInEB;              // event electromagnetic scalar ET in EB
      Double_t    fEmEtInEE;              // event electromagnetic scalar ET in EE
      Double_t    fEmEtInHF;              // event electromagnetic scalar ET from HF
      Double_t    fMetSignificance;       // MET Significance = MET / sqrt(SumET) 
      Double_t    fCaloSumEtInpHF;        // SumET in HF+
      Double_t    fCaloSumEtInmHF;        // SumET in HF-
      Double_t    fCaloMetInpHF;          // MET in HF+
      Double_t    fCaloMetInmHF;          // MET in HF-
      Double_t    fCaloMetPhiInpHF;       // MET-phi in HF+
      Double_t    fCaloMetPhiInmHF;       // MET-phi in HF-
  
    ClassDef(CaloMet, 1) // Missing Et from calorimeter towers class
  };
}

#endif
