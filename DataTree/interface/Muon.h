//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.8 2008/06/30 16:54:40 loizides Exp $
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
      
      const Track   *GetGlobalTrack()     const;
      const Track   *GetStandaloneTrack() const;
      const Track   *GetTrackerTrack()    const;
      const Track*   GetTrack()           const;
      Double_t       Mass()               const { return 105.658369e-3; }  
      
      void	     SetGlobalTrack(Track* t)     { fGlobalTrackRef = t; }
      void	     SetStandaloneTrack(Track* t) { fStandaloneTrackRef = t; }
      void	     SetTrackerTrack(Track* t)    { fTrackerTrackRef = t; }
      
    protected:
      TRef	     fGlobalTrackRef;      //global combined track reference
      TRef	     fStandaloneTrackRef;  //standalone muon track reference
      TRef	     fTrackerTrackRef;     //tracker track reference
      
    ClassDef(Muon, 1) // Muon class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::GetGlobalTrack() const 
{ 
  // Return global combined track.

  return static_cast<const Track*>(fGlobalTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::GetStandaloneTrack() const 
{ 
  // Return standalone track.

  return static_cast<const Track*>(fStandaloneTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::GetTrackerTrack() const 
{ 
  // Return tracker track.

  return static_cast<const Track*>(fTrackerTrackRef.GetObject()); 
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Muon::GetTrack() const
{
  // Return "best" track.

  if (GetGlobalTrack())
    return GetGlobalTrack();
  else if (GetStandaloneTrack())
    return GetStandaloneTrack();
  else if (GetTrackerTrack())
    return GetTrackerTrack();

  return 0;
}
#endif
