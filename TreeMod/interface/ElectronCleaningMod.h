//--------------------------------------------------------------------------------------------------
// $Id: $
//
// ElectronCleaningMod
//
// This Module performs cleaning of objects including, removal of
// duplicate objects, removal of good muons from the good electrons,
// removal of good isolated electrons from good jets
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_ELECTRONCLEANINGMOD_H
#define MITANA_TREEMOD_ELECTRONCLEANINGMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class ElectronCleaningMod : public BaseMod
  {
    public:
      ElectronCleaningMod(const char *name="ElectronCleaningMod", 
                     const char *title="Example analysis module with all branches");
      ~ElectronCleaningMod() {}
      void               SetPrintDebug(bool b)            { fPrintDebug = b;         }   
      void               SetGoodElectronsName(TString s)  { fGoodElectronsName = s;  }        
      void               SetCleanMuonsName(TString s)     { fCleanMuonsName = s;     }        
      void               SetCleanElectronsName(TString s) { fCleanElectronsName = s; }        

    protected:
      bool                     fPrintDebug;      
      TString                  fGoodElectronsName ;       //name of electrons passing ID
      TString                  fCleanMuonsName ;          //name of clean muons
      TString                  fCleanElectronsName ;      //name of clean electrons  
      MuonCol		      *fMuons;                    //!Muon branch
      ElectronCol	      *fElectrons;                //!Electron branch
 
      int                      fNEventsProcessed;         // Number of events processed

      void               Begin();
      void               Process();
      void               SlaveBegin();
      void               SlaveTerminate();
      void               Terminate();

    
      ClassDef(ElectronCleaningMod,1) // TAM example analysis module
  };
}
#endif
