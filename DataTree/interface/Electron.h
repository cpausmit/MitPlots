//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.7 2008/06/24 14:01:41 loizides Exp $
//
// Electron
//
// Details to be worked out...
//
// Authors: C.Loizides, J. Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_ELECTRON_H
#define DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/Lepton.h"

namespace mithep 
{
  class Electron : public Lepton
  {
    public:
      Electron() {}
      ~Electron() {}
      
      Track*	GetGsfTrack() const { return (Track*)fGsfTrackRef.GetObject(); }
      Track*	GetTrackerTrack() const { return (Track*)fTrackerTrackRef.GetObject(); }
      
      Track*	GetTrack() const {return 0;}
      
      Double_t  Mass() const { return 0.51099892e-3; }
      
      void	SetGsfTrack(Track* gsfTrack) { fGsfTrackRef = gsfTrack; }
      void	SetTrackerTrack(Track* trackerTrack) { fTrackerTrackRef = trackerTrack; }
      
    protected:
    	TRef	fGsfTrackRef;
	TRef	fTrackerTrackRef;
      
    ClassDef(Electron, 1) // Electron class
  };
}
#endif

#if 0
> Track* Electron::GetTrack() const {
>       if (GetGsfTrack())
>               return GetGsfTrack();
>       else if (GetTrackerTrack())
>               return GetTrackerTrack();
>       else return (Track*)0;
> }
#endif
