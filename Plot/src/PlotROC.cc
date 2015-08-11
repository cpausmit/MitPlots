#include <iostream>

#include "TLegend.h"
#include "MitPlots/Plot/interface/PlotROC.h"

using namespace mithep;

ClassImp(mithep::PlotROC)

//--------------------------------------------------------------------
PlotROC::PlotROC()
{
  fROCVars.resize(0);
  fInTrees.resize(2);
  fInCuts.resize(2);
}

//--------------------------------------------------------------------
TGraph*
PlotROC::MakeROC(TString CutVar, Int_t NumBins)
{
  SetDefaultExpr(CutVar);

  // Get the minimum and maximum values of the histograms
  TH1F *htemp;
  fInTrees[0]->Draw(fDefaultExpr,fInCuts[0]);
  htemp = (TH1F*) gPad->GetPrimitive("htemp");
  Double_t XMin = htemp->GetXaxis()->GetBinLowEdge(1);
  Int_t   NBins = htemp->GetNbinsX();
  Double_t XMax = htemp->GetXaxis()->GetBinLowEdge(NBins) + htemp->GetXaxis()->GetBinWidth(NBins);
  fInTrees[1]->Draw(fDefaultExpr,fInCuts[1]);
  htemp = (TH1F*) gPad->GetPrimitive("htemp");
  Double_t checkM = htemp->GetXaxis()->GetBinLowEdge(1);
  if (XMin > checkM)
    XMin = checkM;
  NBins = htemp->GetNbinsX();
  checkM = htemp->GetXaxis()->GetBinLowEdge(NBins) + htemp->GetXaxis()->GetBinWidth(NBins);
  if (XMax < checkM)
    XMax = checkM;
  
  std::vector<TH1D*> theHists = MakeHists(NumBins, XMin, XMax);
  const Int_t numPoints = NumBins + 1;
  Double_t XVals[numPoints];
  Double_t RevXVals[numPoints];
  Double_t YVals[numPoints];
  Double_t RevYVals[numPoints];
  for (Int_t i0 = 0; i0 < numPoints; i0++) {
    Double_t sigArea  = theHists[0]->Integral();
    Double_t backArea = theHists[1]->Integral();
    XVals[i0]    = theHists[0]->Integral(i0,numPoints)/sigArea;
    RevXVals[i0] = theHists[0]->Integral(numPoints-i0,numPoints)/sigArea;
    YVals[i0]    = theHists[1]->Integral(i0,numPoints)/backArea;
    RevYVals[i0] = theHists[1]->Integral(numPoints-i0,numPoints)/backArea;
  }
  TGraph *rocCurve    = new TGraph(numPoints,XVals,YVals);
  TGraph *revRocCurve = new TGraph(numPoints,RevXVals,RevYVals);
  delete theHists[0];
  delete theHists[1];
  if (revRocCurve->Integral() > rocCurve->Integral()) {
    delete rocCurve;
    return revRocCurve;
  }
  else {
    delete revRocCurve;
    return rocCurve;
  }
}

//--------------------------------------------------------------------
std::vector<TGraph*>
PlotROC::MakeROCs(Int_t NumBins)
{
  std::vector<TGraph*> theGraphs;
  for (UInt_t i0 = 0; i0 < fROCVars.size(); i0++)
    theGraphs.push_back(MakeROC(fROCVars[i0], NumBins));

  return theGraphs;
}

//--------------------------------------------------------------------
TCanvas*
PlotROC::MakeCanvas(Int_t NumBins, Bool_t logY, TString CanvasTitle, 
                           TString XLabel, TString YLabel)
{
  std::vector<TGraph*> theGraphs = MakeROCs(NumBins);
  UInt_t NumPlots = theGraphs.size();

  TCanvas *theCanvas = new TCanvas(fCanvasName,fCanvasName);
  theCanvas->SetTitle(CanvasTitle+";"+XLabel+";"+YLabel);
  TLegend *theLegend = new TLegend(l1,l2,l3,l4);
  theLegend->SetBorderSize(fLegendBorderSize);

  for (UInt_t i0 = 0; i0 < NumPlots; i0++) {
    theGraphs[i0]->SetTitle(CanvasTitle+";"+XLabel+";"+YLabel);
    theGraphs[i0]->SetLineWidth(fLineWidths[i0]);
    theGraphs[i0]->SetLineStyle(fLineStyles[i0]);
    theGraphs[i0]->SetLineColor(fLineColors[i0]);
    theLegend->AddEntry(theGraphs[i0],fLegendEntries[i0],"l");
  }

  for (UInt_t i0 = 1; i0 < NumPlots; i0++)
    theGraphs[i0]->Draw("same");

  theLegend->Draw();
  if (logY)
    theCanvas->SetLogy();

  return theCanvas;
}

//--------------------------------------------------------------------
void
PlotROC::MakeCanvas(TString FileBase, Int_t NumBins, Bool_t logY, 
                           TString CanvasTitle, TString XLabel, TString YLabel)
{
  TCanvas *theCanvas = MakeCanvas(NumBins,logY,CanvasTitle,XLabel,YLabel);

  theCanvas->SaveAs(FileBase+".C");
  theCanvas->SaveAs(FileBase+".png");
  theCanvas->SaveAs(FileBase+".pdf");

  delete theCanvas;
}
