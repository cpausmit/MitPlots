//--------------------------------------------------------------------------------------------------
// $Id: $
//
// JetCleaningMod
//
// This Module performs cleaning of jets. Removes jets which point 
// in the same direction as a clean isolated electron
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_JETCLEANINGMOD_H
#define MITANA_TREEMOD_JETCLEANINGMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  class JetCleaningMod : public BaseMod
  {
    public:
      JetCleaningMod(const char *name="JetCleaningMod", 
                     const char *title="Example analysis module with all branches");
      ~JetCleaningMod() {}
      void               SetPrintDebug(bool b)              { fPrintDebug           = b;   }   
      void               SetCleanElectronsName(TString s)   { fCleanElectronsName   = s;   }        
      void               SetGoodJetsName(TString s)         { fGoodJetsName         = s;   }  
      void               SetCleanJetsName(TString s)        { fCleanJetsName        = s;   }
 
    protected:
      bool                     fPrintDebug;      
      TString                  fCleanElectronsName ;        
      TString                  fGoodJetsName;        
      TString                  fCleanJetsName;        

      ElectronCol	      *fElectrons;                //!Electron branch
      JetCol                  *fJets;                     //!IC5 Jet branch

      int                      fNEventsProcessed;              // Number of events processed

      void               Begin();
      void               Process();
      void               SlaveBegin();
      void               SlaveTerminate();
      void               Terminate();
   
      ClassDef(JetCleaningMod,1) // TAM example analysis module
  };
}
#endif
