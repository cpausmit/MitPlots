//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.8 2008/06/30 16:54:40 loizides Exp $
//
// Electron
//
// Details to be worked out...
//
// Authors: C.Loizides, J.Bendavid
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
      
      const Track         *GetGsfTrack()     const;
      const Track         *GetTrackerTrack() const;
      const Track         *GetTrack()        const;
      Double_t             Mass()            const { return 0.51099892e-3; }
      
      void	           SetGsfTrack(Track* t)     { fGsfTrackRef = t; }
      void	           SetTrackerTrack(Track* t) { fTrackerTrackRef = t; }
      
    protected:
      TRef	           fGsfTrackRef;     //global combined track reference
      TRef	           fTrackerTrackRef; //tracker track reference
      
    ClassDef(Electron, 1) // Electron class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::GetGsfTrack() const
{
  // Return global combined track.

  return static_cast<const Track*>(fGsfTrackRef.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::GetTrackerTrack() const
{
  // Return tracker track.

  return static_cast<const Track*>(fTrackerTrackRef.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::GetTrack() const
{
  // Return "best" track.

  if (GetGsfTrack())
    return GetGsfTrack();
  else if (GetTrackerTrack())
    return GetTrackerTrack();

  return 0;
}
#endif
