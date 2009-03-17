// $Id: TracksValMod.cc,v 1.4 2008/12/09 10:18:34 loizides Exp $

#include "MitAna/Validation/interface/TracksValMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::TracksValMod)

//--------------------------------------------------------------------------------------------------
TracksValMod::TracksValMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fTrackName(Names::gkTrackBrn),
  fTracks(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void TracksValMod::Process()
{
  // Process entries of the tree. For this module, we just load
  // the branch and fill the histograms.

  LoadBranch(GetTrackName());

  Int_t ents=fTracks->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     const Track *t = fTracks->At(i);
     fHs[0]->Fill(t->QOverP());
     fHs[1]->Fill(t->QOverPErr());
     fHs[2]->Fill(t->Lambda());
     fHs[3]->Fill(t->LambdaErr());
     fHs[4]->Fill(t->Phi0());
     fHs[5]->Fill(t->Phi0Err());
     fHs[6]->Fill(t->Dxy());
     fHs[7]->Fill(t->DxyErr());
     fHs[8]->Fill(t->EtaEcal());
     fHs[9]->Fill(t->PhiEcal());
     fHs[10]->Fill(t->RChi2());
  }
}

//--------------------------------------------------------------------------------------------------
void TracksValMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual
  // analysis. Here, we typically initialize histograms and 
  // other analysis objects and request branches. For this module,
  // we request a branch of the MitTree.

  ReqBranch(GetTrackName(), fTracks);

  AddTH1(fHs[0],"hQoverP",";QoverP;#",100,-10,10);
  AddTH1(fHs[1],"hQoverPErr",";QoverPErr;#",100,0,10);
  AddTH1(fHs[2],"hLambda",";Lambda;#",100,-2,2);
  AddTH1(fHs[3],"hLambdaErr",";LambdaErr;#",100,0,1);
  AddTH1(fHs[4],"hPhi0",";Phi0;#",100,-2,2);
  AddTH1(fHs[5],"hPhi0Err",";Phi0Err;#",100,0,1);
  AddTH1(fHs[6],"hDxy",";Dxy;#",100,-5,5);
  AddTH1(fHs[7],"hDxyErr",";DxyErr;#",100,0,1);
  AddTH1(fHs[8],"hEtaEcal",";EtaEcal;#",100,-3,3);
  AddTH1(fHs[9],"hPhiEcal",";PhiEcal;#",100,-2,2);
  AddTH1(fHs[10],"hChi2perNdof",";Chi2perNdo;#",100,0,5);
}

//--------------------------------------------------------------------------------------------------
void TracksValMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the
  // analysis. For this module, we dont do anything here.
}

