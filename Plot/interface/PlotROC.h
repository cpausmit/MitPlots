#ifndef MITPLOTS_PLOT_PLOTROC_H
#define MITPLOTS_PLOT_PLOTROC_H

#include "TGraph.h"
#include "TTree.h"
#include "TString.h"

#include "MitPlots/Plot/interface/PlotHists.h"

namespace mithep
{
  class PlotROC : private PlotHists
  {
  public:
    PlotROC()            {};
    virtual ~PlotROC()   {};

    enum ROCType {
      kROC = 0,
      kSignificance
    };

    void            GetOptimalCut  ( Double_t &significance, Double_t &cutVal,
                                     TString CutVar, TTree *sigTree, TTree *backTree, 
                                     TString sigCut, TString backCut, Int_t NumBins, Double_t *XBins);

    void            GetOptimalCut  ( Double_t &significance, Double_t &cutVal,
                                     TString CutVar, TTree *sigTree, TTree *backTree, 
                                     TString sigCut, TString backCut, Int_t NumBins,
                                     Double_t XMin, Double_t XMax );

  private:

    TGraph         *makeROC        ( TString CutVar, TTree *sigTree, TTree *backTree, 
                                     TString sigCut, TString backCut, Int_t NumBins, Double_t *XBins,
                                     ROCType type = kROC );

    ClassDef(PlotROC, 1)
  };
}

#endif
