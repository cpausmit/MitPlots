//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.3 2008/07/16 10:00:58 bendavid Exp $
//
// Met
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MET_H
#define MITANA_DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() : fPx(0), fPy(0) {}
      Met(Double_t px, Double_t py) : fPx(px), fPy(py) {}
      ~Met() {}

      Double_t          Charge() const { return 0; }
      Double_t		E()      const { return Pt();}
      Double_t		Eta()    const { return Mom().Eta();}
      Double_t		Mass()   const { return TMath::Sqrt(Mom().M2()); }
      FourVector	Mom()    const { return FourVector(fPx,fPy,0,Pt()); }
      Double_t		Phi()    const { return TMath::ATan2(fPy,fPx); }
      Double_t		Pt()     const { return TMath::Sqrt(fPx*fPx+fPy*fPy);}
      Double_t		Px()     const { return fPx;}
      Double_t		Py()     const { return fPy;}
      Double_t		Pz()     const { return 0; }
      Double_t		P()      const { return Pt(); }

    protected:
      Double_t fPx;          //x-component
      Double_t fPy;          //y-component

    ClassDef(Met, 1) // Missing Et class
  };
}
#endif
