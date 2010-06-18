//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.38 2010/05/29 18:08:05 bendavid Exp $
//
// Muon
//
// Classified into 3 Types
//  Standalone  : Muon fit from hits in the muon chambers
//  Tracker     : Tracker matched track to muon chambers with segments
//  Global      : Combined track and muon chambers fit
//
//  In the muon class all three muon classes exist and can be determined by checking
//  whether a fit track exists for such a Muon (eg HasTrackerTrk() == kTRUE). When 
//  BestTrk function is called the global fit is returned, if that does not
//  exist the tracker fit is returned upon that failure the standalone muon
//  is subsequently returned. To consult more see:
//  http://cmsdoc.cern.ch/cms/Physics/muon/MPOG/Notes/MuonReco.pdf
//
// Quality Varaibles for Selection
//  Isolation : decomposed to IsoRNNXXXXX 
//    NN = 03,05 to denote R =0.3,0.5 in Isolation Cone
//    XXXXX = SumPt - Sum of Pt of Tracks in Cone (using all Pt Tracks)
//    XXXXX = EmEt  - Sum of Et of Em component of Calo Towers  (Veto=0.08)
//    XXXXX = HadEt - Sum of Et of Had component of Calo Towers (Veto=0.1)
//    XXXXX = HoEt  - Sum of Pt of Ho component of Calo Towers  (Veto=0.1)
//    XXXXX = NTrk  - Number of Tracks within Cone (using all Pt Tracks)
//    XXXXX = NJet  - Sum of Jets inside Cone
//
// Muon Quality Variables
//  Extracted from the Muon Tracking Associator 
//   For more se https://twiki.cern.ch/twiki/bin/view/CMS/TrackAssociator
//  Energy Variables : Energy within (5x5 Ecal Crystal/Hcal/Ho) along Track 
//   using calo towers
//  S9 Energy Variables : Energy using reconstructed hits calo towers default
//  Segment Variables :
//   Segment variables are stored in array of 8:
//     0-3: Correspond to segments in 4 DT chambers  in->outward(3 has no Y res)
//     4-7: Correspond to segments in 4 CSC chambers in->out
//    If value undetermined 999999 is returned.
//   Variables:
//    DX,DY,PullX,PullY: Uncertainties/Pulls of propagated track 
//     with respect to local muon segment
//   TrackDist,TrackDistErr: Summed Dist/Err (in X,Y) of segment with respect
//    to propagated track
//   NSegments : Number of segments in muon using Segment+Track Arbitration 
//   NChambers : Number of muon chambers traversed in propagated track
//   LastHit   : Returns farest (from center) station with a recorded segment
//   LastStation  : Returns farest station using Segment+Track Arbitration
//
//  Muon Id Methods: Please see Muon Id Note(as of now unpublished): 
//      https://www.cmsaf.mit.edu/twiki/pub/CmsHep/HepWAnalysis/MuonID-ingo.pdf
//   TMOneStation : Returns bool whether muon passes "Tracker Muon One StationId"
//    -Matching criteria for one of all segments matched to muon
//   TMLastStation : Returns bool whether muon passes "LastStation Id" criteria
//    -Matching criteria for last most segment 
//
// Authors: J.Bendavid, C.Loizides, C.Paus, P.Harris
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MUON_H
#define MITANA_DATATREE_MUON_H

#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataTree/interface/MuonQuality.h"

namespace mithep {
  class Muon : public ChargedParticle {
    public:
      Muon();

      enum EClassType {
        kNone,              //no track assigned
        kGlobal,            //"Global"
        kTracker,           //"Tracker"
        kSta,               //"Standalone"
        kAny                //any "best" of the above
      };
      
      const Track   *BestTrk()                       const;
      const Track   *GlobalTrk()                     const { return fGlobalTrkRef.Obj();       }
      const Track   *StandaloneTrk()                 const { return fStaTrkRef.Obj();          }
      const Track   *TrackerTrk()                    const { return fTrkTrkRef.Obj();          }
      const Track   *Trk()                           const { return BestTrk();                 }
      Double_t       D0PV()                          const { return fD0PV;                     }
      Double_t       D0PVErr()                       const { return fD0PVErr;                  }
      Double_t       D0PVSignificance()              const { return fD0PV/fD0PVErr;            }
      Double_t       Ip3dPV()                        const { return fIp3dPV;                   }
      Double_t       Ip3dPVErr()                     const { return fIp3dPVErr;                }
      Double_t       Ip3dPVSignificance()            const { return fIp3dPV/fIp3dPVErr;        }
      Double_t       D0PVBS()                        const { return fD0PVBS;                   }
      Double_t       D0PVBSErr()                     const { return fD0PVBSErr;                }
      Double_t       D0PVBSSignificance()            const { return fD0PVBS/fD0PVBSErr;        }
      Double_t       Ip3dPVBS()                      const { return fIp3dPVBS;                 }
      Double_t       Ip3dPVBSErr()                   const { return fIp3dPVBSErr;              }
      Double_t       Ip3dPVBSSignificance()          const { return fIp3dPVBS/fIp3dPVBSErr;    }
      Double_t       PVCompatibility()               const { return fPVCompatibility;          }
      Double_t       PVBSCompatibility()             const { return fPVBSCompatibility;        }
      Double_t       EmEnergy()                      const { return fEmEnergy;                 }
      Double_t       EmS9Energy()                    const { return fEmS9Energy;               }
      Double_t       GetDX(Int_t iStation)           const;
      Double_t       GetDY(Int_t iStation)           const;
      Double_t       GetPullX(Int_t iStation)        const;
      Double_t       GetPullY(Int_t iStation)        const;
      Double_t       GetTrackDist(Int_t iStation)    const;
      Double_t       GetTrackDistErr(Int_t iStation) const;
      Int_t          GetNSegments(Int_t iStation)    const;
      Bool_t         Has(EClassType type)            const;
      Bool_t         HasTrk()                        const;
      Bool_t         HasGlobalTrk()                  const { return fGlobalTrkRef.IsValid();   }
      Bool_t         HasStandaloneTrk()              const { return fStaTrkRef.IsValid();      }
      Bool_t         HasTrackerTrk()                 const { return fTrkTrkRef.IsValid();      }
      Double_t       HadEnergy()                     const { return fHadEnergy;                }
      Double_t       HadS9Energy()                   const { return fHadS9Energy;              }
      Double_t       HoEnergy()                      const { return fHoEnergy;                 }
      Double_t       HoS9Energy()                    const { return fHoS9Energy;               }
      EClassType     Is()                            const;
      Bool_t         IsGlobalMuon()                  const { return fIsGlobalMuon;             }
      Bool_t         IsTrackerMuon()                 const { return fIsTrackerMuon;            }
      Bool_t         IsStandaloneMuon()              const { return fIsStandaloneMuon;         }
      Bool_t         IsCaloMuon()                    const { return fIsCaloMuon;               }
      Double_t       IsoR03SumPt()                   const { return fIsoR03SumPt;              }
      Double_t       IsoR03EmEt()                    const { return fIsoR03EmEt;               }
      Double_t       IsoR03HadEt()                   const { return fIsoR03HadEt;              }
      Double_t       IsoR03HoEt()                    const { return fIsoR03HoEt;               }
      UShort_t       IsoR03NTracks()                 const { return fIsoR03NTracks;            }
      UShort_t       IsoR03NJets()                   const { return fIsoR03NJets;              } 
      Double_t       IsoR05SumPt()                   const { return fIsoR05SumPt;              }
      Double_t       IsoR05EmEt()                    const { return fIsoR05EmEt;               }
      Double_t       IsoR05HadEt()                   const { return fIsoR05HadEt;              }
      Double_t       IsoR05HoEt()                    const { return fIsoR05HoEt;               }
      UShort_t       IsoR05NTracks()                 const { return fIsoR05NTracks;            }
      UShort_t       IsoR05NJets()                   const { return fIsoR05NJets;              }
      UInt_t         NValidHits()                    const { return fNValidHits;               }
      UInt_t         NChambers()                     const { return fNTraversedChambers;       }
      UInt_t         NSegments()                     const { return fStationMask.NBitsSet();   }
      Int_t          LastHit()                       const;
      Int_t          LastStation(Double_t iMaxD, Double_t iMaxP)               const;
      Int_t          LastStation(Int_t iMax=8)       const;
      Int_t          ObjId()                         const { return ObjType()*1000+Is();       }
      EObjType       ObjType()                       const { return kMuon;                     }
      void           Print(Option_t *opt="")         const;
      Bool_t         PromptTight(EClassType type)    const;
      const MuonQuality  &Quality()                  const { return fQuality;                  }
      MuonQuality        &Quality()                        { return fQuality;                  }
      Bool_t         StationBit(Int_t bit)           const { return fStationMask.TestBit(bit); }
      Bool_t         TMLastStation(Double_t iDYMin = 3, Double_t iPYMin = 3,
                                   Double_t iDXMin = 3, Double_t iPXMin = 3,UInt_t iN = 2) const;
      Bool_t         TMOneStation(Double_t iDYMin = 3, Double_t iPYMin = 3,
                                  Double_t iDXMin = 3, Double_t iPXMin = 3,UInt_t iN = 1)  const;
      void           SetCharge(Char_t x)                   { fCharge = x; ClearCharge();       }
      void	     SetGlobalTrk(const Track *t)          
                       { fGlobalTrkRef = t; ClearMom(); ClearCharge(); }
      void	     SetStandaloneTrk(const Track *t)      
                       { fStaTrkRef = t;    ClearMom(); ClearCharge(); }
      void	     SetTrackerTrk(const Track *t)         
                       { fTrkTrkRef = t;    ClearMom(); ClearCharge(); }
      void           SetDX(Int_t iStation, Double_t iDX);
      void           SetDY(Int_t iStation, Double_t iDY);
      void           SetD0PV(Double_t x)                   { fD0PV = x;                        }
      void           SetD0PVErr(Double_t x)                { fD0PVErr = x;                     }
      void           SetIp3dPV(Double_t x)                 { fIp3dPV = x;                      }
      void           SetIp3dPVErr(Double_t x)              { fIp3dPVErr = x;                   }
      void           SetD0PVBS(Double_t x)                 { fD0PVBS = x;                      }
      void           SetD0PVBSErr(Double_t x)              { fD0PVBSErr = x;                   }
      void           SetIp3dPVBS(Double_t x)               { fIp3dPVBS = x;                    }
      void           SetIp3dPVBSErr(Double_t x)            { fIp3dPVBSErr = x;                 }
      void           SetPVCompatibility(Double_t x)        { fPVCompatibility = x;             }
      void           SetPVBSCompatibility(Double_t x)      { fPVBSCompatibility = x;           }
      void           SetEmEnergy(Double_t EmEnergy)        { fEmEnergy = EmEnergy;             }
      void           SetEmS9Energy(Double_t EmS9Energy)    { fEmS9Energy = EmS9Energy;         }
      void           SetHadEnergy(Double_t HadEnergy)      { fHadEnergy = HadEnergy;           }
      void           SetHadS9Energy(Double_t HadS9Energy)  { fHadS9Energy = HadS9Energy;       }
      void           SetHoEnergy(Double_t HoEnergy)        { fHoEnergy = HoEnergy;             }
      void           SetHoS9Energy(Double_t HoS9Energy)    { fHoS9Energy = HoS9Energy;         }
      void           SetIsGlobalMuon(Bool_t b)             { fIsGlobalMuon = b;                }
      void           SetIsTrackerMuon(Bool_t b)            { fIsTrackerMuon = b;               }
      void           SetIsStandaloneMuon(Bool_t b)         { fIsStandaloneMuon = b;            }
      void           SetIsCaloMuon(Bool_t b)               { fIsCaloMuon = b;                  }
      void           SetIsoR03SumPt(Double_t isoR03SumPt)  { fIsoR03SumPt = isoR03SumPt;       }
      void           SetIsoR03EmEt(Double_t isoR03EmEt)    { fIsoR03EmEt = isoR03EmEt;         }
      void           SetIsoR03HadEt(Double_t isoR03HadEt)  { fIsoR03HadEt = isoR03HadEt;       }
      void           SetIsoR03HoEt(Double_t isoR03HoEt)    { fIsoR03HoEt = isoR03HoEt;         }
      void           SetIsoR03NTracks(UShort_t isoR03NTrk) { fIsoR03NTracks = isoR03NTrk;      }
      void           SetIsoR03NJets(UShort_t isoR03NJets)  { fIsoR03NJets = isoR03NJets;       }
      void           SetIsoR05SumPt(Double_t isoR05SumPt)  { fIsoR05SumPt = isoR05SumPt;       }
      void           SetIsoR05EmEt(Double_t isoR05EmEt)    { fIsoR05EmEt = isoR05EmEt;         }
      void           SetIsoR05HadEt(Double_t isoR05HadEt)  { fIsoR05HadEt = isoR05HadEt;       }
      void           SetIsoR05HoEt(Double_t isoR05HoEt)    { fIsoR05HoEt = isoR05HoEt;         }
      void           SetIsoR05NTracks(UShort_t isoR05NTrk) { fIsoR05NTracks = isoR05NTrk;      }
      void           SetIsoR05NJets(UShort_t isoR05NJets)  { fIsoR05NJets = isoR05NJets;       }
      void           SetNValidHits(UShort_t iNValidHits)   { fNValidHits  = iNValidHits;       }
      void           SetNChambers(UShort_t iNTraCh)        { fNTraversedChambers = iNTraCh;    }
      void           SetNSegments(Int_t iStation, Int_t NSegments);
      void           SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi);
      void           SetPullX(Int_t iStation, Double_t iPullX);
      void           SetPullY(Int_t iStation, Double_t iPullY);
      void           SetStationMask(UInt_t iStMask)        { fStationMask.SetBits(iStMask);    }
      void           SetTrackDist(Int_t iStation, Double_t iDist);
      void           SetTrackDistErr(Int_t iStation, Double_t iDistErr);

    protected:
      Double_t       GetCharge()                     const;
      Double_t       GetMass()                       const { return 105.658369e-3;             }  
      void           GetMom()                        const;

      Vect3C         fMom;                 //stored three-momentum
      Char_t         fCharge;              //stored charge - filled with -99 when reading old files
      Ref<Track>     fGlobalTrkRef;        //global combined track reference
      Ref<Track>     fStaTrkRef;           //standalone muon track reference
      Ref<Track>     fTrkTrkRef;           //tracker track reference
      Double32_t     fIsoR03SumPt;         //[0,0,14]isolation size R=0.3 sum pt
      Double32_t     fIsoR03EmEt;          //[0,0,14]isolation size R=0.3 em  trans energy 
      Double32_t     fIsoR03HadEt;         //[0,0,14]isolation size R=0.3 had trans energy
      Double32_t     fIsoR03HoEt;          //[0,0,14]isolation size R=0.3 ho  trans energy
      UShort_t       fIsoR03NTracks;       //isolation size R=0.3 number of tracks
      UShort_t       fIsoR03NJets;         //isolation size R=0.3 number of jets
      Double32_t     fIsoR05SumPt;         //[0,0,14]isolation size R=0.5 sum pt
      Double32_t     fIsoR05EmEt;          //[0,0,14]isolation size R=0.5 em  trans energy 
      Double32_t     fIsoR05HadEt;         //[0,0,14]isolation size R=0.5 had trans energy
      Double32_t     fIsoR05HoEt;          //[0,0,14]isolation size R=0.5 ho  trans energy
      UShort_t       fIsoR05NTracks;       //isolation size R=0.5 number of tracks
      UShort_t       fIsoR05NJets;         //isolation size R=0.5 number of jets      
      Double32_t     fEmEnergy;            //[0,0,14]energy deposit in ecal
      Double32_t     fHadEnergy;           //[0,0,14]energy deposit in hcal
      Double32_t     fHoEnergy;            //[0,0,14]energy deposit in outer hcal
      Double32_t     fEmS9Energy;          //[0,0,14]energy deposit in 3x3 ecal 
      Double32_t     fHadS9Energy;         //[0,0,14]energy deposit in 3x3 hcal
      Double32_t     fHoS9Energy;          //[0,0,14]energy deposit in 3x3 outer hcal
      Double32_t     fD0PV;                //[0,0,14]transverse impact parameter to signal PV
      Double32_t     fD0PVErr;             //[0,0,14]transverse impact parameter uncertainty to signal PV
      Double32_t     fIp3dPV;              //[0,0,14]3d impact parameter to signal PV
      Double32_t     fIp3dPVErr;           //[0,0,14]3d impact parameter uncertainty to signal PV
      Double32_t     fD0PVBS;              //[0,0,14]transverse impact parameter to signal PV w/ bs constraint
      Double32_t     fD0PVBSErr;           //[0,0,14]transverse impact parameter uncertainty to signal PV w/ bs constraint
      Double32_t     fIp3dPVBS;            //[0,0,14]3d impact parameter to signal PV w/ bs constraint
      Double32_t     fIp3dPVBSErr;         //[0,0,14]3d impact parameter uncertainty to signal PV w/ bs constraint
      Double32_t     fPVCompatibility;     //[0,0,14]chi^2 compatibility with signal PV (ndof=2)
      Double32_t     fPVBSCompatibility;   //[0,0,14]chi^2 compatibility with signal PV w/ bs constraint (ndof=2)
      UShort_t       fNValidHits;          //number of Valid hits in global fit
      UShort_t       fNTraversedChambers;  //number of traversed chambers
      MuonQuality    fQuality;             //muon quality
      BitMask8       fStationMask;         //bitmap of station with tracks, 0-3 DT, 4-7 CSCs
      Double32_t     fDX[8];               //[0,0,14]uncertainty in x in given muon chamber
      Double32_t     fDY[8];               //[0,0,14]uncertainty in y in given muon chamber
      Double32_t     fPullX[8];            //[0,0,14]pull in x in given muon chamber
      Double32_t     fPullY[8];            //[0,0,14]pull in y in given muon chamber
      Double32_t     fTrackDist[8];        //[0,0,14]dist. to track in trans. plane in muon chamber
      Double32_t     fTrackDistErr[8];     //[0,0,14]error of dist. to track in trans. plane
      Int_t          fNSegments[8];        //number of segments in given muon chamber
      Bool_t         fIsGlobalMuon;        //GlobalMuon algo flag
      Bool_t         fIsTrackerMuon;       //TrackerMuon algo flag
      Bool_t         fIsStandaloneMuon;    //StandaloneMuon algo flag
      Bool_t         fIsCaloMuon;          //CaloMuon algo flag

    ClassDef(Muon, 6) // Muon class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::BestTrk() const
{
  // Return "best" track.

  if (HasTrackerTrk())
    return TrackerTrk();
  else if (HasGlobalTrk())
    return GlobalTrk();
  else if (HasStandaloneTrk())
    return StandaloneTrk();

  Error("BestTrk", "No track reference found, returning NULL pointer.");
  return 0;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Muon::GetCharge() const
{
  // Return stored charge, unless it is set to invalid (-99),
  // in that case get charge from track as before

  if (fCharge==-99)
    return mithep::ChargedParticle::GetCharge();
  else
    return fCharge;

}

//--------------------------------------------------------------------------------------------------
inline void mithep::Muon::GetMom() const
{
  // Get momentum of the muon. We use an explicitly stored three vector, with the pdg mass,
  // since the momentum vector may be computed non-trivially in cmssw (since the tracker
  // information has better resolution apparently in some cases than the global fit.)
  // If momentum is unfilled, fall back to old method of getting momentum from best track
  // (for backwards compatibility.)
  
  if (fMom.Rho()>0.0) {
    fCachedMom.SetCoordinates(fMom.Rho(),fMom.Eta(),fMom.Phi(),GetMass());
  }
  else {
    mithep::ChargedParticle::GetMom();
  }
  
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
      if (HasTrk()) 
        return kTRUE;
      break;
    case kGlobal:
      if (HasGlobalTrk()) 
        return kTRUE;
      break;
    case kTracker:
      if (HasTrackerTrk()) 
        return kTRUE;
      break;
    case kSta:
      if (HasStandaloneTrk()) 
        return kTRUE;
      break;
    case kNone:
      if (!HasTrk()) 
        return kTRUE;
      break;
    default:
      break;
  }

  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::Muon::HasTrk() const
{
  // Return true if the muon has assigned any kind of track.

  return (HasGlobalTrk() || HasTrackerTrk() || HasStandaloneTrk());
}

//--------------------------------------------------------------------------------------------------
inline mithep::Muon::EClassType mithep::Muon::Is() const
{
  // Return the "best" classification of the muon according to the assigned tracks.

  if (HasGlobalTrk())
    return kGlobal;
  else if (HasTrackerTrk())
    return kTracker;
  else if (HasStandaloneTrk())
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
    case kTracker:
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
                                         Double_t iDXMin, Double_t iPXMin, UInt_t iN) const
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
                                          Double_t iDXMin, Double_t iPXMin, UInt_t iN) const
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

//-------------------------------------------------------------------------------------------------
inline void mithep::Muon::SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi)
{
  // Set three-vector
  
  fMom.Set(pt,eta,phi);
  ClearMom();
}
#endif





