 // $Id: ZXEvtSelMod.cc,v 1.2 2008/10/09 18:10:23 ceballos Exp $

#include "MitAna/PhysicsMod/interface/ZXEvtSelMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

using namespace mithep;
ClassImp(mithep::ZXEvtSelMod)

//-----------------------------------------------------------------------------
ZXEvtSelMod::ZXEvtSelMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fMetName(Names::gkCaloMetBrn),
  fCleanJetsName(Names::gkCleanJetsName),
  fMCLeptonsName(Names::gkMCLeptonsName),
  fMet(0),
  fNEventsProcessed(0)
{
  // Constructor.
}

//-----------------------------------------------------------------------------
void ZXEvtSelMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//-----------------------------------------------------------------------------
void ZXEvtSelMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and  
  fNEventsProcessed++;

  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);
    cerr << endl << "ZXEvtSelMod : Process Event " << fNEventsProcessed
         << "  Time: " << ctime(&systime) << endl;
  }

  //Get Generator Level information for matching
  //ObjArray<MCParticle> *GenLeptons   = dynamic_cast<ObjArray<MCParticle>* > (FindObjThisEvt(fMCLeptonsName.Data()));

  //Obtain all the good objects from the event cleaning module
  ObjArray<Electron> *CleanElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(Names::gkCleanElectronsName));
  ObjArray<Muon> *CleanMuons = dynamic_cast<ObjArray<Muon>* >
    (FindObjThisEvt(Names::gkCleanMuonsName));
  ObjArray<Jet> *CleanJets = dynamic_cast<ObjArray<Jet>* >
    (FindObjThisEvt(fCleanJetsName.Data()));

  LoadBranch(fMetName);
  Met *caloMet = fMet->At(0);

  vector<ChargedParticle*> leptonsMu;
  vector<ChargedParticle*> leptonsEl;
  vector<ChargedParticle*> leptonsAll;

  // Make lepton vector from muons and electrons
  for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
    leptonsMu.push_back(CleanMuons->At(j));
    leptonsAll.push_back(CleanMuons->At(j));
  }
  for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {   
    leptonsEl.push_back(CleanElectrons->At(j));
    leptonsAll.push_back(CleanElectrons->At(j));
  }

  // Sort the Muons by Pt   
  for(UInt_t i=0; i<leptonsMu.size(); i++){
    for(UInt_t j=i+1; j<leptonsMu.size(); j++){
      if(leptonsMu[i]->Pt() < leptonsMu[j]->Pt()) {
	//swap i and j
	ChargedParticle* templepton = leptonsMu[i];
	leptonsMu[i] = leptonsMu[j];
	leptonsMu[j] = templepton;
      }
    }
  }
  // Sort the Electrons by Pt   
  for(UInt_t i=0; i<leptonsEl.size(); i++){
    for(UInt_t j=i+1; j<leptonsEl.size(); j++){
      if(leptonsEl[i]->Pt() < leptonsEl[j]->Pt()) {
	//swap i and j
	ChargedParticle* templepton = leptonsEl[i];
	leptonsEl[i] = leptonsEl[j];
	leptonsEl[j] = templepton;
      }
    }
  }
  // Sort the Leptons by Pt   
  for(UInt_t i=0; i<leptonsAll.size(); i++){
    for(UInt_t j=i+1; j<leptonsAll.size(); j++){
      if(leptonsAll[i]->Pt() < leptonsAll[j]->Pt()) {
	//swap i and j
	ChargedParticle* templepton = leptonsAll[i];
	leptonsAll[i] = leptonsAll[j];
	leptonsAll[j] = templepton;
      }
    }
  }
  hDZXSel[0]->Fill((double)leptonsAll.size());

  if(CleanMuons->GetEntries()+CleanElectrons->GetEntries() < 3) return;

  // The selection of the correct pair is ugly, but you know, life is tough

  // WZ analysis
  if(leptonsMu.size()+leptonsEl.size() == 3){
    int nWZType = -1;
    vector<ChargedParticle*> leptonsWZ;
    if     (leptonsMu.size() == 2){
      leptonsWZ.push_back(leptonsMu[0]);
      leptonsWZ.push_back(leptonsMu[1]);
      leptonsWZ.push_back(leptonsEl[0]);
      nWZType = 0;
      if(leptonsWZ[0]->Charge() == leptonsWZ[1]->Charge()) nWZType = 4;
    }
    else if(leptonsEl.size() == 2){
      leptonsWZ.push_back(leptonsEl[0]);
      leptonsWZ.push_back(leptonsEl[1]);
      leptonsWZ.push_back(leptonsMu[0]);
      nWZType = 1;
      if(leptonsWZ[0]->Charge() == leptonsWZ[1]->Charge()) nWZType = 5;
    }
    else if(leptonsMu.size() == 3){
      if(fabs(leptonsMu[0]->Charge()+leptonsMu[1]->Charge()+
              leptonsMu[2]->Charge())==1){
        nWZType = 2;
	if     (leptonsMu[0]->Charge() != leptonsMu[1]->Charge() &&
	        leptonsMu[0]->Charge() != leptonsMu[2]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsMu[0]);
          dileptonA->AddDaughter(leptonsMu[1]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsMu[0]);
          dileptonB->AddDaughter(leptonsMu[2]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsMu[0]);
            leptonsWZ.push_back(leptonsMu[1]);
            leptonsWZ.push_back(leptonsMu[2]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsMu[0]);
            leptonsWZ.push_back(leptonsMu[2]);
            leptonsWZ.push_back(leptonsMu[1]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else if(leptonsMu[1]->Charge() != leptonsMu[0]->Charge() &&
	        leptonsMu[1]->Charge() != leptonsMu[2]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsMu[1]);
          dileptonA->AddDaughter(leptonsMu[0]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsMu[1]);
          dileptonB->AddDaughter(leptonsMu[2]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsMu[0]);
            leptonsWZ.push_back(leptonsMu[1]);
            leptonsWZ.push_back(leptonsMu[2]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsMu[1]);
            leptonsWZ.push_back(leptonsMu[2]);
            leptonsWZ.push_back(leptonsMu[0]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else if(leptonsMu[2]->Charge() != leptonsMu[0]->Charge() &&
	        leptonsMu[2]->Charge() != leptonsMu[1]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsMu[2]);
          dileptonA->AddDaughter(leptonsMu[0]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsMu[2]);
          dileptonB->AddDaughter(leptonsMu[1]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsMu[0]);
            leptonsWZ.push_back(leptonsMu[2]);
            leptonsWZ.push_back(leptonsMu[1]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsMu[1]);
            leptonsWZ.push_back(leptonsMu[2]);
            leptonsWZ.push_back(leptonsMu[0]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else {
	  printf("Impossible in nWZType = 2\n");
	}
      }
      else {
        nWZType = 6;
      }
    }
    else if(leptonsEl.size() == 3){
      if(fabs(leptonsEl[0]->Charge()+leptonsEl[1]->Charge()+
              leptonsEl[2]->Charge())==1){
        nWZType = 3;
	if     (leptonsEl[0]->Charge() != leptonsEl[1]->Charge() &&
	        leptonsEl[0]->Charge() != leptonsEl[2]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsEl[0]);
          dileptonA->AddDaughter(leptonsEl[1]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsEl[0]);
          dileptonB->AddDaughter(leptonsEl[2]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsEl[0]);
            leptonsWZ.push_back(leptonsEl[1]);
            leptonsWZ.push_back(leptonsEl[2]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsEl[0]);
            leptonsWZ.push_back(leptonsEl[2]);
            leptonsWZ.push_back(leptonsEl[1]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else if(leptonsEl[1]->Charge() != leptonsEl[0]->Charge() &&
	        leptonsEl[1]->Charge() != leptonsEl[2]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsEl[1]);
          dileptonA->AddDaughter(leptonsEl[0]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsEl[1]);
          dileptonB->AddDaughter(leptonsEl[2]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsEl[0]);
            leptonsWZ.push_back(leptonsEl[1]);
            leptonsWZ.push_back(leptonsEl[2]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsEl[1]);
            leptonsWZ.push_back(leptonsEl[2]);
            leptonsWZ.push_back(leptonsEl[0]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else if(leptonsEl[2]->Charge() != leptonsEl[0]->Charge() &&
	        leptonsEl[2]->Charge() != leptonsEl[1]->Charge()){
          CompositeParticle *dileptonA = new CompositeParticle();
          dileptonA->AddDaughter(leptonsEl[2]);
          dileptonA->AddDaughter(leptonsEl[0]);
          CompositeParticle *dileptonB = new CompositeParticle();
          dileptonB->AddDaughter(leptonsEl[2]);
          dileptonB->AddDaughter(leptonsEl[1]);
	  if(fabs(dileptonA->Mass()-91.1876) < fabs(dileptonB->Mass()-91.1876)){
            leptonsWZ.push_back(leptonsEl[0]);
            leptonsWZ.push_back(leptonsEl[2]);
            leptonsWZ.push_back(leptonsEl[1]);	    
	  }
	  else {
            leptonsWZ.push_back(leptonsEl[1]);
            leptonsWZ.push_back(leptonsEl[2]);
            leptonsWZ.push_back(leptonsEl[0]);	    
	  }
	  delete dileptonA;
	  delete dileptonB;
	}
	else {
	  printf("Impossible in nWZType = 3\n");
	}
      }
      else {
        nWZType = 7;
      }
    }

    // Start analysis after selecting WZ -> l0 l1 l2
    hDWZSel[90]->Fill((double) nWZType);

    // Charge of the leptons should be opposite
    if (nWZType < 4){
      CompositeParticle *dilepton = new CompositeParticle();
      dilepton->AddDaughter(leptonsWZ[0]);
      dilepton->AddDaughter(leptonsWZ[1]);

      if(dilepton->Charge() != 0) 
         printf("Impossible, nchaZ != 0, nWZType ===> %d\n",nWZType);

      // Sort and count the number of central Jets for vetoing
      vector<Jet*> sortedJets;
      for(UInt_t i=0; i<CleanJets->GetEntries(); i++){
	if(fabs(CleanJets->At(i)->Eta()) < 2.5){
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
      double deltaRJetl = 999.;
      double deltaRJetMet = 999.;
      if(sortedJets.size() > 0){
       for(int i=0; i<3; i++){
          if(MathUtils::DeltaR(leptonsWZ[i]->Phi(), leptonsWZ[i]->Eta(),
	                       sortedJets[0]->Phi(), sortedJets[0]->Eta()) < deltaRJetl)
	    deltaRJetl = MathUtils::DeltaR(leptonsWZ[i]->Phi(), leptonsWZ[i]->Eta(),
	                                   sortedJets[0]->Phi(), sortedJets[0]->Eta()); 
	}
	deltaRJetMet = MathUtils::DeltaPhi(caloMet->Phi(), sortedJets[0]->Phi());
      }
      double deltaPhiln = MathUtils::DeltaPhi(leptonsWZ[2]->Phi(), caloMet->Phi());
      double mTW = TMath::Sqrt(2.0*leptonsWZ[2]->Pt()*caloMet->Pt()*
                              (1.0 - cos(deltaPhiln)));
      double deltaRWl[2] = {MathUtils::DeltaR(leptonsWZ[0]->Phi(), leptonsWZ[0]->Eta(),
	                                      leptonsWZ[2]->Phi(), leptonsWZ[2]->Eta()),
			    MathUtils::DeltaR(leptonsWZ[1]->Phi(), leptonsWZ[1]->Eta(),
	                                      leptonsWZ[2]->Phi(), leptonsWZ[2]->Eta())};		    ;
      hDWZSel[ 0+100*nWZType]->Fill(TMath::Min(caloMet->Pt(),199.999));
      hDWZSel[ 1+100*nWZType]->Fill(TMath::Min(leptonsWZ[0]->Pt(),199.999));
      hDWZSel[ 2+100*nWZType]->Fill(TMath::Min(leptonsWZ[1]->Pt(),199.999));
      hDWZSel[ 3+100*nWZType]->Fill(TMath::Min(leptonsWZ[2]->Pt(),199.999));
      hDWZSel[ 4+100*nWZType]->Fill(TMath::Min(dilepton->Mass(),199.999));
      hDWZSel[ 5+100*nWZType]->Fill((double)sortedJets.size());
      hDWZSel[ 6+100*nWZType]->Fill(caloMet->MetSig());
      hDWZSel[ 7+100*nWZType]->Fill(caloMet->SumEt());
      hDWZSel[ 8+100*nWZType]->Fill(TMath::Min(mTW,199.999));
      hDWZSel[ 9+100*nWZType]->Fill(deltaPhiln * 180./TMath::Pi());
      hDWZSel[10+100*nWZType]->Fill(TMath::Min(deltaRWl[0],deltaRWl[1]));
      hDWZSel[11+100*nWZType]->Fill(TMath::Max(deltaRWl[0],deltaRWl[1]));
      hDWZSel[12+100*nWZType]->Fill(TMath::Min(caloMet->Pt()*deltaPhiln/4.,199.999));
      if(sortedJets.size() > 0){
	hDWZSel[13+100*nWZType]->Fill(TMath::Min(sortedJets[0]->Pt(),199.99));
	hDWZSel[14+100*nWZType]->Fill(deltaRJetl);
	hDWZSel[15+100*nWZType]->Fill(deltaRJetMet * 180./TMath::Pi());
      }
      delete dilepton;
      for(UInt_t i=0; i<sortedJets.size(); i++) delete sortedJets[i];
    } // Z Charge == 0
  } // WZ Selection

  // ZZ analysis
  if(leptonsMu.size()+leptonsEl.size() >= 4){
    int nZZType = -3;
    vector<ChargedParticle*> leptonsZZ;
    if     (leptonsMu.size() >= 2 && leptonsEl.size() >= 2){
      nZZType = 0;
      leptonsZZ.push_back(leptonsMu[0]);
      leptonsZZ.push_back(leptonsMu[1]);
      leptonsZZ.push_back(leptonsEl[0]);
      leptonsZZ.push_back(leptonsEl[1]);
    }
    else if(leptonsMu.size() >= 4){
      CompositeParticle *dileptonA = new CompositeParticle();
      CompositeParticle *dileptonB = new CompositeParticle();
      if     (leptonsMu[0]->Charge() != leptonsMu[1]->Charge() &&
              leptonsMu[0]->Charge() != leptonsMu[2]->Charge()){
	nZZType = 1;
        dileptonA->AddDaughter(leptonsMu[0]);
        dileptonA->AddDaughter(leptonsMu[1]);
        dileptonB->AddDaughter(leptonsMu[0]);
        dileptonB->AddDaughter(leptonsMu[2]);
	delete dileptonA;
	delete dileptonB;
      }
      else if(leptonsMu[0]->Charge() != leptonsMu[1]->Charge() &&
              leptonsMu[0]->Charge() != leptonsMu[3]->Charge()){
	nZZType = 2;
        dileptonA->AddDaughter(leptonsMu[0]);
        dileptonA->AddDaughter(leptonsMu[1]);
        dileptonB->AddDaughter(leptonsMu[0]);
        dileptonB->AddDaughter(leptonsMu[3]);
      } 
      else if(leptonsMu[0]->Charge() != leptonsMu[2]->Charge() &&
              leptonsMu[0]->Charge() != leptonsMu[3]->Charge()){
	nZZType = 3;
        dileptonA->AddDaughter(leptonsMu[0]);
        dileptonA->AddDaughter(leptonsMu[2]);
        dileptonB->AddDaughter(leptonsMu[0]);
        dileptonB->AddDaughter(leptonsMu[3]);
      }
      else {
        nZZType = -1;
      }
      if     (nZZType == 1 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[2]);
        leptonsZZ.push_back(leptonsMu[3]);
      }
      else if(nZZType == 1) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[2]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[3]);
        nZZType = 4;
      }
      else if(nZZType == 2 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[2]);
        leptonsZZ.push_back(leptonsMu[3]);
      }
      else if(nZZType == 2) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[3]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[2]);
        nZZType = 5;
      }
      else if(nZZType == 3 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[2]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[3]);
      }
      else if(nZZType == 3) {
        leptonsZZ.push_back(leptonsMu[0]);
        leptonsZZ.push_back(leptonsMu[3]);
        leptonsZZ.push_back(leptonsMu[1]);
        leptonsZZ.push_back(leptonsMu[2]);
        nZZType = 6;
      }
    }
    else if(leptonsEl.size() >= 4){
      CompositeParticle *dileptonA = new CompositeParticle();
      CompositeParticle *dileptonB = new CompositeParticle();
      if     (leptonsEl[0]->Charge() != leptonsEl[1]->Charge() &&
              leptonsEl[0]->Charge() != leptonsEl[2]->Charge()){
	nZZType = 7;
        dileptonA->AddDaughter(leptonsEl[0]);
        dileptonA->AddDaughter(leptonsEl[1]);
        dileptonB->AddDaughter(leptonsEl[0]);
        dileptonB->AddDaughter(leptonsEl[2]);
      }
      else if(leptonsEl[0]->Charge() != leptonsEl[1]->Charge() &&
              leptonsEl[0]->Charge() != leptonsEl[3]->Charge()){
	nZZType = 8;
        dileptonA->AddDaughter(leptonsEl[0]);
        dileptonA->AddDaughter(leptonsEl[1]);
        dileptonB->AddDaughter(leptonsEl[0]);
        dileptonB->AddDaughter(leptonsEl[3]);
      } 
      else if(leptonsEl[0]->Charge() != leptonsEl[2]->Charge() &&
              leptonsEl[0]->Charge() != leptonsEl[3]->Charge()){
	nZZType = 9;
        dileptonA->AddDaughter(leptonsEl[0]);
        dileptonA->AddDaughter(leptonsEl[2]);
        dileptonB->AddDaughter(leptonsEl[0]);
        dileptonB->AddDaughter(leptonsEl[3]);
      }
      else {
        nZZType = -2;
      }
      if     (nZZType == 7 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[2]);
        leptonsZZ.push_back(leptonsEl[3]);
      }
      else if(nZZType == 7) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[2]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[3]);
        nZZType = 10;
      }
      else if(nZZType == 8 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[2]);
        leptonsZZ.push_back(leptonsEl[3]);
      }
      else if(nZZType == 8) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[3]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[2]);
        nZZType = 11;
      }
      else if(nZZType == 9 &&
	      fabs(dileptonA->Mass()-91.1876) <
	      fabs(dileptonB->Mass()-91.1876)  ) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[2]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[3]);
      }
      else if(nZZType == 9) {
        leptonsZZ.push_back(leptonsEl[0]);
        leptonsZZ.push_back(leptonsEl[3]);
        leptonsZZ.push_back(leptonsEl[1]);
        leptonsZZ.push_back(leptonsEl[2]);
        nZZType = 12;
      }
      delete dileptonA;
      delete dileptonB;
    }
    hDZZSel[90]->Fill((double)nZZType);
    if(nZZType >= 0){
      CompositeParticle *dileptonZ1 = new CompositeParticle();
      dileptonZ1->AddDaughter(leptonsZZ[0]);
      dileptonZ1->AddDaughter(leptonsZZ[1]);
      CompositeParticle *dileptonZ2 = new CompositeParticle();
      dileptonZ2->AddDaughter(leptonsZZ[2]);
      dileptonZ2->AddDaughter(leptonsZZ[3]);
      hDZZSel[91]->Fill((double)(dileptonZ1->Charge()+dileptonZ2->Charge()));

      CompositeParticle *particleH = new CompositeParticle();
      particleH->AddDaughter(leptonsZZ[0]);
      particleH->AddDaughter(leptonsZZ[1]);
      particleH->AddDaughter(leptonsZZ[2]);
      particleH->AddDaughter(leptonsZZ[3]);

      int simpleZZType = 0;
      if     (nZZType >= 1 && nZZType <=  6) simpleZZType = 1;
      else if(nZZType >= 7 && nZZType <= 12) simpleZZType = 2;

      hDZZSel[ 0+100*simpleZZType]->Fill(TMath::Min(leptonsAll[0]->Pt(),199.999));
      hDZZSel[ 1+100*simpleZZType]->Fill(TMath::Min(leptonsAll[1]->Pt(),199.999));
      hDZZSel[ 2+100*simpleZZType]->Fill(TMath::Min(leptonsAll[2]->Pt(),199.999));
      hDZZSel[ 3+100*simpleZZType]->Fill(TMath::Min(leptonsAll[3]->Pt(),199.999));
      if(fabs(dileptonZ1->Mass()-91.1876) < fabs(dileptonZ2->Mass()-91.1876)){
        hDZZSel[ 4+100*simpleZZType]->Fill(TMath::Min(dileptonZ1->Mass(),199.99));
        hDZZSel[ 5+100*simpleZZType]->Fill(TMath::Min(dileptonZ2->Mass(),199.99));
      }
      else {
        hDZZSel[ 4+100*simpleZZType]->Fill(TMath::Min(dileptonZ2->Mass(),199.99));
        hDZZSel[ 5+100*simpleZZType]->Fill(TMath::Min(dileptonZ1->Mass(),199.99));
      }
      hDZZSel[ 6+100*simpleZZType]->Fill(TMath::Min(particleH->Mass(),599.99));
      delete dileptonZ1;
      delete dileptonZ2;
      delete particleH;
    } // nZZType >= 0
  } // ZZ analysis

  leptonsMu.clear();
  leptonsEl.clear();
  leptonsAll.clear();
}
//--------------------------------------------------------------------------------------------------
void ZXEvtSelMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMetName,    fMet);

  char sb[200];
  sprintf(sb,"hDZXSel_0"); hDZXSel[0] = new TH1D(sb,sb,10,-0.5,9.5); 
  AddOutput(hDZXSel[0]);

  // WZ histograms
  for(int j=0; j<4; j++){
    int ind = 100 * j;
    sprintf(sb,"hDWZSel_%d",ind+0);  hDWZSel[ind+0]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+1);  hDWZSel[ind+1]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+2);  hDWZSel[ind+2]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+3);  hDWZSel[ind+3]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+4);  hDWZSel[ind+4]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+5);  hDWZSel[ind+5]  = new TH1D(sb,sb,10,-0.5,9.5); 
    sprintf(sb,"hDWZSel_%d",ind+6);  hDWZSel[ind+6]  = new TH1D(sb,sb,100,0.0,20.); 
    sprintf(sb,"hDWZSel_%d",ind+7);  hDWZSel[ind+7]  = new TH1D(sb,sb,200,0.0,800.);
    sprintf(sb,"hDWZSel_%d",ind+8);  hDWZSel[ind+8]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDWZSel_%d",ind+9);  hDWZSel[ind+9]  = new TH1D(sb,sb,90,0.0,180.);
    sprintf(sb,"hDWZSel_%d",ind+10); hDWZSel[ind+10] = new TH1D(sb,sb,100,0.0,5.);
    sprintf(sb,"hDWZSel_%d",ind+11); hDWZSel[ind+11] = new TH1D(sb,sb,100,0.0,5.);
    sprintf(sb,"hDWZSel_%d",ind+12); hDWZSel[ind+12] = new TH1D(sb,sb,100,0.0,200.); 
    sprintf(sb,"hDWZSel_%d",ind+13); hDWZSel[ind+13] = new TH1D(sb,sb,100,0.0,200);
    sprintf(sb,"hDWZSel_%d",ind+14); hDWZSel[ind+14] = new TH1D(sb,sb,100,0.0,5.); 
    sprintf(sb,"hDWZSel_%d",ind+15); hDWZSel[ind+15] = new TH1D(sb,sb,90,0.0,180.); 
  }

  for(int i=0; i<16; i++){
    for(int j=0; j<4; j++){
      AddOutput(hDWZSel[i+j*100]);
    }
  }

  sprintf(sb,"hDWZSel_90"); hDWZSel[90] = new TH1D(sb,sb,8,-0.5,7.5); 
  AddOutput(hDWZSel[90]);

  // ZZ histograms
  for(int j=0; j<3; j++){
    int ind = 100 * j;
    sprintf(sb,"hDZZSel_%d",ind+0);  hDZZSel[ind+0]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+1);  hDZZSel[ind+1]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+2);  hDZZSel[ind+2]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+3);  hDZZSel[ind+3]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+4);  hDZZSel[ind+4]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+5);  hDZZSel[ind+5]  = new TH1D(sb,sb,100,0.0,200.);
    sprintf(sb,"hDZZSel_%d",ind+6);  hDZZSel[ind+6]  = new TH1D(sb,sb,300,0.0,600.);
  }

  for(int i=0; i<7; i++){
    for(int j=0; j<3; j++){
      AddOutput(hDZZSel[i+j*100]);
    }
  }

  sprintf(sb,"hDZZSel_90"); hDZZSel[90] = new TH1D(sb,sb,16,-3.5,12.5); 
  sprintf(sb,"hDZZSel_91"); hDZZSel[91] = new TH1D(sb,sb,9,-4.5,4.5); 
  AddOutput(hDZZSel[90]);
  AddOutput(hDZZSel[91]);
}

//--------------------------------------------------------------------------------------------------
void ZXEvtSelMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis
}

//--------------------------------------------------------------------------------------------------
void ZXEvtSelMod::Terminate()
{
  // Run finishing code on the client computer
}
