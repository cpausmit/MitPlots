//--------------------------------------------------------------------------------------------------
// $Id: AnaFwkMod.h,v 1.1 2008/11/19 15:30:26 loizides Exp $
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

class TH1D;
class TStopwatch;

namespace mithep 
{
  class AnaFwkMod : public BaseMod
  {
    public:
      AnaFwkMod(const char *name="AnaFwkMod", 
                const char *title="Analysis framework module");
      ~AnaFwkMod() {}

    protected:
      TStopwatch    *fSWtotal;                  //!stop watch for overall timing
      TStopwatch    *fSWevent;                  //!stop watch per n events

      void           Process();
      void           SlaveBegin();
      void           SlaveTerminate();
    
      ClassDef(AnaFwkMod,1) // Analysis framework module
  };
}
#endif
