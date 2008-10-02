// $Id: JetCleaningMod.cc,v 1.1 2008/09/30 16:37:17 sixie Exp $

#include "MitAna/TreeMod/interface/JetCleaningMod.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;

ClassImp(mithep::JetCleaningMod)

//--------------------------------------------------------------------------------------------------
  JetCleaningMod::JetCleaningMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fCleanElectronsName(Names::gkCleanElectronsName),        
  fGoodJetsName(Names::gkGoodJetsName),        
  fCleanJetsName(Names::gkCleanJetsName),        
  fElectrons(0),
  fJets(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void JetCleaningMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void JetCleaningMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and
  //output debug info or not   

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "JetCleaningMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }  

  //Get Clean Electrons
  ObjArray<Electron> *CleanElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(fCleanElectronsName.Data()));
  //Get Good Jets
  ObjArray<Jet> *GoodJets = dynamic_cast<ObjArray<Jet>* >
    (FindObjThisEvt(fGoodJetsName.Data()));  
  ObjArray<Jet> *CleanJets = new ObjArray<Jet>; 

  //remove any jet that overlaps in eta phi with an isolated electron
  for (UInt_t i=0; i<GoodJets->GetEntries(); ++i) {
    Jet *jet = GoodJets->At(i);        
    bool isElectronOverlap =  false;
     
    //Check for overlap with an electron
    for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(CleanElectrons->At(j)->Mom(),jet->Mom());  
      if (deltaR < 0.3) {
	isElectronOverlap = true;	 	 	
	break;	 	 
      }      
    }
    //Save Clean Jets
    if (!isElectronOverlap) {
      CleanJets->Add(jet);     
    }        
  } 

  //Final Summary Debug Output   
  if ( fPrintDebug ) {
    cerr << "Event Dump: " << fNEventsProcessed << endl;
    cerr << "GoodJets : " << 
    cerr << "Clean  Jets" << endl;
    for (UInt_t i = 0; i < CleanJets->GetEntries(); i++) {
      cerr << i << " " << CleanJets->At(i)->Pt() << " " 
           << CleanJets->At(i)->Eta() << " " << CleanJets->At(i)->Phi() << endl;    
    }
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(CleanJets, fCleanJetsName.Data());
}


//--------------------------------------------------------------------------------------------------
void JetCleaningMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

}

//--------------------------------------------------------------------------------------------------
void JetCleaningMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void JetCleaningMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
