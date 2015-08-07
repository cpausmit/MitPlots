#include <iostream>

#include "MitPlots/Plot/interface/PlotROC.h"

using namespace mithep;

ClassImp(mithep::PlotROC)


//--------------------------------------------------------------------
TGraph*
PlotROC::makeROC(TString CutVar, TTree *sigTree, TTree *backTree, 
                 TString sigCut, TString backCut, Int_t numBins, Double_t *XBins,
                 ROCType type)
{
  AddLine(sigTree, sigCut, CutVar);
  AddLine(backTree, backCut, CutVar);
  std::vector<TH1D*> theHists = MakeHists(numBins, XBins);
  if (type == kROC) {
    const Int_t numPoints = numBins + 1;
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
    if (revRocCurve->Integral() > rocCurve->Integral()) {
      delete rocCurve;
      return revRocCurve;
    }
    else {
      delete revRocCurve;
      return rocCurve;
    }
  }
  else if (type == kSignificance) {
    const Int_t numPoints = numBins;
    Double_t XVals[numPoints];
    Double_t RevXVals[numPoints];
    Double_t YVals[numPoints];
    Double_t RevYVals[numPoints];
    for (Int_t i0 = 0; i0 < numPoints; i0++) {
      XVals[i0]    = theHists[0]->GetBinLowEdge(i0+1);
      RevXVals[i0] = theHists[0]->GetBinLowEdge(i0+1) + theHists[0]->GetBinWidth(i0+1);
      Double_t sigArea     = theHists[0]->Integral(i0, numBins + 1);
      Double_t revSigArea  = theHists[0]->Integral(numBins - i0, 0);
      Double_t backArea    = theHists[1]->Integral(i0, numBins + 1);
      Double_t revBackArea = theHists[1]->Integral(numBins - i0, 0);
      YVals[i0]    = sigArea/sqrt(sigArea + backArea);
      RevYVals[i0] = revSigArea/sqrt(revSigArea + revBackArea);
    }
    TGraph *sigCurve = new TGraph(numPoints,XVals,YVals);
    TGraph *revSigCurve = new TGraph(numPoints,RevXVals,RevYVals);
    if (revSigCurve->GetMaximum() > sigCurve->GetMaximum()) {
      delete sigCurve;
      return revSigCurve;
    }
    else {
      delete revSigCurve;
      return sigCurve;
    }
  }

  TGraph *fillerGraph = new TGraph();
  return fillerGraph;
}

//--------------------------------------------------------------------
Double_t*
PlotROC::GetOptimalCut(TString CutVar, TTree *sigTree, TTree *backTree, 
                       TString sigCut, TString backCut, Int_t numBins, Double_t *XBins)
{
  TGraph *theGraph = makeROC(CutVar, sigTree, backTree, sigCut, backCut, numBins, XBins, kSignificance);
  Double_t *YEntries = theGraph->GetY();
  Double_t *XEntries = theGraph->GetX();
  Double_t YMax = theGraph->GetMaximum();
  Double_t XMax = -100;
  for (Int_t i0 = 0; i0 < theGraph->GetN(); i0++) {
    if (YEntries[i0] == YMax) {
      XMax = XEntries[i0];
      break;
    }
  }
  delete theGraph;
  Double_t *returnInfo = new Double_t[2];
  returnInfo[0] = YMax;
  returnInfo[1] = XMax;
  return returnInfo;
}

//--------------------------------------------------------------------
Double_t*
PlotROC::GetOptimalCut(TString CutVar, TTree *sigTree, TTree *backTree, 
                       TString sigCut, TString backCut, Int_t numBins, 
                       Double_t XMin, Double_t XMax)
{
  Double_t binWidth = (XMax - XMin)/numBins;
  Double_t XBins[numBins+1];
  for (Int_t i0 = 0; i0 < numBins + 1; i0++)
    XBins[i0] = XMin + i0 * binWidth;

  return GetOptimalCut(CutVar,sigTree,backTree,sigCut,backCut,numBins,XBins);
}
