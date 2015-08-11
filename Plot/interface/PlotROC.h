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

    void            SetSignalTree( TTree *tree )                             { fSignalTree = tree;           }
    void            SetBackgroundTree( TTree *tree )                         { fBackgroundTree = tree;       }

    TGraph         *makeROC        ( TString CutVar, TTree *sigTree, TTree *backTree, 
                                     TString sigCut, TString backCut, Int_t NumBins, Double_t *XBins);

  private:

    TTree                    *fSignalTree;
    TTree                    *fBackgroundTree;

    TString                   fSignalCut;
    TString                   fBackgroundCut;

    ClassDef(PlotROC, 1)
  };
}

#endif
