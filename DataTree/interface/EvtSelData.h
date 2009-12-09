//--------------------------------------------------------------------------------------------------
// $Id: EvtSelData.h,v 1.2 2009/12/08 20:51:10 loizides Exp $
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
                      fPxbHits(0), fPxHits(0), fClusVtxQual(0), fClusVtxDiff(0) {}
      EvtSelData(Double_t HcalNeg, Double_t HcalPos,
                 Double_t HfNeg, Double_t HfPos, Double_t HfNegTime, Double_t HfPosTime,
                 Double_t CaNeg, Double_t CaPos, Double_t CaNegTime, Double_t CaPosTime,
                 Double_t ZdcNeg, Double_t ZdcPos, Double_t ZdcNegTime, Double_t ZdcPosTime,
                 Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff);
                 
      ~EvtSelData() {}

      Double_t      HcalNeg()       const { return fHcalNeg;    }
      Double_t      HcalPos()       const { return fHcalPos;    }
      Double_t      CastorNeg()     const { return fCaNeg;      }
      Double_t      CastorPos()     const { return fCaPos;      }
      Double_t      CastorNegTime() const { return fCaNegTime;  }
      Double_t      CastorPosTime() const { return fCaPosTime;  }
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
                         Int_t PxbHits, Int_t PxHits, Double_t ClusVtxQual, Double_t ClusVtxDiff);

    protected:
      Double_t      fHcalNeg;     //energy HCAL negative side
      Double_t      fHcalPos;     //energy HCAL positive side
      Double_t      fHfNeg;       //energy HF negative side
      Double_t      fHfPos;       //energy HF positive side
      Double_t      fHfNegTime;   //energy weighted HF time on negative side 
      Double_t      fHfPosTime;   //energy weighted HF time on positive side 
      Double_t      fCaNeg;       //energy CASTOR negative side
      Double_t      fCaPos;       //energy CASTOR positive side
      Double_t      fCaNegTime;   //energy weighted CASTOR time on negative side 
      Double_t      fCaPosTime;   //energy weighted CASTOR time on positive side 
      Double_t      fZdcNeg;      //energy ZDC negative side
      Double_t      fZdcPos;      //energy ZDC positive side
      Double_t      fZdcNegTime;  //energy weighted ZDC time on negative side 
      Double_t      fZdcPosTime;  //energy weighted ZDC time on positive side 
      Int_t         fPxbHits;     //number of pixel rechits in the three barrel layers
      Int_t         fPxHits;      //number of pixel rechits in all barrel and forward layers
      Double_t      fClusVtxQual; //incompatibility of pixel cluster shapes with vertex (ratio)
      Double_t      fClusVtxDiff; //incompatibility of pixel cluster shapes with vertex (diff)

    ClassDef(EvtSelData, 2) // Event selection data
  };
}
#endif
