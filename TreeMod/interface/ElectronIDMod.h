//--------------------------------------------------------------------------------------------------
// $Id: ElectronIDMod.h,v 1.2 2008/10/01 11:19:20 sixie Exp $
//
// ElectronIDMod
//
// This Module applies electron ID criteria and exports a pointer to a collection
// of Good Electrons according to some specified ID scheme
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_ELECTRONIDMOD_H
#define MITANA_TREEMOD_ELECTRONIDMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class ElectronIDMod : public BaseMod
  {
    public:
      ElectronIDMod(const char *name="ElectronIDMod", 
                     const char *title="Example analysis module with all branches");
      ~ElectronIDMod() {}
      void        SetPrintDebug(bool b)                       { fPrintDebug               = b;    }
      void        SetElectronPtMin(double p)                  { fElectronPtMin            = p;    }
      void        SetElectronIDType(TString type)             { fElectronIDType           = type; }
      void        SetElectronIsoType(TString type)            { fElectronIsoType          = type; }
      void        SetIDLikelihoodCut(Double_t cut)            { fIDLikelihoodCut          = cut;  }
      void        SetTrackIsolationCut(Double_t cut)          { fTrackIsolationCut        = cut;  }
      void        SetCaloIsolationCut(Double_t cut)           { fCaloIsolationCut         = cut;  }
      void        SetEcalJurassicIsolationCut(Double_t cut)   { fEcalJurassicIsolationCut = cut;  }
      void        SetHcalJurassicIsolationCut(Double_t cut)   { fHcalJurassicIsolationCut = cut;  }
      void        SetGoodElectronsName(TString s)             { fGoodElectronsName        = s;    }   
    protected:
      bool                     fPrintDebug;               //flag for printing debug output
      TString                  fElectronName;             //name of electron collection
      TString                  fGoodElectronsName ;       //name of good electrons collection
      TString                  fElectronIDType;           //Type of electron ID we impose
      TString                  fElectronIsoType;          //Type of electron Isolation we impose
      ElectronCol	      *fElectrons;                //!Electron branch
      int                      fNEventsProcessed;         // Number of events processed

      double                   fElectronPtMin;            //min Pt requirement
      double                   fIDLikelihoodCut;          //Cut value for ID likelihood
      double                   fTrackIsolationCut;        //Cut value for track isolation
      double                   fCaloIsolationCut;         //Cut value for calo isolation
      double                   fEcalJurassicIsolationCut; //Cut value for ecal jurassic isolation
      double                   fHcalJurassicIsolationCut; //Cut value for hcal jurassic isolation

      void        Begin();
      void        Process();
      void        SlaveBegin();
      void        SlaveTerminate();
      void        Terminate();
      
    
      ClassDef(ElectronIDMod,1) // TAM example analysis module
  };
}
#endif
