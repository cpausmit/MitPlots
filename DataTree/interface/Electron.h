//--------------------------------------------------------------------------------------------------
// $Id: Electron.h,v 1.9 2008/07/01 08:54:57 loizides Exp $
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
      
      const Track         *BestTrk()         const;
      const Track         *GsfTrk()          const;
      const Track         *TrackerTrk()      const;
      Double_t             Mass()            const { return 0.51099892e-3; }
      
      void	           SetGsfTrk(Track* t)     { fGsfTrackRef = t; }
      void	           SetTrackerTrk(Track* t) { fTrackerTrackRef = t; }
      
    protected:
      TRef	           fGsfTrackRef;     //global combined track reference
      TRef	           fTrackerTrackRef; //tracker track reference
      
    ClassDef(Electron, 1) // Electron class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::BestTrk() const
{
  // Return "best" track.

  if (GsfTrk())
    return GsfTrk();
  else if (TrackerTrk())
    return TrackerTrk();

  return 0;
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::GsfTrk() const
{
  // Return global combined track.

  return static_cast<const Track*>(fGsfTrackRef.GetObject());
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::TrackerTrk() const
{
  // Return tracker track.

  return static_cast<const Track*>(fTrackerTrackRef.GetObject());
}
#endif
