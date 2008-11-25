// $Id: SimpleExampleMod.cc,v 1.1 2008/09/28 02:33:13 loizides Exp $

#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::SimpleExampleMod)

//--------------------------------------------------------------------------------------------------
SimpleExampleMod::SimpleExampleMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPartName(Names::gkMCPartBrn),
  fParticles(0),
  fPtHist(0),
  fEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::BeginRun()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::EndRun()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load
  // the branch and fill the histograms.

  LoadBranch(GetPartName());

  Int_t ents=fParticles->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     MCParticle* p = fParticles->At(i);
     fPtHist->Fill(p->Pt());
     fEtaHist->Fill(p->Eta());
  }

}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::SlaveBegin()
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

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the
  // analysis. For this module, we dont do anything here.
}

//--------------------------------------------------------------------------------------------------
void SimpleExampleMod::Terminate()
{
  // Run finishing code on the client computer. 
  // For this module, we dont do anything here.
}
