//--------------------------------------------------------------------------------------------------
// $Id: Types.h,v 1.6 2008/06/24 14:01:41 loizides Exp $
//
// Types
//
// Here we define additional types.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_TYPES_H
#define DATATREE_TYPES_H
 
#include <Rtypes.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/Point3Dfwd.h>

namespace mithep 
{
  typedef ::ROOT::Math::LorentzVector< ::ROOT::Math::PxPyPzE4D<double> > FourVector;
  typedef ::ROOT::Math::PositionVector3D< ::ROOT::Math::Cartesian3D<double>, ::ROOT::Math::DefaultCoordinateSystemTag > ThreeVector;
}
#endif
