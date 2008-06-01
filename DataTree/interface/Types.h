// $Id: Types.h,v 1.2 2008/05/27 19:59:54 loizides Exp $

#ifndef DATATREE_TYPES_H
#define DATATREE_TYPES_H
 
#include <Rtypes.h>
#include <Math/GenVector/LorentzVector.h>

typedef ::ROOT::Math::LorentzVector< ::ROOT::Math::PxPyPzE4D<double> > FourVector;

/* this is a hack needed for current version of rootcint */
namespace mithep 
{
  namespace ROOT 
  {
    namespace Math 
    {
      using namespace ::ROOT::Math;
    }
  }
} /*namespace mithep*/

#endif /*DATATREE_TYPES_H*/
