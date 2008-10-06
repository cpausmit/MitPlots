 // $Id: ttEvtSelMod.cc,v 1.1 2008/09/30 19:24:22 ceballos Exp $

#include "MitAna/PhysicsMod/interface/ttEvtSelMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;
ClassImp(mithep::ttEvtSelMod)

//--------------------------------------------------------------------------------------------------
ttEvtSelMod::ttEvtSelMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fMetName(Names::gkCaloMetBrn),
  fMuonName(Names::gkMuonBrn),
  fCleanJetsName(Names::gkCleanJetsName),
  fMCLeptonsName(Names::gkMCLeptonsName),
  fMCQuarksName(Names::gkMCQuarksName),
  fMet(0),
  fMuons(0),
  fNEventsProcessed(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ttEvtSelMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void ttEvtSelMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and  
  fNEventsProcessed++;

  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);
    cerr << endl << "ttEvtSelMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;
  }

  //Get Generator Level information for matching
  //ObjArray<MCParticle> *GenLeptons   = dynamic_cast<ObjArray<MCParticle>* > (FindObjThisEvt(fMCLeptonsName.Data()));
  ObjArray<MCParticle> *GenQuarks    = dynamic_cast<ObjArray<MCParticle>* > (FindObjThisEvt(fMCQuarksName.Data()));

  //Obtain all the good objects from the event cleaning module
  ObjArray<Electron> *CleanElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(Names::gkCleanElectronsName));
  ObjArray<Muon> *CleanMuons = dynamic_cast<ObjArray<Muon>* >
    (FindObjThisEvt(Names::gkCleanMuonsName));
  ObjArray<Jet> *CleanJets = dynamic_cast<ObjArray<Jet>* >
    (FindObjThisEvt(fCleanJetsName.Data()));

  LoadBranch(fMetName);
  Met *caloMet = fMet->At(0);

  vector<ChargedParticle*> leptons;
  vector<string> leptonType; 

  LoadBranch(fMuonName);
  ObjArray<Muon> *DirtyMuons = new ObjArray<Muon>;
  for (UInt_t i=0; i<fMuons->GetEntries(); ++i) {
    Muon *mu = fMuons->At(i);
    if(!mu->GlobalTrk()) continue;
    if(mu->Pt() < 5.0)   continue;

    bool isCleanMuon = false;
    for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
      if(fMuons->At(i) == CleanMuons->At(j)) isCleanMuon = true;
    }
    if(isCleanMuon == false) DirtyMuons->Add(mu);
  }

  // Make lepton vector from muons and electrons
  for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
    leptons.push_back(CleanMuons->At(j));
    leptonType.push_back("mu");
  }
  for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {   
    leptons.push_back(CleanElectrons->At(j));
    leptonType.push_back("e");
  }

  // Sort the Leptons by Pt   
  for(UInt_t i=0; i<leptons.size(); i++){
    for(UInt_t j=i+1; j<leptons.size(); j++){
      if(leptons[i]->Pt() < leptons[j]->Pt()) {
	//swap i and j
	ChargedParticle* templepton = leptons[i];
	leptons[i] = leptons[j];
	leptons[j] = templepton;
	string templeptonType = leptonType[i];
	leptonType[i] = leptonType[j];
	leptonType[j] = templeptonType;	 
      }
    }
  }
  if (fPrintDebug) {
    cout << "Check Lepton Sort\n";
    for(UInt_t i=0; i<leptons.size(); i++)
      cout << leptons[i]->Pt() << endl;
  }

  // Pt requirements
  if (leptons.size() < 2 || leptons[0]->Pt() < 20 || 
                            leptons[1]->Pt() < 15) return;

  // MET requirement
  if (caloMet->Pt() < 0) return;

  CompositeParticle *dilepton = new CompositeParticle();
  dilepton->AddDaughter(leptons[0]);
  dilepton->AddDaughter(leptons[1]);
  // Charge of the leptons should be opposite
  if (dilepton->Charge() != 0) return;

  // Minimum mass requirement
  if (dilepton->Mass() < 12) return;

  // Sort and count the number of central Jets for vetoing
  vector<Jet*> sortedJets;
  int nCentralJets = 0;
  for(UInt_t i=0; i<CleanJets->GetEntries(); i++){
    if(fabs(CleanJets->At(i)->Eta()) < 2.5){
      nCentralJets++;
      Jet* jet_f = new Jet(CleanJets->At(i)->Px()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
                           CleanJets->At(i)->Py()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
                           CleanJets->At(i)->Pz()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
			   CleanJets->At(i)->E() *CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale());
      sortedJets.push_back(jet_f);
    }
  }
  for(UInt_t i=0; i<sortedJets.size(); i++){
    for(UInt_t j=i+1; j<sortedJets.size(); j++){
      if(sortedJets[i]->Pt() < sortedJets[j]->Pt()) {
	//swap i and j
        Jet* tempjet = sortedJets[i];
        sortedJets[i] = sortedJets[j];
        sortedJets[j] = tempjet;	
      }
    }
  }

  // Delta phi between the 2 leptons in degrees
  double deltaPhiLeptons = MathUtils::DeltaPhi(leptons[0]->Phi(), 
                                               leptons[1]->Phi())* 180./TMath::Pi();

  double deltaEtaLeptons = abs(leptons[0]->Eta() - leptons[1]->Eta());

  double deltaPhiDileptonMet = MathUtils::DeltaPhi(caloMet->Phi(), 
                                                   dilepton->Phi())* 180./TMath::Pi();

  double mtHiggs = TMath::Sqrt(2.0*dilepton->Pt() * caloMet->Pt()*
			       (1.0 - cos(deltaPhiDileptonMet * TMath::Pi()/180.0)));

  // Angle between MET and closest lepton
  double deltaPhiMetLepton[2] = {MathUtils::DeltaPhi(caloMet->Phi(), leptons[0]->Phi()),
                                 MathUtils::DeltaPhi(caloMet->Phi(), leptons[1]->Phi())};
  
  double minDeltaPhiMetLepton = (deltaPhiMetLepton[0] < deltaPhiMetLepton[1])?
    deltaPhiMetLepton[0]:deltaPhiMetLepton[1];
  minDeltaPhiMetLepton = minDeltaPhiMetLepton * 180./TMath::Pi();

  double METdeltaPhilEt = caloMet->Pt();
  if(minDeltaPhiMetLepton < 90.0) 
    METdeltaPhilEt = METdeltaPhilEt * sin(minDeltaPhiMetLepton * TMath::Pi()/180.);

  double mTW[2] = {TMath::Sqrt(2.0*leptons[0]->Pt()*caloMet->Pt()*
                               (1.0 - cos(deltaPhiMetLepton[0]))),
		   TMath::Sqrt(2.0*leptons[1]->Pt()*caloMet->Pt()*
                               (1.0 - cos(deltaPhiMetLepton[1])))};

  int pairType = -1;
  if (leptonType[0] == "mu" && leptonType[1] == "mu" )
    pairType = 0;
  else if(leptonType[0] == "e" && leptonType[1] == "e")
    pairType = 1;
  else if((leptonType[0] == "e" && leptonType[1] == "mu") || 
	  (leptonType[0] == "mu" && leptonType[1] == "e"))
    pairType = 2;
  else {
    cout << "Hey, this is not possible, leptonTypes: "
         << leptonType[0] << " - " 
	 << leptonType[1] << endl;
  }

  hDttPresel[ 0+100*pairType]->Fill((double)leptons.size());
  // No more than 2 isolated good leptons
  if (leptons.size() > 2) return;

  hDttPresel[ 1+100*pairType]->Fill(caloMet->Pt());
  hDttPresel[ 2+100*pairType]->Fill(leptons[0]->Pt());
  hDttPresel[ 3+100*pairType]->Fill(leptons[1]->Pt());
  hDttPresel[ 4+100*pairType]->Fill(dilepton->Mass());
  hDttPresel[ 5+100*pairType]->Fill((double)nCentralJets);
  hDttPresel[ 6+100*pairType]->Fill(deltaEtaLeptons);
  hDttPresel[ 7+100*pairType]->Fill(deltaPhiLeptons);
  hDttPresel[ 8+100*pairType]->Fill(mtHiggs);
  hDttPresel[ 9+100*pairType]->Fill(minDeltaPhiMetLepton);
  hDttPresel[10+100*pairType]->Fill(METdeltaPhilEt);
  hDttPresel[11+100*pairType]->Fill(caloMet->MetSig());
  hDttPresel[12+100*pairType]->Fill(caloMet->SumEt());
  hDttPresel[13+100*pairType]->Fill(TMath::Max(mTW[0],mTW[1]));
  hDttPresel[14+100*pairType]->Fill(TMath::Min(mTW[0],mTW[1]));
  hDttPresel[15+100*pairType]->Fill(leptons[0]->Pt()+leptons[1]->Pt()+caloMet->Pt());
  for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
    hDttPresel[16+100*pairType]->Fill(TMath::Min(fabs(CleanMuons->At(j)->GlobalTrk()->D0()),0.3999));
  }
  for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {   
    hDttPresel[17+100*pairType]->Fill(TMath::Min(fabs(CleanElectrons->At(j)->GsfTrk()->D0()),0.3999));
  }

  // Study for genuine tt->WbWb->2l2nubb
  if(nCentralJets >= 2){
    hDttPresel[18+100*pairType]->Fill(TMath::Max(fabs(sortedJets[0]->Eta()),
                                                 fabs(sortedJets[1]->Eta())));
    hDttPresel[19+100*pairType]->Fill(TMath::Min(fabs(sortedJets[0]->Eta()),
                                                 fabs(sortedJets[1]->Eta())));
    hDttPresel[20+100*pairType]->Fill(MathUtils::DeltaPhi(sortedJets[0]->Phi(),sortedJets[1]->Phi())
                                      * 180.0 / TMath::Pi());
    hDttPresel[21+100*pairType]->Fill(fabs(sortedJets[0]->Eta()-sortedJets[1]->Eta()));
    hDttPresel[22+100*pairType]->Fill(MathUtils::DeltaR(sortedJets[0]->Phi(),sortedJets[0]->Eta(),
                                                        sortedJets[1]->Phi(),sortedJets[1]->Eta()));
    hDttPresel[23+100*pairType]->Fill(TMath::Max(fabs(sortedJets[0]->Pt()),
                                                 fabs(sortedJets[1]->Pt())));
    hDttPresel[24+100*pairType]->Fill(TMath::Min(fabs(sortedJets[0]->Pt()),
                                                 fabs(sortedJets[1]->Pt())));
    CompositeParticle *dijet = new CompositeParticle();
    dijet->AddDaughter(sortedJets[0]);
    dijet->AddDaughter(sortedJets[1]);
    hDttPresel[25+100*pairType]->Fill(dijet->Mass());
    hDttPresel[26+100*pairType]->Fill(dijet->Pt());

    // Study energy scale corrections
    if(GenQuarks->GetEntries() >= 2){
      double deltarAux[2];
      double deltaPt;
      deltarAux[0] = MathUtils::DeltaR(sortedJets[0]->Phi(),sortedJets[0]->Eta(),
                                       GenQuarks->At(0)->Phi(),GenQuarks->At(0)->Eta());
      deltarAux[1] = MathUtils::DeltaR(sortedJets[0]->Phi(),sortedJets[0]->Eta(),
                                       GenQuarks->At(1)->Phi(),GenQuarks->At(1)->Eta());
      hDttPresel[27+100*pairType]->Fill(TMath::Min(deltarAux[0],deltarAux[1]));
      deltaPt = -999;
      if     (deltarAux[0] < deltarAux[1] && deltarAux[0] < 1.0){
	deltaPt = (sortedJets[0]->Pt()-GenQuarks->At(0)->Pt())/sortedJets[0]->Pt();
      }
      else if(deltarAux[1] < deltarAux[0] && deltarAux[1] < 1.0){
	deltaPt = (sortedJets[0]->Pt()-GenQuarks->At(1)->Pt())/sortedJets[0]->Pt();
      }
      if(deltaPt != -999) hDttPresel[28+100*pairType]->Fill(deltaPt);
      deltarAux[0] = MathUtils::DeltaR(sortedJets[1]->Phi(),sortedJets[1]->Eta(),
                                       GenQuarks->At(0)->Phi(),GenQuarks->At(0)->Eta());
      deltarAux[1] = MathUtils::DeltaR(sortedJets[1]->Phi(),sortedJets[1]->Eta(),
                                       GenQuarks->At(1)->Phi(),GenQuarks->At(1)->Eta());
      hDttPresel[29+100*pairType]->Fill(TMath::Min(deltarAux[0],deltarAux[1]));
      deltaPt = -999;
      if     (deltarAux[0] < deltarAux[1] && deltarAux[0] < 1.0){
	deltaPt = (sortedJets[1]->Pt()-GenQuarks->At(0)->Pt())/sortedJets[1]->Pt();
      }
      else if(deltarAux[1] < deltarAux[0] && deltarAux[1] < 1.0){
	deltaPt = (sortedJets[1]->Pt()-GenQuarks->At(1)->Pt())/sortedJets[1]->Pt();
      }
      if(deltaPt != -999) hDttPresel[30+100*pairType]->Fill(deltaPt);
    }
  }

  // Study for additional muons
  hDttPresel[31+100*pairType]->Fill((double)DirtyMuons->GetEntries());
  for (UInt_t i=0; i<DirtyMuons->GetEntries(); ++i) {
    Muon *mu = DirtyMuons->At(i);
    hDttPresel[32+100*pairType]->Fill(mu->Pt());
    hDttPresel[33+100*pairType]->Fill(TMath::Min(fabs(mu->GlobalTrk()->D0()),0.3999));
  }
  if(DirtyMuons->GetEntries() > 0){
    hDttPresel[34+100*pairType]->Fill((double)nCentralJets);
  }

  // Study dijet mass
  if(nCentralJets >= 2){
    double dijetMass = 999.;
    int indDiJet[2] = {-1, -1};
    for(UInt_t i=0; i<sortedJets.size(); i++){
      for(UInt_t j=i+1; j<sortedJets.size(); j++){
	CompositeParticle *dijetTemp = new CompositeParticle();
	dijetTemp->AddDaughter(sortedJets[i]);
	dijetTemp->AddDaughter(sortedJets[j]);
	if(fabs(dijetTemp->Mass()-91.18) < fabs(dijetMass-91.18)){
	  dijetMass = dijetTemp->Mass();
	  indDiJet[0] = i;
	  indDiJet[1] = j;
	}
      }
    }
    hDttPresel[35+100*pairType]->Fill(dijetMass);
    if(indDiJet[0] == 0 && indDiJet[1] == 1)
      hDttPresel[36+100*pairType]->Fill(dijetMass);
    else
      hDttPresel[37+100*pairType]->Fill(dijetMass);
    hDttPresel[38+100*pairType]->Fill((double)(indDiJet[0]+10*indDiJet[1]));
  }
}
//--------------------------------------------------------------------------------------------------
void ttEvtSelMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMetName,    fMet);
  ReqBranch(fMuonName,   fMuons);

  char sb[200];
  for(int j=0; j<3; j++){
    int ind = 100 * j;
    sprintf(sb,"hDttPresel_%d",ind+0);  hDttPresel[ind+0]  = new TH1D(sb,sb,10,-0.5,9.5); 
    sprintf(sb,"hDttPresel_%d",ind+1);  hDttPresel[ind+1]  = new TH1D(sb,sb,150,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+2);  hDttPresel[ind+2]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDttPresel_%d",ind+3);  hDttPresel[ind+3]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDttPresel_%d",ind+4);  hDttPresel[ind+4]  = new TH1D(sb,sb,150,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+5);  hDttPresel[ind+5]  = new TH1D(sb,sb,10,-0.5,9.5); 
    sprintf(sb,"hDttPresel_%d",ind+6);  hDttPresel[ind+6]  = new TH1D(sb,sb,50,0.0,5.);  
    sprintf(sb,"hDttPresel_%d",ind+7);  hDttPresel[ind+7]  = new TH1D(sb,sb,90,0.0,180.); 
    sprintf(sb,"hDttPresel_%d",ind+8);  hDttPresel[ind+8]  = new TH1D(sb,sb,150,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+9);  hDttPresel[ind+9]  = new TH1D(sb,sb,90,0.0,180.); 
    sprintf(sb,"hDttPresel_%d",ind+10); hDttPresel[ind+10] = new TH1D(sb,sb,150,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+11); hDttPresel[ind+11] = new TH1D(sb,sb,100,0.0,20.); 
    sprintf(sb,"hDttPresel_%d",ind+12); hDttPresel[ind+12] = new TH1D(sb,sb,200,0.0,800.);
    sprintf(sb,"hDttPresel_%d",ind+13); hDttPresel[ind+13] = new TH1D(sb,sb,200,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+14); hDttPresel[ind+14] = new TH1D(sb,sb,200,0.0,300.);
    sprintf(sb,"hDttPresel_%d",ind+15); hDttPresel[ind+15] = new TH1D(sb,sb,250,0.0,500.);
    sprintf(sb,"hDttPresel_%d",ind+16); hDttPresel[ind+16] = new TH1D(sb,sb,200,0.0,0.4); 
    sprintf(sb,"hDttPresel_%d",ind+17); hDttPresel[ind+17] = new TH1D(sb,sb,200,0.0,0.4); 
    sprintf(sb,"hDttPresel_%d",ind+18); hDttPresel[ind+18] = new TH1D(sb,sb,25,0.0,2.5);
    sprintf(sb,"hDttPresel_%d",ind+19); hDttPresel[ind+19] = new TH1D(sb,sb,25,0.0,2.5);
    sprintf(sb,"hDttPresel_%d",ind+20); hDttPresel[ind+20] = new TH1D(sb,sb,90,0.0,180.);
    sprintf(sb,"hDttPresel_%d",ind+21); hDttPresel[ind+21] = new TH1D(sb,sb,50,0.0, 5.0);
    sprintf(sb,"hDttPresel_%d",ind+22); hDttPresel[ind+22] = new TH1D(sb,sb,50,0.0,10.0);
    sprintf(sb,"hDttPresel_%d",ind+23); hDttPresel[ind+23] = new TH1D(sb,sb,100,0.0,200.0);
    sprintf(sb,"hDttPresel_%d",ind+24); hDttPresel[ind+24] = new TH1D(sb,sb,100,0.0,200.0);
    sprintf(sb,"hDttPresel_%d",ind+25); hDttPresel[ind+25] = new TH1D(sb,sb,100,0.0,400.0);
    sprintf(sb,"hDttPresel_%d",ind+26); hDttPresel[ind+26] = new TH1D(sb,sb,100,0.0,400.0);
    sprintf(sb,"hDttPresel_%d",ind+27); hDttPresel[ind+27] = new TH1D(sb,sb,200,0.0,10.0);
    sprintf(sb,"hDttPresel_%d",ind+28); hDttPresel[ind+28] = new TH1D(sb,sb,80,-2.0,2.0);
    sprintf(sb,"hDttPresel_%d",ind+29); hDttPresel[ind+29] = new TH1D(sb,sb,200,0.0,10.0);
    sprintf(sb,"hDttPresel_%d",ind+30); hDttPresel[ind+30] = new TH1D(sb,sb,80,-2.0,2.0);
    sprintf(sb,"hDttPresel_%d",ind+31); hDttPresel[ind+31] = new TH1D(sb,sb,10,-0.5,9.5); 
    sprintf(sb,"hDttPresel_%d",ind+32); hDttPresel[ind+32] = new TH1D(sb,sb,200,0.0,50.0);
    sprintf(sb,"hDttPresel_%d",ind+33); hDttPresel[ind+33] = new TH1D(sb,sb,200,0.0,0.4); 
    sprintf(sb,"hDttPresel_%d",ind+34); hDttPresel[ind+34] = new TH1D(sb,sb,10,-0.5,9.5); 
    sprintf(sb,"hDttPresel_%d",ind+35); hDttPresel[ind+35] = new TH1D(sb,sb,100,0.0,400.0);
    sprintf(sb,"hDttPresel_%d",ind+36); hDttPresel[ind+36] = new TH1D(sb,sb,100,0.0,400.0);
    sprintf(sb,"hDttPresel_%d",ind+37); hDttPresel[ind+37] = new TH1D(sb,sb,100,0.0,400.0);
    sprintf(sb,"hDttPresel_%d",ind+38); hDttPresel[ind+38] = new TH1D(sb,sb,100,-0.5,99.5); 
  }

  for(int i=0; i<39; i++){
    for(int j=0; j<3; j++){
      AddOutput(hDttPresel[i+j*100]);
    }
  }
}

//--------------------------------------------------------------------------------------------------
void ttEvtSelMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis
}

//--------------------------------------------------------------------------------------------------
void ttEvtSelMod::Terminate()
{
  // Run finishing code on the client computer
}
