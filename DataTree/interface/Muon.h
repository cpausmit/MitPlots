//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.7 2008/06/24 14:01:41 loizides Exp $
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
      
      Track*	GetGlobalTrack() const { return (Track*)fGlobalTrackRef.GetObject(); }
      Track*	GetStandaloneTrack() const { return (Track*)fStandaloneTrackRef.GetObject(); }
      Track*	GetTrackerTrack() const { return (Track*)fTrackerTrackRef.GetObject(); }
      
      Track*	GetTrack() const {return 0;}
      
      Double_t  Mass() const { return 105.658369e-3; }  
      
      void	SetGlobalTrack(Track* globalTrack) { fGlobalTrackRef = globalTrack; }
      void	SetStandaloneTrack(Track* standaloneTrack) { fStandaloneTrackRef = standaloneTrack; }
      void	SetTrackerTrack(Track* trackerTrack) { fTrackerTrackRef = trackerTrack; }
      
    protected:
    	TRef	fGlobalTrackRef;
	TRef	fStandaloneTrackRef;
	TRef	fTrackerTrackRef;
      
    ClassDef(Muon, 1) // Muon class
  };
}

#if 0
> using namespace mithep;
> 
> Track* Muon::GetTrack() const {
>       if (GetGlobalTrack())
>               return GetGlobalTrack();
>       else if (GetStandaloneTrack())
>               return GetStandaloneTrack();
>       else if (GetTrackerTrack())
>               return GetTrackerTrack();
>       else return (Track*)0;
> }
#endif

#endif
