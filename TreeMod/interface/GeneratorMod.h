//--------------------------------------------------------------------------------------------------
// $Id: GeneratorMod.h,v 1.1 2008/10/01 13:00:09 ceballos Exp $
//
// GeneratorMod
//
// This module finds interesting generator information
//
// Authors: ceballos
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_GENERATORMOD_H
#define MITANA_TREEMOD_GENERATORMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;
class TH2D;

namespace mithep 
{
  class GeneratorMod : public BaseMod
  {
    public:
      GeneratorMod(const char *name="GeneratorMod", 
                   const char *title="generator information");
      ~GeneratorMod() {}
      void           SetPrintDebug(bool b)	  { fPrintDebug      = b;}
      void           SetFillHist(bool b)	  { fFillHist	     = b;}
      void           SetIsMC(bool b)  	          { fIsMC	     = b;}
      void           SetMCPartName(TString s)	  { fMCPartName      = s;}     
      void           SetMCLeptonsName(TString s)  { fMCLeptonsName   = s;}     
      void           SetMCTausName(TString s)	  { fMCTausName      = s;}     
      void           SetMCNeutrinosName(TString s){ fMCNeutrinosName = s;}     
      void           SetMCQuarksName(TString s)   { fMCQuarksName    = s;}     
      void           SetMCqqHsName(TString s)	  { fMCqqHsName      = s;}     
      void           SetMCBosonsName(TString s)   { fMCBosonsName    = s;}     
    protected:
      bool           fPrintDebug;		// debug output
      bool           fFillHist; 		// Fill histograms?
      TString        fIsMC;			// is MC?
      TString        fMCPartName;		// generator coll
      TString        fMCLeptonsName ;		// new lepton coll
      TString        fMCTausName;		// new tau coll
      TString        fMCNeutrinosName;  	// new Neutrinos coll
      TString        fMCQuarksName;		// new Quarks coll
      TString        fMCqqHsName;		// new qqH coll
      TString        fMCBosonsName;		// new Bosons coll
      MCParticleCol *fParticles;		// GenParticle branch
      int            fNEventsProcessed; 	// Number of events

      TH1D          *hDGenLeptons[20];
      TH1D          *hDGenTaus[20];
      TH1D          *hDGenNeutrinos[20];
      TH1D          *hDGenQuarks[20];
      TH1D          *hDGenWBF[20];
      TH1D          *hDGenBosons[20];

      void           Begin();
      void           Process();
      void           SlaveBegin();
      void           SlaveTerminate();
      void           Terminate();
     
    
      ClassDef(GeneratorMod,1) // TAM example analysis module
  };
}
#endif
