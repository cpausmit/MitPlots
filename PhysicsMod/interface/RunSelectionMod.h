//--------------------------------------------------------------------------------------------------
// RunSelectionMod
//
// This module selects or excludes a list or runs/ranges.  A list of accepted and excluded runs
// may be simultaneously provided, in which case both conditions are checked.  Runs which are not
// covered by either list will be handled according to the fDefaultAccept switch (false by default
// such that runs not covered by either list will be rejected).
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_RUNSELECTIONMOD_H
#define MITANA_PHYSICSMOD_RUNSELECTIONMOD_H

#include <string>
#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 

namespace mithep 
{
  class RunSelectionMod : public BaseMod {
    public:
      RunSelectionMod(const char *name="RunSelectionMod", const char *title="Run selection module");
      ~RunSelectionMod();

      void                        AddRun(UInt_t i)                { fAcceptedRuns.push_back(UIntPair(i,i)); }
      void                        AddRuns(UInt_t l, UInt_t u)     { fAcceptedRuns.push_back(UIntPair(l,u)); }
      void                        ExcludeRun(UInt_t i)            { fExcludedRuns.push_back(UIntPair(i,i)); }
      void                        ExcludeRuns(UInt_t l, UInt_t u) { fExcludedRuns.push_back(UIntPair(l,u)); }
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

      Bool_t                      fAbort;         //=true then abort (sub-)modules if not accepted
      Bool_t                      fDefaultAccept; //=true then accept runs not explicitly included or excluded
      Int_t                       fNEvents;       //!number of processed events
      Int_t                       fNAcceped;      //!number of accepted events
      Int_t                       fNFailed;       //!number of failed events
      Bool_t                      fAcceptCurrentRun; //!cached decision for current run
      UIntBounds                  fAcceptedRuns; //list of run ranges to accept
      UIntBounds                  fExcludedRuns; //list of run ranges to exclude

    ClassDef(RunSelectionMod, 1) // L1 TAM module
  };
}
#endif
