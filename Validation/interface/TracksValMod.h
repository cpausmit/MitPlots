//--------------------------------------------------------------------------------------------------
// $Id: TracksMod.h,v 1.4 2008/12/10 17:25:17 loizides Exp $
//
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_VALIDATION_TRACKSVALMOD_H
#define MITANA_VALIDATION_TRACKSVALMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class TracksValMod : public BaseMod 
  {
    public:
      TracksValMod(const char *name="TracksValMod", 
                   const char *title="Tracks analysis module");
      ~TracksValMod() {}

      const char              *GetTrackName()              const { return fTrackName; }
      void                     SetTrackName(const char *n)       { fTrackName=n;      }

    protected:
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fTrackName;  //branch name of Track collection
      const TrackCol          *fTracks;     //!pointer to Tracks branch
      TH1D                    *fHs[100];    //!histograms

      ClassDef(TracksValMod, 1) // Tracks analysis module
  };
}
#endif
