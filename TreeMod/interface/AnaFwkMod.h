//--------------------------------------------------------------------------------------------------
// $Id: AnaFwkMod.h,v 1.5 2009/03/12 15:37:52 loizides Exp $
//
// AnaFwkMod
//
// This module collects interesting global information, like the overall number of processed
// events and puts this information into the OutputList.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEEMOD_ANAFWKMOD_H
#define MITANA_TREEEMOD_ANAFWKMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TTree;
class TH1D;
class TStopwatch;

namespace mithep 
{
  class AnaFwkMod : public BaseMod
  {
    public:
      AnaFwkMod(const char *name="AnaFwkMod", 
                const char *title="Analysis framework module");

      Long64_t         GetSkipNEvents()           const { return fSkipNEvents; }
      void             SetSkipNEvents(Long64_t n)       { fSkipNEvents = n;    }

    protected:
      void             BeginRun();
      Bool_t           Notify();
      void             CopyAllEventHeaders();
      void             Process();
      void             SlaveBegin();
      void             SlaveTerminate();

      TString          fAllHeadTreeName;   //all events tree name
      TString          fAllHeadBrName;     //all event headers branch name
      Long64_t         fSkipNEvents;       //number of events to skip from beginning (def=0)
      TStopwatch      *fSWtotal;           //!stop watch for overall timing
      TStopwatch      *fSWevent;           //!stop watch per n events
      EventHeaderArr   fAllHeaders;        //!pointer to array of all event headers
      TTree           *fAllHeadTree;       //!all event headers tree in current file
      EventHeader     *fAllEventHeader;    //!all event header
      Bool_t           fReload;            //!reload tree after file changed
      Int_t            fCurEnt;            //!curent entry in AllEvents tree
      Int_t            fNEventsSkimmed;    //!number of skimmed events
      Int_t            fNEventsSkipped;    //!number of skippeded events
      
    ClassDef(AnaFwkMod, 1) // Analysis framework module
  };
}
#endif
