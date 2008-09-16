//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.5 2008/09/10 17:04:38 ksung Exp $
//
// Met
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MET_H
#define MITANA_DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() : fMex(0), fMey(0) {}
      Met(Double_t mex, Double_t mey) : fMex(mex), fMey(mey) {}
      ~Met() {}

      Double_t          Charge()             const { return 0; }
      Double_t		E()                  const { return Pt();}
      Double_t		Eta()                const { return Mom().Eta();}
      Double_t	 	Mass()               const { return TMath::Sqrt(Mom().M2()); }
      FourVector	Mom()                const { return FourVector(fMex,fMey,0,Pt()); }
      Double_t		Phi()                const { return TMath::ATan2(fMey,fMex); }
      Double_t		Pt()                 const { return TMath::Sqrt(fMex*fMex+fMey*fMey);}
      Double_t	 	Px()                 const { return fMex;}
      Double_t		Py()                 const { return fMey;}
      Double_t		Pz()                 const { return 0; }
      Double_t		P()                  const { return Pt(); }

      Double_t          SumEt()              const { return fSumEt; } 
      Double_t          MetSig()             const { return fMetSig; }    
      Double_t          E_longitudinal()     const { return fElongit; }
      
      const std::vector<Double_t>  Dmex()    const { return fDmex; }
      const std::vector<Double_t>  Dmey()    const { return fDmey; }
      const std::vector<Double_t>  DSumEt()  const { return fDSumEt; }
      
      Double_t          MaxEtInEmTowers()    const { return fMaxEtInEmTowers; }
      Double_t          MaxEtInHadTowers()   const { return fMaxEtInHadTowers; }
      Double_t          EtFractionHadronic() const { return fEtFractionHadronic; }
      Double_t          EmEtFraction()       const { return fEmEtFraction; }
      Double_t          HadEtInHB()          const { return fHadEtInHB; }
      Double_t          HadEtInHO()          const { return fHadEtInHO; } 
      Double_t          HadEtInHE()          const { return fHadEtInHE; }
      Double_t          HadEtInHF()          const { return fHadEtInHF; }
      Double_t          EmEtInEB()           const { return fEmEtInEB; }
      Double_t          EmEtInEE()           const { return fEmEtInEE; }
      Double_t          EmEtInHF()           const { return fEmEtInHF; }
      Double_t          CaloSumEtInpHF()     const { return fCaloSumEtInpHF; }
      Double_t          CaloSumEtInmHF()     const { return fCaloSumEtInmHF; }      
      Double_t          CaloMetInpHF()       const { return fCaloMetInpHF; }
      Double_t          CaloMetInmHF()       const { return fCaloMetInmHF; }
      Double_t          CaloMetPhiInpHF()    const { return fCaloMetPhiInpHF; }
      Double_t          CaloMetPhiInmHF()    const { return fCaloMetPhiInmHF; }
      
      void              SetSumEt(Double_t x)              { fSumEt = x; }
      void              SetE_longitudinal(Double_t x)     { fElongit = x; }
      void              SetMetSig(Double_t x)             { fMetSig = x; }
      void              PushCorrectionX(Double_t x)       { fDmex.push_back(x); }
      void              PushCorrectionY(Double_t x)       { fDmey.push_back(x); }
      void              PushCorrectionSumEt(Double_t x)   { fDSumEt.push_back(x); }
      
      void              SetMaxEtInEmTowers(Double_t x)    { fMaxEtInEmTowers = x; }
      void              SetMaxEtInHadTowers(Double_t x)   { fMaxEtInHadTowers = x; }
      void              SetEtFractionHadronic(Double_t x) { fEtFractionHadronic = x; }
      void              SetEmEtFraction(Double_t x)       { fEmEtFraction = x; }
      void              SetHadEtInHB(Double_t x)          { fHadEtInHB = x; }
      void              SetHadEtInHO(Double_t x)          { fHadEtInHO = x; }
      void              SetHadEtInHE(Double_t x)          { fHadEtInHE = x; }
      void              SetHadEtInHF(Double_t x)          { fHadEtInHF = x; }
      void              SetEmEtInEB(Double_t x)           { fEmEtInEB = x; }
      void              SetEmEtInEE(Double_t x)           { fEmEtInEE = x; }
      void              SetEmEtInHF(Double_t x)           { fEmEtInHF = x; }
      void              SetCaloSumEtInpHF(Double_t x)     { fCaloSumEtInpHF = x; }
      void              SetCaloSumEtInmHF(Double_t x)     { fCaloSumEtInmHF = x; }
      void              SetCaloMetInpHF(Double_t x)       { fCaloMetInpHF = x; }
      void              SetCaloMetInmHF(Double_t x)       { fCaloMetInmHF = x; }
      void              SetCaloMetPhiInpHF(Double_t x)    { fCaloMetPhiInpHF = x; }
      void              SetCaloMetPhiInmHF(Double_t x)    { fCaloMetPhiInmHF = x; }
      
    protected:
      Double_t                  fMex;                 // x-component
      Double_t                  fMey;                 // y-component              
      Double_t                  fSumEt;               // scalar sum of ET over all objects
      Double_t                  fMetSig;              // MET Significance = MET / sqrt(SumET)            
      Double_t                  fElongit;             // z-comp. of vector E sum over all inputs
      std::vector<Double_t>     fDmex;                // vector of all corr. applied to MEx
      std::vector<Double_t>     fDmey;                // vector of all corr. applied to MEy
      std::vector<Double_t>     fDSumEt;              // vector of all corr. applied to SumET

      Double_t                  fMaxEtInEmTowers;     // max ET deposited in ECAL towers
      Double_t                  fMaxEtInHadTowers;    // max ET deposited in HCAL towers
      Double_t                  fEtFractionHadronic;  // event hadronic scaler ET fraction
      Double_t                  fEmEtFraction;        // event electromagnetic scalar ET fraction
      Double_t                  fHadEtInHB;           // event hadronic scalar ET in HB
      Double_t                  fHadEtInHO;           // event hadronic scalar ET in HO
      Double_t                  fHadEtInHE;           // event hadronic scalar ET in HE
      Double_t                  fHadEtInHF;           // event hadronic scalar ET in HF
      Double_t                  fEmEtInEB;            // event electromagnetic scalar ET in EB
      Double_t                  fEmEtInEE;            // event electromagnetic scalar ET in EE
      Double_t                  fEmEtInHF;            // event electromagnetic scalar ET from HF
      Double_t                  fCaloSumEtInpHF;      // SumET in HF+
      Double_t                  fCaloSumEtInmHF;      // SumET in HF-
      Double_t                  fCaloMetInpHF;        // MET in HF+
      Double_t                  fCaloMetInmHF;        // MET in HF-
      Double_t                  fCaloMetPhiInpHF;     // MET-phi in HF+
      Double_t                  fCaloMetPhiInmHF;     // MET-phi in HF-
    
    ClassDef(Met, 1) // Missing Et class
  };
}
#endif
