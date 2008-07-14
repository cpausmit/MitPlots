//--------------------------------------------------------------------------------------------------
// $Id: FitVertex.h,v 1.2 2008/07/01 08:53:42 loizides Exp $
//
// FitVertex
//
// This class holds reconstructed vertex information.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_FITVERTEX_H
#define DATATREE_FITVERTEX_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep 
{
  class FitVertex : public Vertex
  {
    public:
      FitVertex() : fXErr(0), fYErr(0), fZErr(0), fChi2(0), fNDof(0) {}
      FitVertex(Double_t x, Double_t y, Double_t z) : Vertex(x,y,z), fXErr(0), fYErr(0), 
                                                      fZErr(0), fChi2(0), fNDof(0) {}
      FitVertex(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) : 
        Vertex(x,y,z), fXErr(xErr), fYErr(yErr), fZErr(zErr), fChi2(0), fNDof(0) {}
      ~FitVertex() {}

      Double_t		Chi2()      const { return fChi2; } 
      Int_t		NDof()      const { return fNDof; }
      Double_t		XErr()      const { return fXErr; }
      Double_t		YErr()      const { return fYErr; }
      Double_t		ZErr()      const { return fZErr; }
      Double_t		Prob()      const { return TMath::Prob(fChi2,fNDof); }
      void		SetChi2(Double_t chi2) { fChi2 = chi2; }
      void		SetErrors(Double_t xErr, Double_t yErr, Double_t zErr);
      void		SetNDof(Int_t nDof)    { fNDof = nDof; }
            
    protected:
      Double_t	        fXErr; //error in x
      Double_t	        fYErr; //error in y
      Double_t	        fZErr; //error in z
      Double_t	        fChi2; //chi squared of conversion vertex fit
      Int_t             fNDof; //number of degrees of freedom of conversion vertex fit
	
    ClassDef(FitVertex, 1) // Reconstructed vertex class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::FitVertex::SetErrors(Double_t xErr, Double_t yErr, Double_t zErr) 
{
  // Set errors of vertex fix.

  fXErr = xErr;
  fYErr = yErr;
  fZErr = zErr;
}
#endif
