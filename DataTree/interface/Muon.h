//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.15 2008/09/10 17:10:55 pharris Exp $
//
// Muon
//
// Details to be worked out...
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
      Muon() {}
      ~Muon() {}
      
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
      Double_t       GetDX(Int_t iStation)             const;
      Double_t       GetDY(Int_t iStation)             const;
      Double_t       GetPullX(Int_t iStation)          const;
      Double_t       GetPullY(Int_t iStation)          const;
      Double_t       GetTrackDist(Int_t iStation)      const;
      Double_t       GetTrackDistErr(Int_t iStation)   const;
      Int_t          GetNSegments(Int_t iStation) const;
      void	     SetGlobalTrk(Track* t)                { fGlobalTrackRef = t;            }
      void	     SetStandaloneTrk(Track* t)            { fStandaloneTrackRef = t;        }
      void	     SetTrackerTrk(Track* t)               { fTrackerTrackRef = t;           }
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
      Double32_t     fEmEnergy;            //?
      Double32_t     fHadEnergy;           //?
      Double32_t     fHoEnergy;            //?
      Double32_t     fEmS9Energy;          //?
      Double32_t     fHadS9Energy;         //?
      Double32_t     fHoS9Energy;          //?
      Int_t          fNTraversedChambers;  //number of tranversed chambers
      BitMask8       fStationMask;         //bitmap of station with tracks, 0-3 DT, 4-7 CSCs segment components
      Double32_t     fDX[8];               //uncertainty in x in given muon chamber
      Double32_t     fDY[8];               //uncertainty in y in given muon chamber
      Double32_t     fPullX[8];            //pull in x in given muon chamber
      Double32_t     fPullY[8];            //pull in y in given muon chamber
      Double32_t     fTrackDist[8];        //distance to track in tranverse plane in given muon chamber
      Double32_t     fTrackDistErr[8];     //error of distance to track in transverse plane in given muon chamber
      Int_t          fNSegments[8];        //number of segments in chamber in given muon chamber

    ClassDef(Muon, 1) // Muon class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::BestTrk() const
{
  // Return "best" track.

  if (GlobalTrk())
    return GlobalTrk();
  else if (StandaloneTrk())
    return StandaloneTrk();
  else if (TrackerTrk())
    return TrackerTrk();

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
