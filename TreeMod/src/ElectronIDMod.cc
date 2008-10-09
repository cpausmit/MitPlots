// $Id: ElectronIDMod.cc,v 1.4 2008/10/06 15:49:38 ceballos Exp $

#include "MitAna/TreeMod/interface/ElectronIDMod.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;

ClassImp(mithep::ElectronIDMod)

//--------------------------------------------------------------------------------------------------
  ElectronIDMod::ElectronIDMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fElectronName(Names::gkElectronBrn),
  fGoodElectronsName(Names::gkGoodElectronsName),  
  fElectronIDType("Tight"),
  fElectronIsoType("TrackCalo"),
  fElectrons(0),
  fElectronPtMin(10),
  fIDLikelihoodCut(0.9),
  fTrackIsolationCut(5.0),
  fCaloIsolationCut(5.0),
  fEcalJurassicIsolationCut(5.0),
  fHcalJurassicIsolationCut(5.0),
  fNEventsProcessed(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ElectronIDMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void ElectronIDMod::Process()
{
  // Process entries of the tree. 

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "ElectronIDMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }  

  //Get Electrons
  LoadBranch(fElectronName);

  ObjArray<Electron> *GoodElectrons = new ObjArray<Electron>;
  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {    
    Electron *e = fElectrons->At(i);        
    
    bool allCuts = false;  
    
    //Decide which ID scheme to use
    if(fElectronIDType.CompareTo("Tight") == 0) 
      allCuts = e->PassTightID();
    else if (fElectronIDType.CompareTo("Loose") == 0) 
       allCuts = e->PassLooseID();
    else if (fElectronIDType.CompareTo("IDLikelihood") == 0) 
      allCuts = (e->IDLikelihood() > fIDLikelihoodCut);
    else if (fElectronIDType.CompareTo("CustomMitCuts") == 0)
      allCuts = false; //we don't have these yet. will have to wait for Phil and Pieter
    else {
      cerr << "The specified electron ID type : " << fElectronIDType.Data() 
           << " is invalid. Please specify a correct ID type. " << endl;
      allCuts = false;
    }

    //isolation Cuts
    bool passTrackIsolation = (e->TrackIsolation() < fTrackIsolationCut);
    bool passCaloIsolation      = (e->CaloIsolation() < fCaloIsolationCut);
    bool passEcalJurassicIsolation = (e->EcalJurassicIsolation() < fEcalJurassicIsolationCut);
    bool passHcalJurassicIsolation = (e->HcalJurassicIsolation() < fHcalJurassicIsolationCut);
    //Decide which Isolation cut to use
    if (fElectronIsoType.CompareTo("TrackCalo") == 0 )
      allCuts = (allCuts && passTrackIsolation && passCaloIsolation);
    else if (fElectronIsoType.CompareTo( "TrackJurassic" ) == 0) {
      allCuts = (allCuts && passTrackIsolation && 
                 passEcalJurassicIsolation && passHcalJurassicIsolation);
    }else if (fElectronIsoType.CompareTo("NoIso") == 0 ) {
      //Do Nothing here
    } else {
      cerr << "The specified electron Isolation type : " << fElectronIDType.Data() 
           << "is invalid. Please specify a correct isolation type. " << endl;
      allCuts = false;
    }

    //Pt Cut
    if(e->Pt() < fElectronPtMin) allCuts = false;

    //These are Good Electrons
    if ( allCuts ) {    
      GoodElectrons->Add(fElectrons->At(i));
    }
  }   
  
  //Final Summary Debug Output   
  if ( fPrintDebug ) {
    cerr << "Event Dump: " << fNEventsProcessed << endl;
    
    //print out event content to text
    cerr << "Electrons" << endl;
    for (UInt_t i = 0; i < GoodElectrons->GetEntries(); i++) {
      cerr << i << " " << GoodElectrons->At(i)->Pt() << " " << GoodElectrons->At(i)->Eta() 
           << " " << GoodElectrons->At(i)->Phi() << " " 
           << GoodElectrons->At(i)->ESuperClusterOverP() << endl;    
    }       
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(GoodElectrons, fGoodElectronsName.Data());  
}


//--------------------------------------------------------------------------------------------------
void ElectronIDMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fElectronName,              fElectrons);
}

//--------------------------------------------------------------------------------------------------
void ElectronIDMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void ElectronIDMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
