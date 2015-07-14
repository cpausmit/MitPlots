
#include <iostream>
#include "TGraph.h"
#include "TF1.h"
#include "TH2D.h"
#include "TLegend.h"

#include "MitPlots/Plot/interface/PlotResolution.h"

using namespace mithep;

ClassImp(mithep::PlotResolution)

//--------------------------------------------------------------------
PlotResolution::PlotResolution() :
  fNumPlots(0),
  fCanvasName("canvas"),
  fDefaultTree(0),
  fDefaultCut(""),
  fDefaultExprRes(""),
  fInExprX(""),
  l1(0.6),
  l2(0.7),
  l3(0.9),
  l4(0.9)
{
  fInTrees.resize(0);
  fInCuts.resize(0);
  fInExprRes.resize(0);
}

//--------------------------------------------------------------------
PlotResolution::~PlotResolution()
{}

//--------------------------------------------------------------------
void
PlotResolution::AddLine(TTree *tree, TString cut, TString expr_res){
  if(fDefaultTree != NULL){
    std::cout << "Default tree already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultCut != ""){
    std::cout << "Default cut already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultExprRes != ""){
    std::cout << "Default resolution expression already set! Check configuration..." << std::endl;
    exit(1);
  }
  fInTrees.push_back(tree);
  fInCuts.push_back(cut);
  fInExprRes.push_back(expr_res);
  fNumPlots++;
}

//--------------------------------------------------------------------
void
PlotResolution::AddTreeCut(TTree *tree, TString cut){
  if(fDefaultTree != NULL){
    std::cout << "Default tree already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultCut != ""){
    std::cout << "Default cut already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultExprRes == ""){
    std::cout << "Please set default resolution expression first!" << std::endl;
    exit(1);
  }
  fInTrees.push_back(tree);
  fInCuts.push_back(cut);
  fNumPlots++;
}

//--------------------------------------------------------------------
void
PlotResolution::AddTreeExprRes(TTree *tree, TString expr_res){
  if(fDefaultTree != NULL){
    std::cout << "Default tree already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultCut == ""){
    std::cout << "Please set default cut first!" << std::endl;
    exit(1);
  }
  if(fDefaultExprRes != ""){
    std::cout << "Default resolution expression already set! Check configuration..." << std::endl;
    exit(1);
  }
  fInTrees.push_back(tree);
  fInExprRes.push_back(expr_res);
  fNumPlots++;
}

//--------------------------------------------------------------------
void
PlotResolution::AddCutExprRes(TString cut, TString expr_res){
  if(fDefaultTree == NULL){
    std::cout << "Please set default tree first!" << std::endl;
    exit(1);
  }
  if(fDefaultCut != ""){
    std::cout << "Default cut already set! Check configuration..." << std::endl;
    exit(1);
  }
  if(fDefaultExprRes != ""){
    std::cout << "Default resolution expression already set! Check configuration..." << std::endl;
    exit(1);
  }
  fInCuts.push_back(cut);
  fInExprRes.push_back(expr_res);
  fNumPlots++;
}

//--------------------------------------------------------------------
void
PlotResolution::SetLegendLimits(Double_t lim1, Double_t lim2, Double_t lim3, Double_t lim4){
  l1 = lim1;
  l2 = lim2;
  l3 = lim3;
  l4 = lim4;
}


//--------------------------------------------------------------------
TCanvas*
PlotResolution::MakeCanvas(LegendContainer *theLegendContainer,
                           TString XLabel, TString YLabel,
                           Int_t NumXBins, Double_t MinX, Double_t MaxX,
                           Int_t NumYBins, Double_t MinY, Double_t MaxY,
                           Int_t ParamNumber, Double_t FinalMin, Double_t FinalMax,Bool_t logY){
  if(fInExprX == ""){
    std::cout << "You haven't initialized an x expression yet!" << std::endl;
    exit(1);
  }
  if(fNumPlots == 0){
    if(fInTrees.size() > 0) fNumPlots = fInTrees.size();
    else if(fInCuts.size() > 0) fNumPlots = fInCuts.size();
    else fNumPlots = fInExprRes.size();
    if(fNumPlots == 0){
      std::cout << "Nothing has been initialized in resolution plot." << std::endl;
      exit(1);
    }
  }

  TTree *inTree = fDefaultTree;
  TString inCut = fDefaultCut;
  TString inExpr = fDefaultExprRes;

  TH2D *tempHist;

  TGraph *tempGraph;
  std::vector<TGraph*> theGraphs;

  TF1 *fitFunc = new TF1("func","[0]*TMath::Gaus(x,[1],[2])",MinY,MaxY);

  for(UInt_t i0 = 0; i0 < fNumPlots; i0++){
    if(fInTrees.size()   != 0) inTree = fInTrees[i0];
    if(fInCuts.size()    != 0) inCut  = fInCuts[i0];
    if(fInExprRes.size() != 0) inExpr = fInExprRes[i0];

    TString tempName;
    tempName.Form("Hist_%d",i0);
    tempHist = new TH2D(tempName,tempName,NumXBins,MinX,MaxX,NumYBins,MinY,MaxY);
    inTree->Draw(inExpr+":"+fInExprX+">>"+tempName,inCut);
    tempGraph = new TGraph(NumXBins);
    for(Int_t i1 = 0; i1 < NumXBins; i1++){
      fitFunc->SetParameters(1.,(MaxY + MinY)/2,(MaxY - MinY)/4);
      tempHist->ProjectionY(tempName+"_py",i1+1,i1+1)->Fit(fitFunc,"","",MinY,MaxY);
      tempGraph->SetPoint(i1,tempHist->GetXaxis()->GetBinCenter(i1+1),fitFunc->GetParameter(ParamNumber));
    }
    theGraphs.push_back(tempGraph);
  }

  TCanvas *theCanvas = new TCanvas(fCanvasName,fCanvasName);
  TLegend *theLegend = new TLegend(l1,l2,l3,l4);
  for(UInt_t i0 = 0; i0 < fNumPlots; i0++){
    theGraphs[i0]->SetLineWidth(2);
    theGraphs[i0]->SetLineColor(theLegendContainer->ReturnColor(i0));
    theLegend->AddEntry(theGraphs[i0],theLegendContainer->ReturnLegendEntry(i0),"l");
  }
  theGraphs[0]->GetYaxis()->SetRangeUser(FinalMin,FinalMax);
  theGraphs[0]->Draw();
  for(UInt_t i0 = 1; i0 < theGraphs.size(); i0++){
    theGraphs[i0]->Draw("same");
  }
  theLegend->Draw();
  if(logY) theCanvas->SetLogy();
  return theCanvas;
}

