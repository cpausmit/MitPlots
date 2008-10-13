// $Id: StableData.cc,v 1.1 2008/09/30 12:52:53 bendavid Exp $

#include "MitAna/DataTree/interface/StableData.h"

ClassImp(mithep::StableData)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
const BitMask64 StableData::MissedHits() const
{
  // Construct layer mask of missed hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask64(0);

  BitMask64 missedHits = Layers() & ~cOrig->Trk()->Hits();

  return missedHits;

}

//--------------------------------------------------------------------------------------------------
const BitMask64 StableData::WrongHits() const
{
  // Construct layer mask of wrong (before decay vertex) hits

  const ChargedParticle *cOrig = dynamic_cast<const ChargedParticle*>(Original());
  if (!cOrig)
    return BitMask64(0);

  BitMask64 wrongHits = ~Layers() & cOrig->Trk()->Hits();

  return wrongHits;

}