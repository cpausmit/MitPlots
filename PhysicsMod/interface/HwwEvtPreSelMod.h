//--------------------------------------------------------------------------------------------------
// $Id: HwwEvtPreSelMod.h,v 1.1 2008/09/30 19:24:01 sixie Exp $
//
// HwwEvtSelMod
//
// A Module for Preselection of H->WW events
// Apply very loose cuts in order to reduce the number of
// irrelevent events that we have to process
//
// Authors: Si Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_HWWEVTPRESELMOD_H
#define MITANA_PHYSICSMOD_HWWEVTPRESELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class HwwEvtPreSelMod : public BaseMod
  {
    public:
      HwwEvtPreSelMod(const char *name="HwwEvtPreSelMod", 
		 const char *title="Example analysis module with all branches");
      ~HwwEvtPreSelMod() {}

      void         SetPrintDebug(bool b)   { fPrintDebug = b;     }   

    protected:
      bool                     fPrintDebug;
      TString                  fMuonName;             //name of muon collection
      TString                  fElectronName;         //name of electron collection
      MuonCol		      *fMuons;                //!Muon branch
      ElectronCol	      *fElectrons;            //!Electron branch
      TH1D                    *fHWWPreSelection;

      int                      fNEventsProcessed;
      int                      fNEventsPassed;     

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();      

      ClassDef(HwwEvtPreSelMod,1) // TAM example analysis module
  };
}
#endif
