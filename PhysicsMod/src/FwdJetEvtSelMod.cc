 // $Id: FwdJetEvtSelMod.cc,v 1.1 2008/10/06 16:59:48 ceballos Exp $

#include "MitAna/PhysicsMod/interface/FwdJetEvtSelMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
#include "MitAna/Utils/interface/DiTauSystem.h"

using namespace mithep;
ClassImp(mithep::FwdJetEvtSelMod)

//--------------------------------------------------------------------------------------------------
FwdJetEvtSelMod::FwdJetEvtSelMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fFillHist(false),
  fMetName(Names::gkCaloMetBrn),
  fCleanJetsName(Names::gkCleanJetsName),
  fCleanFwdJetsName(Names::gkCleanFwdJetsName),
  fCleanNoFwdJetsName(Names::gkCleanNoFwdJetsName),
  fMCqqHsName(Names::gkMCqqHsName),
  fMet(0),
  fUseANN(false),
  fUseHighestPtJets(true),
  fJetPtMax(40),
  fJetPtMin(40),
  fDeltaEtaMin(4),
  fDiJetMassMin(900),
  fANNOutputMin(0.5),
  fNEventsProcessed(0)
{
  // Constructor.
}

//-----------------------------------------------------------------------------
void FwdJetEvtSelMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//-----------------------------------------------------------------------------
void FwdJetEvtSelMod::Process()
{
  // Process entries of the tree. For this module, we just load the branches and  
  fNEventsProcessed++;

  if (fNEventsProcessed % 1000 == 0 || fPrintDebug) {
    time_t systime;
    systime = time(NULL);
    cerr << endl << "FwdJetEvtSelMod : Process Event " << fNEventsProcessed << "  Time: " << ctime(&systime) << endl;
  }

  //Get Generator Level information for matching
  ObjArray<MCParticle> *GenqqHs      = dynamic_cast<ObjArray<MCParticle>* > 
       (FindObjThisEvt(fMCqqHsName.Data()));

  //Obtain all the good objects from the event cleaning module
  ObjArray<Electron> *CleanElectrons = dynamic_cast<ObjArray<Electron>* >
    (FindObjThisEvt(Names::gkCleanElectronsName));
  ObjArray<Muon> *CleanMuons = dynamic_cast<ObjArray<Muon>* >
    (FindObjThisEvt(Names::gkCleanMuonsName));
  ObjArray<Jet> *CleanJets = dynamic_cast<ObjArray<Jet>* >
    (FindObjThisEvt(fCleanJetsName.Data()));

  ObjArray<Jet> *CleanFwdJets   = new ObjArray<Jet>; CleanFwdJets->SetOwner(true);
  ObjArray<Jet> *CleanNoFwdJets = new ObjArray<Jet>; CleanNoFwdJets->SetOwner(true);

  // Sort and count the number of central Jets for vetoing
  vector<Jet*> sortedJets;
  for(UInt_t i=0; i<CleanJets->GetEntries(); i++){
    Jet* jet_f = new Jet(CleanJets->At(i)->Px()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
    			 CleanJets->At(i)->Py()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
    			 CleanJets->At(i)->Pz()*CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale(),
        		 CleanJets->At(i)->E() *CleanJets->At(i)->L2RelativeCorrectionScale()*CleanJets->At(i)->L3AbsoluteCorrectionScale());
    sortedJets.push_back(jet_f);
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
  if(sortedJets.size() >= 2 && sortedJets[0]->Pt() > 20 &&
                               sortedJets[1]->Pt() > 20){
    // Use either the 2 or the 4 highest Pt jets
    UInt_t NMaxLoop = 4;
    if(fUseHighestPtJets == true) NMaxLoop = 2;
    int jmax = -1;
    int jmin = -1;
    double nnOutputPair = 0.0;
    for(UInt_t i=0; i<TMath::Min(sortedJets.size()-1,NMaxLoop-1); i++){
      for(UInt_t j=i+1; j<TMath::Min(sortedJets.size(),NMaxLoop); j++){
        // Stop if a good jet pair is already found
        if(jmax != -1) continue;
	CompositeParticle *dijet = new CompositeParticle();
	dijet->AddDaughter(sortedJets[i]);
	dijet->AddDaughter(sortedJets[j]);
	double deltaPhi = MathUtils::DeltaPhi(sortedJets[i]->Phi(), 
	                                      sortedJets[j]->Phi());
	double deltaEta = fabs(sortedJets[i]->Eta()-sortedJets[j]->Eta());
	bool isFwdJet[2] = {false, false};
	isFwdJet[0] = sortedJets[i]->Pt() > fJetPtMax &&
	              sortedJets[j]->Pt() > fJetPtMin &&
                      sortedJets[i]->Eta()*sortedJets[j]->Eta() < 0 &&
		      deltaEta > fDeltaEtaMin && dijet->Mass() > fDiJetMassMin;
	double varqqHNN[6] = {sortedJets[i]->Pt(),sortedJets[j]->Pt(),
                              deltaEta,deltaPhi,dijet->Mass(),
	               sortedJets[i]->Eta()*sortedJets[j]->Eta()};
	if(deltaEta > 2.0 && dijet->Mass() > 300) 
	     nnOutputPair = Testmlp_qqH(varqqHNN);
	isFwdJet[1] = nnOutputPair > fANNOutputMin;
	if     (fUseANN == false and isFwdJet[0] == true){
	  CleanFwdJets->Add(sortedJets[i]);
	  CleanFwdJets->Add(sortedJets[j]);
	  jmax = i; jmin = j;
	}
	else if(fUseANN == true and isFwdJet[1] == true){
	  CleanFwdJets->Add(sortedJets[i]);
	  CleanFwdJets->Add(sortedJets[j]);
	  jmax = i; jmin = j;
	}
	delete dijet;
      } // j...
    } // i...
    // Looking for central jets if a good forward tagging pair is found
    if(jmax >= 0){
      for(UInt_t i=0; i<sortedJets.size(); i++){
	if((sortedJets[i]->Eta() > sortedJets[jmax]->Eta() &&
	    sortedJets[i]->Eta() < sortedJets[jmin]->Eta()) ||
           (sortedJets[i]->Eta() > sortedJets[jmin]->Eta() &&
	    sortedJets[i]->Eta() < sortedJets[jmax]->Eta())){
          CleanNoFwdJets->Add(sortedJets[i]);
	}
      }
    }
    if(fFillHist == true){
      if(fUseHighestPtJets == true){
	CompositeParticle *dijet = new CompositeParticle();
	dijet->AddDaughter(sortedJets[0]);
	dijet->AddDaughter(sortedJets[1]);
	double deltaPhi = MathUtils::DeltaPhi(sortedJets[0]->Phi(), 
	                                      sortedJets[1]->Phi());
	double deltaEta = fabs(sortedJets[0]->Eta()-sortedJets[1]->Eta());
	bool isFwdJet[2] = {false, false};
	isFwdJet[0] = sortedJets[0]->Pt() > fJetPtMax &&
	              sortedJets[1]->Pt() > fJetPtMin &&
        	      sortedJets[0]->Eta()*sortedJets[1]->Eta() < 0 &&
        	      deltaEta > fDeltaEtaMin && dijet->Mass() > fDiJetMassMin;
	double varqqHNN[6] = {sortedJets[0]->Pt(),sortedJets[1]->Pt(),
        		      deltaEta,deltaPhi,dijet->Mass(),
        	       sortedJets[0]->Eta()*sortedJets[1]->Eta()};
	double nnOutput = 0.0;
	if(deltaEta > 2.0 && dijet->Mass() > 300)
	     nnOutput = Testmlp_qqH(varqqHNN);
	isFwdJet[1] = nnOutput > fANNOutputMin;
	int VBYtype = 2;
	if(GenqqHs->GetEntries() == 2){
          double deltaR00 = MathUtils::DeltaR(sortedJets[0]->Phi(),sortedJets[0]->Eta(),
                                              GenqqHs->At(0)->Phi(),GenqqHs->At(0)->Eta());
          double deltaR01 = MathUtils::DeltaR(sortedJets[0]->Phi(),sortedJets[0]->Eta(),
                                              GenqqHs->At(1)->Phi(),GenqqHs->At(1)->Eta());
          double deltaR10 = MathUtils::DeltaR(sortedJets[1]->Phi(),sortedJets[1]->Eta(),
                                              GenqqHs->At(0)->Phi(),GenqqHs->At(0)->Eta());
          double deltaR11 = MathUtils::DeltaR(sortedJets[1]->Phi(),sortedJets[1]->Eta(),
                                              GenqqHs->At(1)->Phi(),GenqqHs->At(1)->Eta());
          if((deltaR00 < 0.5 && deltaR11 < 0.5) ||
             (deltaR01 < 0.5 && deltaR10 < 0.5)) VBYtype = 0;
          else                                   VBYtype = 1;
	}
	hDFwdJetSel[0+VBYtype*100]->Fill(deltaPhi*180./TMath::Pi());	     
	hDFwdJetSel[1+VBYtype*100]->Fill(TMath::Min(deltaEta,9.999));		     
	hDFwdJetSel[2+VBYtype*100]->Fill(TMath::Min(sortedJets[0]->Pt(),399.999));     
	hDFwdJetSel[3+VBYtype*100]->Fill(TMath::Min(sortedJets[1]->Pt(),399.999));     
	hDFwdJetSel[4+VBYtype*100]->Fill(TMath::Min(dijet->Mass(),3999.999));
	hDFwdJetSel[5+VBYtype*100]->Fill(sortedJets[0]->Eta()* sortedJets[1]->Eta()/
                                	 fabs(sortedJets[0]->Eta()* sortedJets[1]->Eta()));
	hDFwdJetSel[6+VBYtype*100]->Fill(nnOutput);
	hDFwdJetSel[7+VBYtype*100]->Fill((double)isFwdJet[0]);
	hDFwdJetSel[8+VBYtype*100]->Fill((double)isFwdJet[1]);
	delete dijet;
      }

      // Event has a good forward tagging pair
      if(jmax >= 0){
	int VBYtype = 2;
	if(GenqqHs->GetEntries() == 2){
          double deltaR00 = MathUtils::DeltaR(sortedJets[jmax]->Phi(),sortedJets[jmax]->Eta(),
                                              GenqqHs->At(0)->Phi(),GenqqHs->At(0)->Eta());
          double deltaR01 = MathUtils::DeltaR(sortedJets[jmax]->Phi(),sortedJets[jmax]->Eta(),
                                              GenqqHs->At(1)->Phi(),GenqqHs->At(1)->Eta());
          double deltaR10 = MathUtils::DeltaR(sortedJets[jmin]->Phi(),sortedJets[jmin]->Eta(),
                                              GenqqHs->At(0)->Phi(),GenqqHs->At(0)->Eta());
          double deltaR11 = MathUtils::DeltaR(sortedJets[jmin]->Phi(),sortedJets[jmin]->Eta(),
                                              GenqqHs->At(1)->Phi(),GenqqHs->At(1)->Eta());
          if((deltaR00 < 0.5 && deltaR11 < 0.5) ||
             (deltaR01 < 0.5 && deltaR10 < 0.5)) VBYtype = 0;
          else                                   VBYtype = 1;
	}
	hDFwdJetSel[9+VBYtype*100]->Fill((double)CleanNoFwdJets->GetEntries());
	// Lepton selection
	vector<ChargedParticle*> leptons;
	vector<string> leptonType;

	// Make lepton vector from muons and electrons
	for (UInt_t j=0; j<CleanMuons->GetEntries(); j++) {
	  leptons.push_back(CleanMuons->At(j));
	  leptonType.push_back("mu");
	}
	for (UInt_t j=0; j<CleanElectrons->GetEntries(); j++) {   
	  leptons.push_back(CleanElectrons->At(j));
	  leptonType.push_back("e");
	}
	hDFwdJetSel[10+VBYtype*100]->Fill((double)leptons.size());

	if(leptons.size() >= 2){
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
	  CompositeParticle *dilepton = new CompositeParticle();
	  dilepton->AddDaughter(leptons[0]);
	  dilepton->AddDaughter(leptons[1]);

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

	  // Charge of the leptons should be opposite
	  if (dilepton->Charge() == 0 && dilepton->Mass() > 12 &&
              leptons[0]->Pt() > 20 && leptons[0]->Pt() > 10){
   	    // MET is needed from here
	    LoadBranch(fMetName);
	    Met *caloMet = fMet->At(0);
            // Delta phi between the 2 leptons in degrees
            double deltaPhiLeptons = MathUtils::DeltaPhi(leptons[0]->Phi(), 
                                          		 leptons[1]->Phi())* 180. / TMath::Pi();
            hDFwdJetSel[11+VBYtype*100]->Fill(deltaPhiLeptons);    
            hDFwdJetSel[12+VBYtype*100]->Fill(caloMet->Pt());	    
            hDFwdJetSel[13+VBYtype*100]->Fill(dilepton->Mass());
            hDFwdJetSel[14+VBYtype*100]->Fill(nnOutputPair);     
            hDFwdJetSel[15+VBYtype*100]->Fill((double)CleanNoFwdJets->GetEntries());

            DiTauSystem ditau(leptons[0], leptons[1], caloMet);
            hDFwdJetSel[16+VBYtype*100]->Fill(TMath::Max(TMath::Min(ditau.XTau1(),1.99),-0.99));
            hDFwdJetSel[16+VBYtype*100]->Fill(TMath::Max(TMath::Min(ditau.XTau2(),1.99),-0.99));
	    hDFwdJetSel[17+VBYtype*100]->Fill(TMath::Min(ditau.VisMass(),399.99));
            if(ditau.XTau1() > 0 && ditau.XTau2() > 0){
	      hDFwdJetSel[18+VBYtype*100]->Fill(TMath::Min(ditau.VisMass(),399.99));
	      hDFwdJetSel[19+VBYtype*100]->Fill(TMath::Min(ditau.RecoMass(),399.99));
	    }
	    if(dilepton->Mass() < 80 && caloMet->Pt() > 30){
	      hDFwdJetSel[20+VBYtype*100]->Fill(deltaPhiLeptons);	
              hDFwdJetSel[21+VBYtype*100]->Fill((double)CleanNoFwdJets->GetEntries());
	    }
	    if(fabs(dilepton->Mass()-91.18) < 20){
	      hDFwdJetSel[22+VBYtype*100]->Fill(caloMet->Pt());	
              hDFwdJetSel[23+VBYtype*100]->Fill((double)CleanNoFwdJets->GetEntries());
	    }
	  }
	  delete dilepton;
	} // At least 2 identifed leptons
      } // jmax >= 0
    } // FillHist
  } // Minimum preselection
  else {
    if(fFillHist == true){
      if(fUseHighestPtJets == true){
        if(GenqqHs->GetEntries() == 2){
          hDFwdJetSel[6+1*100]->Fill(0.0);     
        }
        else {
          hDFwdJetSel[6+2*100]->Fill(0.0);     
        }
      }
    }
  } // Include also this to know how many events are rejected at preselection level

  //Save Objects for Other Modules to use
  AddObjThisEvt(CleanFwdJets,  fCleanFwdJetsName.Data());
  AddObjThisEvt(CleanNoFwdJets,fCleanNoFwdJetsName.Data());

}

//--------------------------------------------------------------------------------------------------
void FwdJetEvtSelMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fMetName,    fMet);

  if(fFillHist == true){
    char sb[200];
    for(int j=0; j<3; j++){
      int ind = 100 * j;
      sprintf(sb,"hDFwdJetSel_%d",ind+0);  hDFwdJetSel[ind+0]  = new TH1D(sb,sb,90,0.0,180.);
      sprintf(sb,"hDFwdJetSel_%d",ind+1);  hDFwdJetSel[ind+1]  = new TH1D(sb,sb,100,0.0,10.);
      sprintf(sb,"hDFwdJetSel_%d",ind+2);  hDFwdJetSel[ind+2]  = new TH1D(sb,sb,200,0.0,400.);
      sprintf(sb,"hDFwdJetSel_%d",ind+3);  hDFwdJetSel[ind+3]  = new TH1D(sb,sb,200,0.0,400.);
      sprintf(sb,"hDFwdJetSel_%d",ind+4);  hDFwdJetSel[ind+4]  = new TH1D(sb,sb,200,0.0,4000.);
      sprintf(sb,"hDFwdJetSel_%d",ind+5);  hDFwdJetSel[ind+5]  = new TH1D(sb,sb,2,-1.5,1.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+6);  hDFwdJetSel[ind+6]  = new TH1D(sb,sb,100,0,1);
      sprintf(sb,"hDFwdJetSel_%d",ind+7);  hDFwdJetSel[ind+7]  = new TH1D(sb,sb,2,-0.5,1.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+8);  hDFwdJetSel[ind+8]  = new TH1D(sb,sb,2,-0.5,1.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+9);  hDFwdJetSel[ind+9]  = new TH1D(sb,sb,10,-0.5,9.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+10); hDFwdJetSel[ind+10] = new TH1D(sb,sb,10,-0.5,9.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+11); hDFwdJetSel[ind+11] = new TH1D(sb,sb,90,0.0,180.);
      sprintf(sb,"hDFwdJetSel_%d",ind+12); hDFwdJetSel[ind+12] = new TH1D(sb,sb,100,0.0,200.);
      sprintf(sb,"hDFwdJetSel_%d",ind+13); hDFwdJetSel[ind+13] = new TH1D(sb,sb,200,0.0,400.);
      sprintf(sb,"hDFwdJetSel_%d",ind+14); hDFwdJetSel[ind+14] = new TH1D(sb,sb,100,0,1);
      sprintf(sb,"hDFwdJetSel_%d",ind+15); hDFwdJetSel[ind+15] = new TH1D(sb,sb,10,-0.5,9.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+16); hDFwdJetSel[ind+16] = new TH1D(sb,sb,150,-1.0,2.0);
      sprintf(sb,"hDFwdJetSel_%d",ind+17); hDFwdJetSel[ind+17] = new TH1D(sb,sb,200,0.0,400.0);
      sprintf(sb,"hDFwdJetSel_%d",ind+18); hDFwdJetSel[ind+18] = new TH1D(sb,sb,200,0.0,400.0);
      sprintf(sb,"hDFwdJetSel_%d",ind+19); hDFwdJetSel[ind+19] = new TH1D(sb,sb,200,0.0,400.0);
      sprintf(sb,"hDFwdJetSel_%d",ind+20); hDFwdJetSel[ind+20] = new TH1D(sb,sb,90,0.0,180.);
      sprintf(sb,"hDFwdJetSel_%d",ind+21); hDFwdJetSel[ind+21] = new TH1D(sb,sb,10,-0.5,9.5);
      sprintf(sb,"hDFwdJetSel_%d",ind+22); hDFwdJetSel[ind+22] = new TH1D(sb,sb,100,0.0,200.);
      sprintf(sb,"hDFwdJetSel_%d",ind+23); hDFwdJetSel[ind+23] = new TH1D(sb,sb,10,-0.5,9.5);
   }

    for(int i=0; i<24; i++){
      for(int j=0; j<3; j++){
	AddOutput(hDFwdJetSel[i+j*100]);
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------
void FwdJetEvtSelMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis
}

//--------------------------------------------------------------------------------------------------
void FwdJetEvtSelMod::Terminate()
{
  // Run finishing code on the client computer
}

//------------------------------------------------------------------------------
double FwdJetEvtSelMod::Testmlp_qqH(double var[6]){
// qqH ANN

double OUT1  ,OUT2 , OUT3 , OUT4 , OUT5;
double OUT6  ,OUT7 , OUT8 , OUT9 , OUT10;
double OUT11 ,OUT12, OUT13, OUT14, OUT15;
double RIN1  ,RIN2 , RIN3 , RIN4 , RIN5;
double RIN6  ,RIN7 , RIN8 , RIN9 , RIN10;
double RIN11 ,RIN12, RIN13, RIN14, RIN15;

OUT1 = var[0]; // PTJ1
OUT2 = var[1]; // PTJ2
OUT3 = var[2]; // DELTAETA
OUT4 = var[3]; // DELTAPHI
OUT5 = var[4]; // MJJ
OUT6 = var[5]; // ETAMAX*ETAMIN


// layer 2
RIN1 = 3.401877e-01
 +(-1.056171e-01) * OUT1
 +(2.830992e-01) * OUT2
 +(2.984400e-01) * OUT3
 +(4.116473e-01) * OUT4
 +(-3.024486e-01) * OUT5
 +(-1.647772e-01) * OUT6;
RIN2 = 2.686068e-01
 +(-2.222253e-01) * OUT1
 +(9.109838e-02) * OUT2
 +(4.124089e-04) * OUT3
 +(1.299482e-01) * OUT4
 +(-1.341908e-01) * OUT5
 +(-6.297962e-02) * OUT6;
RIN3 = 4.522297e-01
 +(4.161951e-01) * OUT1
 +(1.357117e-01) * OUT2
 +(2.172969e-01) * OUT3
 +(-3.583975e-01) * OUT4
 +(1.069689e-01) * OUT5
 +(-4.836994e-01) * OUT6;
RIN4 = -2.571132e-01
 +(-3.627684e-01) * OUT1
 +(3.041767e-01) * OUT2
 +(-3.433209e-01) * OUT3
 +(-9.905560e-02) * OUT4
 +(-3.702095e-01) * OUT5
 +(-3.911912e-01) * OUT6;
RIN5 = 4.989245e-01
 +(-2.817431e-01) * OUT1
 +(1.292617e-02) * OUT2
 +(3.391084e-01) * OUT3
 +(1.126397e-01) * OUT4
 +(-2.039686e-01) * OUT5
 +(1.375673e-01) * OUT6;
RIN6 = 2.428719e-02
 +(-6.415707e-03) * OUT1
 +(4.727750e-01) * OUT2
 +(-2.074832e-01) * OUT3
 +(2.713577e-01) * OUT4
 +(2.674546e-02) * OUT5
 +(2.699139e-01) * OUT6;
RIN7 = -9.977138e-02
 +(3.915294e-01) * OUT1
 +(-2.166853e-01) * OUT2
 +(-1.475417e-01) * OUT3
 +(3.077245e-01) * OUT4
 +(4.190265e-01) * OUT5
 +(-4.302447e-01) * OUT6;
RIN8 = 4.493271e-01
 +(2.599535e-02) * OUT1
 +(-4.139442e-01) * OUT2
 +(-3.077862e-01) * OUT3
 +(1.632269e-01) * OUT4
 +(3.902326e-01) * OUT5
 +(-1.511071e-01) * OUT6;
RIN9 = -4.361163e-01
 +(-4.419279e-01) * OUT1
 +(-4.473301e-02) * OUT2
 +(-4.376293e-01) * OUT3
 +(-2.604143e-01) * OUT4
 +(5.240741e-01) * OUT5
 +(4.011090e-01) * OUT6;
RIN10 = 3.173292e-01
 +(-2.241760e-01) * OUT1
 +(-6.317291e-01) * OUT2
 +(-2.830620e-01) * OUT3
 +(1.750255e-01) * OUT4
 +(-4.006414e-02) * OUT5
 +(2.725541e-01) * OUT6;
RIN11 = 3.396690e-02
 +(-4.485282e-01) * OUT1
 +(-1.537250e-02) * OUT2
 +(4.377254e-01) * OUT3
 +(4.355614e-01) * OUT4
 +(3.298911e-01) * OUT5
 +(-1.948187e-01) * OUT6;
RIN12 = 8.802536e-02
 +(-1.645690e-02) * OUT1
 +(-3.593754e-02) * OUT2
 +(-3.300631e-01) * OUT3
 +(1.853030e-01) * OUT4
 +(1.364193e-02) * OUT5
 +(6.227304e-01) * OUT6;
RIN13 = 3.295576e-01
 +(-4.563790e-02) * OUT1
 +(-2.571594e-01) * OUT2
 +(3.939400e-01) * OUT3
 +(-1.492818e-01) * OUT4
 +(3.167820e-01) * OUT5
 +(4.563062e-01) * OUT6;
RIN14 = 1.007358e-01
 +(-4.626892e-03) * OUT1
 +(9.315815e-03) * OUT2
 +(-1.653549e-01) * OUT3
 +(6.544170e-01) * OUT4
 +(-1.062288e-03) * OUT5
 +(1.809237e-01) * OUT6;
RIN15 = 1.842185e-01
 +(4.109720e-01) * OUT1
 +(-1.750934e-02) * OUT2
 +(-2.841750e-01) * OUT3
 +(4.502524e-01) * OUT4
 +(4.201283e-01) * OUT5
 +(-3.523400e-01) * OUT6;

OUT1 = Sigmoid(RIN1);
OUT2 = Sigmoid(RIN2);
OUT3 = Sigmoid(RIN3);
OUT4 = Sigmoid(RIN4);
OUT5 = Sigmoid(RIN5);
OUT6 = Sigmoid(RIN6);
OUT7 = Sigmoid(RIN7);
OUT8 = Sigmoid(RIN8);
OUT9 = Sigmoid(RIN9);
OUT10 = Sigmoid(RIN10);
OUT11 = Sigmoid(RIN11);
OUT12 = Sigmoid(RIN12);
OUT13 = Sigmoid(RIN13);
OUT14 = Sigmoid(RIN14);
OUT15 = Sigmoid(RIN15);

// layer 3
RIN1 = 4.840965e-01
 +(1.042806e-01) * OUT1
 +(-1.559401e-01) * OUT2
 +(2.621663e-01) * OUT3
 +(-2.558055e-01) * OUT4
 +(2.465964e-01) * OUT5
 +(-5.264297e-02) * OUT6
 +(8.963995e-02) * OUT7
 +(-9.445861e-02) * OUT8
 +(-2.836257e-01) * OUT9
 +(-2.444416e-02) * OUT10
 +(4.221516e-01) * OUT11
 +(-1.707438e-01) * OUT12
 +(-1.831930e-01) * OUT13
 +(6.496654e-01) * OUT14
 +(-2.541290e-01) * OUT15;
RIN2 = -3.759727e-01
 +(3.201696e-03) * OUT1
 +(2.814706e-01) * OUT2
 +(4.590240e-01) * OUT3
 +(4.426849e-01) * OUT4
 +(2.079947e-01) * OUT5
 +(-1.268005e-01) * OUT6
 +(2.240432e-01) * OUT7
 +(-1.648751e-01) * OUT8
 +(-2.282312e-01) * OUT9
 +(-3.116120e-01) * OUT10
 +(1.741257e-02) * OUT11
 +(-1.827420e-01) * OUT12
 +(-3.576361e-01) * OUT13
 +(1.537631e-01) * OUT14
 +(-4.002528e-01) * OUT15;
RIN3 = 3.328196e-01
 +(-3.241346e-01) * OUT1
 +(2.649351e-01) * OUT2
 +(-3.956927e-01) * OUT3
 +(4.618675e-01) * OUT4
 +(-4.378990e-01) * OUT5
 +(4.913286e-02) * OUT6
 +(-2.940118e-01) * OUT7
 +(-2.419236e-01) * OUT8
 +(3.560494e-01) * OUT9
 +(8.887588e-02) * OUT10
 +(1.189877e-01) * OUT11
 +(5.520993e-01) * OUT12
 +(1.662827e-01) * OUT13
 +(2.030284e-01) * OUT14
 +(-3.767420e-01) * OUT15;
RIN4 = -3.021794e-01
 +(2.426857e-02) * OUT1
 +(-4.206145e-01) * OUT2
 +(-3.557886e-01) * OUT3
 +(-2.914001e-01) * OUT4
 +(-4.993384e-02) * OUT5
 +(3.783907e-01) * OUT6
 +(1.474936e-01) * OUT7
 +(3.256811e-01) * OUT8
 +(-3.321865e-01) * OUT9
 +(-3.979840e-01) * OUT10
 +(5.148389e-01) * OUT11
 +(-4.002522e-01) * OUT12
 +(4.484992e-01) * OUT13
 +(-3.581619e-01) * OUT14
 +(5.721040e-01) * OUT15;
RIN5 = -4.385875e-01
 +(3.705718e-01) * OUT1
 +(-4.430307e-01) * OUT2
 +(-4.508402e-01) * OUT3
 +(4.231011e-01) * OUT4
 +(5.637889e-02) * OUT5
 +(-3.123048e-01) * OUT6
 +(-2.918703e-01) * OUT7
 +(-6.334352e-02) * OUT8
 +(4.725171e-01) * OUT9
 +(3.391282e-01) * OUT10
 +(-1.324763e-01) * OUT11
 +(-7.793628e-02) * OUT12
 +(8.607008e-02) * OUT13
 +(7.129920e-02) * OUT14
 +(2.323856e-01) * OUT15;

OUT1 = Sigmoid(RIN1);
OUT2 = Sigmoid(RIN2);
OUT3 = Sigmoid(RIN3);
OUT4 = Sigmoid(RIN4);
OUT5 = Sigmoid(RIN5);

// layer 4
double testmlp = -6.035074e+00
 +(-6.215130e+00) * OUT1
 +(4.345867e+00) * OUT2
 +(5.610218e+00) * OUT3
 +(6.488374e+00) * OUT4
 +(5.429897e+00) * OUT5;

testmlp = testmlp/0.98;
if     (testmlp<=0.0) testmlp = 0.00000;
else if(testmlp>=1.0) testmlp = 0.99999;

return testmlp;
}

//------------------------------------------------------------------------------
double FwdJetEvtSelMod::Sigmoid(double x){
double value = 0.;
if(x > 37.){
   value = 1.;
}
else if(x < -37.){
   value = 0.;
}
else{
   value = 1./(1.+exp(-x));
}
return value;
}
