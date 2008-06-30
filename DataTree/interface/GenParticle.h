//--------------------------------------------------------------------------------------------------
// $Id: GenParticle.h,v 1.6 2008/06/24 14:01:41 loizides Exp $
//
// GenParticle
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid...
//--------------------------------------------------------------------------------------------------



#ifndef DATATREE_GENPARTICLE_H
#define DATATREE_GENPARTICLE_H
 
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/Vertex.h"


namespace mithep 
{
  class GenParticle : public CompositeParticle
  {
    public:
      GenParticle() {}
      GenParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Int_t id, Int_t s) 
        : fPdgId(id), fStatus(s), fFourVector(px,py,pz,e), fDecayVertex(0,0,0) {}
      ~GenParticle() {}

      Int_t               GetPdgId()  const { return fPdgId; }
      Int_t               GetStatus() const { return fStatus; }

      FourVector	  Mom() const { return fFourVector; }
      Vertex*		  GetDecayVertex() { return &fDecayVertex; }
      
      void		  SetMom(Double_t px, Double_t py, Double_t pz, Double_t e) { fFourVector.SetXYZT(px, py, pz, e); }
      
    protected:
      Int_t               fPdgId;        // pdg identifier
      Int_t               fStatus;       // status flag of generator
      FourVector          fFourVector; // four momentum vector
      Vertex		  fDecayVertex; //gen decay vertex
      

    ClassDef(GenParticle,1) // Generated particle class
  };
}
#endif
