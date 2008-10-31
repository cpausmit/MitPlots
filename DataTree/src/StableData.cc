// $Id: StableData.cc,v 1.4 2008/10/29 17:03:31 bendavid Exp $

#include "MitAna/DataTree/interface/StableData.h"

ClassImp(mithep::StableData)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
const BitMask48 StableData::MissedHits() const
{
  // Construct layer mask of missed hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask48();

  BitMask48 missedHits = BadLayers() & ~cOrig->Trk()->Hits();

  return missedHits;

}

//--------------------------------------------------------------------------------------------------
const BitMask48 StableData::WrongHits() const
{
  // Construct layer mask of wrong (before decay vertex) hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask48();

  BitMask48 wrongHits = BadLayers() & cOrig->Trk()->Hits();

  return wrongHits;

}
