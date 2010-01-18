//--------------------------------------------------------------------------------------------------
// $Id: Track.h,v 1.46 2010/01/07 11:03:41 bendavid Exp $
//
// TrackQuality
//
// Wrapper for BitMask storing the Track Quality flags.  Implemented as a seperate class
// to simplify dependencies and reduce code duplication in case one wants to work with track
// quality elsewhere than in an actual Track object.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRACKQUALITY_H
#define MITANA_DATATREE_TRACKQUALITY_H
 
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataCont/interface/Types.h"

namespace mithep 
{
  class TrackQuality
  {
    public:
      enum EQuality { //taken from DataFormats/TrackReco/interface/TrackBase.h
        undefQuality=-1,
        loose=0,
        tight=1,
        highPurity=2,
        confirmed=3,
        goodIterative=4,
        qualitySize=5
      };


      TrackQuality() {}
      virtual ~TrackQuality() {}

      void                 ClearQuality(EQuality q)  { fQualityMask.ClearBit(q);            } 
      Bool_t               Quality(EQuality q) const { return fQualityMask.TestBit(q);      }
      const BitMask8      &QualityMask()       const { return fQualityMask;                 }
      UInt_t               NQuality()          const { return fQualityMask.NBitsSet();      }
      void                 SetQuality(EQuality q)    { fQualityMask.SetBit(q);              }
      void                 SetQualityMask(const BitMask8 &q) { fQualityMask = q;            }


    protected:
      BitMask8             fQualityMask;         //track quality bitmask
	      
    ClassDef(TrackQuality, 1) // Track class
  };
}
#endif
