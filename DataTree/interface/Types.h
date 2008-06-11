// $Id: Types.h,v 1.4 2008/06/04 20:00:14 loizides Exp $

#ifndef DATATREE_TYPES_H
#define DATATREE_TYPES_H
 
#include <Rtypes.h>
#include <Math/GenVector/LorentzVector.h>

namespace mithep 
{
  typedef ::ROOT::Math::LorentzVector< ::ROOT::Math::PxPyPzE4D<double> > FourVector;
}

#endif
