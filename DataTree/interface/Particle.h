//--------------------------------------------------------------------------------------------------
// $Id: Particle.h,v 1.13 2008/07/15 11:31:08 loizides Exp $
//
// Particle
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_PARTICLE_H
#define DATATREE_PARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() {}
      ~Particle() {}
     
      virtual Double_t 		Charge() const { return 0; }
      virtual Double_t		E()      const { return Mom().E();}
      virtual Double_t		Eta()    const { return Mom().Eta();}
      virtual Double_t		Mass()   const { return TMath::Sqrt(Mom().M2()); }
      virtual FourVector	Mom()    const { return FourVector(0,0,0,0); }
      virtual Double_t		Phi()    const { return Mom().Phi();}
      virtual Double_t		Pt()     const { return Mom().Pt();}
      virtual Double_t		Px()     const { return Mom().Px();}
      virtual Double_t		Py()     const { return Mom().Py();}
      virtual Double_t		Pz()     const { return Mom().Pz();}
      virtual Double_t		P()      const { return Mom().P();}

      void                      Print(Option_t *opt="") const;

    protected:
     
    ClassDef(Particle, 1) // Generic particle class
  };
}
#endif
