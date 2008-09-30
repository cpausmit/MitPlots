// $Id: ObjectCleaningMod.cc,v 1.5 2008/09/10 03:33:28 loizides Exp $

#include "MitAna/TreeMod/interface/ObjectCleaningMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/Utils/interface/IsolationTools.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
#include "MitAna/Utils/interface/IsolationTools.h"

using namespace mithep;

ClassImp(mithep::ObjectCleaningMod)

//--------------------------------------------------------------------------------------------------
  ObjectCleaningMod::ObjectCleaningMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fMCPartName(Names::gkMCPartBrn),
  fMuonName(Names::gkMuonBrn),
  fElectronName(Names::gkElectronBrn),
  fJetName(Names::gkCaloJetBrn),
  fSCJetName(Names::gkSC5JetBrn),
  fMetName(Names::gkCaloMetBrn),
  fGoodElectronsName("GoodElectrons"),        
  fGoodMuonsName("GoodMuons"),        
  fGoodCentralJetsName("GoodCentralJets" ),        
  fGoodForwardJetsName("GoodForwardJets" ),  
  fGoodCentralSCJetsName("GoodCentralSCJets" ),        
  fGoodForwardSCJetsName("GoodForwardSCJets" ),
  fGenLeptonsName("GenLeptons"),
  fParticles(0),
  fMuons(0),
  fElectrons(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and
  //output debug info or not   

  fNEventsProcessed++;
 
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);

    cerr << endl << "ObjectCleaningMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;  
  }
  
 //Muons
  ObjArray<Muon> *GoodMuons = new ObjArray<Muon>; 
  LoadBranch(fMuonName);

  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    Muon *mu = fMuons->At(i);
    fAllMuonPtHist->Fill(mu->Pt());
    fAllMuonEtaHist->Fill(mu->Eta());    

    Double_t MuonClass = -1;    
    //Find Class of Muons: Global(0), Standalone(1), Tracker(2)
    //Double_t MuonClass = -1;
    
    if (mu->GlobalTrk())      
      MuonClass = 0;
    else if (mu->StandaloneTrk())

      MuonClass = 1;
    else if (mu->TrackerTrk())
      MuonClass = 2;

    //Define the ID Cuts
    const int nCuts = 4;
    double cutValue[nCuts] = {0.1, 3.0, 3.0, 1.5 };
    bool passCut[nCuts] = {false, false, false, false};
    
    double muonD0 = -0.05;

    muonD0 = mu->BestTrk()->D0();
    if(muonD0 < cutValue[0] &&  MuonClass == 0 ) 
      passCut[0] = true;
    if(mu->IsoR03SumPt() < cutValue[1]) passCut[1] = true;
    if(mu->IsoR03EmEt() + 
       mu->IsoR03HadEt() < cutValue[2]) passCut[2] = true;    
    if(mu->Pt() > 5)
      passCut[3] = true;   

    // if(mu->Trk()->NHits() > 6)
//       passCut[4] = true;

//     if(mu->Trk()->Chi2() / mu->Trk()->Ndof() < 5 )
//       passCut[5] = true;

    // Final decision
    bool allCuts = true;
    for(int c=0; c<nCuts; c++) {
      allCuts = allCuts & passCut[c];
    }

    //make muon ID selection histograms
    fMuonSelection->Fill(-1);    
    //Fill the rest of the muon selection histograms
    for (int k=0;k<3;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
        pass = (pass && passCut[p]);
      
      if (pass) {
        fMuonSelection->Fill(k);
      }
    } 
    //Fill histogram for the Good Muons
    if ( allCuts
         && abs(mu->Eta()) < 2.5
      ) {     
      fGoodMuonPtHist->Fill(mu->Pt());
      fGoodMuonEtaHist->Fill(mu->Eta());       
      GoodMuons->Add(mu);
    }                    
  }
  

  //Get Electrons
  LoadBranch(fElectronName);

  //we have to use a vector first and then fill the ObjArray with the vector 
  //contents because ObJArray does not allow removal of duplicates.
  vector<Electron*> GoodElectronsVector;
  vector<Electron*> GoodLooseElectronsVector;
  vector<Electron*> GoodTightElectronsVector;
  vector<Electron*> GoodLikelihoodIDElectronsVector;

  for (UInt_t i=0; i<fElectrons->GetEntries(); ++i) {    
    Electron *e = fElectrons->At(i);   
    fAllElectronPtHist->Fill(e->Pt());
    fAllElectronEtaHist->Fill(e->Eta());               
    
    //from RecoEgamma/ElectronIdentification/src/CurBasedElectronID.cc  : CMSSW 2_1_0
    Int_t InEndcapOrBarrel = (fabs(e->Eta()) < 1.479)? 0 : 1;     
    double sigmaEtaEta = e->CovEtaEta();
    //have to correct sigma_etaeta dependance on eta in the endcap
    if (InEndcapOrBarrel == 1) {
      sigmaEtaEta = sigmaEtaEta - 0.02*(fabs(e->Eta()) - 2.3);
      e->SetCovEtaEta(e->CovEtaEta() - 0.02*(fabs(e->Eta()) - 2.3));
    }

    //Calculate the electron category for determining which cuts to make
    Int_t ElectronCategory;
    Double_t fBrem = (e->PIn() - e->POut())/e->PIn();
    if((fabs(e->Eta())<1.479 && fBrem<0.06) || (fabs(e->Eta())>1.479 && fBrem<0.1)) 
      ElectronCategory=1;
    else if (e->ESuperClusterOverP() < 1.2 && e->ESuperClusterOverP() > 0.8) 
      ElectronCategory=0;
    else 
      ElectronCategory=2;       
    
    // Final decision
    bool allCuts = true;  
    allCuts = e->PassTightID();    

    //Check whether it overlaps with a good muon.
    bool isMuonOverlap = false;
    for (UInt_t j=0; j<GoodMuons->GetEntries();j++) {
      double deltaR = MathUtils::DeltaR(GoodMuons->At(j)->Mom(), e->Mom());     
      if (deltaR < 0.1) {
        isMuonOverlap = true;
        break;	 
      }
    }

    //Check whether it overlaps with another electron candidate
    bool isElectronOverlap = false;
    for (UInt_t j=0; j<GoodElectronsVector.size(); j++) {      
      double deltaR = MathUtils::DeltaR(GoodElectronsVector[j]->Mom(), e->Mom());

      if (deltaR < 0.1) {
        isElectronOverlap = true;        
        
        //if there's an overlap and the new one being considered has E/P closer to 1.0 
        //then replace the overlapping one with this new one because it's better.
        //Once we get super cluster info, we should make sure the superclusters match 
        //before declaring it is a duplicate
        //can have one SC matched to many tracks. or one track matched to many SC's. 
        //we should cover all the cases. see SUSYAnalyzer...
        //Si: This will be unnecessary very soon. It is to be removed in reconstruction.
        if (abs(GoodElectronsVector[j]->ESuperClusterOverP() - 1) > 
            abs(e->ESuperClusterOverP() - 1)) {	   
          GoodElectronsVector[j] = e;
        }        
        break;
      }
    }

    //These are Good Electrons
    if ( allCuts && !isMuonOverlap && !isElectronOverlap                   
      ) {       
      fGoodElectronPtHist->Fill(e->Pt());
      fGoodElectronEtaHist->Fill(e->Eta());  
      fGoodElectronClassification->Fill(e->Classification());      
      GoodElectronsVector.push_back(fElectrons->At(i));   
    }   

  }     
  //fill the electron ObjArray with the contents of the vector
  //this is necessary because I want to swap out the duplicates, can't be done with ObjArray...
  ObjArray<Electron> *GoodElectrons = new ObjArray<Electron>;
  for (UInt_t j=0; j<GoodElectronsVector.size(); j++) 
    GoodElectrons->Add(GoodElectronsVector[j]);
  
  //Get Jet info
  ObjArray<Jet> *GoodCentralJets = new ObjArray<Jet>; 
  ObjArray<Jet> *GoodForwardJets = new ObjArray<Jet>; 
  LoadBranch(fJetName);
  for (UInt_t i=0; i<fJets->GetEntries(); ++i) {
    Jet *jet = fJets->At(i);
        
    bool isElectronOverlap =  false;
     
    //Check for overlap with an electron
    for (UInt_t j=0; j<GoodElectrons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GoodElectrons->At(j)->Mom(),jet->Mom());  
      if (deltaR < 0.1) {
	isElectronOverlap = true;	 	 	
	break;	 	 
      }      
    }
    if (isElectronOverlap) continue; //skip this jet if it was an overlap
    
    
    fAllJetPtHist->Fill(jet->Pt());
    fAllJetEtaHist->Fill(jet->Eta());
        
    const int nCuts = 4;
    double cutValue[nCuts] = {1.0, 15., 2.5, 0.2};
    bool passCut[nCuts] = {false, false, false, false};
    
    passCut[0] = (!isElectronOverlap); //This is supposed to check e/ph overlap
    if(jet->Et() > cutValue[1])           passCut[1] = true;
    if(fabs(jet->Eta()) < cutValue[2])    passCut[2] = true;        
    if(jet->Alpha() > cutValue[3] ||
       jet->Et() > 20.) 
      passCut[3] = true; 
    
    // Final decision
    bool passAllCentralJetCuts = true;
    bool passAllForwardJetCuts = true;
    for(int i=0; i<nCuts; i++) {
      passAllCentralJetCuts = passAllCentralJetCuts && passCut[i];
      passAllForwardJetCuts = passAllForwardJetCuts && ((i==2)?(!passCut[i]):passCut[i]);       
    }
    
    //make electron ID selection histogram
    fCentralJetSelection->Fill(-1);
   
    for (int k=0;k<nCuts;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
	pass = (pass && passCut[p]);
      
      if (pass) {
	fCentralJetSelection->Fill(k);	
     }
    } 
                
    //Save Good Jets
    if (passAllCentralJetCuts) {
      GoodCentralJets->Add(jet);     
    }
    
    if(passAllForwardJetCuts)
      GoodForwardJets->Add(jet);
    
  } //for all jets
   

//Get Siscone 5 Jet info
  ObjArray<Jet> *GoodCentralSCJets = new ObjArray<Jet>; 
  ObjArray<Jet> *GoodForwardSCJets = new ObjArray<Jet>; 
  LoadBranch(fSCJetName);
  for (UInt_t i=0; i<fSCJets->GetEntries(); ++i) {
    Jet *jet = fSCJets->At(i);
        
    bool isElectronOverlap =  false;
     
    //Check for overlap with an electron
    for (UInt_t j=0; j<GoodElectrons->GetEntries(); j++) {
      double deltaR = MathUtils::DeltaR(GoodElectrons->At(j)->Mom(),jet->Mom());  
      if (deltaR < 0.1) {
	isElectronOverlap = true;	 	 	
	break;	 	 
      }      
    }
    if (isElectronOverlap) continue; //skip this jet if it was an overlap
            
    const int nCuts = 4;
    double cutValue[nCuts] = {1.0, 15., 2.5, 0.2};
    bool passCut[nCuts] = {false, false, false, false};
    
    passCut[0] = (!isElectronOverlap); //This is supposed to check e/ph overlap
    if(jet->Et() > cutValue[1])           passCut[1] = true;
    if(fabs(jet->Eta()) < cutValue[2])    passCut[2] = true;        
    if(jet->Alpha() > cutValue[3] ||
       jet->Et() > 20.) 
      passCut[3] = true; 
    
    // Final decision
    bool passAllCentralJetCuts = true;
    bool passAllForwardJetCuts = true;
    for(int i=0; i<nCuts; i++) {
      passAllCentralJetCuts = passAllCentralJetCuts && passCut[i];
      passAllForwardJetCuts = passAllForwardJetCuts && ((i==2)?(!passCut[i]):passCut[i]);       
    }
        
    for (int k=0;k<nCuts;k++) {
      bool pass = true;
      for (int p=0;p<=k;p++)
	pass = (pass && passCut[p]);
            
    }       
    
    //Save Good SCJets
    if (passAllCentralJetCuts) {
      GoodCentralSCJets->Add(jet);      
    }
    
    if(passAllForwardJetCuts)
      GoodForwardSCJets->Add(jet);
    
  } //for all jets    

   //Get MET
  LoadBranch(fMetName);

  Met *met = fMet->At(0); //define the met
  fMetPtHist->Fill(met->Pt());
  fMetPhiHist->Fill(met->Phi());
      
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
    
    cerr << "Muons" << endl;
    for (UInt_t i = 0; i < GoodMuons->GetEntries(); i++) {
      cerr << i << " " << GoodMuons->At(i)->Pt() << " " << GoodMuons->At(i)->Eta() 
           << " " << GoodMuons->At(i)->Phi() << endl;    
    }
    
    cerr << "Central Jets" << endl;
    for (UInt_t i = 0; i < GoodCentralJets->GetEntries(); i++) {
      cerr << i << " " << GoodCentralJets->At(i)->Pt() << " " 
           << GoodCentralJets->At(i)->Eta() << " " << GoodCentralJets->At(i)->Phi() << endl;    
    }
    
    cerr << "MET" << endl;	  
    cerr << met->Pt() << " " << met->Eta() << " " 
         << met->Phi() << endl;    	                
  }   
  
  //Save Objects for Other Modules to use
  AddObjThisEvt(GoodElectrons, fGoodElectronsName.Data());
  AddObjThisEvt(GoodMuons, fGoodMuonsName.Data());
  AddObjThisEvt(GoodCentralJets, fGoodCentralJetsName.Data());
  AddObjThisEvt(GoodForwardJets, fGoodForwardJetsName.Data());
  AddObjThisEvt(GoodCentralSCJets, fGoodCentralSCJetsName.Data());
  AddObjThisEvt(GoodForwardSCJets, fGoodForwardSCJetsName.Data());
  
}


//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMCPartName,                fParticles);
  ReqBranch(fMuonName,                  fMuons);
  ReqBranch(fElectronName,              fElectrons);
  ReqBranch(fJetName,                   fJets);
  ReqBranch(fSCJetName,                 fSCJets);
  ReqBranch(fMetName,                   fMet);


  fAllMuonPtHist                   = new TH1D("hAllMuonPtHist",";p_{t};#",200,0.,200.);
  fAllMuonEtaHist                  = new TH1D("hAllMuonEtaHist",";#eta;#",100,-5.,5.);
  fGoodMuonPtHist                  = new TH1D("hGoodMuonPtHist",";p_{t};#",200,0.,200.);
  fGoodMuonEtaHist                 = new TH1D("hGoodMuonEtaHist",";#eta;#",21,-5.,5.);
  fMuonSelection                   = new TH1D("hMuonSelection", ";MuonSelection;#",4,-1.5,2.5 ) ;  
  AddOutput(fAllMuonPtHist);
  AddOutput(fAllMuonEtaHist);
  AddOutput(fGoodMuonPtHist);
  AddOutput(fGoodMuonEtaHist);
  AddOutput(fMuonSelection);
 
  fAllElectronPtHist                     = new TH1D("hAllElectronPtHist",";p_{t};#",100,0.,200.);  
  fAllElectronEtaHist                    = new TH1D("hAllElectronEtaHist",";#eta;#",100,-5.,5.);
  fGoodElectronPtHist                    = new TH1D("hGoodElectronPtHist",";p_{t};#",25,0.,200.);
  fGoodElectronEtaHist                   = new TH1D("hGoodElectronEtaHist",";#eta;#",21,-5.,5.);
  fGoodElectronClassification            = new TH1D("hGoodElectronClassification",
                                                    ";Good Electron Classification;#",51,0,50 ) ; 
  AddOutput(fAllElectronPtHist);
  AddOutput(fAllElectronEtaHist);
  AddOutput(fGoodElectronPtHist);
  AddOutput(fGoodElectronEtaHist);
  AddOutput(fGoodElectronClassification);

  //Jet Plots
  fAllJetPtHist                   = new TH1D("hAllJetPtHist",";All Jet p_{t};#",100,0.,200.);
  fAllJetEtaHist                  = new TH1D("hAllJetEtaHist",";All Jet #eta;#",160,-8.,8.);
  fCentralJetSelection            = new TH1D("hCentralJetSelection",
                                             ";CentralJetSelection;#",5,-1.5,3.5 ) ; 
  AddOutput(fAllJetPtHist);
  AddOutput(fAllJetEtaHist);
  AddOutput(fCentralJetSelection);

  //MET Plots
  fMetPtHist                = new TH1D("hMetPtHist",";p_{t};#",30,0.,300.);
  fMetPhiHist               = new TH1D("hMetPhiHist",";#phi;#",28,-3.5,3.5);
  AddOutput(fMetPtHist);
  AddOutput(fMetPhiHist);


}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

}

//--------------------------------------------------------------------------------------------------
void ObjectCleaningMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
