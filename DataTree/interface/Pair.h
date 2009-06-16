//--------------------------------------------------------------------------------------------------
// $Id: Pair.h,v 1.1 2009/06/16 15:56:21 loizides Exp $
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
      Pair() : fP1(0), fP2(0), fOwn1(0), fOwn2(0) {}
      Pair(const A *p1, const B *p2) : fP1(const_cast<A*>(p1)), fP2(const_cast<B*>(p2)), 
                                       fOwn1(0), fOwn2(0) {}
      Pair(A *p1, Bool_t o, const B *p2) : fP1(p1), fP2(const_cast<B*>(p2)), 
                                           fOwn1(o), fOwn2(0) {}
      Pair(const A *p1, B *p2, Bool_t o) : fP1(const_cast<A*>(p1)), fP2(p2), 
                                                 fOwn1(0), fOwn2(o) {}
      Pair(A *p1, B *p2, Bool_t o1, Bool_t o2) : fP1(p1), fP2(p2), 
                                                 fOwn1(o1), fOwn2(o2) {}
      ~Pair() { if (fOwn1) delete fP1; if (fOwn2) delete fP2; } 

      const A    *First()    const { return fP1;   }
      const B    *Second()   const { return fP2;   }
      EObjType    ObjType()  const { return kPair; }      
      const A    *P1()       const { return fP1;   }
      const B    *P2()       const { return fP2;   }
             
    protected:
      A          *fP1;      //first object 
      B          *fP2;      //second object
      Bool_t      fOwn1;    //=true then first object is owned
      Bool_t      fOwn2;    //=true then second object is owned

    ClassDef(Pair, 1) // Pair class
  };
}
#endif
