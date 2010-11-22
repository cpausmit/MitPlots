// $Id: StableData.cc,v 1.5 2008/10/31 17:42:09 bendavid Exp $

#include "MitAna/DataTree/interface/StableData.h"

ClassImp(mithep::StableData)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
const BitMask48 StableData::MissedLayers() const
{
  // Construct layer mask of missed hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask48();

  BitMask48 missedHits = BadLayers() & ~cOrig->Trk()->Hits();

  return missedHits;

}

//--------------------------------------------------------------------------------------------------
const BitMask48 StableData::WrongLayers() const
{
  // Construct layer mask of wrong (before decay vertex) hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask48();

  BitMask48 wrongHits = BadLayers() & cOrig->Trk()->Hits();

  return wrongHits;

}
