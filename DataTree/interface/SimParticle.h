//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.5 2008/06/18 19:08:14 loizides Exp $
//
// SimParticle
//
// Details to be worked out...
//
// Authors: J.Bendavid...
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_SIMPARTICLE_H
#define DATATREE_SIMPARTICLE_H
 
#include <TRef.h>
#include "MitAna/DataTree/interface/GenParticle.h"

namespace mithep 
{
  class SimParticle : public GenParticle
  {
    public:
      SimParticle() : fGenPartRef(0) {}
      SimParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id) 
        : GenParticle(px,py,pz,e,id,0) {}
      ~SimParticle() {}
      
      void 		SetGenParticle(GenParticle* p) { fGenPartRef = p; }
      GenParticle*	GetGenParticle() const { return (GenParticle*)fGenPartRef.GetObject(); }
      
    protected:
      TRef		fGenPartRef;

    ClassDef(SimParticle,1) // Simulated particle class
  };
}
#endif
