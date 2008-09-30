// $Id:  $

#include "MitAna/TreeMod/interface/MuonIDMod.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
#include "MitAna/Utils/interface/IsolationTools.h"


using namespace mithep;

ClassImp(mithep::MuonIDMod)

//--------------------------------------------------------------------------------------------------
  MuonIDMod::MuonIDMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fMuonName(Names::gkMuonBrn),
  fCleanMuonsName(Names::gkCleanMuonsName),  
  fMuonIDType("Tight"),
  fMuonIsoType("TrackCalo"),  
  fMuons(0),
  fTrackIsolationCut(5.0),
  fCaloIsolationCut(5.0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void MuonIDMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void MuonIDMod::Process()
{
  // Process entries of the tree. 

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "MuonIDMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }  

  //Get Muons
  LoadBranch(fMuonName);
  ObjArray<Muon> *CleanMuons = new ObjArray<Muon>; 
  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    Muon *mu = fMuons->At(i);
  
    Double_t MuonClass = -1;    
    if (mu->GlobalTrk())      
      MuonClass = 0;
    else if (mu->StandaloneTrk())      
      MuonClass = 1;
    else if (mu->TrackerTrk())
      MuonClass = 2;

    //These cuts are from the 1.6.X analysis. I'm waiting for Phil to finalize his Muon ID class
    const int nCuts = 4;
    double cutValue[nCuts] = {0.1, 3.0, 3.0, 1.5 };
    bool passCut[nCuts] = {false, false, false, false};
    double muonD0 = mu->BestTrk()->D0();
    if(muonD0 < cutValue[0] &&  MuonClass == 0 ) 
      passCut[0] = true;
    if(mu->IsoR03SumPt() < cutValue[1]) passCut[1] = true;
    if(mu->IsoR03EmEt() + 
       mu->IsoR03HadEt() < cutValue[2]) passCut[2] = true;    
    if(mu->Pt() > 5)
      passCut[3] = true;   
    
    // Final decision
    bool allCuts = true;
    for(int c=0; c<nCuts; c++) {
      allCuts = allCuts & passCut[c];
    }       
    
    if ( allCuts
         && abs(mu->Eta()) < 2.5
      ) {     
      CleanMuons->Add(mu);
    }                    


  }

  //Final Summary Debug Output   
  if ( fPrintDebug ) {
    cerr << "Event Dump: " << fNEventsProcessed << endl;  
    cerr << "Muons" << endl;
    for (UInt_t i = 0; i < CleanMuons->GetEntries(); i++) {
      cerr << i << " " << CleanMuons->At(i)->Pt() << " " << CleanMuons->At(i)->Eta() 
           << " " << CleanMuons->At(i)->Phi() << endl;    
    }  
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(CleanMuons, fCleanMuonsName.Data());  
}


//--------------------------------------------------------------------------------------------------
void MuonIDMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMuonName,              fMuons);
}

//--------------------------------------------------------------------------------------------------
void MuonIDMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void MuonIDMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
