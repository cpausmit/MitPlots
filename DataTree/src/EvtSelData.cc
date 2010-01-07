// $Id: EvtSelData.cc,v 1.3 2010/01/05 16:39:44 edwenger Exp $

#include "MitAna/DataTree/interface/EvtSelData.h"

ClassImp(mithep::EvtSelData)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
EvtSelData::EvtSelData(Double_t HcalNeg, Double_t HcalPos,
                       Double_t HfNeg, Double_t HfPos, Double_t HfNegTime, Double_t HfPosTime,
                       Double_t CaNeg, Double_t CaPos, Double_t CaNegTime, Double_t CaPosTime,
                       Double_t ZdcNeg, Double_t ZdcPos, Double_t ZdcNegTime, Double_t ZdcPosTime,
                       Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff,
                       Int_t nHfNegHits, Int_t nHfPosHits, Int_t nHfTowersP, Int_t nHfTowersN,
                       Double_t sumEsubEpPos, Double_t sumEaddEpPos, Double_t sumEsubEpNeg, 
                       Double_t sumEaddEpNeg, Double_t sumHfEsubEpPos, Double_t sumHfEaddEpPos, 
                       Double_t sumHfEsubEpNeg, Double_t sumHfEaddEpNeg,
		       Double_t HPTrkFrac)
  :   fHcalNeg(HcalNeg), fHcalPos(HcalPos),
      fHfNeg(HfNeg), fHfPos(HfPos), fHfNegTime(HfNegTime), fHfPosTime(HfPosTime),
      fCaNeg(CaNeg), fCaPos(CaPos), fCaNegTime(CaNegTime), fCaPosTime(CaPosTime),
      fZdcNeg(ZdcNeg), fZdcPos(ZdcPos), fZdcNegTime(ZdcNegTime), fZdcPosTime(ZdcPosTime),
      fPxbHits(PxbHits), fPxHits(PxHits), fClusVtxQual(ClusVtxQual), fClusVtxDiff(ClusVtxDiff),
      fNHfNegHits(nHfNegHits), fNHfPosHits(nHfPosHits), 
      fNHfTowersP(nHfTowersP), fNHfTowersN(nHfTowersN),
      fSumEsubEpPos(sumEsubEpPos), fSumEaddEpPos(sumEaddEpPos), fSumEsubEpNeg(sumEsubEpNeg), 
      fSumEaddEpNeg(sumEaddEpNeg), fSumHfEsubEpPos(sumHfEsubEpPos), fSumHfEaddEpPos(sumHfEaddEpPos),
      fSumHfEsubEpNeg(sumHfEsubEpNeg), fSumHfEaddEpNeg(sumHfEaddEpNeg),
      fHPTrkFrac(HPTrkFrac)
{
  // Default constructor.
}

//--------------------------------------------------------------------------------------------------
void EvtSelData::Set (Double_t HcalNeg, Double_t HcalPos,
                      Double_t HfNeg, Double_t HfPos, Double_t HfNegTime, Double_t HfPosTime,
                      Double_t CaNeg, Double_t CaPos, Double_t CaNegTime, Double_t CaPosTime,
                      Double_t ZdcNeg, Double_t ZdcPos, Double_t ZdcNegTime, Double_t ZdcPosTime,
		      Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff,
                      Int_t nHfNegHits, Int_t nHfPosHits, Int_t nHfTowersP, Int_t nHfTowersN,
                      Double_t sumEsubEpPos, Double_t sumEaddEpPos, Double_t sumEsubEpNeg, 
                      Double_t sumEaddEpNeg, Double_t sumHfEsubEpPos, Double_t sumHfEaddEpPos, 
                      Double_t sumHfEsubEpNeg, Double_t sumHfEaddEpNeg,
		      Double_t HPTrkFrac)
{
  // Set values.

  fHcalNeg        = HcalNeg; 
  fHcalPos        = HcalPos;
  fHfNeg          = HfNeg; 
  fHfPos          = HfPos; 
  fHfNegTime      = HfNegTime; 
  fHfPosTime      = HfPosTime;
  fCaNeg          = CaNeg; 
  fCaPos          = CaPos; 
  fCaNegTime      = CaNegTime; 
  fCaPosTime      = CaPosTime;
  fZdcNeg         = ZdcNeg; 
  fZdcPos         = ZdcPos;
  fZdcNegTime     = ZdcNegTime; 
  fZdcPosTime     = ZdcPosTime;
  fPxbHits        = PxbHits;
  fPxHits         = PxHits;
  fClusVtxQual    = ClusVtxQual;
  fClusVtxDiff    = ClusVtxDiff;
  fNHfNegHits     = nHfNegHits; 
  fNHfPosHits     = nHfPosHits; 
  fNHfTowersP     = nHfTowersP; 
  fNHfTowersN     = nHfTowersN;
  fSumEsubEpPos   = sumEsubEpPos; 
  fSumEaddEpPos   = sumEaddEpPos; 
  fSumEsubEpNeg   = sumEsubEpNeg; 
  fSumEaddEpNeg   = sumEaddEpNeg; 
  fSumHfEsubEpPos = sumHfEsubEpPos; 
  fSumHfEaddEpPos = sumHfEaddEpPos;
  fSumHfEsubEpNeg = sumHfEsubEpNeg; 
  fSumHfEaddEpNeg = sumHfEaddEpNeg;
  fHPTrkFrac      = HPTrkFrac;
}
