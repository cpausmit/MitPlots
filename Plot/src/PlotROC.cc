#include <iostream>

#include "MitPlots/Plot/interface/PlotROC.h"

using namespace mithep;

ClassImp(mithep::PlotROC)


//--------------------------------------------------------------------
TGraph*
PlotROC::makeROC(TString CutVar, TTree *sigTree, TTree *backTree, 
                 TString sigCut, TString backCut, Int_t numBins, Double_t *XBins)
{
  AddLine(sigTree, sigCut, CutVar);
  AddLine(backTree, backCut, CutVar);
  std::vector<TH1D*> theHists = MakeHists(numBins, XBins);
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
