 // $Id: HwwEvtSelMod.cc,v 1.1 2008/09/30 19:24:22 sixie Exp $

#include "MitAna/PhysicsMod/interface/HwwEvtSelMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;
ClassImp(mithep::HwwEvtSelMod)

//--------------------------------------------------------------------------------------------------
HwwEvtSelMod::HwwEvtSelMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fPlotType("N-1"),
  fMCPartName(Names::gkMCPartBrn),
  fMetName(Names::gkCaloMetBrn),
  fTrackName(Names::gkTrackBrn),
  fJetName(Names::gkCaloJetBrn),
  fCleanJetsName(Names::gkCleanJetsName), 
  fLoadGenParticles(false),
  fParticles(0),
  fMet(0),
  fTracks(0),
  fJets(0),
  fNEventsProcessed(0),
  fNEventsPassedSkim(0),
  fNEventsPassedLeptonSelection(0),
  fNEventsPassedKinematicPreselection(0),
  fNEventsInsideAcceptance(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void HwwEvtSelMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void HwwEvtSelMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and  
  fNEventsProcessed++;

  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);
    cerr << endl << "HwwEvtSelMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;
  }

  //Get Generator Level information for matching
  ObjArray<MCParticle> *GenLeptons = new ObjArray<MCParticle>;


  if (fLoadGenParticles) {
    LoadBranch(fMCPartName);
    
    for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
      MCParticle* p = fParticles->At(i);
      
      if (p->IsGenerated() && 
          (p-> HasMother() && p->Mother()->AbsPdgId() == 24) &&
          (p->AbsPdgId() == 11 || p->AbsPdgId() == 13) 
          && p->Status() == 3
        )  
        GenLeptons->Add(p);    
    }
    
    if (fPrintDebug) cerr << "check generator leptons\n";
    for (UInt_t i=0; i<GenLeptons->GetEntries(); ++i) {    
      if (fPrintDebug) {
        cerr << i << " " << GenLeptons->At(i)->PdgId() << " " << GenLeptons->At(i)->Status() 
             << " " << GenLeptons->At(i)->Pt() << " " << GenLeptons->At(i)->Eta() << " " 
             << GenLeptons->At(i)->Phi() << endl;
      }
    }   

    int nGenLeptonsInsideAcceptance = 0;
    for(UInt_t i=0; i<GenLeptons->GetEntries();i++) {
      if (fabs(GenLeptons->At(i)->Eta()) < 2.5)
        nGenLeptonsInsideAcceptance++;
    }
    if (nGenLeptonsInsideAcceptance == 2)
      fNEventsInsideAcceptance++;
  }  

  //Obtain all the good objects from the event cleaning module
  ObjArray<Electron> *CleanElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(Names::gkCleanElectronsName));
  ObjArray<Muon> *CleanMuons = dynamic_cast<ObjArray<Muon>* >(FindObjThisEvt(Names::gkCleanMuonsName));
  ObjArray<Jet> *CleanJets = dynamic_cast<ObjArray<Jet>* >
    (FindObjThisEvt(fCleanJetsName.Data()));

  LoadBranch(fMetName);
  Met *caloMet = fMet->At(0);

  vector<ChargedParticle*> leptons;
  vector<string> leptonType; 
  
  //make lepton vector from muons and electrons
  for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
    leptons.push_back(CleanMuons->At(j));
    leptonType.push_back("mu");
  }
  for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {   
    leptons.push_back(CleanElectrons->At(j));
    leptonType.push_back("e");
  }

  //We should sort the Leptons by Pt   
  for(UInt_t i=0; i<leptons.size(); i++)
    for(UInt_t j=i+1; j<leptons.size(); j++)
      if(leptons[i]->Pt() < leptons[j]->Pt()) {
	//swap i and j
	ChargedParticle* templepton = leptons[i];
	leptons[i] = leptons[j];
	leptons[j] = templepton;
	string templeptonType = leptonType[i];
	leptonType[i] = leptonType[j];
	leptonType[j] = templeptonType;	 
      }
  
  if (fPrintDebug) {
    cerr << "Check Lepton Sort\n";
    for(UInt_t i=0; i<leptons.size(); i++)
      cerr << leptons[i]->Pt() << endl;
  }
  
  if (fPrintDebug)
    cerr << "Analysis begins" << endl;
  
  //make sure 2nd highest pt lepton has Pt > 0
  if (leptons.size() < 2 || leptons[1]->Pt() <= 0) return;
  
  //make sure the 3rd highest pt lepton has pt <= 10.
  if (leptons.size() >= 3 && leptons[2]->Pt() > 10) return;
  
  //needs to pass HLT  
  fNEventsPassedLeptonSelection++;
    
  CompositeParticle *dilepton = new CompositeParticle();
  dilepton->AddDaughter(leptons[0]);
  dilepton->AddDaughter(leptons[1]);
  
  //charge of the leptons should be opposite
  if (dilepton->Charge() != 0) return;
  
  fNEventsPassedKinematicPreselection++;

  if (fPrintDebug)
    cerr << "Event Passes PreSelection" << endl;  
  
  //delta phi between the 2 leptons in degrees
  double deltaPhiLeptons = MathUtils::DeltaPhi(leptons[0]->Phi(), 
                                               leptons[1]->Phi())* 360.0 / 2 / TMath::Pi();

  double deltaEtaLeptons = abs(leptons[0]->Eta() - leptons[1]->Eta()) * 360.0 / 2 / TMath::Pi();

  double deltaPhiDileptonMet = MathUtils::DeltaPhi(caloMet->Phi(), 
                                                   dilepton->Phi())*360.0 / 2 / TMath::Pi();

  double mtHiggs = TMath::Sqrt(2.0*dilepton->Pt() * caloMet->Pt()*
			       (1.0 - cos(deltaPhiDileptonMet * 2 * TMath::Pi() / 360.0)));

  //angle between MET and closest lepton
  double deltaPhiMetLepton[2] = {MathUtils::DeltaPhi(caloMet->Phi(), leptons[0]->Phi()),
                                 MathUtils::DeltaPhi(caloMet->Phi(), leptons[1]->Phi())};
  
  double mTW[2] = {TMath::Sqrt(2.0*leptons[0]->Pt()*caloMet->Pt()*
                               (1.0 - cos(deltaPhiMetLepton[0]))),
		   TMath::Sqrt(2.0*leptons[1]->Pt()*caloMet->Pt()*
                               (1.0 - cos(deltaPhiMetLepton[1])))};

  double minDeltaPhiMetLepton = (deltaPhiMetLepton[0] < deltaPhiMetLepton[1])?
    deltaPhiMetLepton[0]:deltaPhiMetLepton[1];
  minDeltaPhiMetLepton = minDeltaPhiMetLepton * 360.0 / 2 / TMath::Pi();

  //count the number of central Jets for vetoing
  int nCentralJets = 0;
  for (UInt_t j=0; j<CleanJets->GetEntries(); j++) {
    if (fabs(CleanJets->At(j)->Eta()) < 2.5)
      nCentralJets++;
  }

  //study low energy jets + track
  LoadBranch(fTrackName);
  LoadBranch(fJetName);
  int nCentralJetPlusOneTrack = 0;
  int nCentralJetTrackSumPt = 0;
  //Get all Tracks not corresponding to leptons
  ObjArray<Track> *CleanTracks = new ObjArray<Track>;
  for (UInt_t i=0; i<fTracks->GetEntries(); ++i) {
    bool TrackIsLepton = false;
    if (MathUtils::DeltaR(fTracks->At(i)->Eta(),fTracks->At(i)->Phi(),leptons[0]->Eta(),
                          leptons[0]->Phi()) > 0.01 &&
        MathUtils::DeltaR(fTracks->At(i)->Eta(),fTracks->At(i)->Phi(),leptons[1]->Eta(),
                          leptons[1]->Phi()) > 0.01
      ) {
    } else {
      TrackIsLepton = true;
    }
    if (fPrintDebug) {
      cerr << "Track " << i << " : "  << fTracks->At(i)->Pt() << " " << fTracks->At(i)->Eta() 
           << " " << fTracks->At(i)->Phi() << " islepton=" << TrackIsLepton << endl;      
    }      
    if (!TrackIsLepton && fTracks->At(i)->Pt() > 3.0 ) {
      CleanTracks->Add(fTracks->At(i));
    }
  }
  //Look for low energy jets + track confirmation
  for (UInt_t i=0; i<fJets->GetEntries(); i++) {
    if (fabs(fJets->At(i)->Eta()) < 2.5) {
    
      //remove overlaps with electrons
      bool isElectronOverlap = false;
      for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {
        double deltaR = MathUtils::DeltaR(CleanElectrons->At(j)->Mom(),fJets->At(i)->Mom());  
        if (deltaR < 0.3) {
          isElectronOverlap = true;	 	 	
          break;	 	 
        }      
      }
      if (isElectronOverlap) continue; //skip if it overlaps with an electron
      //remove overlap with clean jets
      bool isCleanJet = false;
      for(UInt_t j=0; j<CleanJets->GetEntries(); j++){
//        double deltaR = MathUtils::DeltaR(CleanJets->At(j)->Mom(),fJets->At(i)->Mom());  
        //cerr << "CleanJets->At(j):" << CleanJets->At(j) << " fJets->At(i):" << fJets->At(i) << endl;        
        if (CleanJets->At(j) == fJets->At(i)) {
          isCleanJet = true;	 	 	
          break;
        }                  
      }
      if (isCleanJet) continue; //skip if it was already a clean jet      
      if (fJets->At(i)->Et() < 10) continue; //skip jets below 10 GeV      
      
      //find high pt tracks inside these jets
      double trackSumPt = 0;
      int NHighPtTracksInsideJet = 0;
      for (UInt_t j=0; j<CleanTracks->GetEntries(); ++j) { 
        double deltaR = MathUtils::DeltaR(CleanTracks->At(j)->Phi(),CleanTracks->At(j)->Eta(),
                                          fJets->At(i)->Phi(),fJets->At(i)->Eta()); 
        
        if (deltaR < 0.5) {
          trackSumPt += CleanTracks->At(j)->Pt();
          if (CleanTracks->At(j)->Pt() > 3.0) {
            NHighPtTracksInsideJet++;
            if (fPrintDebug) cerr << "HighPtTrack " << j << " " << CleanTracks->At(j)->Pt() << " " 
                                  << CleanTracks->At(j)->Eta() << " " << CleanTracks->At(j)->Phi() << endl;
          }
        }  
      }
      //at least one high pt track inside
      if (NHighPtTracksInsideJet >= 1) {
        nCentralJetPlusOneTrack++;
      }
      //track sumpt / jet et > 1.0
      if (trackSumPt / fJets->At(i)->Et() > 1.0) {
        nCentralJetTrackSumPt++;
      }
      
    }
  }
  
  const int nCuts = 8;
  bool passCut[nCuts] = {false, false, false, false,
			   false, false, false, false};
 
  if(leptons[0]->Pt() > 7.0 &&
       leptons[1]->Pt() > 7.0)   passCut[0] = true;
  
  if(caloMet->Pt() > 30.0 &&
     dilepton->Mass()         > 12.0 &&
       //nCleanJets           < 3    &&
     leptons[0]->Pt()       > 20.0 &&
     leptons[1]->Pt()       > 10.0)  passCut[1] = true;
  
  if(nCentralJets < 1)     passCut[2] = true;

  if (leptonType[0] == "mu" && leptonType[1] == "mu" ){ // mumu
    if(caloMet->Pt()			> 50.0 &&
       caloMet->Pt()			< 200.0) passCut[3] = true;
    if(deltaPhiLeptons		< 45.0)  passCut[4] = true;
    if(dilepton->Mass()		< 50.0)  passCut[5] = true;
    if(leptons[0]->Pt()	> 35.0   &&
       leptons[0]->Pt()	< 55.0)  passCut[6] = true;
    if(leptons[1]->Pt()	> 25.0)  passCut[7] = true;
  }
  else if(leptonType[0] == "e" && leptonType[1] == "e"){ // ee
    if(caloMet->Pt()			> 51.0 &&
       caloMet->Pt()			< 200.0) passCut[3] = true;
    if(deltaPhiLeptons		< 45.0)  passCut[4] = true;
    if(dilepton->Mass()		< 40.0)  passCut[5] = true;
      if(leptons[0]->Pt()	> 25.0   &&
	 leptons[0]->Pt()	< 49.0)  passCut[6] = true;
      if(leptons[1]->Pt()	> 25.0)  passCut[7] = true;
  }      
  else if((leptonType[0] == "e" && leptonType[1] == "mu") || 
	  (leptonType[0] == "mu" && leptonType[1] == "e")
    ){ //emu
    if(caloMet->Pt()			> 45.0 &&
       caloMet->Pt()			< 105.0) passCut[3] = true;
    if(deltaPhiLeptons		< 70.0)  passCut[4] = true;
    if(dilepton->Mass()		< 45.0)  passCut[5] = true;
    if(leptons[0]->Pt()	> 25.0   &&
       leptons[0]->Pt()	< 50.0)  passCut[6] = true;
    if(leptons[1]->Pt()	> 25.0)  passCut[7] = true;
  }

  // Final decision
  bool allCuts = true;
  for(int i=0; i<nCuts; i++) allCuts = allCuts & passCut[i];
  
  
  fHWWSelection->Fill(-1);
  if (leptonType[0] == "mu" && leptonType[1] == "mu" )
    fHWWToMuMuSelection->Fill(-1);
  else if(leptonType[0] == "e" && leptonType[1] == "e")
    fHWWToEESelection->Fill(-1);
  else if((leptonType[0] == "e" && leptonType[1] == "mu") || 
	  (leptonType[0] == "mu" && leptonType[1] == "e"))
    fHWWToEMuSelection->Fill(-1);
  
    if (fPlotType == "Sequential") {
      for (int k=0;k<8;k++) {
        bool pass = true;
        for (int p=0;p<=k;p++)
          pass = (pass && passCut[p]);
        
        if (pass) {
          fHWWSelection->Fill(k);
          if (leptonType[0] == "mu" && leptonType[1] == "mu" )
            fHWWToMuMuSelection->Fill(k);
          else if(leptonType[0] == "e" && leptonType[1] == "e")
            fHWWToEESelection->Fill(k);
          else if((leptonType[0] == "e" && leptonType[1] == "mu") || 
                  (leptonType[0] == "mu" && leptonType[1] == "e"))
            fHWWToEMuSelection->Fill(k);
        }
        
        if (k==0 && pass) {
          fLeptonPtMax->Fill(leptons[0]->Pt());
          fLeptonPtMin->Fill(leptons[1]->Pt());
          fLeptonEta->Fill(leptons[0]->Eta());
          fLeptonEta->Fill(leptons[1]->Eta());
        }
        
        if (k==1 && pass) {
          fNCentralJets->Fill(nCentralJets);
        }
        if (k==2 && pass) {      
          //fMetPtAfterSelectionHist->Fill(caloMet->Pt());
        }
        if (k==3 && pass) {
          fDeltaPhiLeptons->Fill(deltaPhiLeptons);
        }
        if (k==4 && pass) {
          fDileptonMass->Fill(dilepton->Mass());
        }
        if (k==5 && pass) {
          fLepton1Pt_afterCuts->Fill(leptons[0]->Pt());
        }
        if (k==6 && pass) {
          fLepton2Pt_afterCuts->Fill(leptons[1]->Pt());
        }
        if (k==7 && pass) {
          fMetPtAfterSelectionHist->Fill(caloMet->Pt());
          fMtHiggs->Fill(mtHiggs);
          fDeltaEtaLeptons->Fill(deltaEtaLeptons);
          fMinDeltaPhiLeptonMet->Fill(minDeltaPhiMetLepton);
          fMetSignificanceAfterCuts->Fill(caloMet->MetSig());
          fSumEtAfterCuts->Fill(caloMet->SumEt());
          fMtLepton1->Fill(mTW[0]);
          fMtLepton2->Fill(mTW[1]);
          fLeptonPtPlusMet->Fill(leptons[0]->Pt()+leptons[1]->Pt()+caloMet->Pt());
        }      
      }
      
    } else if (fPlotType = "N-1") {
      for (int k=0;k<8;k++) {
        bool pass = true;
        for (int p=0;p<=k;p++)
          pass = (pass && passCut[p]);
        
        if (pass) {
          fHWWSelection->Fill(k);
          if (leptonType[0] == "mu" && leptonType[1] == "mu" )
            fHWWToMuMuSelection->Fill(k);
          else if(leptonType[0] == "e" && leptonType[1] == "e")
            fHWWToEESelection->Fill(k);
          else if((leptonType[0] == "e" && leptonType[1] == "mu") || 
                  (leptonType[0] == "mu" && leptonType[1] == "e"))
            fHWWToEMuSelection->Fill(k);
        }
        
        if (k==0 && pass) {
          fLeptonPtMax->Fill(leptons[0]->Pt());
          fLeptonPtMin->Fill(leptons[1]->Pt());
          fLeptonEta->Fill(leptons[0]->Eta());
          fLeptonEta->Fill(leptons[1]->Eta());
        }
      }
      
      //N Jet Veto  
      bool pass = true;
      for (int k=0;k<8;k++) {
        if (k != 2) {
          pass = (pass && passCut[k]);      
        }
      }
      if (pass) {
        fNCentralJets->Fill(nCentralJets);
        fNCentralJetsPlusOneTrack->Fill(nCentralJetPlusOneTrack);
        fNCentralJetsTrackSumPt->Fill(nCentralJetTrackSumPt);
      }
      
      // Delta Phi leptons
      pass = true;
      for (int k=0;k<8;k++) {
        if (k != 3)
          pass = (pass && passCut[k]);    
      }
      if (pass) {
        fMetPtHist->Fill(caloMet->Pt());
        fMetPhiHist->Fill(caloMet->Phi());  
      }


      // Delta Phi leptons
      pass = true;
      for (int k=0;k<8;k++) {
        if (k != 4)
          pass = (pass && passCut[k]);    
      }
      if (pass) {
        fDeltaPhiLeptons->Fill(deltaPhiLeptons);
      }
      
      //dilepton mass
      pass = true;
      for (int k=0;k<8;k++) {
        if (k != 5)
          pass = (pass && passCut[k]);    
      }
      if (pass) {
        fDileptonMass->Fill(dilepton->Mass());
      }
      
      //Lepton1Pt
      pass = true;
      for (int k=0;k<8;k++) {
        if (k != 6)
          pass = (pass && passCut[k]);    
      }
      if (pass) {
        fLepton1Pt_afterCuts->Fill(leptons[0]->Pt());
      }
      
      //Lepton2Pt
      pass = true;
      for (int k=0;k<8;k++) {
        if (k != 7)
          pass = (pass && passCut[k]);    
      }
      if (pass) {
        fLepton2Pt_afterCuts->Fill(leptons[1]->Pt());
      }
      
      pass = true;
      for (int k=0;k<8;k++) {  
        pass = (pass && passCut[k]);    
      }
      if (pass) {
        fMetPtAfterSelectionHist->Fill(caloMet->Pt());
        fMtHiggs->Fill(mtHiggs);
        fDeltaEtaLeptons->Fill(deltaEtaLeptons);
        fMinDeltaPhiLeptonMet->Fill(minDeltaPhiMetLepton);
        fMetSignificanceAfterCuts->Fill(caloMet->MetSig());
        fSumEtAfterCuts->Fill(caloMet->SumEt());
        fMtLepton1->Fill(mTW[0]);
        fMtLepton2->Fill(mTW[1]);
        fLeptonPtPlusMet->Fill(leptons[0]->Pt()+leptons[1]->Pt()+caloMet->Pt());
      }   
    }

    if(fPrintDebug) 
    {
      //print out event content to text
      cerr << "Electrons" << endl;
      for (UInt_t i = 0; i < CleanElectrons->GetEntries(); i++) {
        cerr << i << " " << CleanElectrons->At(i)->Pt() << " " 
             << CleanElectrons->At(i)->Eta() << " " << CleanElectrons->At(i)->Phi() 
             << " " << CleanElectrons->At(i)->ESuperClusterOverP() << endl;    
      }
      
      cerr << "Muons" << endl;
      for (UInt_t i = 0; i < CleanMuons->GetEntries(); i++) {
        cerr << i << " " << CleanMuons->At(i)->Pt() << " " << CleanMuons->At(i)->Eta() 
             << " " << CleanMuons->At(i)->Phi() << endl;    
      }
      
      cerr << "Jets" << endl;
      for (UInt_t i = 0; i < CleanJets->GetEntries(); i++) {
        cerr << i << " " << CleanJets->At(i)->Pt() << " " 
             << CleanJets->At(i)->Eta() << " " << CleanJets->At(i)->Phi() << endl;    
      }
      
      cerr << "CorrectedMET" << endl;	  
      cerr << caloMet->Pt() << " " << caloMet->Eta() << " " << caloMet->Phi() << endl;      
    } 

}
//--------------------------------------------------------------------------------------------------
void HwwEvtSelMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMetName, fMet);
  ReqBranch(fMCPartName, fParticles);
  ReqBranch(fTrackName,  fTracks);
  ReqBranch(fJetName,    fJets);

  fMetPtHist      = new TH1D("hMetPtHist",";Met;Number of Events",150,0.,300.);  
  fMetPhiHist     = new TH1D("hMetPhiHist",";#phi;Number of Events",28,-3.5,3.5);
  fMetPtAfterSelectionHist      = new TH1D("hMetPtAfterSelectionHist",";p_{t};Number of Events",150,0.,300.);  
  fMetPhiAfterSelectionHist     = new TH1D("hMetPhiAfterSelectionHist",";#phi;Number of Events",28,-3.5,3.5);
  fMetSignificanceAfterCuts      = new TH1D("hMetSignificanceAfterCuts",
                                            ";MetSignificanceAfterCuts;Number of Events",100,0.,20.);
  fSumEtAfterCuts      = new TH1D("hSumEtAfterCuts",";SumEt;Number of Events",100,0.,500.);
  AddOutput(fMetPhiHist);
  AddOutput(fMetPtHist);
  AddOutput(fMetPtAfterSelectionHist);
  AddOutput(fMetPhiAfterSelectionHist);
  AddOutput(fMetSignificanceAfterCuts);
  AddOutput(fSumEtAfterCuts);

  fNCentralJets      = new TH1D("hNCentralJets",";Number of Central Jets;Number of Events",6,-0.5,5.5);
  fNForwardJets      = new TH1D("hNForwardJets",";Number of Forward Jets;Number of Events",20,0,20);
  fNCentralJetsPlusOneTrack = new TH1D("hNCentralJetsPlusOneTrack",";Number of Central Jets Plus One Track;Number of Events",6,-0.5,5.5);
  fNCentralJetsTrackSumPt = new TH1D("hNCentralJetsTrackSumPt",";Number of Central Jets with TrackSumPt/Et > 1.0 ;Number of Events",6,-0.5,5.5);
  fVBFJetPt      = new TH1D("hVBFJetPt",";VBF Tagged Jet Pt;Number of Events",40,0,200);
  fVBFJetEta      = new TH1D("hVBFJetEta",";VBF Tagged Jet Eta;Number of Events",33,-8,8);
  fDeltaEtaVBFJets      = new TH1D("hDeltaEtaVBFJets",
                                   ";#Delta#eta between the two VBF Tagged Jets;Number of Events",20,0,10);
  AddOutput(fNCentralJets);
  AddOutput(fNForwardJets);
  AddOutput(fNCentralJetsPlusOneTrack);
  AddOutput(fNCentralJetsTrackSumPt);
  AddOutput(fVBFJetPt);
  AddOutput(fVBFJetEta);
  AddOutput(fDeltaEtaVBFJets);

  fDeltaPhiLeptons      = new TH1D("hDeltaPhiLeptons",";#Delta#phi_{ll};Number of Events",90,0,180);
  fDeltaEtaLeptons      = new TH1D("hDeltaEtaLeptons",";#Delta#eta_{ll};Number of Events",90,0.,180);
  fDileptonMass      = new TH1D("hDileptonMass",";Mass_{ll};Number of Events",150,0.,300.);
  fLeptonPtMax      = new TH1D("hLeptonPtMax",";Lepton P_t Max;Number of Events",150,0.,150.);
  fLeptonPtMin      = new TH1D("hLeptonPtMin",";Lepton P_t Min;Number of Events",150,0.,150.);
  fLeptonEta      = new TH1D("hLeptonEta",";LeptonEta;Number of Events",100,-5.,5.0);
  AddOutput(fDeltaPhiLeptons);
  AddOutput(fDeltaEtaLeptons);
  AddOutput(fDileptonMass);
  AddOutput(fLeptonPtMax);
  AddOutput(fLeptonPtMin);
  AddOutput(fLeptonEta);

  fLepton1Pt_afterCuts      = new TH1D("hLepton1Pt_afterCuts",";Lepton1Pt_afterCuts;Number of Events",150,0.,150.);
  fLepton2Pt_afterCuts      = new TH1D("hLepton2Pt_afterCuts",";Lepton2Pt_afterCuts;Number of Events",150,0.,150.);
  fMinDeltaPhiLeptonMet      = new TH1D("hMinDeltaPhiLeptonMet",
                                        ";Min #Delta#phi_{l,Met};Number of Events",90,0.,180);
  AddOutput(fLepton1Pt_afterCuts);
  AddOutput(fLepton2Pt_afterCuts);
  AddOutput(fMinDeltaPhiLeptonMet);

  fMtLepton1     = new TH1D("hMtLepton1",";M_t (Lepton1,Met);Number of Events",100,0.,200.);
  AddOutput(fMtLepton1);
  fMtLepton2     = new TH1D("hMtLepton2",";M_t (Lepton2,Met);Number of Events",100,0.,200.);
  AddOutput(fMtLepton2);
  fMtHiggs     = new TH1D("hMtHiggs",";M_t (l1+l2+Met);Number of Events",150,0.,300.);
  AddOutput(fMtHiggs);

  fpTTot     = new TH1D("hpTTot",";p_T Total;Number of Events",20,0.,200.);
  AddOutput(fpTTot);

  fLeptonPtPlusMet      = new TH1D("hLeptonPtPlusMet",";LeptonPtPlusMet;Number of Events",150,0.,300.);
  AddOutput(fLeptonPtPlusMet);

  fHWWSelection = new TH1D("hHWWSelection", ";Cut Number;Number of Events", 9, -1.5, 7.5);
  fHWWToEESelection = new TH1D("hHWWToEESelection", ";Cut Number;Number of Events", 9, -1.5, 7.5);
  fHWWToMuMuSelection = new TH1D("hHWWToMuMuSelection", ";Cut Number;Number of Events", 9, -1.5, 7.5);
  fHWWToEMuSelection = new TH1D("hHWWToEMuSelection", ";Cut Number;Number of Events", 9, -1.5, 7.5);
  AddOutput(fHWWSelection);
  AddOutput(fHWWToEESelection);
  AddOutput(fHWWToMuMuSelection);
  AddOutput(fHWWToEMuSelection);
}

//--------------------------------------------------------------------------------------------------
void HwwEvtSelMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.

  cerr << "Events Inside Acceptance: " << fNEventsInsideAcceptance << endl;
  cerr << "Events Processed: " << fNEventsProcessed << endl;
  cerr << "Events Passed Skim: " << fNEventsPassedSkim << endl;
  cerr << "Events Passed LeptonSelection: " << fNEventsPassedLeptonSelection << endl;
  cerr << "Events Passed KinematicPreselection: " << fNEventsPassedKinematicPreselection << endl;

  cerr << "For All" << endl;
  for (int i=1;i<=9;i++) {
    double CutEff = (i>1)?fHWWSelection->GetBinContent(i)/fHWWSelection->GetBinContent(i-1):1.0;
    cerr << "After Cut" << i-2 << " : " << fHWWSelection->GetBinContent(i) 
         << "   Efficiency of this Cut : " << CutEff << endl;
  }

  cerr << "For ee" << endl;
  for (int i=1;i<=9;i++) {
    double CutEff = (i>1)?fHWWToEESelection->GetBinContent(i)/fHWWToEESelection->
      GetBinContent(i-1):1.0;
    cerr << "After Cut" << i-2 << " : " << fHWWToEESelection->GetBinContent(i)
         << "   Efficiency of this Cut : " << CutEff << endl;
  }

  cerr << "For mumu" << endl;
  for (int i=1;i<=9;i++) {
    double CutEff = (i>1)?fHWWToMuMuSelection->GetBinContent(i)/fHWWToMuMuSelection->
      GetBinContent(i-1):1.0;
    cerr << "After Cut" << i-2 << " : " << fHWWToMuMuSelection->GetBinContent(i)
         << "   Efficiency of this Cut : " << CutEff << endl;
  }
  
  cerr << "For emu" << endl;  
  for (int i=1;i<=9;i++) {
    double CutEff = (i>1)?fHWWToEMuSelection->GetBinContent(i)/fHWWToEMuSelection->
      GetBinContent(i-1):1.0;
    cerr << "After Cut" << i-2 << " : " << fHWWToEMuSelection->GetBinContent(i)
         << "   Efficiency of this Cut : " << CutEff << endl;
  }

}

//--------------------------------------------------------------------------------------------------
void HwwEvtSelMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
