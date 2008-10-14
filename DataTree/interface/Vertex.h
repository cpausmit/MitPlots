//--------------------------------------------------------------------------------------------------
// $Id: Vertex.h,v 1.4 2008/09/30 12:51:37 bendavid Exp $
//
// Vertex
//
// Vertex class implemented as holding a 3d vector as a point in space with fit information.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_VERTEX_H
#define MITANA_DATATREE_VERTEX_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Vertex : public DataObject
  {
    public:
      Vertex() : 
        fPosition(0,0,0), fXErr(0.0), fYErr(0.0), fZErr(0.0), fChi2(0.0), fNdof(0), fNTracks(0) {}
      Vertex(Double_t x, Double_t y, Double_t z) : 
        fPosition(x,y,z), fXErr(0.0), fYErr(0.0), fZErr(0.0), fChi2(0.0), fNdof(0), fNTracks(0) {}

      Vertex(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
        fPosition(x,y,z), fXErr(xErr), fYErr(yErr), fZErr(zErr), fChi2(0.0), fNdof(0), fNTracks(0) {}
      Vertex(const ThreeVector &pos) :
        fPosition(pos), fXErr(0.0), fYErr(0.0), fZErr(0.0), fChi2(0.0), fNdof(0), fNTracks(0) {}
      ~Vertex() {}
      
      Double_t            Chi2()      const { return fChi2; } 
      UInt_t              Ndof()      const { return fNdof; }
      UInt_t              NTracks()   const { return fNTracks; }
      Double_t            Phi()       const { return fPosition.Phi();  }
      const ThreeVector  &Position()  const { return fPosition;        }
      Double_t            Rho()       const { return fPosition.Rho();  }
      Double_t            X()         const { return fPosition.X();    }
      Double_t            XErr()      const { return fXErr; }
      Double_t            Y()         const { return fPosition.Y();    }
      Double_t            YErr()      const { return fYErr; }
      Double_t            Z()         const { return fPosition.Z();    }
      Double_t            ZErr()      const { return fZErr; }
      Double_t            Prob()      const { return TMath::Prob(fChi2,fNdof); }
      void                SetChi2(Double_t chi2)              { fChi2 = chi2; }
      void                SetErrors(Double_t xErr, Double_t yErr, Double_t zErr);
      void                SetNdof(UInt_t nDof)                { fNdof = nDof; }
      void                SetPosition(const ThreeVector &pos) { fPosition = pos; }
      void                SetPosition(Double_t x, Double_t y, Double_t z); 
      void                SetNTracks(UInt_t ntrks)            { fNTracks = ntrks; }
            
    protected:
      ThreeVector	  fPosition; //point in space
      Double32_t          fXErr;     //error in x
      Double32_t          fYErr;     //error in y
      Double32_t          fZErr;     //error in z
      Double32_t          fChi2;     //chi squared of conversion vertex fit
      UInt_t              fNdof;     //number of degrees of freedom of conversion vertex fit
      UInt_t              fNTracks;  //number of tracks used for the fit
	
    ClassDef(Vertex, 1) // Vertex class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Vertex::SetErrors(Double_t xErr, Double_t yErr, Double_t zErr)
{ 
  // Set uncertainties on vertex position.

  fXErr = xErr;
  fYErr = yErr;
  fZErr = zErr;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Vertex::SetPosition(Double_t x, Double_t y, Double_t z)
{ 
  // Set vertex position.

  fPosition.SetXYZ(x,y,z);
}

#endif
