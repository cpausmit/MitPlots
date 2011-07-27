//--------------------------------------------------------------------------------------------------
// $Id: RunLumiSelectionMod.h,v 1.4 2010/06/29 15:51:53 bendavid Exp $
//
// RunLumiSelectionMod
//
// This module selects or excludes a list or runs/ranges.  A list of accepted and excluded runs
// may be simultaneously provided, in which case both conditions are checked.  Runs which are not
// covered by either list will be handled according to the fDefaultAccept switch (false by default
// such that runs not covered by either list will be rejected).
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_RUNLUMISELECTIONMOD_H
#define MITANA_PHYSICSMOD_RUNLUMISELECTIONMOD_H

#include <string>
#include <TString.h>
#include <TGraph.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataCont/interface/RunLumiRangeMap.h"
#include "MitAna/DataCont/interface/RunLumiSet.h"

namespace mithep 
{
  class RunLumiSelectionMod : public BaseMod {
    typedef RunLumiRangeMap::RunLumiPairType RunLumiPairType;


    public:
      RunLumiSelectionMod(const char *name="RunLumiSelectionMod", const char *title="Run selection module");
      ~RunLumiSelectionMod();

      void                        AddJSONFile(const std::string &filepath);
      Int_t                       GetNEvents()      const { return fNEvents;       }
      Int_t                       GetNAccepted()    const { return fNAcceped;      }
      Int_t                       GetNFailed()      const { return fNFailed;       }
      void                        SetAbortIfNotAccepted(Bool_t b)   { fAbort         = b; }
      void                        SetAcceptMC(Bool_t b)   { fAcceptMC  = b; }
      void                        SetAcceptAll(Bool_t b)  { fAcceptAll = b; }

    protected:
      void                        BeginRun();
      virtual void                OnAccepted()  {/*could be implemented in derived classes*/}
      virtual void                OnFailed()    {/*could be implemented in derived classes*/}
      void                        Process();
      void                        SlaveBegin();
      void                        SlaveTerminate();

      Bool_t                      fAbort;         //=true then abort (sub-)modules if not accepted
      Bool_t                      fAcceptMC;      //=true then accept Monte Carlo unconditionally
      Bool_t                      fAcceptAll;     //=true then accept all events unconditionally
      Int_t                       fNEvents;       //!number of processed events
      Int_t                       fNAcceped;      //!number of accepted events
      Int_t                       fNFailed;       //!number of failed events
      RunLumiPairType             fCurrentRunLumi; //!cached current run-lumi pair
      Bool_t                      fAcceptCurrentRunLumi; //!cached decision for current run-lumi pair
      RunLumiRangeMap             fAcceptedRunsLumis; //!mapped run-lumi ranges to accept
      RunLumiSet                  fRunLumiSet; //!
      TGraph                     *fRunLumiGraph; //!

    ClassDef(RunLumiSelectionMod, 1) // L1 TAM module
  };
}
#endif
