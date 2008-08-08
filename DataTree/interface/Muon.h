//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.12 2008/07/29 07:55:40 loizides Exp $
//
// Muon
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_MUON_H
#define DATATREE_MUON_H

#include <TRef.h>
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Muon : public ChargedParticle
  {
    public:
      Muon() {}
      ~Muon() {}
      
      const Track   *BestTrk()            const;
      const Track   *GlobalTrk()          const;
      const Track   *StandaloneTrk()      const;
      const Track   *TrackerTrk()         const;
      const Track   *Trk()                const  { return BestTrk();          }
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
      Double_t       Mass()                const { return 105.658369e-3;      }  
      
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

    protected:
      TRef	     fGlobalTrackRef;      //global combined track reference
      TRef	     fStandaloneTrackRef;  //standalone muon track reference
      TRef	     fTrackerTrackRef;     //tracker track reference
      Double_t       fIsoR03SumPt;
      Double_t       fIsoR03EmEt;
      Double_t       fIsoR03HadEt;
      Double_t       fIsoR03HoEt;
      Int_t          fIsoR03NTracks;
      Int_t          fIsoR03NJets;
      Double_t       fIsoR05SumPt;
      Double_t       fIsoR05EmEt;
      Double_t       fIsoR05HadEt;
      Double_t       fIsoR05HoEt;
      Int_t          fIsoR05NTracks;
      Int_t          fIsoR05NJets;      
      Double_t       fEmEnergy;
      Double_t       fHadEnergy;
      Double_t       fHoEnergy;
      Double_t       fEmS9Energy;
      Double_t       fHadS9Energy;
      Double_t       fHoS9Energy;

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
#endif
