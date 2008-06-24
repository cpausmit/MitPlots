//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.5 2008/06/18 19:08:14 loizides Exp $
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, xxx
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H
 
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class GenParticle : public Particle
  {
    public:
      GenParticle() {}
      GenParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s, Short_t mo) 
        : Particle(px,py,pz,e), fPdgId(id), fStatus(s), fMother(mo) {}
      ~GenParticle() {}

      Int_t               GetPdgId()  const { return fPdgId; }
      Int_t               GetStatus() const { return fStatus; }

    protected:
      Int_t               fPdgId;        // pdg identifier
      Int_t               fStatus;       // status flag of generator
      Short_t             fMother;       // mother index

    ClassDef(GenParticle,1) // Generated particle class
  };
}
#endif
