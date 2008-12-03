//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.20 2008/12/01 17:32:34 loizides Exp $
//
// Muon
//
// Details to be worked out... TODO by Phil
//
// Authors: J.Bendavid, C.Loizides, C.Paus, P.Harris
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MUON_H
#define MITANA_DATATREE_MUON_H

#include <TRef.h>
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"

namespace mithep {
  class Muon : public ChargedParticle {
    public:
      Muon();
      ~Muon() {}

      enum EClassType {
        kNone,              //no track assigned
        kGlobal,            //"Global"
        kTrackerOnly,       //"TrackerOnly"
        kSta,               //"Standalone"
        kAny                //any "best" of the above
      };
      
      const Track   *BestTrk()             const;
      const Track   *GlobalTrk()           const;
      const Track   *StandaloneTrk()       const;
      const Track   *TrackerTrk()          const;
      const Track   *Trk()                 const { return BestTrk();          }
      Double_t       IsoR03SumPt()         const { return fIsoR03SumPt;       }
      Double_t       IsoR03EmEt()          const { return fIsoR03EmEt;        }
      Double_t       IsoR03HadEt()         const { return fIsoR03HadEt;       }
      Double_t       IsoR03HoEt()          const { return fIsoR03HoEt;        }
      Int_t          IsoR03NTracks()       const { return fIsoR03NTracks;     }
      Int_t          IsoR03NJets()         const { return fIsoR03NJets;       }
      Double_t       IsoR05SumPt()         const { return fIsoR05SumPt;       }
      Double_t       IsoR05EmEt()          const { return fIsoR05EmEt;        }
      Double_t       IsoR05HadEt()         const { return fIsoR05HadEt;       }
      Double_t       IsoR05HoEt()          const { return fIsoR05HoEt;        }
      Int_t          IsoR05NTracks()       const { return fIsoR05NTracks;     }
      Int_t          IsoR05NJets()         const { return fIsoR05NJets;       }            
      Double_t       EmEnergy()            const { return fEmEnergy;          }
      Double_t       HadEnergy()           const { return fHadEnergy;         }
      Double_t       HoEnergy()            const { return fHoEnergy;          }
      Double_t       EmS9Energy()          const { return fEmS9Energy;        }
      Double_t       HadS9Energy()         const { return fHadS9Energy;       }
      Double_t       HoS9Energy()          const { return fHoS9Energy;        }
      Double_t       Mass()                const { return 105.658369e-3;             }  
      Int_t          NChambers()           const { return fNTraversedChambers;       }
      Int_t          NSegments()           const { return fStationMask.NBitsSet();   }
      Bool_t         StationBit(Int_t bit) const { return fStationMask.TestBit(bit); }
      Double_t       GetDX(Int_t iStation)           const;
      Double_t       GetDY(Int_t iStation)           const;
      Double_t       GetPullX(Int_t iStation)        const;
      Double_t       GetPullY(Int_t iStation)        const;
      Double_t       GetTrackDist(Int_t iStation)    const;
      Double_t       GetTrackDistErr(Int_t iStation) const;
      Int_t          GetNSegments(Int_t iStation)    const;
      Bool_t         HasGlobalTrk()                  const { return fGlobalTrackRef.IsValid(); }
      Bool_t         HasStandaloneTrk()              const { return fStandaloneTrackRef.IsValid(); }
      Bool_t         HasTrackerTrk()                 const { return fTrackerTrackRef.IsValid(); }
      Bool_t         Has(EClassType type)            const;
      EClassType     Is()                            const;
      Int_t          LastHit()                       const;
      Int_t          LastStation(Double_t iMaxD, Double_t iMaxP)               const;
      Int_t          LastStation(Int_t iMax=8)                                 const;
      Bool_t         PromptTight(EClassType type)                              const;
      Bool_t         TMLastStation(Double_t iDYMin = 3., Double_t iPYMin = 3.,
                                   Double_t iDXMin = 3., Double_t iPXMin = 3.,Int_t iN = 2) const;
      Bool_t         TMOneStation(Double_t iDYMin = 3., Double_t iPYMin = 3.,
                                  Double_t iDXMin = 3., Double_t iPXMin = 3.,Int_t iN = 1)  const;
      void	     SetGlobalTrk(const Track *t)          { fGlobalTrackRef = const_cast<Track*>(t); }
      void	     SetStandaloneTrk(const Track *t)      { fStandaloneTrackRef = const_cast<Track*>(t); }
      void	     SetTrackerTrk(const Track *t)         { fTrackerTrackRef = const_cast<Track*>(t); }
      void           SetIsoR03SumPt(Double_t isoR03SumPt)  { fIsoR03SumPt = isoR03SumPt;     }
      void           SetIsoR03EmEt(Double_t isoR03EmEt)    { fIsoR03EmEt = isoR03EmEt;       }
      void           SetIsoR03HadEt(Double_t isoR03HadEt)  { fIsoR03HadEt = isoR03HadEt;     }
      void           SetIsoR03HoEt(Double_t isoR03HoEt)    { fIsoR03HoEt = isoR03HoEt;       }
      void           SetIsoR03NTracks(Int_t isoR03NTracks) { fIsoR03NTracks = isoR03NTracks; }
      void           SetIsoR03NJets(Int_t isoR03NJets)     { fIsoR03NJets = isoR03NJets;     }
      void           SetIsoR05SumPt(Double_t isoR05SumPt)  { fIsoR05SumPt = isoR05SumPt;     }
      void           SetIsoR05EmEt(Double_t isoR05EmEt)    { fIsoR05EmEt = isoR05EmEt;       }
      void           SetIsoR05HadEt(Double_t isoR05HadEt)  { fIsoR05HadEt = isoR05HadEt;     }
      void           SetIsoR05HoEt(Double_t isoR05HoEt)    { fIsoR05HoEt = isoR05HoEt;       }
      void           SetIsoR05NTracks(Int_t isoR05NTracks) { fIsoR05NTracks = isoR05NTracks; }
      void           SetIsoR05NJets(Int_t isoR05NJets)     { fIsoR05NJets = isoR05NJets;     }      
      void           SetEmEnergy(Double_t EmEnergy)        { fEmEnergy = EmEnergy;           }
      void           SetHadEnergy(Double_t HadEnergy)      { fHadEnergy = HadEnergy;         }
      void           SetHoEnergy(Double_t HoEnergy)        { fHoEnergy = HoEnergy;           }
      void           SetEmS9Energy(Double_t EmS9Energy)    { fEmS9Energy = EmS9Energy;       }
      void           SetHadS9Energy(Double_t HadS9Energy)  { fHadS9Energy = HadS9Energy;     }
      void           SetHoS9Energy(Double_t HoS9Energy)    { fHoS9Energy = HoS9Energy;       }
      void           SetNChambers(Int_t iNTraCh)           { fNTraversedChambers = iNTraCh;  }
      void           SetStationMask(UInt_t iStMask)        { fStationMask.SetBits(iStMask);  }
      void           SetDX(Int_t iStation, Double_t iDX);
      void           SetDY(Int_t iStation, Double_t iDY);
      void           SetPullX(Int_t iStation, Double_t iPullX);
      void           SetPullY(Int_t iStation, Double_t iPullY);
      void           SetTrackDist(Int_t iStation, Double_t iDist);
      void           SetTrackDistErr(Int_t iStation, Double_t iDistErr);
      void           SetNSegments(Int_t iStation, Int_t NSegments);

    protected:
      TRef	     fGlobalTrackRef;      //global combined track reference
      TRef	     fStandaloneTrackRef;  //standalone muon track reference
      TRef	     fTrackerTrackRef;     //tracker track reference
      Double32_t     fIsoR03SumPt;         //isolation size R=0.3 sum pt
      Double32_t     fIsoR03EmEt;          //isolation size R=0.3 em  trans energy 
      Double32_t     fIsoR03HadEt;         //isolation size R=0.3 had trans energy
      Double32_t     fIsoR03HoEt;          //isolation size R=0.3 ho  trans energy
      Int_t          fIsoR03NTracks;       //isolation size R=0.3 number of tracks
      Int_t          fIsoR03NJets;         //isolation size R=0.3 number of jets
      Double32_t     fIsoR05SumPt;         //isolation size R=0.5 sum pt
      Double32_t     fIsoR05EmEt;          //isolation size R=0.5 em  trans energy 
      Double32_t     fIsoR05HadEt;         //isolation size R=0.5 had trans energy
      Double32_t     fIsoR05HoEt;          //isolation size R=0.5 ho  trans energy
      Int_t          fIsoR05NTracks;       //isolation size R=0.5 number of tracks
      Int_t          fIsoR05NJets;         //isolation size R=0.5 number of jets      
      Double32_t     fEmEnergy;            //energy deposit in ecal
      Double32_t     fHadEnergy;           //energy deposit in hcal
      Double32_t     fHoEnergy;            //energy deposit in outer hcal
      Double32_t     fEmS9Energy;          //?
      Double32_t     fHadS9Energy;         //?
      Double32_t     fHoS9Energy;          //?
      Int_t          fNTraversedChambers;  //number of tranversed chambers
      BitMask8       fStationMask;         //bitmap of station with tracks, 0-3 DT, 4-7 CSCs
      Double32_t     fDX[8];               //uncertainty in x in given muon chamber
      Double32_t     fDY[8];               //uncertainty in y in given muon chamber
      Double32_t     fPullX[8];            //pull in x in given muon chamber
      Double32_t     fPullY[8];            //pull in y in given muon chamber
      Double32_t     fTrackDist[8];        //dist. to track in trans. plane in given muon chamber
      Double32_t     fTrackDistErr[8];     //error of dist. to track in trans. plane in chamber
      Int_t          fNSegments[8];        //number of segments in given muon chamber

    ClassDef(Muon, 1) // Muon class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::BestTrk() const
{
  // Return "best" track.

  if (GlobalTrk())
    return GlobalTrk();
  else if (TrackerTrk())
    return TrackerTrk();
  else if (StandaloneTrk())
    return StandaloneTrk();

  Error("BestTrk", "No track reference found, returning NULL pointer.");
  return 0;
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::GlobalTrk() const 
{ 
  // Return global combined track.

  return static_cast<const Track*>(fGlobalTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::StandaloneTrk() const 
{ 
  // Return standalone track.

  return static_cast<const Track*>(fStandaloneTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::TrackerTrk() const 
{ 
  // Return tracker track.

  return static_cast<const Track*>(fTrackerTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetDX(Int_t iStation) const 
{
  // Return uncertainty in x in given chamber.

  assert(iStation >= 0 && iStation < 8);
  return fDX[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetDY(Int_t iStation) const 
{
  // Return uncertainty in y in given chamber.

  assert(iStation >= 0 && iStation < 8);
  return fDY[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetPullX(Int_t iStation) const 
{
  // Return pull in x in given chamber.

  assert(iStation >= 0 && iStation < 8);
  return fPullX[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetPullY(Int_t iStation) const 
{
  // Return pull in y in given chamber.
  
  assert(iStation >= 0 && iStation < 8);
  return fPullY[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetTrackDist(Int_t iStation) const 
{
  // Return track distance in given chamber.

  assert(iStation >= 0 && iStation < 8);
  return fTrackDist[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetTrackDistErr(Int_t iStation) const 
{
  // Return error of track distance in given chamber.

  assert(iStation >= 0 && iStation < 8);
  return fTrackDistErr[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Muon::GetNSegments(Int_t iStation) const 
{
  // Return number of segments in chamber.

  assert(iStation >= 0 && iStation < 8);
  return fNSegments[iStation]; 
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Muon::Has(EClassType type) const
{
  // Return true if the muon has a track of given class.

  switch (type) {
    case kAny:
      if (BestTrk()) 
        return kTRUE;
      break;
    case kGlobal:
      if (GlobalTrk()) 
        return kTRUE;
      break;
    case kTrackerOnly:
      if (TrackerTrk()) 
        return kTRUE;
      break;
    case kSta:
      if (StandaloneTrk()) 
        return kTRUE;
      break;
    case kNone:
      if (!BestTrk()) 
        return kTRUE;
      break;
    default:
      break;
  }

  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline mithep::Muon::EClassType mithep::Muon::Is() const
{
  // Return the "best" classification of the muon according to the assigned tracks.

  if (GlobalTrk())
    return kGlobal;
  else if (TrackerTrk())
    return kTrackerOnly;
  else if (StandaloneTrk())
    return kSta;

  return kNone;
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Muon::LastHit() const
{
  // Return the last hit, or -1 if no one found.

  Int_t lId = -1;
  for (Int_t i0 = 0; i0 < 8; ++i0) {
    if (GetDX(i0) < 99999 || GetDY(i0) < 99999) 
      lId = i0;
  }
  return lId;
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Muon::LastStation(Int_t iMax) const
{
  // Return the last station, or -1 of no one found.

  Int_t lId = -1; 
  if(TMath::Abs(iMax) > 8) 
    iMax = 8;
  for (Int_t i0 = 0; i0 < iMax; ++i0) {
    if (StationBit(i0) && ((lId % 4) < (i0 % 4)))
      lId = i0;
  }
  return lId;
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Muon::LastStation(Double_t iMaxD, Double_t iMaxP) const
{
  // Return the last station for given deviation and relative error, or -1 if no one found.

  Int_t lId = -1;
  for (Int_t i0 = 0; i0 < 8; ++i0) {
    if ((lId % 4) > (i0 % 4)) 
      continue;
    if (GetTrackDist(i0) < iMaxD &&
        GetTrackDist(i0)/GetTrackDistErr(i0) < iMaxP) 
      lId = i0;
  }
  return lId;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Muon::PromptTight(EClassType type) const
{
  // Return whether track for given class matches tight quality criteria.

  const mithep::Track *lTrack = 0;
  switch (type) {
    case kAny:
      lTrack = BestTrk();
      break;
    case kGlobal:
      lTrack = GlobalTrk();
      break;
    case kTrackerOnly:
      lTrack = TrackerTrk();
      break;
    case kSta:
      lTrack = StandaloneTrk();
      break;
    default:
      break;
  }

  if (lTrack == 0) 
    return kFALSE;
  if (lTrack->NHits() < 11)        
    return kFALSE;
  if (lTrack->Chi2()/lTrack->Ndof() > 10.)                         
    return kFALSE;
  if (lTrack->D0() > 0.2)                                          
    return kFALSE;
  if ((LastHit() % 4) == 0)                                   
    return kFALSE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Muon::TMOneStation(Double_t iDYMin, Double_t iPYMin,
                                         Double_t iDXMin, Double_t iPXMin, Int_t iN) const
{
  // Check if the muon is matched to at least one station (chamber). 

  if (NSegments() < iN)
    return kFALSE; //second last one

  Bool_t pGoodX  = kFALSE; 
  Bool_t pBadY   = kFALSE;
  for (Int_t i0 = 0; i0 < 8; ++i0) {
    if ((TMath::Abs(GetDX(i0))    < iDXMin  ||
         TMath::Abs(GetPullX(i0)) < iPXMin)) 
      pGoodX = kTRUE; 
    if (pGoodX &&
        (TMath::Abs(GetDY(i0))    < iDYMin  || 
         TMath::Abs(GetPullY(i0)) < iPYMin))  
      return kTRUE;
    if (TMath::Abs(GetDY(i0)) < 999999) 
      pBadY = kTRUE;
    if (i0 == 3 && pGoodX && !pBadY)             
      return kTRUE;
  }
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Muon::TMLastStation(Double_t iDYMin, Double_t iPYMin,
                                          Double_t iDXMin, Double_t iPXMin, Int_t iN) const
{
  // Check if the muon is matched to its last station (chamber). 
  
  if (NSegments() < iN) 
    return kFALSE; //second last one

  Int_t lLast = LastStation(-3.,-3.); // last required station
  if (lLast < 0)                                   
    return kFALSE;
  if (GetDX(lLast) > 9999.)                
    return kFALSE;
  lLast = LastStation(); //no requirements
  if (lLast < 0)                                   
    return kFALSE;
  if (!(TMath::Abs(GetDX(lLast))    < iDXMin  ||
        TMath::Abs(GetPullX(lLast)) < iPXMin))  
    return kFALSE;
  if (lLast == 3) 
    lLast = LastStation(3);
  if (lLast < 0)                                   
    return kFALSE;
  if (!(TMath::Abs(GetDY(lLast))    < iDYMin ||
        TMath::Abs(GetPullY(lLast)) < iPYMin))  
    return kFALSE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetDX(Int_t iStation, Double_t iDX) 
{
  // Return uncertainty in x in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fDX[iStation] = iDX;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetDY(Int_t iStation, Double_t iDY)
{
  // Return uncertainty in y in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fDY[iStation] = iDY;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetPullX(Int_t iStation, Double_t iPullX)
{
  // Set pull in x in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fPullX[iStation] = iPullX;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetPullY(Int_t iStation, Double_t iPullY) 
{
  // Set pull in y in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fPullY[iStation] = iPullY;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetTrackDist(Int_t iStation, Double_t iDist) 
{
  // Set track distance in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fTrackDist[iStation] = iDist;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetTrackDistErr(Int_t iStation, Double_t iDistErr)
{
  // Set error of track distance in given chamber.

  assert(iStation >= 0 && iStation < 8);
  fTrackDistErr[iStation] = iDistErr;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetNSegments(Int_t iStation, Int_t NSegments) 
{
  // Set number of segments in chamber.

  assert(iStation >= 0 && iStation < 8);
  fNSegments[iStation] = NSegments;
}
#endif





