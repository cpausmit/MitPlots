//--------------------------------------------------------------------------------------------------
// $Id: L1Mod.h,v 1.2 2009/11/24 15:58:12 loizides Exp $
//
// L1Mod
//
// This module allows to select events according to given L1 trigger bits. The trigger bits 
// are selected via their corresponding L1 trigger name. 
// The trigger name is added to the list of accepted triggers using AddTrigger(). Each member of 
// this list will be logically "ored" to the search mask (see description of AddTrigger()). 
// L1Mod will abort processing the chain of sub-modules if the trigger bits did not 
// match the given trigger mask, unless you call SetAbortIfNotAccepted(kFALSE). 
// For convenience L1Mod defines two virtual functions, OnAccepted() and OnFailed() 
// that can be implemented in derived classes. OnAccepted() will be called if the event passes
// the trigger mask, on Failed() if it did not.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_L1MOD_H
#define MITANA_TREEMOD_L1MOD_H

#include <string>
#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 

namespace mithep 
{
  class TriggerTable;
  class L1TriggerMask;

  class L1Mod : public BaseMod {
    public:
      L1Mod(const char *name="L1Mod", const char *title="L1 trigger module");
      ~L1Mod();

      void                        AddTrigger(const char *expr);
      const char                 *GetBitsName()     const { return fBitsName;      }
      Int_t                       GetNEvents()      const { return fNEvents;       }
      Int_t                       GetNAccepted()    const { return fNAcceped;      }
      Int_t                       GetNFailed()      const { return fNFailed;       }
      void                        SetAbortIfNotAccepted(Bool_t b)   { fAbort         = b; }
      void                        SetBitsName(const char *n)        { fBitsName      = n; }
      void                        SetIgnoreBits(Bool_t b)           { fIgnoreBits    = b; }
      void                        SetPrintTable(Bool_t b)           { fPrintTable    = b; }

    protected:
      void                        BeginRun();
      virtual void                OnAccepted()  {/*could be implemented in derived classes*/}
      virtual void                OnFailed()    {/*could be implemented in derived classes*/}
      void                        Process();
      void                        SlaveBegin();
      void                        SlaveTerminate();

      Bool_t                      fAbort;         //=true then abort (sub-)modules if not accepted
      Bool_t                      fPrintTable;    //=true then print L1 trigger table in BeginRun
      Bool_t                      fIgnoreBits;    //=true then try to get trigger objects (def=0)
      TString                     fBitsName;      //trigger bits branch name
      std::vector<std::string>    fTrigNames;     //trigger names requested for test mask
      const L1TriggerMask        *fBits;          //!trigger bits branch
      std::vector<BitMask128>     fTrigBitsAnd;   //!trigger bits used in mask
      std::vector<BitMask128>     fTrigBitsCmp;   //!trigger bits used for comparison
      BitMask256                  fBitsDone;      //!bits for which events are accepted
      const TriggerTable         *fTriggers;      //!imported published L1 trigger table
      Int_t                       fNEvents;       //!number of processed events
      Int_t                       fNAcceped;      //!number of accepted events
      Int_t                       fNFailed;       //!number of failed events

    ClassDef(L1Mod, 1) // L1 TAM module
  };
}
#endif
