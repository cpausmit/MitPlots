 // $Id: HwwEvtPreSelMod.cc,v 1.1 2008/09/30 19:24:01 sixie Exp $

#include "MitAna/PhysicsMod/interface/HwwEvtPreSelMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;
ClassImp(mithep::HwwEvtPreSelMod)

//--------------------------------------------------------------------------------------------------
HwwEvtPreSelMod::HwwEvtPreSelMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fMuonName(Names::gkMuonBrn),
  fElectronName(Names::gkElectronBrn),
  fMuons(0),
  fElectrons(0),
  fNEventsProcessed(0),
  fNEventsPassed(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void HwwEvtPreSelMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void HwwEvtPreSelMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches an
  
  fNEventsProcessed++;

  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);
    cerr << endl << "HwwEvtPreSelMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;
  }
 
  int nLeptons = 0;

  LoadBranch(fMuonName);
  double maxLeptonPt = 0;
  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    if (fPrintDebug) cerr << "mu " << i << " " << fMuons->At(i)->Pt() << endl;

    if (fMuons->At(i)->Pt() > 5) 
      nLeptons++;
    if (fMuons->At(i)->Pt() > maxLeptonPt)       
      maxLeptonPt = fMuons->At(i)->Pt();    
  }

  if (maxLeptonPt > 20 &&  nLeptons >= 2) {
    fNEventsPassed++;
    return;
  }

  LoadBranch(fElectronName);
  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {
    if (fPrintDebug) cerr << "ele " << i << " " << fElectrons->At(i)->Pt() << endl;
    if (fElectrons->At(i)->Pt() > 5)
      nLeptons++;
    if (fElectrons->At(i)->Pt() > maxLeptonPt)
      maxLeptonPt = fElectrons->At(i)->Pt();
  }
  
  if (maxLeptonPt > 20 &&  nLeptons >= 2) {
    fNEventsPassed++;
    return;
  }

  //By now the event fails preselection. If nLeptons < 2 or if maxLeptonPt
  //is less than 20
  if (fPrintDebug) cerr << nLeptons << " " << maxLeptonPt << endl;  
  if (fPrintDebug) cerr << "fail preselection - skip event" << endl;
  SkipEvent();
  return;
    


}
//--------------------------------------------------------------------------------------------------
void HwwEvtPreSelMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.
  ReqBranch(fMuonName,                  fMuons);
  ReqBranch(fElectronName,              fElectrons);

  fHWWPreSelection = new TH1D("hHWWPreSelection", ";Cut Number;#", 9, -1.5, 7.5);
  AddOutput(fHWWPreSelection);

}

//--------------------------------------------------------------------------------------------------
void HwwEvtPreSelMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

  cerr << "Events Processed: " << fNEventsProcessed << endl;
  cerr << "Events Passed PreSelection: " << fNEventsPassed << endl;

}

//--------------------------------------------------------------------------------------------------
void HwwEvtPreSelMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
