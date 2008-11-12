//--------------------------------------------------------------------------------------------------
// $Id: BeamSpot.h,v 1.5 2008/10/14 05:27:54 loizides Exp $
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
        fSigmaZ(0.0), fBeamWidth(0.0), fDxDz(0.0), fDyDz(0.0),
        fSigmaZErr(0.0), fBeamWidthErr(0.0), fDxDzErr(0.0), fDyDzErr(0.0) {}
      BeamSpot(Double_t x, Double_t y, Double_t z) : 
        BaseVertex(x,y,z), fSigmaZ(0.0), fBeamWidth(0.0), fDxDz(0.0), fDyDz(0.0),
        fSigmaZErr(0.0), fBeamWidthErr(0.0), fDxDzErr(0.0), fDyDzErr(0.0) {}

      BeamSpot(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
        BaseVertex(x,y,z,xErr,yErr,zErr), fSigmaZ(0.0), fBeamWidth(0.0), fDxDz(0.0), fDyDz(0.0),
        fSigmaZErr(0.0), fBeamWidthErr(0.0), fDxDzErr(0.0), fDyDzErr(0.0) {}
      BeamSpot(const ThreeVector &pos) :
        BaseVertex(pos), fSigmaZ(0.0), fBeamWidth(0.0), fDxDz(0.0), fDyDz(0.0),
        fSigmaZErr(0.0), fBeamWidthErr(0.0), fDxDzErr(0.0), fDyDzErr(0.0) {}
      ~BeamSpot() {}
      
      Double_t            SigmaZ()                               const { return fSigmaZ; } 
      Double_t            BeamWidth()                            const { return fBeamWidth; }
      Double_t            DxDz()                                 const { return fDxDz; }
      Double_t            DyDz()                                 const { return fDyDz; }
      Double_t            SigmaZErr()                            const { return fSigmaZErr; } 
      Double_t            BeamWidthErr()                         const { return fBeamWidthErr; }
      Double_t            DxDzErr()                              const { return fDxDzErr; }
      Double_t            DyDzErr()                              const { return fDyDzErr; }
      void                SetSigmaZ(Double_t sigmaZ)                   { fSigmaZ = sigmaZ; } 
      void                SetBeamWidth(Double_t beamWidth)             { fBeamWidth = beamWidth; }
      void                SetDxDz(Double_t dxDz)                       { fDxDz = dxDz; }
      void                SetDyDz(Double_t dyDz)                       { fDyDz = dyDz; }
      void                SetSigmaZErr(Double_t sigmaZErr)             { fSigmaZErr = sigmaZErr; } 
      void                SetBeamWidthErr(Double_t beamWidthErr)       { fBeamWidthErr = beamWidthErr; }
      void                SetDxDzErr(Double_t dxDzErr)                 { fDxDzErr = dxDzErr; }
      void                SetDyDzErr(Double_t dyDzErr)                 { fDyDzErr = dyDzErr; }
            
    protected:
      Double32_t          fSigmaZ;     //z width of beamspot
      Double32_t          fBeamWidth;  //transverse width of beamspot
      Double32_t          fDxDz;       //x-z slope of beamline
      Double32_t          fDyDz;       //y-z slope of beamline
      Double32_t          fSigmaZErr;
      Double32_t          fBeamWidthErr;
      Double32_t          fDxDzErr;
      Double32_t          fDyDzErr;
	
    ClassDef(BeamSpot, 1) // BeamSpot class
  };
}
#endif
