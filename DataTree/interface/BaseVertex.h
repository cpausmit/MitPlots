//--------------------------------------------------------------------------------------------------
// $Id: BaseVertex.h,v 1.5 2008/10/14 05:27:54 loizides Exp $
//
// BaseVertex
//
// BaseVertex class implemented as holding a 3d vector as a point in space with fit information.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_BASEVERTEX_H
#define MITANA_DATATREE_BASEVERTEX_H

#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class BaseVertex : public DataObject
  {
    public:
      BaseVertex() : 
        fPosition(0,0,0), fXErr(0.0), fYErr(0.0), fZErr(0.0) {}
      BaseVertex(Double_t x, Double_t y, Double_t z) : 
        fPosition(x,y,z), fXErr(0.0), fYErr(0.0), fZErr(0.0) {}

      BaseVertex(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
        fPosition(x,y,z), fXErr(xErr), fYErr(yErr), fZErr(zErr) {}
      BaseVertex(const ThreeVector &pos) :
        fPosition(pos), fXErr(0.0), fYErr(0.0), fZErr(0.0) {}
      ~BaseVertex() {}
      
      Double_t            Phi()       const { return fPosition.Phi();  }
      const ThreeVector  &Position()  const { return fPosition;        }
      Double_t            Rho()       const { return fPosition.Rho();  }
      Double_t            X()         const { return fPosition.X();    }
      Double_t            XErr()      const { return fXErr; }
      Double_t            Y()         const { return fPosition.Y();    }
      Double_t            YErr()      const { return fYErr; }
      Double_t            Z()         const { return fPosition.Z();    }
      Double_t            ZErr()      const { return fZErr; }
      void                SetErrors(Double_t xErr, Double_t yErr, Double_t zErr);
      void                SetPosition(const ThreeVector &pos) { fPosition = pos; }
      void                SetPosition(Double_t x, Double_t y, Double_t z); 
            
    protected:
      ThreeVector	  fPosition; //point in space
      Double32_t          fXErr;     //error in x
      Double32_t          fYErr;     //error in y
      Double32_t          fZErr;     //error in z
	
    ClassDef(BaseVertex, 1) // BaseVertex class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::BaseVertex::SetErrors(Double_t xErr, Double_t yErr, Double_t zErr)
{ 
  // Set uncertainties on vertex position.

  fXErr = xErr;
  fYErr = yErr;
  fZErr = zErr;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::BaseVertex::SetPosition(Double_t x, Double_t y, Double_t z)
{ 
  // Set vertex position.

  fPosition.SetXYZ(x,y,z);
}

#endif
