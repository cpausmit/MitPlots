//-----------------------------------------------------------------------------
// $Id: ZXEvtSelMod.h,v 1.1 2008/09/30 19:24:21 ceballos Exp $
//
// ZXEvtSelMod
//
// A Module for Selecting WZ/ZZ-> >=3 leptons
// and produces some distributions
//
//
// Authors: ceballos
//-----------------------------------------------------------------------------

#ifndef HWWMODS_ZXEvtSelMod_H
#define HWWMODS_ZXEvtSelMod_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class ZXEvtSelMod : public BaseMod
  {
    public:
    ZXEvtSelMod(const char *name="ZXEvtSelMod", 
		 const char *title="Example analysis module with all branches");
      ~ZXEvtSelMod() {}
      void         SetPrintDebug(bool b)          { fPrintDebug = b;   }   
      void         SetCleanJetsName (TString s)   { fCleanJetsName = s;}   
      void         SetMCLeptonsName(TString s)    { fMCLeptonsName = s;}     

    protected:
      bool         fPrintDebug;      // Debug info
      TString      fMetName;	     // name of met collection
      TString      fCleanJetsName;   // name of clean central jets collection
      TString      fMCLeptonsName ;  // new lepton coll
      MetCol       *fMet;	     // Missing Et
  
      TH1D         *hDZXSel[1];
      TH1D         *hDWZSel[400];
      TH1D         *hDZZSel[300];

      int          fNEventsProcessed;

      void         Begin();
      void         Process();
      void         SlaveBegin();
      void         SlaveTerminate();
      void         Terminate();      

      ClassDef(ZXEvtSelMod,1) // TAM example analysis module
  };
}
#endif
