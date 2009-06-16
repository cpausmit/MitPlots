//--------------------------------------------------------------------------------------------------
// $Id: Pair.h,v 1.9 2009/03/18 15:44:32 loizides Exp $
//
// Pair
//
// Pair class to allow matching of particles to each other.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PAIR_H
#define MITANA_DATATREE_PAIR_H
 
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  template<class A, class B=A>
  class Pair : public DataBase
  {
    public:
    Pair(const A *p1, const B *p2) : fP1(const_cast<A*>(p1)), fP2(const_cast<B*>(p2)), 
                                     fOwn1(0), fOwn2(0) {}
//      Pair(cA *p1, const B *p2) : fPart1(p1), fPart2(p2), fOwn1(0), fOwn2(0) {}
      ~Pair() { if (fOwn1) delete fP1; if (fOwn2) delete fP2; } 

      const A    *First()   const { return fP1; }
      const B    *Second()  const { return fP2; }

      EObjType    ObjType() const { return kPair;  }      
             
    protected:
      A          *fP1;      //first object 
      B          *fP2;      //second object
      Bool_t      fOwn1;    //=true then first object is owned
      Bool_t      fOwn2;    //=true then second object is owned

    ClassDef(Pair, 1) // Pair class
  };
}
#endif
