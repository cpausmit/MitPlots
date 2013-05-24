//--------------------------------------------------------------------------------------------------
// $Id: EmbedWeight.h,v 1.2 2013/05/06 18:33:00 pharris Exp $
//
// EmebedWeight
//
// Weight for embedded Taus
//
// Authors: P. Harris
//-------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_EMBEDWEIGHT_H
#define MITANA_DATATREE_EMBEDWEIGHT_H
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Types.h"
 
namespace mithep 
{
  class EmbedWeight : public DataObject
  {
    public:
    EmbedWeight() :  
	fGenWeight(1), 
	fSpinnerWeight(1),
	fSpinnerFlipWeight(1),  
	fSpinnerPlusWeight(1),
	fSpinnerMinusWeight(1),
	fMuEffWeight(1),
	fMuEffWeightUp(1),
	fMuEffWeightDown(1),
	fMuRadWeight(1),
	fMuRadWeightUp(1),
	fMuRadWeightDown(1),
	fGenTau2PtVsGenTau1PtGen(1),
	fGenTau2EtaVsGenTau1EtaGen(1),
	fDiTauMassVsGenDiTauPtGen(1),
	fGenTau2PtVsGenTau1PtRec(1),
	fGenTau2EtaVsGenTau1EtaRec(1),
	fDiTauMassVsGenDiTauPtRec(1)
	  {}
      
      Double_t            Weight()                    const { return fWeight;}
      EObjType            ObjType()                   const { return kEmbedWeight;   }  
      Double_t            GenWeight()                 const { return fGenWeight          ;}
      Double_t            SpinnerWeight()             const { return fSpinnerWeight      ;}
      Double_t            SpinnerFlipWeight()         const { return fSpinnerFlipWeight  ;}
      Double_t            SpinnerPlusWeight()         const { return fSpinnerPlusWeight  ;}
      Double_t            SpinnerMinusWeight()        const { return fSpinnerMinusWeight ;}
      Double_t            MuEffWeight()               const { return fMuEffWeight        ;}
      Double_t            MuEffWeightUp()             const { return fMuEffWeightUp      ;}
      Double_t            MuEffWeightDown()           const { return fMuEffWeightDown    ;}
      Double_t            MuRadWeight()               const { return fMuRadWeight        ;}
      Double_t            MuRadWeightUp()             const { return fMuRadWeightUp      ;}
      Double_t            MuRadWeightDown()           const { return fMuRadWeightDown    ;}
      Double_t            GenTau2VsGenTau1PtGen()     const { return fGenTau2PtVsGenTau1PtGen       ;}
      Double_t            GenTau2VsGenTau1EtaGen()    const { return fGenTau2EtaVsGenTau1EtaGen      ;}
      Double_t            DiTauMassVsGenDiTauPtGen()  const { return fDiTauMassVsGenDiTauPtGen    ;}
      Double_t            GenTau2VsGenTau1PtRec()     const { return fGenTau2PtVsGenTau1PtRec       ;}
      Double_t            GenTau2VsGenTau1EtaRec()    const { return fGenTau2EtaVsGenTau1EtaRec      ;}
      Double_t            DiTauMassVsGenDiTauPtRec()  const { return fDiTauMassVsGenDiTauPtRec    ;}
      void                SetGenWeight         (Double_t weight) {fGenWeight          = weight; fWeight = weight;}
      void                SetSpinnerWeight     (Double_t weight) {fSpinnerWeight      = weight;}
      void                SetSpinnerFlipWeight (Double_t weight) {fSpinnerFlipWeight  = weight;}
      void                SetSpinnerPlusWeight (Double_t weight) {fSpinnerPlusWeight  = weight;}
      void                SetSpinnerMinusWeight(Double_t weight) {fSpinnerMinusWeight = weight;}
      void                SetMuEffWeight       (Double_t weight) {fMuEffWeight        = weight;}
      void                SetMuEffWeightUp     (Double_t weight) {fMuEffWeightUp      = weight;}
      void                SetMuEffWeightDown   (Double_t weight) {fMuEffWeightDown    = weight;}
      void                SetMuRadWeight       (Double_t weight) {fMuRadWeight        = weight;}
      void                SetMuRadWeightUp     (Double_t weight) {fMuRadWeightUp      = weight;}
      void                SetMuRadWeightDown   (Double_t weight) {fMuRadWeightDown    = weight;}
      void                SetGenTau2VsGenTau1PtGen (Double_t weight) {fGenTau2PtVsGenTau1PtGen       = weight;}
      void                SetGenTau2VsGenTau1EtaGen(Double_t weight) {fGenTau2EtaVsGenTau1EtaGen      = weight;}
      void                SetDiTauMassVsGenDiTauPtGen (Double_t weight) {fDiTauMassVsGenDiTauPtGen    = weight;}
      void                SetGenTau2VsGenTau1PtRec (Double_t weight) {fGenTau2PtVsGenTau1PtRec       = weight;}
      void                SetGenTau2VsGenTau1EtaRec(Double_t weight) {fGenTau2EtaVsGenTau1EtaRec      = weight;}
      void                SetDiTauMassVsGenDiTauPtRec (Double_t weight) {fDiTauMassVsGenDiTauPtRec    = weight;}
      void                SetWeight() { fWeight = fWeight*fSpinnerWeight*fMuEffWeight*fMuRadWeight*fGenTau2PtVsGenTau1PtRec*fGenTau2EtaVsGenTau1EtaRec*fDiTauMassVsGenDiTauPtRec;        }

  protected:
      //Generator level
      Double32_t          fWeight;
      Double32_t          fGenWeight;
      Double32_t          fSpinnerWeight;
      Double32_t          fSpinnerFlipWeight;
      Double32_t          fSpinnerPlusWeight;
      Double32_t          fSpinnerMinusWeight;

      //Muon Level
      Double32_t          fMuEffWeight;
      Double32_t          fMuEffWeightUp;
      Double32_t          fMuEffWeightDown;
      Double32_t          fMuRadWeight;
      Double32_t          fMuRadWeightUp;
      Double32_t          fMuRadWeightDown;
      //Unfolding weights
      Double32_t          fGenTau2PtVsGenTau1PtGen;
      Double32_t          fGenTau2EtaVsGenTau1EtaGen;
      Double32_t          fDiTauMassVsGenDiTauPtGen;

      Double32_t          fGenTau2PtVsGenTau1PtRec;
      Double32_t          fGenTau2EtaVsGenTau1EtaRec;
      Double32_t          fDiTauMassVsGenDiTauPtRec;

      ClassDef(EmbedWeight,2);
  };
}
#endif
