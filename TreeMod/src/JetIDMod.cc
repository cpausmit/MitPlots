// $Id:  $

#include "MitAna/TreeMod/interface/JetIDMod.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"


using namespace mithep;

ClassImp(mithep::JetIDMod)

//--------------------------------------------------------------------------------------------------
  JetIDMod::JetIDMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fJetName(Names::gkCaloJetBrn),
  fGoodJetsName(Names::gkGoodJetsName),  
  fJetIDType("HWWJets"),
  fJets(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void JetIDMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void JetIDMod::Process()
{
  // Process entries of the tree. 

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "JetIDMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }  

  //Get Jets
  LoadBranch(fJetName);
  ObjArray<Jet> *GoodJets = new ObjArray<Jet>; 

  for (UInt_t i=0; i<fJets->GetEntries(); ++i) {
    Jet *jet = fJets->At(i);
    
    const int nCuts = 3;
    double cutValue[nCuts] = {15., 5.0, 0.2};
    bool passCut[nCuts] = {false, false, false};
    
    if(jet->Et() > cutValue[0])           passCut[0] = true;
    if(fabs(jet->Eta()) < cutValue[1])    passCut[1] = true;        
    if(jet->Alpha() > cutValue[2] ||
       jet->Et() > 20.) 
      passCut[2] = true; 
    
    // Final decision
    bool passAllCuts = true;
    for(int i=0; i<nCuts; i++) {
      passAllCuts = passAllCuts && passCut[i];
    }
                    
    //Save Good Jets
    if (passAllCuts)
      GoodJets->Add(jet);             
   }

  //Final Summary Debug Output   
  if ( fPrintDebug ) {
    cerr << "Event Dump: " << fNEventsProcessed << endl;  
    cerr << "Central Jets" << endl;
    for (UInt_t i = 0; i < GoodJets->GetEntries(); i++) {
      cerr << i << " " << GoodJets->At(i)->Pt() << " " 
           << GoodJets->At(i)->Eta() << " " << GoodJets->At(i)->Phi() << endl;    
    }
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(GoodJets, fGoodJetsName.Data());  
}

//--------------------------------------------------------------------------------------------------
void JetIDMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fJetName,              fJets);
}

//--------------------------------------------------------------------------------------------------
void JetIDMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void JetIDMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
