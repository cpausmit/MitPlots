//--------------------------------------------------------------------------------------------------
// $Id $
//
// MuonQuality
//
// Wrapper for BitMask storing the Muon Quality flags. We save information on exactly which 
// of the official muon ID cuts are passed.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MUONQUALITY_H
#define MITANA_DATATREE_MUONQUALITY_H
 
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataCont/interface/Types.h"

namespace mithep 
{
  class MuonQuality
  {
    public:
      enum MuonSelectionType { //taken from DataFormats/MuonReco/interface/MuonSelectors.h
        All = 0,                      //dummy options - always true
        AllGlobalMuons = 1,           //checks isGlobalMuon flag
        AllStandAloneMuons = 2,       //checks isStandAloneMuon flag
        AllTrackerMuons = 3,          //checks isTrackerMuon flag
        TrackerMuonArbitrated = 4,    //resolve ambiguity of sharing segments
        AllArbitrated = 5,            //all muons with the tracker muon arbitrated
        GlobalMuonPromptTight = 6,    //global muons with tighter fit requirements
        TMLastStationLoose = 7,       //penetration depth loose selector
        TMLastStationTight = 8,       //penetration depth tight selector
        TM2DCompatibilityLoose = 9,   //likelihood based loose selector
        TM2DCompatibilityTight = 10,  //likelihood based tight selector
        TMOneStationLoose = 11,       //require one well matched segment
        TMOneStationTight = 12,       //require one well matched segment
        TMLastStationOptimizedLowPtLoose = 13, //combination of TMLastStation and TMOneStation
        TMLastStationOptimizedLowPtTight = 14, //combination of TMLastStation and TMOneStation
        GMTkChiCompatibility = 15,    //require tk stub have good chi2 relative to glb track
        GMStaChiCompatibility = 16,   //require sta stub have good chi2 compatibility 
                                      //relative to glb track
        GMTkKinkTight = 17,           //require a small kink value in the tracker stub
        TMLastStationAngLoose = 18,   //TMLastStationLoose with additional angular cuts
        TMLastStationAngTight = 19,   //TMLastStationTight with additional angular cuts
        TMOneStationAngLoose = 20,    //TMOneStationLoose with additional angular cuts
        TMOneStationAngTight = 21,    //TMOneStationTight with additional angular cuts
        //The two algorithms that follow are identical to what were known as
        //TMLastStationOptimizedLowPt* (sans the Barrel) as late as revision
        //1.7 of this file. The names were changed because indeed the low pt
        //optimization applies only to the barrel region, whereas the sel-
        //ectors above are more efficient at low pt in the endcaps, which is
        //what we feel is more suggestive of the algorithm name. This will be
        //less confusing for future generations of CMS members, I hope...
        TMLastStationOptimizedBarrelLowPtLoose = 22, //combination of TMLastStation and TMOneStation 
                                                     //but with low pT optimization in barrel only
        TMLastStationOptimizedBarrelLowPtTight = 23  //combination of TMLastStation and TMOneStation 
                                                     //but with low pT optimization in barrel only
      };

      MuonQuality() {}
      virtual ~MuonQuality() {}

      void                 ClearQuality(MuonSelectionType q)  { fQualityMask.ClearBit(q);       } 
      Bool_t               Quality(MuonSelectionType q) const { return fQualityMask.TestBit(q); }
      const BitMask32     &QualityMask()                const { return fQualityMask;            }
      UInt_t               NQuality()                   const { return fQualityMask.NBitsSet(); }
      void                 SetQuality(MuonSelectionType q)    { fQualityMask.SetBit(q);         }
      void                 SetQualityMask(const BitMask32 &q) { fQualityMask = q;               }

    protected:
      BitMask32            fQualityMask;         //track quality bitmask
	      
    ClassDef(MuonQuality, 1) 
  };
}
#endif
