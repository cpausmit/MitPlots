// $Id: ElectronCleaningMod.cc,v 1.1 2008/09/30 16:37:05 sixie Exp $

#include "MitAna/TreeMod/interface/ElectronCleaningMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;

ClassImp(mithep::ElectronCleaningMod)

//--------------------------------------------------------------------------------------------------
  ElectronCleaningMod::ElectronCleaningMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fGoodElectronsName(Names::gkGoodElectronsName),        
  fCleanMuonsName(Names::gkCleanMuonsName),        
  fCleanElectronsName(Names::gkCleanElectronsName),        
  fMuons(0),
  fElectrons(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ElectronCleaningMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void ElectronCleaningMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and
  //output debug info or not   

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "ElectronCleaningMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }  
  //Get Clean Muons
  ObjArray<Muon> *CleanMuons = dynamic_cast<ObjArray<Muon>* >
    (FindObjThisEvt(fCleanMuonsName.Data()));
  //Get Good ID Electrons
  ObjArray<Electron> *GoodElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(fGoodElectronsName.Data()));

  vector<Electron*> CleanElectronsVector;
  //Go through all electrons and remove electron overlaps with muons and duplicates
  for (UInt_t i=0; i<GoodElectrons->GetEntries(); ++i) {    
    Electron *e = GoodElectrons->At(i);   

    //Check whether it overlaps with a good muon. If the muon and electron both have
    //proper tracker tracks then compare the tracks. otherwise check dR
    bool isMuonOverlap = false;
    for (UInt_t j=0; j<CleanMuons->GetEntries();j++) {
      if (CleanMuons->At(j)->TrackerTrk() && e->TrackerTrk()) {
        isMuonOverlap = (CleanMuons->At(j)->TrackerTrk() == e->TrackerTrk());
        if (isMuonOverlap)
          break;
      } else {      
        double deltaR = MathUtils::DeltaR(CleanMuons->At(j)->Mom(), e->Mom());     
        if (deltaR < 0.1) {
          isMuonOverlap = true;
          break;	 
        }
      }
    }

    //Check whether it overlaps with another electron candidate
    //Here I check whether we have two electron candidates with the same super cluster
    //or two electron candidates with the same track. At the end we also check deltaR
    //to be sure. If there is a duplicate we swap the old one with the new one if the new
    //one has E/P closer to 1.0
    bool isElectronOverlap = false;
    for (UInt_t j=0; j<CleanElectronsVector.size(); j++) {
      if (e->SCluster() == CleanElectronsVector[j]->SCluster() ||
          e->Trk() == CleanElectronsVector[j]->Trk())
        isElectronOverlap = true;

      double deltaR = MathUtils::DeltaR(CleanElectronsVector[j]->Mom(), e->Mom());
      if (deltaR < 0.1)
        isElectronOverlap = true;        
      
      if (isElectronOverlap) {
        if (abs(CleanElectronsVector[j]->ESuperClusterOverP() - 1) > 
            abs(e->ESuperClusterOverP() - 1)) {	   
          CleanElectronsVector[j] = e;
        }        
        break;
      }
    }
    //If no overlaps then add to clean electrons
    if ( !isMuonOverlap && !isElectronOverlap ) {       
      CleanElectronsVector.push_back(GoodElectrons->At(i));   
    }   
  } 

  //fill the electron ObjArray with the contents of the vector
  //this is necessary because I want to swap out the duplicates, can't be done with ObjArray...
  ObjArray<Electron> *CleanElectrons = new ObjArray<Electron>;
  for (UInt_t j=0; j<CleanElectronsVector.size(); j++) 
    CleanElectrons->Add(CleanElectronsVector[j]);
       
   //Final Summary Debug Output   
  if ( fPrintDebug ) {
    cerr << "Event Dump: " << fNEventsProcessed << endl;
    
    //print out event content to text
    cerr << "Clean Electrons" << endl;
    for (UInt_t i = 0; i < CleanElectrons->GetEntries(); i++) {
      cerr << i << " " << CleanElectrons->At(i)->Pt() << " " << CleanElectrons->At(i)->Eta() 
           << " " << CleanElectrons->At(i)->Phi() << " " 
           << CleanElectrons->At(i)->ESuperClusterOverP() << endl;    
    }       
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(CleanElectrons, fCleanElectronsName.Data());  
}


//--------------------------------------------------------------------------------------------------
void ElectronCleaningMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

}

//--------------------------------------------------------------------------------------------------
void ElectronCleaningMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void ElectronCleaningMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
