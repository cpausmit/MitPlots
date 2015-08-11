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
    PlotROC();
    virtual ~PlotROC()   {}

    void                    SetSignalTree        ( TTree *tree )                     { fInTrees[0] = tree;           }
    void                    SetBackgroundTree    ( TTree *tree )                     { fInTrees[1] = tree;           }
    void                    SetSignalCut         ( TString cut )                     { fInCuts[0] = cut;             }
    void                    SetBackgroundCut     ( TString cut )                     { fInCuts[1] = cut;             }

    void                    ResetVars            ()                                  { fROCVars.resize(0);           }
    void                    AddVar               ( TString var )                     { fROCVars.push_back(var);      }

    TGraph                 *MakeROC              ( TString CutVar, Int_t NumBins = 500 );
    std::vector<TGraph*>    MakeROCs             ( Int_t NumBins = 500 );

    TCanvas                *MakeCanvas           ( Int_t NumBins = 500, Bool_t logY = false, TString CanvasTitle = "",
                                                   TString XLabel = "#epsilon_{Signal}", 
                                                   TString YLabel = "#epsilon_{Background}" );

    void                    MakeCanvas           ( TString FileBase, Int_t NumBins = 500,
                                                   Bool_t logY = false, TString CanvasTitle = "",
                                                   TString XLabel = "#epsilon_{Signal}", 
                                                   TString YLabel = "#epsilon_{Background}" );

  private:

    std::vector<TString>    fROCVars;

    ClassDef(PlotROC, 1)
  };
}

#endif
