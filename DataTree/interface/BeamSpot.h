//--------------------------------------------------------------------------------------------------
// $Id: BeamSpot.h,v 1.4 2009/03/18 15:44:31 loizides Exp $
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
        fSigmaZ(0), fBeamWidthX(0), fBeamWidthY(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthXErr(0), fBeamWidthYErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(Double_t x, Double_t y, Double_t z) : 
        BaseVertex(x,y,z), fSigmaZ(0), fBeamWidthX(0), fBeamWidthY(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthXErr(0), fBeamWidthYErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
        BaseVertex(x,y,z,xErr,yErr,zErr), fSigmaZ(0), fBeamWidthX(0), fBeamWidthY(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthXErr(0), fBeamWidthYErr(0), fDxDzErr(0), fDyDzErr(0) {}
      BeamSpot(const ThreeVector &pos) :
        BaseVertex(pos), fSigmaZ(0), fBeamWidthX(0), fBeamWidthY(0), fDxDz(0), fDyDz(0),
        fSigmaZErr(0), fBeamWidthXErr(0), fBeamWidthYErr(0), fDxDzErr(0), fDyDzErr(0) {}
      
      Double_t            BeamWidthX()                           const { return fBeamWidthX;    }
      Double_t            BeamWidthY()                           const { return fBeamWidthY;    }
      Double_t            BeamWidthXErr()                        const { return fBeamWidthXErr; }
      Double_t            BeamWidthYErr()                        const { return fBeamWidthYErr; }
      Double_t            DxDz()                                 const { return fDxDz;          }
      Double_t            DyDz()                                 const { return fDyDz;          }
      Double_t            DxDzErr()                              const { return fDxDzErr;       }
      Double_t            DyDzErr()                              const { return fDyDzErr;       }
      EObjType            ObjType()                              const { return kBeamSpot;      }
      Double_t            SigmaZ()                               const { return fSigmaZ;        } 
      Double_t            SigmaZErr()                            const { return fSigmaZErr;     } 
      void                SetBeamWidthX(Double_t beamWidth)            { fBeamWidthX = beamWidth;   }
      void                SetBeamWidthY(Double_t beamWidth)            { fBeamWidthY = beamWidth;   }
      void                SetBeamWidthXErr(Double_t beamWErr)          { fBeamWidthXErr = beamWErr; }
      void                SetBeamWidthYErr(Double_t beamWErr)          { fBeamWidthYErr = beamWErr; }
      void                SetDxDz(Double_t dxDz)                       { fDxDz = dxDz;              }
      void                SetDyDz(Double_t dyDz)                       { fDyDz = dyDz;              }
      void                SetDxDzErr(Double_t dxDzErr)                 { fDxDzErr = dxDzErr;        }
      void                SetDyDzErr(Double_t dyDzErr)                 { fDyDzErr = dyDzErr;        }
      void                SetSigmaZ(Double_t sigmaZ)                   { fSigmaZ = sigmaZ;          }
      void                SetSigmaZErr(Double_t sigmaZErr)             { fSigmaZErr = sigmaZErr;    }
            
    protected:
      Double32_t          fSigmaZ;        //[0,0,14]z width of beamspot
      Double32_t          fBeamWidthX;    //[0,0,14]transverse width of beamspot (x-axis)
      Double32_t          fBeamWidthY;    //[0,0,14]transverse width of beamspot (y-axis)
      Double32_t          fDxDz;          //[0,0,14]x-z slope of beamline
      Double32_t          fDyDz;          //[0,0,14]y-z slope of beamline
      Double32_t          fSigmaZErr;     //[0,0,14]error of z width
      Double32_t          fBeamWidthXErr; //[0,0,14]error of transverse width (x-axis)
      Double32_t          fBeamWidthYErr; //[0,0,14]error of transverse width (y-axis)
      Double32_t          fDxDzErr;       //[0,0,14]error of x-z slope
      Double32_t          fDyDzErr;       //[0,0,14]error of y-z slope
	
    ClassDef(BeamSpot, 2) // Beam spot class
  };
}
#endif
