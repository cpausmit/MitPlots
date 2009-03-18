//--------------------------------------------------------------------------------------------------
// $Id: BeamSpot.h,v 1.3 2009/02/18 15:38:54 loizides Exp $
//
// BeamSpot
//
// BeamSpot class implemented as holding a 3d vector as a point in space with fit information.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BEAMSPOT_H
#define MITANA_DATATREE_BEAMSPOT_H
 
#include "MitAna/DataTree/interface/BaseVertex.h"

namespace mithep 
{
  class BeamSpot : public BaseVertex
  {
    public:
      BeamSpot() : 
        fSigmaZ(0), fBeamWidth(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(Double_t x, Double_t y, Double_t z) : 
        BaseVertex(x,y,z), fSigmaZ(0), fBeamWidth(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
        BaseVertex(x,y,z,xErr,yErr,zErr), fSigmaZ(0), fBeamWidth(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(const ThreeVector &pos) :
        BaseVertex(pos), fSigmaZ(0), fBeamWidth(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthErr(0), fDxDzErr(0), fDyDzErr(0) {}
      
      Double_t            BeamWidth()                            const { return fBeamWidth;    }
      Double_t            BeamWidthErr()                         const { return fBeamWidthErr; }
      Double_t            DxDz()                                 const { return fDxDz;         }
      Double_t            DyDz()                                 const { return fDyDz;         }
      Double_t            DxDzErr()                              const { return fDxDzErr;      }
      Double_t            DyDzErr()                              const { return fDyDzErr;      }
      EObjType            ObjType()                              const { return kBeamSpot;     }
      Double_t            SigmaZ()                               const { return fSigmaZ;       } 
      Double_t            SigmaZErr()                            const { return fSigmaZErr;    } 
      void                SetBeamWidth(Double_t beamWidth)             { fBeamWidth = beamWidth;   }
      void                SetBeamWidthErr(Double_t beamWErr)           { fBeamWidthErr = beamWErr; }
      void                SetDxDz(Double_t dxDz)                       { fDxDz = dxDz;             }
      void                SetDyDz(Double_t dyDz)                       { fDyDz = dyDz;             }
      void                SetDxDzErr(Double_t dxDzErr)                 { fDxDzErr = dxDzErr;       }
      void                SetDyDzErr(Double_t dyDzErr)                 { fDyDzErr = dyDzErr;       }
      void                SetSigmaZ(Double_t sigmaZ)                   { fSigmaZ = sigmaZ;         }
      void                SetSigmaZErr(Double_t sigmaZErr)             { fSigmaZErr = sigmaZErr;   }
            
    protected:
      Double32_t          fSigmaZ;        //[0,0,14]z width of beamspot
      Double32_t          fBeamWidth;     //[0,0,14]transverse width of beamspot
      Double32_t          fDxDz;          //[0,0,14]x-z slope of beamline
      Double32_t          fDyDz;          //[0,0,14]y-z slope of beamline
      Double32_t          fSigmaZErr;     //[0,0,14]error of z width
      Double32_t          fBeamWidthErr;  //[0,0,14]error of transverse width
      Double32_t          fDxDzErr;       //[0,0,14]error of x-z slope
      Double32_t          fDyDzErr;       //[0,0,14]error of y-z slope
	
    ClassDef(BeamSpot, 1) // Beam spot class
  };
}
#endif
