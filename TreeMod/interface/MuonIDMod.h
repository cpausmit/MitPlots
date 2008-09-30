//--------------------------------------------------------------------------------------------------
// $Id: $
//
// MuonIDMod
//
// This Module applies electron ID criteria and exports a pointer to a collection
// of Good Electrons according to some specified ID scheme
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_MUONIDMOD_H
#define MITANA_TREEMOD_MUONIDMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class MuonIDMod : public BaseMod
  {
    public:
      MuonIDMod(const char *name="MuonIDMod", 
                     const char *title="Example analysis module with all branches");
      ~MuonIDMod() {}
      void                     SetPrintDebug(bool b)              { fPrintDebug         = b;     }
      void                     SetMuonIDType(TString type)        { fMuonIDType         = type;  }
      void                     SetTrackIsolationCut(Double_t cut) { fTrackIsolationCut  = cut;   }
      void                     SetCaloIsolationCut(Double_t cut)  { fCaloIsolationCut   = cut;   }
      void                     SetCleanMuonsName(TString s)       { fCleanMuonsName     = s;     }     
    protected:
      bool                     fPrintDebug;               //flag for printing debug output
      TString                  fMuonName;                 //name of muon collection
      TString                  fCleanMuonsName ;           //name of good muons collection  
      TString                  fMuonIDType;               //Type of electron ID we impose
      TString                  fMuonIsoType;              //Type of electron Isolation we impose
      MuonCol		      *fMuons;                    //!Muon branch
      int                      fNEventsProcessed;         // Number of events processed

      double                   fTrackIsolationCut;        //Cut value for track isolation
      double                   fCaloIsolationCut;         //Cut value for calo isolation

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();
     
    
      ClassDef(MuonIDMod,1) // TAM example analysis module
  };
}
#endif
