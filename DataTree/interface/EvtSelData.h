//--------------------------------------------------------------------------------------------------
// $Id: EvtSelData.h,v 1.5 2010/01/05 16:39:44 edwenger Exp $
//
// EvtSelData
//
// Class to store event properties on which one may want to select clean events.
// This may be needed for early collision data only.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_EVENTSELDATA_H
#define MITANA_DATATREE_EVENTSELDATA_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class EvtSelData : public DataBase
  {
    public:
      EvtSelData() :  fHcalNeg(0), fHcalPos(0), 
                      fHfNeg(0), fHfPos(0), fHfNegTime(0), fHfPosTime(0), 
                      fCaNeg(0), fCaPos(0), fCaNegTime(0), fCaPosTime(0),
                      fZdcNeg(0), fZdcPos(0), fZdcNegTime(0), fZdcPosTime(0),
                      fPxbHits(0), fPxHits(0), fClusVtxQual(0), fClusVtxDiff(0),
                      fNHfNegHits(0), fNHfPosHits(0), fNHfTowersP(0), fNHfTowersN(0),
                      fSumEsubEpPos(0), fSumEaddEpPos(0), fSumEsubEpNeg(0), 
                      fSumEaddEpNeg(0), fSumHfEsubEpPos(0), fSumHfEaddEpPos(0), 
                      fSumHfEsubEpNeg(0), fSumHfEaddEpNeg(0), fHPTrkFrac(0) {}
      EvtSelData(Double_t HcalNeg, Double_t HcalPos,
                 Double_t HfNeg, Double_t HfPos, Double_t HfNegTime, Double_t HfPosTime,
                 Double_t CaNeg, Double_t CaPos, Double_t CaNegTime, Double_t CaPosTime,
                 Double_t ZdcNeg, Double_t ZdcPos, Double_t ZdcNegTime, Double_t ZdcPosTime,
                 Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff,
                 Int_t nHfNegHits, Int_t nHfPosHits, Int_t nHfTowersP, Int_t nHfTowersN,
                 Double_t sumEsubEpPos, Double_t sumEaddEpPos, Double_t sumEsubEpNeg, 
                 Double_t sumEaddEpNeg, Double_t sumHfEsubEpPos, Double_t sumHfEaddEpPos, 
                 Double_t sumHfEsubEpNeg, Double_t sumHfEaddEpNeg, Double_t HPTrkFrac);
      ~EvtSelData() {}

      Double_t      HcalNeg()       const { return fHcalNeg;    }
      Double_t      HcalPos()       const { return fHcalPos;    }
      Double_t      CastorNeg()     const { return fCaNeg;      }
      Double_t      CastorPos()     const { return fCaPos;      }
      Double_t      CastorNegTime() const { return fCaNegTime;  }
      Double_t      CastorPosTime() const { return fCaPosTime;  }
      Double_t      ClusVtxQual()   const { return fClusVtxQual;}
      Double_t      ClusVtxDiff()   const { return fClusVtxDiff;}
      Double_t      HPTrkFrac()     const { return fHPTrkFrac;  }
      Double_t      HfNeg()         const { return fHfNeg;      }
      Double_t      HfPos()         const { return fHfPos;      }
      Double_t      HfNegTime()     const { return fHfNegTime;  }
      Double_t      HfPosTime()     const { return fHfPosTime;  }
      Int_t         NpixBarrel()    const { return fPxbHits;    }
      Int_t         Npix()          const { return fPxHits;     }
      Double_t      ZdcNeg()        const { return fZdcNeg;     }
      Double_t      ZdcPos()        const { return fZdcPos;     }
      Double_t      ZdcNegTime()    const { return fZdcNegTime; }
      Double_t      ZdcPosTime()    const { return fZdcPosTime; }
      EObjType      ObjType()       const { return kEvtSelData; }
      void          Set (Double_t HcalNeg, Double_t HcalPos,
                         Double_t HfNeg, Double_t HfPos, Double_t HfNegTime, Double_t HfPosTime,
                         Double_t CaNeg, Double_t CaPos, Double_t CaNegTime, Double_t CaPosTime,
                         Double_t ZdcNeg, Double_t ZdcPos, Double_t ZdcNegTime, Double_t ZdcPosTime,
                         Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff,
                         Int_t nHfNegHits, Int_t nHfPosHits, Int_t nHfTowersP, Int_t nHfTowersN,
                         Double_t sumEsubEpPos, Double_t sumEaddEpPos, Double_t sumEsubEpNeg, 
                         Double_t sumEaddEpNeg, Double_t sumHfEsubEpPos, Double_t sumHfEaddEpPos, 
                         Double_t sumHfEsubEpNeg, Double_t sumHfEaddEpNeg,
			 Double_t HPTrkFrac);

    protected:
      Double_t      fHcalNeg;        //energy HCAL negative side
      Double_t      fHcalPos;        //energy HCAL positive side
      Double_t      fHfNeg;          //energy HF negative side
      Double_t      fHfPos;          //energy HF positive side
      Double_t      fHfNegTime;      //energy weighted HF time on negative side 
      Double_t      fHfPosTime;      //energy weighted HF time on positive side 
      Double_t      fCaNeg;          //energy CASTOR negative side
      Double_t      fCaPos;          //energy CASTOR positive side
      Double_t      fCaNegTime;      //energy weighted CASTOR time on negative side 
      Double_t      fCaPosTime;      //energy weighted CASTOR time on positive side 
      Double_t      fZdcNeg;         //energy ZDC negative side
      Double_t      fZdcPos;         //energy ZDC positive side
      Double_t      fZdcNegTime;     //energy weighted ZDC time on negative side 
      Double_t      fZdcPosTime;     //energy weighted ZDC time on positive side 
      Int_t         fPxbHits;        //number of pixel rechits in the three barrel layers
      Int_t         fPxHits;         //number of pixel rechits in all barrel and forward layers
      Double_t      fClusVtxQual;    //incompatibility of pixel cluster shapes with vertex (ratio)
      Double_t      fClusVtxDiff;    //incompatibility of pixel cluster shapes with vertex (diff)
      Int_t         fNHfNegHits;     //hf neg hits above threshold
      Int_t         fNHfPosHits;     //hf pos hits above threshold
      Int_t         fNHfTowersP;     //hf neg calo towers above threshold
      Int_t         fNHfTowersN;     //hf pos calo towers above threshold
      Double_t      fSumEsubEpPos;   //sum E sub Ep for pos calo towers
      Double_t      fSumEaddEpPos;   //sum E add Ep for pos calo towers
      Double_t      fSumEsubEpNeg;   //sum E sub Ep for neg calo towers
      Double_t      fSumEaddEpNeg;   //sum E add Ep for neg calo towers
      Double_t      fSumHfEsubEpPos; //sum E sub Ep for pos hf calo towers
      Double_t      fSumHfEaddEpPos; //sum E add Ep for pos hf calo towers
      Double_t      fSumHfEsubEpNeg; //sum E sub Ep for neg hf calo towers
      Double_t      fSumHfEaddEpNeg; //sum E add Ep for neg hf calo towers
      Double_t      fHPTrkFrac;      //fraction of high-purity tracks out of all with "loose" cuts

    ClassDef(EvtSelData, 3) // Event selection data
  };
}
#endif
