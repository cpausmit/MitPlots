//--------------------------------------------------------------------------------------------------
// $Id: ConversionQuality.h,v 1.1 2010/01/18 14:35:10 bendavid Exp $
//
// ConversionQuality
//
// Wrapper for BitMask storing the Conversion Quality flags.  Implemented as a seperate class
// to simplify dependencies and reduce code duplication in case one wants to work with conversion
// quality elsewhere than in an actual DecayParticle/Conversion object.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CONVERSIONQUALITY_H
#define MITANA_DATATREE_CONVERSIONQUALITY_H
 
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataCont/interface/Types.h"

namespace mithep 
{
  class ConversionQuality
  {
    public:
      enum EQuality { //taken from DataFormats/EgammaCandidates/interface/Conversion.h
         generalTracksOnly=0, 
         arbitratedEcalSeeded=1, 
         arbitratedMerged=2, 
         highPurity=8, 
         highEfficiency=9,
         ecalMatched1Track=10,
         ecalMatched2Track=11
      };


      ConversionQuality() {}
      virtual ~ConversionQuality() {}

      void                 ClearQuality(EQuality q)  { fQualityMask.ClearBit(q);            } 
      Bool_t               Quality(EQuality q) const { return fQualityMask.TestBit(q);      }
      const BitMask16     &QualityMask()       const { return fQualityMask;                 }
      UInt_t               NQuality()          const { return fQualityMask.NBitsSet();      }
      void                 SetQuality(EQuality q, Bool_t b=kTRUE) { fQualityMask.SetBit(q,b); }
      void                 SetQualityMask(const BitMask16 &q) { fQualityMask = q;            }


    protected:
      BitMask16            fQualityMask;         //conversion quality bitmask
	      
    ClassDef(ConversionQuality, 1) // ConversionQuality class
  };
}
#endif
