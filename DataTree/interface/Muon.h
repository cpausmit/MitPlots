//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.9 2008/07/01 08:54:57 loizides Exp $
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
#include "MitAna/DataTree/interface/Lepton.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Muon : public Lepton
  {
    public:
      Muon() {}
      ~Muon() {}
      
      const Track   *BestTrk()            const;
      const Track   *GlobalTrk()          const;
      const Track   *StandaloneTrk()      const;
      const Track   *TrackerTrk()         const;
      Double_t       Mass()               const { return 105.658369e-3; }  
      
      void	     SetGlobalTrk(Track* t)     { fGlobalTrackRef = t; }
      void	     SetStandaloneTrk(Track* t) { fStandaloneTrackRef = t; }
      void	     SetTrackerTrk(Track* t)    { fTrackerTrackRef = t; }
      
    protected:
      TRef	     fGlobalTrackRef;      //global combined track reference
      TRef	     fStandaloneTrackRef;  //standalone muon track reference
      TRef	     fTrackerTrackRef;     //tracker track reference
      
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
