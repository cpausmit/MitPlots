//------------------------------------------------------------------------------
// $Id: ttEvtSelMod.h,v 1.1 2008/09/30 19:24:21 ceballos Exp $
//
// ttEvtSelMod
//
// A Module for Selecting ttbar events
// and produces some distributions
//
//
// Authors: ceballos
//------------------------------------------------------------------------------

#ifndef HWWMODS_TTEVTSELMOD_H
#define HWWMODS_TTEVTSELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class ttEvtSelMod : public BaseMod
  {
    public:
    ttEvtSelMod(const char *name="ttEvtSelMod", 
		 const char *title="Example analysis module with all branches");
      ~ttEvtSelMod() {}
      void         SetPrintDebug(bool b)          { fPrintDebug = b;   }   
      void         SetCleanJetsName (TString s)   { fCleanJetsName = s;}   
      void         SetMCLeptonsName(TString s)    { fMCLeptonsName = s;}     
      void         SetMCQuarksName(TString s)	  { fMCQuarksName = s; }     

    protected:
      bool         fPrintDebug;     // Debug info
      TString      fPlotType;	    // Type of histograms to make
      TString      fMetName;	    // name of met collection
      TString      fMuonName;	    // name of muon collection
      TString      fCleanJetsName;  // name of clean central jets collection
      TString      fMCLeptonsName ; // new lepton coll
      TString      fMCQuarksName;   // new Quarks coll
      MetCol       *fMet;	    // Missing Et
      MuonCol	   *fMuons;	    // Muon branch
  
      TH1D                    *hDttPresel[300];

      int                      fNEventsProcessed;

      void         Begin();
      void         Process();
      void         SlaveBegin();
      void         SlaveTerminate();
      void         Terminate();      

      ClassDef(ttEvtSelMod,1) // TAM example analysis module
  };
}
#endif
