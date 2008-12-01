//--------------------------------------------------------------------------------------------------
// $Id: Particle.h,v 1.22 2008/11/27 20:34:54 loizides Exp $
//
// Particle
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PARTICLE_H
#define MITANA_DATATREE_PARTICLE_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Particle : public DataObject
  {
    public:
      Particle() {}
      ~Particle() {}
     
      Double_t                  AbsEta() const { return TMath::Abs(Eta()); }
      virtual Double_t 		Charge() const = 0;
      
      virtual Double_t		E()      const { return Mom().E();}
      virtual Double_t		Et()     const { return Mom().E()*Mom().Pt()/Mom().P(); }
      virtual Double_t		Eta()    const { return Mom().Eta();}
      virtual Double_t		Mass()   const { return TMath::Sqrt(Mom().M2()); }
      virtual Double_t		Mt()     const { return TMath::Sqrt(Mom().Mt2()); }
      virtual FourVector	Mom()    const = 0;
      virtual Double_t		Phi()    const { return Mom().Phi();}
      Double_t                  PhiDeg() const { return Phi() * 180. / TMath::Pi(); }
      virtual Double_t		Pt()     const { return Mom().Pt();}
      virtual Double_t		Px()     const { return Mom().Px();}
      virtual Double_t		Py()     const { return Mom().Py();}
      virtual Double_t		Pz()     const { return Mom().Pz();}
      virtual Double_t		P()      const { return Mom().P();}
      virtual Double_t          Theta()  const { return Mom().Theta(); }
      void                      Print(Option_t *opt="") const;
     
    ClassDef(Particle, 1) // Generic particle class
  };
}
#endif
