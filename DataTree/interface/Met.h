//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.8 2008/12/09 17:47:00 loizides Exp $
//
// Met
//
// Class to store missing transverse energy information.
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
      Met() :
        fMex(0), fMey(0), fSumEt(0), fMetSig(0), fElongit(0), fDmex(0), fDmey(0),
        fDSumEt(0), fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) { SetClearBit(); }
      Met(Double_t mex, Double_t mey) : 
        fMex(mex), fMey(mey), fSumEt(0), fMetSig(0), fElongit(0), fDmex(0), fDmey(0),
        fDSumEt(0), fMaxEtInEmTowers(0), fMaxEtInHadTowers(0), fEtFractionHadronic(0), 
        fEmEtFraction(0), fHadEtInHB(0), fHadEtInHO(0), fHadEtInHE(0), fHadEtInHF(0), 
        fEmEtInEB(0), fEmEtInEE(0), fEmEtInHF(0), fCaloSumEtInpHF(0), fCaloSumEtInmHF(0), 
        fCaloMetInmHF(0), fCaloMetPhiInpHF(0), fCaloMetPhiInmHF(0) { SetClearBit(); }

      Double_t                     CaloSumEtInpHF()     const { return fCaloSumEtInpHF; }
      Double_t                     CaloSumEtInmHF()     const { return fCaloSumEtInmHF; }      
      Double_t                     CaloMetInpHF()       const { return fCaloMetInpHF; }
      Double_t                     CaloMetInmHF()       const { return fCaloMetInmHF; }
      Double_t                     CaloMetPhiInpHF()    const { return fCaloMetPhiInpHF; }
      Double_t                     CaloMetPhiInmHF()    const { return fCaloMetPhiInmHF; }
      const std::vector<Double_t> &Dmex()               const { return fDmex; }
      const std::vector<Double_t> &Dmey()               const { return fDmey; }
      const std::vector<Double_t> &DSumEt()             const { return fDSumEt; }
      Double_t                     EmEtFraction()       const { return fEmEtFraction; }
      Double_t                     EmEtInEB()           const { return fEmEtInEB; }
      Double_t                     EmEtInEE()           const { return fEmEtInEE; }
      Double_t                     EmEtInHF()           const { return fEmEtInHF; }
      Double_t                     Elongitudinal()      const { return fElongit; }
      Double_t                     EtFractionHadronic() const { return fEtFractionHadronic; }
      Double_t                     HadEtInHB()          const { return fHadEtInHB; }
      Double_t                     HadEtInHO()          const { return fHadEtInHO; } 
      Double_t                     HadEtInHE()          const { return fHadEtInHE; }
      Double_t                     HadEtInHF()          const { return fHadEtInHF; }
      Double_t                     MaxEtInEmTowers()    const { return fMaxEtInEmTowers; }
      Double_t                     MaxEtInHadTowers()   const { return fMaxEtInHadTowers; }
      Double_t                     MetSig()             const { return fMetSig; }    
      EObjType                     ObjType()            const { return kMet;             }      
      Double_t                     SumEt()              const { return fSumEt; } 
      void                         PushCorrectionX(Double_t x)       { fDmex.push_back(x); }
      void                         PushCorrectionY(Double_t x)       { fDmey.push_back(x); }
      void                         PushCorrectionSumEt(Double_t x)   { fDSumEt.push_back(x); }
      void                         SetCaloSumEtInpHF(Double_t x)     { fCaloSumEtInpHF = x; }
      void                         SetCaloSumEtInmHF(Double_t x)     { fCaloSumEtInmHF = x; }
      void                         SetCaloMetInpHF(Double_t x)       { fCaloMetInpHF = x; }
      void                         SetCaloMetInmHF(Double_t x)       { fCaloMetInmHF = x; }
      void                         SetCaloMetPhiInpHF(Double_t x)    { fCaloMetPhiInpHF = x; }
      void                         SetCaloMetPhiInmHF(Double_t x)    { fCaloMetPhiInmHF = x; }
      void                         SetEmEtFraction(Double_t x)       { fEmEtFraction = x; }
      void                         SetElongitudinal(Double_t x)      { fElongit = x; }
      void                         SetEtFractionHadronic(Double_t x) { fEtFractionHadronic = x; }
      void                         SetHadEtInHB(Double_t x)          { fHadEtInHB = x; }
      void                         SetHadEtInHO(Double_t x)          { fHadEtInHO = x; }
      void                         SetHadEtInHE(Double_t x)          { fHadEtInHE = x; }
      void                         SetHadEtInHF(Double_t x)          { fHadEtInHF = x; }
      void                         SetEmEtInEB(Double_t x)           { fEmEtInEB = x; }
      void                         SetEmEtInEE(Double_t x)           { fEmEtInEE = x; }
      void                         SetEmEtInHF(Double_t x)           { fEmEtInHF = x; }
      void                         SetMaxEtInEmTowers(Double_t x)    { fMaxEtInEmTowers = x; }
      void                         SetMaxEtInHadTowers(Double_t x)   { fMaxEtInHadTowers = x; }
      void                         SetMetSig(Double_t x)             { fMetSig = x; }
      void                         SetSumEt(Double_t x)              { fSumEt = x; }
      
    protected:
      void                         Clear(Option_t * /*option*/ ="");
      void	                   GetMom()             const;

      Double_t                     fMex;                 //x-component
      Double_t                     fMey;                 //y-component              
      Double_t                     fSumEt;               //scalar sum of ET over all objects
      Double_t                     fMetSig;              //MET Significance = MET / sqrt(SumET)
      Double_t                     fElongit;             //z-comp. of vector E sum over all inputs
      std::vector<Double_t>        fDmex;                //vector of all corr. applied to MEx
      std::vector<Double_t>        fDmey;                //vector of all corr. applied to MEy
      std::vector<Double_t>        fDSumEt;              //vector of all corr. applied to SumET
      Double_t                     fMaxEtInEmTowers;     //max ET deposited in ECAL towers
      Double_t                     fMaxEtInHadTowers;    //max ET deposited in HCAL towers
      Double_t                     fEtFractionHadronic;  //event hadronic scaler ET fraction
      Double_t                     fEmEtFraction;        //event electromagnetic scalar ET fraction
      Double_t                     fHadEtInHB;           //event hadronic scalar ET in HB
      Double_t                     fHadEtInHO;           //event hadronic scalar ET in HO
      Double_t                     fHadEtInHE;           //event hadronic scalar ET in HE
      Double_t                     fHadEtInHF;           //event hadronic scalar ET in HF
      Double_t                     fEmEtInEB;            //event electromagnetic scalar ET in EB
      Double_t                     fEmEtInEE;            //event electromagnetic scalar ET in EE
      Double_t                     fEmEtInHF;            //event electromagnetic scalar ET from HF
      Double_t                     fCaloSumEtInpHF;      //SumET in HF+
      Double_t                     fCaloSumEtInmHF;      //SumET in HF-
      Double_t                     fCaloMetInpHF;        //MET in HF+
      Double_t                     fCaloMetInmHF;        //MET in HF-
      Double_t                     fCaloMetPhiInpHF;     //MET-phi in HF+
      Double_t                     fCaloMetPhiInmHF;     //MET-phi in HF-
    
    ClassDef(Met, 1) // Missing transverse energy class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::Clear(Option_t *)
{ 
  // Clear by deleting the std::vectors.
  
  fDmex.~vector<Double_t>();
  fDmey.~vector<Double_t>();
  fDSumEt.~vector<Double_t>();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::GetMom() const
{
  // Get momentum values from stored values.

  Double_t pt = TMath::Sqrt(fMex*fMex+fMey*fMey);
  Double_t phi = TMath::ATan2(fMey,fMex);
  fCachedMom.SetCoordinates(pt,0,phi,0);
}
#endif
