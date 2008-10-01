// $Id: JetValidationMod.cc,v 1.1 2008/10/01 11:21:26 sixie Exp $

#include "MitAna/Validation/interface/JetValidationMod.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
#include <map>

using namespace mithep;

ClassImp(mithep::JetValidationMod)

//--------------------------------------------------------------------------------------------------
  JetValidationMod::JetValidationMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPrintDebug(false),
  fIC5GenJetName("IC5GenJets"),
  fSC5GenJetName("SC5GenJets"),
  fIC5JetName(Names::gkCaloJetBrn),
  fSC5JetName("SisCone5Jets"),
  fIC5Jets(0),
  fSC5Jets(0),
  fIC5GenJets(0),
  fSC5GenJets(0),
  fNEventsProcessed(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void JetValidationMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont do
  // anything here.
}

//--------------------------------------------------------------------------------------------------
void JetValidationMod::Process()
{
  // Process entries of the tree. 

  fNEventsProcessed++;
  if (fNEventsProcessed % 1000 == 0 || fPrintDebug)
    cerr << endl << "Process Event " << fNEventsProcessed << endl;
    
  //************************************************************************************************
  //
  // For IterativeCone 0.5 Jets
  //
  //************************************************************************************************

  ObjArray<Jet> *GoodIC5Jets = new ObjArray<Jet>;
  LoadBranch(fIC5JetName);
  for (UInt_t i=0; i<fIC5Jets->GetEntries(); ++i) {
    if(fabs(fIC5Jets->At(i)->Eta()) >= 5.0) continue; // minimum eta requirement
    if(fIC5Jets->At(i)->Pt() <= 5) continue; // minimum Pt requirement
    GoodIC5Jets->Add(fIC5Jets->At(i));   
    fIC5CaloJetsPt->Fill(fIC5Jets->At(i)->Pt());
    fIC5CaloJetsEta->Fill(fIC5Jets->At(i)->Eta());
  }
  fIC5NCaloJets->Fill(GoodIC5Jets->GetEntries());

  ObjArray<GenJet> *GoodIC5GenJets = new ObjArray<GenJet>;
  LoadBranch(fIC5GenJetName);
  for (UInt_t i=0; i<fIC5GenJets->GetEntries(); ++i) {
    if(fabs(fIC5GenJets->At(i)->Eta()) >= 5.0) continue; // minimum eta requirement
    if(fIC5GenJets->At(i)->Pt() <= 5) continue; // minimum Pt requirement
    GoodIC5GenJets->Add(fIC5GenJets->At(i));
  }

  std::map <GenJet*, Jet*> IC5GenJetToIC5JetMap;  
  for (UInt_t i=0; i<GoodIC5GenJets->GetEntries(); ++i) {
    double minDR = 5000;
    int closestMatchIndex = -1;
    for (UInt_t j=0; j<GoodIC5Jets->GetEntries(); j++) {
      double tempDR = MathUtils::DeltaR(GoodIC5GenJets->At(i)->Mom(), GoodIC5Jets->At(j)->Mom());
      if (tempDR < minDR) {
        closestMatchIndex = j;
        minDR = tempDR;
      }
    }
    if (closestMatchIndex > -1)
      if (fPrintDebug) cerr << "GoodIC5GenJets->At(i) " << GoodIC5GenJets->At(i)->Pt() << " " << GoodIC5GenJets->At(i)->Eta() << " " << GoodIC5GenJets->At(i)->Phi() << "   GoodIC5Jets->At(" << closestMatchIndex << ") " << GoodIC5Jets->At(closestMatchIndex)->Pt() << " " << GoodIC5Jets->At(closestMatchIndex)->Eta() << " " << GoodIC5Jets->At(closestMatchIndex)->Phi() << "    DR = " << minDR << endl;
    if (minDR < 0.5)
    {
      IC5GenJetToIC5JetMap[GoodIC5GenJets->At(i)] = GoodIC5Jets->At(closestMatchIndex);      
    }
  }

  std::map <Jet*, GenJet*> IC5JetToIC5GenJetMap;  
  for (UInt_t i=0; i<GoodIC5Jets->GetEntries(); ++i) {
    double minDR = 5000;
    int closestMatchIndex = -1;
    for (UInt_t j=0; j<GoodIC5GenJets->GetEntries(); j++) {
      double tempDR = MathUtils::DeltaR(GoodIC5Jets->At(i)->Mom(), GoodIC5GenJets->At(j)->Mom());
      if (tempDR < minDR) {
        closestMatchIndex = j;
        minDR = tempDR;
      }
    }
    if (minDR < 0.5)
      IC5JetToIC5GenJetMap[GoodIC5Jets->At(i)] = GoodIC5GenJets->At(closestMatchIndex);
  }

  for (UInt_t i=0; i<GoodIC5GenJets->GetEntries(); i++) {

    fIC5NGenJetsVsGenJetPt->Fill(GoodIC5GenJets->At(i)->Pt());
    fIC5NGenJetsVsGenJetEta->Fill(GoodIC5GenJets->At(i)->Eta());
    if (GoodIC5GenJets->At(i)->Pt() > 20.0 && GoodIC5GenJets->At(i)->Pt() < 30.0)
      fIC5NGenJetsVsGenJetEta_Pt20To30->Fill(GoodIC5GenJets->At(i)->Eta());
    if (GoodIC5GenJets->At(i)->Pt() > 30.0 && GoodIC5GenJets->At(i)->Pt() < 40.0)
      fIC5NGenJetsVsGenJetEta_Pt30To40->Fill(GoodIC5GenJets->At(i)->Eta());
    if (GoodIC5GenJets->At(i)->Pt() > 60.0 && GoodIC5GenJets->At(i)->Pt() < 80.0)
      fIC5NGenJetsVsGenJetEta_Pt60To80->Fill(GoodIC5GenJets->At(i)->Eta());
    
    map<GenJet*, Jet*>::iterator iter = 
      IC5GenJetToIC5JetMap.find(GoodIC5GenJets->At(i));      
    if (iter != IC5GenJetToIC5JetMap.end()) {          
      double dR = MathUtils::DeltaR(GoodIC5GenJets->At(i)->Mom(), iter->second->Mom());
      
      fIC5GenJetRecoJetDeltaR->Fill(dR);
      fIC5GenJetRecoJetDeltaEta->Fill(fabs(GoodIC5GenJets->At(i)->Eta() - iter->second->Eta()));
      fIC5GenJetRecoJetDeltaPhi->Fill(MathUtils::DeltaPhi(GoodIC5GenJets->At(i)->Phi(),iter->second->Phi()));
      
      if (fabs(iter->second->Eta()) <= 1.4)
        fIC5JetResponseVsGenJetPtInBarrel->Fill(iter->second->Et()/GoodIC5GenJets->At(i)->Et(),GoodIC5GenJets->At(i)->Pt());
      else if (fabs(iter->second->Eta()) <= 3.0)
        fIC5JetResponseVsGenJetPtInEndcap->Fill(iter->second->Et()/GoodIC5GenJets->At(i)->Et(),GoodIC5GenJets->At(i)->Pt());
      else if (fabs(iter->second->Eta()) <= 5.0)
        fIC5JetResponseVsGenJetPtForward->Fill(iter->second->Et()/GoodIC5GenJets->At(i)->Et(),GoodIC5GenJets->At(i)->Pt());                
      
      //avoid the low pt region
      if (iter->second->Pt() > 30)
        fIC5JetResponseVsCaloJetEta->Fill(iter->second->Et()/GoodIC5GenJets->At(i)->Et(),iter->second->Eta());
      
      if (fabs(iter->second->Eta()) <= 3.0) {
        fIC5CentralGenJetRecoJetDeltaR->Fill(dR);
      } else if (fabs(iter->second->Eta()) <= 5.0) {
        fIC5ForwardGenJetRecoJetDeltaR->Fill(dR);
      }
      
      //Number of Matched CaloJet vs Genjet pt and eta
      fIC5NMatchedCaloJetsVsGenJetPt->Fill(GoodIC5GenJets->At(i)->Pt());
      fIC5NMatchedCaloJetsVsGenJetEta->Fill(GoodIC5GenJets->At(i)->Eta());      
      if (GoodIC5GenJets->At(i)->Pt() > 20.0 && GoodIC5GenJets->At(i)->Pt() < 30.0)
        fIC5NMatchedCaloJetsVsGenJetEta_Pt20To30->Fill(GoodIC5GenJets->At(i)->Eta());
      if (GoodIC5GenJets->At(i)->Pt() > 30.0 && GoodIC5GenJets->At(i)->Pt() < 40.0)
        fIC5NMatchedCaloJetsVsGenJetEta_Pt30To40->Fill(GoodIC5GenJets->At(i)->Eta());
      if (GoodIC5GenJets->At(i)->Pt() > 60.0 && GoodIC5GenJets->At(i)->Pt() < 80.0)
        fIC5NMatchedCaloJetsVsGenJetEta_Pt60To80->Fill(GoodIC5GenJets->At(i)->Eta());
     
      fIC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt->Fill(iter->second->Pt() * iter->second->L2RelativeCorrectionScale() * iter->second->L3AbsoluteCorrectionScale() / GoodIC5GenJets->At(i)->Pt(), GoodIC5GenJets->At(i)->Pt());
    }             
  }

  for (UInt_t i=0; i<GoodIC5Jets->GetEntries(); i++) {
    map<Jet*, GenJet*>::iterator iter = 
      IC5JetToIC5GenJetMap.find(GoodIC5Jets->At(i));      
    //unmatched ones
    if (iter == IC5JetToIC5GenJetMap.end()) {          
      fIC5NUnmatchedCaloJetsVsCorrectedCaloJetPt->Fill(GoodIC5Jets->At(i)->Pt() * GoodIC5Jets->At(i)->L2RelativeCorrectionScale() * GoodIC5Jets->At(i)->L3AbsoluteCorrectionScale());
      fIC5NUnmatchedCalojetsVsCorrectedCaloJetEta->Fill(GoodIC5Jets->At(i)->Eta());
    }
  }


  //************************************************************************************************
  //
  // For SisCone 0.5 Jets
  //
  //************************************************************************************************

  ObjArray<Jet> *GoodSC5Jets = new ObjArray<Jet>;
  LoadBranch(fSC5JetName);
  for (UInt_t i=0; i<fSC5Jets->GetEntries(); ++i) {
    if(fabs(fSC5Jets->At(i)->Eta()) >= 5.0) continue; // minimum eta requirement
    if(fSC5Jets->At(i)->Pt() <= 5) continue; // minimum Pt requirement
    GoodSC5Jets->Add(fSC5Jets->At(i));   
    fSC5CaloJetsPt->Fill(fSC5Jets->At(i)->Pt());
    fSC5CaloJetsEta->Fill(fSC5Jets->At(i)->Eta());
  }
  fSC5NCaloJets->Fill(GoodSC5Jets->GetEntries());

  ObjArray<GenJet> *GoodSC5GenJets = new ObjArray<GenJet>;
  LoadBranch(fSC5GenJetName);
  for (UInt_t i=0; i<fSC5GenJets->GetEntries(); ++i) {
    if(fabs(fSC5GenJets->At(i)->Eta()) >= 5.0) continue; // minimum eta requirement
    if(fSC5GenJets->At(i)->Pt() <= 5) continue; // minimum Pt requirement
    GoodSC5GenJets->Add(fSC5GenJets->At(i));
  }

  std::map <GenJet*, Jet*> SC5GenJetToSC5JetMap;  
  for (UInt_t i=0; i<GoodSC5GenJets->GetEntries(); ++i) {
    double minDR = 5000;
    int closestMatchIndex = -1;
    for (UInt_t j=0; j<GoodSC5Jets->GetEntries(); j++) {
      double tempDR = MathUtils::DeltaR(GoodSC5GenJets->At(i)->Mom(), GoodSC5Jets->At(j)->Mom());
      if (tempDR < minDR) {
        closestMatchIndex = j;
        minDR = tempDR;
      }
    }
    if (closestMatchIndex > -1)
      if (fPrintDebug) cerr << "GoodSC5GenJets->At(i) " << GoodSC5GenJets->At(i)->Pt() << " " << GoodSC5GenJets->At(i)->Eta() << " " << GoodSC5GenJets->At(i)->Phi() << "   GoodSC5Jets->At(" << closestMatchIndex << ") " << GoodSC5Jets->At(closestMatchIndex)->Pt() << " " << GoodSC5Jets->At(closestMatchIndex)->Eta() << " " << GoodSC5Jets->At(closestMatchIndex)->Phi() << "    DR = " << minDR << endl;
    if (minDR < 0.5)
    {
      SC5GenJetToSC5JetMap[GoodSC5GenJets->At(i)] = GoodSC5Jets->At(closestMatchIndex);      
    }
  }
  std::map <Jet*, GenJet*> SC5JetToSC5GenJetMap;  
  for (UInt_t i=0; i<GoodSC5Jets->GetEntries(); ++i) {
    double minDR = 5000;
    int closestMatchIndex = -1;
    for (UInt_t j=0; j<GoodSC5GenJets->GetEntries(); j++) {
      double tempDR = MathUtils::DeltaR(GoodSC5Jets->At(i)->Mom(), GoodSC5GenJets->At(j)->Mom());
      if (tempDR < minDR) {
        closestMatchIndex = j;
        minDR = tempDR;
      }
    }
    if (minDR < 0.5)
      SC5JetToSC5GenJetMap[GoodSC5Jets->At(i)] = GoodSC5GenJets->At(closestMatchIndex);
  }
  for (UInt_t i=0; i<GoodSC5GenJets->GetEntries(); i++) {

    fSC5NGenJetsVsGenJetPt->Fill(GoodSC5GenJets->At(i)->Pt());
    fSC5NGenJetsVsGenJetEta->Fill(GoodSC5GenJets->At(i)->Eta());
        if (GoodSC5GenJets->At(i)->Pt() > 20.0 && GoodSC5GenJets->At(i)->Pt() < 30.0)
      fSC5NGenJetsVsGenJetEta_Pt20To30->Fill(GoodSC5GenJets->At(i)->Eta());
    if (GoodSC5GenJets->At(i)->Pt() > 30.0 && GoodSC5GenJets->At(i)->Pt() < 40.0)
      fSC5NGenJetsVsGenJetEta_Pt30To40->Fill(GoodSC5GenJets->At(i)->Eta());
    if (GoodSC5GenJets->At(i)->Pt() > 60.0 && GoodSC5GenJets->At(i)->Pt() < 80.0)
      fSC5NGenJetsVsGenJetEta_Pt60To80->Fill(GoodSC5GenJets->At(i)->Eta());
    
    map<GenJet*, Jet*>::iterator iter = 
      SC5GenJetToSC5JetMap.find(GoodSC5GenJets->At(i));      
    if (iter != SC5GenJetToSC5JetMap.end()) {          
      double dR = MathUtils::DeltaR(GoodSC5GenJets->At(i)->Mom(), iter->second->Mom());
      
      fSC5GenJetRecoJetDeltaR->Fill(dR);
      fSC5GenJetRecoJetDeltaEta->Fill(fabs(GoodSC5GenJets->At(i)->Eta() - iter->second->Eta()));
      fSC5GenJetRecoJetDeltaPhi->Fill(MathUtils::DeltaPhi(GoodSC5GenJets->At(i)->Phi(),iter->second->Phi()));
      
      if (fabs(iter->second->Eta()) <= 1.4)
        fSC5JetResponseVsGenJetPtInBarrel->Fill(iter->second->Et()/GoodSC5GenJets->At(i)->Et(),GoodSC5GenJets->At(i)->Pt());
      else if (fabs(iter->second->Eta()) <= 3.0)
        fSC5JetResponseVsGenJetPtInEndcap->Fill(iter->second->Et()/GoodSC5GenJets->At(i)->Et(),GoodSC5GenJets->At(i)->Pt());
      else if (fabs(iter->second->Eta()) <= 5.0)
        fSC5JetResponseVsGenJetPtForward->Fill(iter->second->Et()/GoodSC5GenJets->At(i)->Et(),GoodSC5GenJets->At(i)->Pt());
      //avoid the low pt region
      if (iter->second->Pt() > 30)
        fSC5JetResponseVsCaloJetEta->Fill(iter->second->Et()/GoodSC5GenJets->At(i)->Et(),iter->second->Eta());
            
      if (fabs(iter->second->Eta()) <= 3.0) {
        fSC5CentralGenJetRecoJetDeltaR->Fill(dR);
      } else if (fabs(iter->second->Eta()) <= 5.0) {
        fSC5ForwardGenJetRecoJetDeltaR->Fill(dR);
      }
      
      //Number of Matched CaloJet vs Genjet pt and eta
         fSC5NMatchedCaloJetsVsGenJetPt->Fill(GoodSC5GenJets->At(i)->Pt());
      fSC5NMatchedCaloJetsVsGenJetEta->Fill(GoodSC5GenJets->At(i)->Eta());
      if (GoodSC5GenJets->At(i)->Pt() > 20.0 && GoodSC5GenJets->At(i)->Pt() < 30.0)
        fSC5NMatchedCaloJetsVsGenJetEta_Pt20To30->Fill(GoodSC5GenJets->At(i)->Eta());
      if (GoodSC5GenJets->At(i)->Pt() > 30.0 && GoodSC5GenJets->At(i)->Pt() < 40.0)
        fSC5NMatchedCaloJetsVsGenJetEta_Pt30To40->Fill(GoodSC5GenJets->At(i)->Eta());
      if (GoodSC5GenJets->At(i)->Pt() > 60.0 && GoodSC5GenJets->At(i)->Pt() < 80.0)
        fSC5NMatchedCaloJetsVsGenJetEta_Pt60To80->Fill(GoodSC5GenJets->At(i)->Eta());
      fSC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt->Fill(iter->second->Pt() * iter->second->L2RelativeCorrectionScale() * iter->second->L3AbsoluteCorrectionScale() / GoodSC5GenJets->At(i)->Pt(), GoodSC5GenJets->At(i)->Pt());
    }         
  }
  
  for (UInt_t i=0; i<GoodSC5Jets->GetEntries(); i++) {
    map<Jet*, GenJet*>::iterator iter = 
      SC5JetToSC5GenJetMap.find(GoodSC5Jets->At(i));      
    //unmatched ones
    if (iter == SC5JetToSC5GenJetMap.end()) {          
      fSC5NUnmatchedCaloJetsVsCorrectedCaloJetPt->Fill(GoodSC5Jets->At(i)->Pt() * GoodSC5Jets->At(i)->L2RelativeCorrectionScale() * GoodSC5Jets->At(i)->L3AbsoluteCorrectionScale());
      fSC5NUnmatchedCalojetsVsCorrectedCaloJetEta->Fill(GoodSC5Jets->At(i)->Eta());
    }
  }

}


//--------------------------------------------------------------------------------------------------
void JetValidationMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here,
  // we typically initialize histograms and other analysis objects and request
  // branches. For this module, we request a branch of the MitTree.

  ReqBranch(fIC5GenJetName,             fIC5GenJets);
  ReqBranch(fSC5GenJetName,             fSC5GenJets);
  ReqBranch(fIC5JetName,                fIC5Jets);
  ReqBranch(fSC5JetName,                fSC5Jets);

  fIC5GenJetRecoJetDeltaR = new TH1D("hIC5GenJetRecoJetDeltaR",";IC5GenJetRecoJetDeltaR;#",100,0.,1.0);
  fIC5GenJetRecoJetDeltaEta = new TH1D("hIC5GenJetRecoJetDeltaEta",";IC5GenJetRecoJetDeltaEta;#",100,0.,0.5);
  fIC5GenJetRecoJetDeltaPhi = new TH1D("hIC5GenJetRecoJetDeltaPhi",";IC5GenJetRecoJetDeltaPhi;#",100,0.,0.5);

  fIC5JetResponseVsGenJetPtInBarrel = new TH2D("hIC5JetResponseVsGenJetPtInBarrel",";IC5JetResponseVsGenJetPtInBarrel;#",500,0.,5.0,5000,0,5000);
  fIC5JetResponseVsGenJetPtInEndcap = new TH2D("hIC5JetResponseVsGenJetPtInEndcap",";IC5JetResponseVsGenJetPtInEndcap;#",500,0.,5.0,5000,0,5000);
  fIC5JetResponseVsGenJetPtForward = new TH2D("hIC5JetResponseVsGenJetPtForward",";IC5JetResponseVsGenJetPtForward;#",500,0.,5.0,5000,0,5000);
  fIC5JetResponseVsCaloJetEta = new TH2D("hIC5JetResponseVsCaloJetEta",";IC5JetResponseVsCaloJetEta;#",500,0.,5.0,100,-5,5);


  
  fIC5CentralGenJetRecoJetDeltaR = new TH1D("hIC5CentralGenJetRecoJetDeltaR",";IC5CentralGenJetRecoJetDeltaR;#",100,0.,1.0);
  fIC5ForwardGenJetRecoJetDeltaR = new TH1D("hIC5ForwardGenJetRecoJetDeltaR",";IC5ForwardGenJetRecoJetDeltaR;#",100,0.,1.0); 
  
  fIC5NMatchedCaloJetsVsGenJetPt = new TH1D("hIC5NMatchedCaloJetsVsGenJetPt",";IC5GenJetPt;#",5000,0.,5000);
  fIC5NMatchedCaloJetsVsGenJetEta = new TH1D("hIC5NMatchedCaloJetsVsGenJetEta",";IC5GenJetEta;#",100,-5.0,5.0);
  fIC5NMatchedCaloJetsVsGenJetEta_Pt20To30 = new TH1D("hIC5NMatchedCaloJetsVsGenJetEta_Pt20To30",";IC5GenJetEta;#",100,-5.0,5.0);
  fIC5NMatchedCaloJetsVsGenJetEta_Pt30To40 = new TH1D("hIC5NMatchedCaloJetsVsGenJetEta_Pt30To40",";IC5GenJetEta;#",100,-5.0,5.0);
  fIC5NMatchedCaloJetsVsGenJetEta_Pt60To80 = new TH1D("hIC5NMatchedCaloJetsVsGenJetEta_Pt60To80",";IC5GenJetEta;#",100,-5.0,5.0);
  fIC5NGenJetsVsGenJetPt = new TH1D("hIC5NGenJetsVsGenJetPt",";IC5GenJetPt;#",5000,0.,5000);
  fIC5NGenJetsVsGenJetEta = new TH1D("hIC5NGenJetsVsGenJetEta",";IC5GenJetEta;#",100,-5.,5.0);
  fIC5NGenJetsVsGenJetEta_Pt20To30 = new TH1D("hIC5NGenJetsVsGenJetEta_Pt20To30",";IC5GenJetEta;#",100,-5.,5.0);
  fIC5NGenJetsVsGenJetEta_Pt30To40 = new TH1D("hIC5NGenJetsVsGenJetEta_Pt30To40",";IC5GenJetEta;#",100,-5.,5.0);
  fIC5NGenJetsVsGenJetEta_Pt60To80 = new TH1D("hIC5NGenJetsVsGenJetEta_Pt60To80",";IC5GenJetEta;#",100,-5.,5.0);

  fIC5CaloJetsPt = new TH1D("hIC5CaloJetsPt",";IC5CaloJetPt;#",5000,0.,5000);
  fIC5CaloJetsEta = new TH1D("hIC5CaloJetsEta",";IC5CaloJetEta;#",100,-5.0,5.0);
  fIC5NUnmatchedCaloJetsVsCorrectedCaloJetPt = new TH1D("hIC5NUnmatchedCaloJetsVsCorrectedCaloJetPt",";IC5CorrectedCaloJetPt;#",5000,0.0,5000.0);
  fIC5NUnmatchedCalojetsVsCorrectedCaloJetEta = new TH1D("hIC5NUnmatchedCalojetsVsCorrectedCaloJetEta",";IC5CorrectedCaloJetEta;#",100,-5.0,5.0);
  
  fIC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt = new TH2D("hIC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt",";IC5GenJetPt;#",1000,0,1000.0, 100,0.0,5.0);
  
  fIC5NCaloJets = new TH1D("hIC5NCaloJets",";IC5NCaloJets;#",100,0.,15);


  fSC5GenJetRecoJetDeltaR = new TH1D("hSC5GenJetRecoJetDeltaR",";SC5GenJetRecoJetDeltaR;#",100,0.,1.0);
  fSC5GenJetRecoJetDeltaEta = new TH1D("hSC5GenJetRecoJetDeltaEta",";SC5GenJetRecoJetDeltaEta;#",100,0.,0.5);
  fSC5GenJetRecoJetDeltaPhi = new TH1D("hSC5GenJetRecoJetDeltaPhi",";SC5GenJetRecoJetDeltaPhi;#",100,0.,0.5);

  fSC5JetResponseVsGenJetPtInBarrel = new TH2D("hSC5JetResponseVsGenJetPtInBarrel",";SC5JetResponseVsGenJetPtInBarrel;#",500,0.,5.0,5000,0,5000);
  fSC5JetResponseVsGenJetPtInEndcap = new TH2D("hSC5JetResponseVsGenJetPtInEndcap",";SC5JetResponseVsGenJetPtInEndcap;#",500,0.,5.0,5000,0,5000);
  fSC5JetResponseVsGenJetPtForward = new TH2D("hSC5JetResponseVsGenJetPtForward",";SC5JetResponseVsGenJetPtForward;#",500,0.,5.0,5000,0,5000);

  fSC5JetResponseVsCaloJetEta = new TH2D("hSC5JetResponseVsCaloJetEta",";SC5JetResponseVsCaloJetEta;#",500,0.,5.0,100,-5,5);


  
  fSC5CentralGenJetRecoJetDeltaR = new TH1D("hSC5CentralGenJetRecoJetDeltaR",";SC5CentralGenJetRecoJetDeltaR;#",100,0.,1.0);
  fSC5ForwardGenJetRecoJetDeltaR = new TH1D("hSC5ForwardGenJetRecoJetDeltaR",";SC5ForwardGenJetRecoJetDeltaR;#",100,0.,1.0); 
  
  fSC5NMatchedCaloJetsVsGenJetPt = new TH1D("hSC5NMatchedCaloJetsVsGenJetPt",";SC5GenJetPt;#",5000,0.,5000);
  fSC5NMatchedCaloJetsVsGenJetEta = new TH1D("hSC5NMatchedCaloJetsVsGenJetEta",";SC5GenJetEta;#",100,-5.0,5.0);
  fSC5NMatchedCaloJetsVsGenJetEta_Pt20To30 = new TH1D("hSC5NMatchedCaloJetsVsGenJetEta_Pt20To30",";SC5GenJetEta;#",100,-5.0,5.0);
  fSC5NMatchedCaloJetsVsGenJetEta_Pt30To40 = new TH1D("hSC5NMatchedCaloJetsVsGenJetEta_Pt30To40",";SC5GenJetEta;#",100,-5.0,5.0);
  fSC5NMatchedCaloJetsVsGenJetEta_Pt60To80 = new TH1D("hSC5NMatchedCaloJetsVsGenJetEta_Pt60To80",";SC5GenJetEta;#",100,-5.0,5.0);
  fSC5NGenJetsVsGenJetPt = new TH1D("hSC5NGenJetsVsGenJetPt",";SC5GenJetPt;#",5000,0.,5000);
  fSC5NGenJetsVsGenJetEta = new TH1D("hSC5NGenJetsVsGenJetEta",";SC5GenJetEta;#",100,-5.,5.0);
  fSC5NGenJetsVsGenJetEta_Pt20To30 = new TH1D("hSC5NGenJetsVsGenJetEta_Pt20To30",";SC5GenJetEta;#",100,-5.,5.0);
  fSC5NGenJetsVsGenJetEta_Pt30To40 = new TH1D("hSC5NGenJetsVsGenJetEta_Pt30To40",";SC5GenJetEta;#",100,-5.,5.0);
  fSC5NGenJetsVsGenJetEta_Pt60To80 = new TH1D("hSC5NGenJetsVsGenJetEta_Pt60To80",";SC5GenJetEta;#",100,-5.,5.0);
  
  fSC5CaloJetsPt = new TH1D("hSC5CaloJetsPt",";SC5CaloJetPt;#",5000,0.,5000);
  fSC5CaloJetsEta = new TH1D("hSC5CaloJetsEta",";SC5CaloJetEta;#",100,-5.0,5.0);
  fSC5NUnmatchedCaloJetsVsCorrectedCaloJetPt = new TH1D("hSC5NUnmatchedCaloJetsVsCorrectedCaloJetPt",";SC5CorrectedCaloJetPt;#",5000,0.0,5000.0);
  fSC5NUnmatchedCalojetsVsCorrectedCaloJetEta = new TH1D("hSC5NUnmatchedCalojetsVsCorrectedCaloJetEta",";SC5CorrectedCaloJetEta;#",100,-5.0,5.0);
  
  fSC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt = new TH2D("hSC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt",";SC5GenJetPt;#",1000,0,1000.0, 100,0.0,5.0);
  
  fSC5NCaloJets = new TH1D("hSC5NCaloJets",";SC5NCaloJets;#",100,0.,15);

  AddOutput(fIC5GenJetRecoJetDeltaR);
  AddOutput(fIC5GenJetRecoJetDeltaEta);
  AddOutput(fIC5GenJetRecoJetDeltaPhi);
  AddOutput(fIC5JetResponseVsGenJetPtInBarrel);
  AddOutput(fIC5JetResponseVsGenJetPtInEndcap);
  AddOutput(fIC5JetResponseVsGenJetPtForward);
  AddOutput(fIC5JetResponseVsCaloJetEta);
  AddOutput(fIC5CentralGenJetRecoJetDeltaR);
  AddOutput(fIC5ForwardGenJetRecoJetDeltaR);  
  AddOutput(fIC5NMatchedCaloJetsVsGenJetPt);
  AddOutput(fIC5NMatchedCaloJetsVsGenJetEta);
  AddOutput(fIC5NMatchedCaloJetsVsGenJetEta_Pt20To30);
  AddOutput(fIC5NMatchedCaloJetsVsGenJetEta_Pt30To40);
  AddOutput(fIC5NMatchedCaloJetsVsGenJetEta_Pt60To80);
  AddOutput(fIC5NGenJetsVsGenJetPt);
  AddOutput(fIC5NGenJetsVsGenJetEta);
  AddOutput(fIC5NGenJetsVsGenJetEta_Pt20To30);
  AddOutput(fIC5NGenJetsVsGenJetEta_Pt30To40);
  AddOutput(fIC5NGenJetsVsGenJetEta_Pt60To80);
  AddOutput(fIC5CaloJetsPt);
  AddOutput(fIC5CaloJetsEta);
  AddOutput(fIC5NUnmatchedCaloJetsVsCorrectedCaloJetPt);
  AddOutput(fIC5NUnmatchedCalojetsVsCorrectedCaloJetEta);  
  AddOutput(fIC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt);  
  AddOutput(fIC5NCaloJets);
  AddOutput(fSC5GenJetRecoJetDeltaR);
  AddOutput(fSC5GenJetRecoJetDeltaEta);
  AddOutput(fSC5GenJetRecoJetDeltaPhi);
  AddOutput(fSC5JetResponseVsGenJetPtInBarrel);
  AddOutput(fSC5JetResponseVsGenJetPtInEndcap);
  AddOutput(fSC5JetResponseVsGenJetPtForward);
  AddOutput(fSC5JetResponseVsCaloJetEta);
  AddOutput(fSC5CentralGenJetRecoJetDeltaR);
  AddOutput(fSC5ForwardGenJetRecoJetDeltaR);  
  AddOutput(fSC5NMatchedCaloJetsVsGenJetPt);
  AddOutput(fSC5NMatchedCaloJetsVsGenJetEta);
  AddOutput(fSC5NMatchedCaloJetsVsGenJetEta_Pt20To30);
  AddOutput(fSC5NMatchedCaloJetsVsGenJetEta_Pt30To40);
  AddOutput(fSC5NMatchedCaloJetsVsGenJetEta_Pt60To80);
  AddOutput(fSC5NGenJetsVsGenJetPt);
  AddOutput(fSC5NGenJetsVsGenJetEta);
  AddOutput(fSC5NGenJetsVsGenJetEta_Pt20To30);
  AddOutput(fSC5NGenJetsVsGenJetEta_Pt30To40);
  AddOutput(fSC5NGenJetsVsGenJetEta_Pt60To80);
  AddOutput(fSC5CaloJetsPt);
  AddOutput(fSC5CaloJetsEta);
  AddOutput(fSC5NUnmatchedCaloJetsVsCorrectedCaloJetPt);
  AddOutput(fSC5NUnmatchedCalojetsVsCorrectedCaloJetEta);  
  AddOutput(fSC5CorrPtCaloJetsOverGenJetsPtVsGenJetPt);  
  AddOutput(fSC5NCaloJets);
}

//--------------------------------------------------------------------------------------------------
void JetValidationMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this
  // module, we dont do anything here.
  cout << "Events Processed: " << fNEventsProcessed << endl;

}

//--------------------------------------------------------------------------------------------------
void JetValidationMod::Terminate()
{
  // Run finishing code on the client computer. For this module, we dont do
  // anything here.
}
