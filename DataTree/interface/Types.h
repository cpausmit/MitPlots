// $Id: Types.h,v 1.3 2008/06/01 10:03:39 loizides Exp $

#ifndef DATATREE_TYPES_H
#define DATATREE_TYPES_H
 
#include <Rtypes.h>
#include <Math/GenVector/LorentzVector.h>

namespace mithep 
{
  typedef ::ROOT::Math::LorentzVector< ::ROOT::Math::PxPyPzE4D<double> > FourVector;
}

#endif /*DATATREE_TYPES_H*/
