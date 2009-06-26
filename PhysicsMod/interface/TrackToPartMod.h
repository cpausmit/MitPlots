//--------------------------------------------------------------------------------------------------
// $Id: TrackToPartMod.h,v 1.10 2009/06/17 11:50:27 loizides Exp $
//
// TrackToPartMod
//
// This module converts a given track particle branch (or collection) into
// a stable particle collection of given particle type (pdg id).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_TRACKTOPARTMOD_H
#define MITANA_PHYSICSMOD_TRACKTOPARTMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/StableParticleFwd.h"
#include "MitAna/DataTree/interface/TrackFwd.h"

namespace mithep 
{
  class TrackToPartMod : public BaseMod 
  {
    public:
      TrackToPartMod(const char *name="TrackToPartMod", 
                     const char *title="Track to StableParticle collection conversion module");

      UInt_t                   GetAbsPdgId(UInt_t pid)            { return fAbsPdgId;       }
      const char              *GetBranchName()              const { return fBranchName;     }
      const char              *GetInputName()               const { return GetBranchName(); }
      const char              *GetOutputName()              const { return GetPublicName(); }
      const char              *GetPublicName()              const { return fPublicName;     }
      Bool_t                   GetPubPerEvent()             const { return fPubPerEvent;    }
      void                     SetBranchName(const char *n)       { fBranchName=n;          }
      void                     SetInputName(const char *n)        { SetBranchName(n);       }
      void                     SetOutputName(const char *n)       { SetPublicName(n);       }
      void                     SetPublicName(const char *n)       { fPublicName=n;          }
      void                     PublishPerEvent(Bool_t b)          { fPubPerEvent = b;       }
      void                     SetAbsPdgId(UInt_t pid)            { fAbsPdgId    = pid;     }

    protected:
      TString                  fBranchName;    //name of collection
      TString                  fPublicName;    //name of collection
      Bool_t                   fPubPerEvent;   //=true then publish per event (def=1)
      UInt_t                   fAbsPdgId;      //pdg identifier (absolute value)
      const TrackCol          *fColIn;         //!pointer to collection (in) 
      StableParticleOArr      *fColOut;        //!pointer to collection (out)

      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      ClassDef(TrackToPartMod, 1) // Track to StableParticle collection conversion module
  };
}
#endif
