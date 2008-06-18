//--------------------------------------------------------------------------------------------------
// $Id: FullExampleMod.h,v 1.2 2008/06/12 10:22:29 loizides Exp $
//
// FullExampleAnaMod
//
// This TAM module shows how to use TAM. It takes a couple of branches
// and produces a pt and eta distribution.
//
// More information about TAM in general can be found at
// http://www.cmsaf.mit.edu/twiki/bin/view/Software/TAM
//
// Authors: C.Loizides, J.Bendavid
//
//--------------------------------------------------------------------------------------------------

#ifndef TREEMOD_FULLEXAMPLEMOD_H
#define TREEMOD_FULLEXAMPLEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class FullExampleMod : public BaseMod
  {
    public:
      FullExampleMod(const char *name="FullExampleMod", 
                     const char *title="Example analysis module with all branches");
      ~FullExampleMod() {}

    protected:
      TString                  fGenPartName;   //name of particle collection
      TString                  fTrackName;     //name of track collection
      TString                  fMuonName;      //name of muon collection
      TString                  fElectronName;  //name of electron collection

      GenParticleCol          *fParticles;          //!GenParticle branch
      TrackCol		      *fTracks;	            //!Track branch
      MuonCol		      *fMuons;              //!Muon branch
      ElectronCol	      *fElectrons;          //!Electron branch
      TH1D                    *fGenPtHist;          //!GenParticle pt histogram
      TH1D                    *fGenEtaHist;         //!GenParticle eta histogram
      TH1D                    *fTrackPtHist;        //!Track pt histogram
      TH1D                    *fTrackEtaHist;       //!Track eta histogram
      TH1D                    *fMuonPtHist;         //!Muon pt histogram
      TH1D                    *fMuonEtaHist;        //!Muon eta histogram
      TH1D                    *fElectronPtHist;	    //!Electron pt histogram
      TH1D                    *fElectronEtaHist;    //!Electron eta histogram

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      ClassDef(FullExampleMod,1) // TAM example analysis module
  };
}
#endif
