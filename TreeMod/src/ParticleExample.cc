// $Id: ParticleExample.cc,v 1.1 2008/05/27 19:50:16 loizides Exp $

#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include <TH1D.h>

using namespace mithep;

ClassImp(mithep::ParticleExampleMod)

//__________________________________________________________________________________________________
ParticleExampleMod::ParticleExampleMod(const char *name, const char *title)
  : TAModule(name,title),
    fParticles(0),
    fPartName("Particles"),
    fPtHist(0),
    fEtaHist(0)
{
  // Constructor.
}

//__________________________________________________________________________________________________
void ParticleExampleMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//__________________________________________________________________________________________________
void ParticleExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load
  // the branch and fill the histograms.

  LoadBranch(GetPartName());

  Int_t ents=fParticles->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     Particle &p = fParticles->At(i);
//     fPtHist->Fill(p.Pt());
//     fEtaHist->Fill(p.Eta());
  }

}

//__________________________________________________________________________________________________
void ParticleExampleMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual
  // analysis. Here, we typically initialize histograms and 
  // other analysis objects and request branches. For this module,
  // we request a branch of the MitTree.

  ReqBranch(GetPartName(), fParticles);

  fPtHist  = new TH1D("hPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fPtHist);
  fEtaHist = new TH1D("hEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fEtaHist);
}

//__________________________________________________________________________________________________
void ParticleExampleMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the
  // analysis. For this module, we dont do anything here.
}

//__________________________________________________________________________________________________
void ParticleExampleMod::Terminate()
{
  // Run finishing code on the client computer. 
  // For this module, we dont do anything here.
}
