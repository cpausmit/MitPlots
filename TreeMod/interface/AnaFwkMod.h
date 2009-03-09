//--------------------------------------------------------------------------------------------------
// $Id: AnaFwkMod.h,v 1.3 2008/12/10 14:20:26 loizides Exp $
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

    protected:
      TString          fAllHeadTreeName;   //
      TString          fAllHeadBrName;     //
      TStopwatch      *fSWtotal;           //!stop watch for overall timing
      TStopwatch      *fSWevent;           //!stop watch per n events
      EventHeaderArr   fAllHeaders;        //!pointer to array of all event headers
      TTree           *fAllHeadTree;       //!all event headers tree in current file
      EventHeader     *fAllEventHeader;    //!all event header
      Bool_t           fReload;            //!reload tree after file changed
      Int_t            fCurEnt;            //!

      void             BeginRun();
      Bool_t           Notify();
      void             CopyAllEventHeaders();
      void             Process();
      void             SlaveBegin();
      void             SlaveTerminate();
    
    ClassDef(AnaFwkMod, 1) // Analysis framework module
  };
}
#endif
