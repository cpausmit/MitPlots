//--------------------------------------------------------------------------------------------------
// $Id: MCProcessSelectionMod.h,v 1.1 2010/01/18 14:35:43 bendavid Exp $
//
// MCProcessSelectionMod
//
// This module selects or excludes a list or runs/ranges.  A list of accepted and excluded runs
// may be simultaneously provided, in which case both conditions are checked.  Runs which are not
// covered by either list will be handled according to the fDefaultAccept switch (false by default
// such that runs not covered by either list will be rejected).
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_MCPROCESSSELECTIONMOD_H
#define MITANA_PHYSICSMOD_MCPROCESSSELECTIONMOD_H

#include <string>
#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/MCEventInfo.h" 

namespace mithep 
{
  class MCProcessSelectionMod : public BaseMod {
    public:
      MCProcessSelectionMod(const char *name="MCProcessSelectionMod", const char *title="Run selection module");
      ~MCProcessSelectionMod();

      void                        AddProcess(Int_t i)                { fAcceptedProcessIds.push_back(i); }
      void                        ExcludeProcess(Int_t i)            { fExcludedProcessIds.push_back(i); }
      Int_t                       GetNEvents()      const { return fNEvents;       }
      Int_t                       GetNAccepted()    const { return fNAcceped;      }
      Int_t                       GetNFailed()      const { return fNFailed;       }
      void                        SetAbortIfNotAccepted(Bool_t b)   { fAbort         = b; }
      void                        SetDefaultAccept(Bool_t b) { fDefaultAccept = b; }

    protected:
      void                        BeginRun();
      virtual void                OnAccepted()  {/*could be implemented in derived classes*/}
      virtual void                OnFailed()    {/*could be implemented in derived classes*/}
      void                        Process();
      void                        SlaveBegin();
      void                        SlaveTerminate();

      TString                     fMCEventInfoName;//
      Bool_t                      fAbort;         //=true then abort (sub-)modules if not accepted
      Bool_t                      fDefaultAccept; //=true then accept processes not explicitly included or excluded
      Int_t                       fNEvents;       //!number of processed events
      Int_t                       fNAcceped;      //!number of accepted events
      Int_t                       fNFailed;       //!number of failed events
      std::vector<Int_t>          fAcceptedProcessIds; //list of process ids accept
      std::vector<Int_t>          fExcludedProcessIds; //list of process ids to exclude
      const MCEventInfo*          fMCEventInfo;        //!MC Event Info pointer

    ClassDef(MCProcessSelectionMod, 1) // L1 TAM module
  };
}
#endif
