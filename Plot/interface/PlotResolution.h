//--------------------------------------------------------------------------------------------------
// PlotResolution
//
// This class Plots the resolution of some variable as a function of some other variable
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_PLOTRESOLUTION_H
#define MITPLOTS_PLOT_PLOTRESOLUTION_H

#include <vector>

#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"

#include "MitPlots/Container/interface/LegendContainer.h"

namespace mithep
{
  class PlotResolution
  {
  public:
    PlotResolution();
    virtual ~PlotResolution();

    void        SetCanvasName         ( TString name )                                { fCanvasName = name;         }

    void        AddLine               ( TTree *tree, TString cut, TString expr_res );

    void        SetExprX              ( TString expr )                                { fInExprX = expr;            }
    void        SetDefaultTree        ( TTree *tree )                                 { fDefaultTree = tree;        }
    void        SetDefaultCut         ( TString cut )                                 { fDefaultCut = cut;          }
    void        SetDefaultExprRes     ( TString expr_res )                            { fDefaultExprRes = expr_res; }

    void        AddTree               ( TTree *tree )                                 { fInTrees.push_back(tree);   }
    void        AddCut                ( TString cut )                                 { fInCuts.push_back(cut);     }
    void        AddExprRes            ( TString expr )                                { fInExprRes.push_back(expr); }
    void        AddTreeCut            ( TTree *tree, TString cut );
    void        AddTreeExprRes        ( TTree *tree, TString expr_res );
    void        AddCutExprRes         ( TString cut, TString expr_res );

    void        SetLegendLimits       ( Double_t lim1, Double_t lim2, Double_t lim3, Double_t lim4 );

    // The defaults are set up for resolution, but response can be gotten too
    TCanvas*    MakeCanvas            ( LegendContainer *theLegend,
                                        TString XLabel, TString YLabel,
                                        Int_t NumXBins, Double_t MinX, Double_t MaxX,
                                        Int_t NumYBins, Double_t MinY, Double_t MaxY,
                                        Int_t ParamNumber = 2, Double_t FinalMin = 0, Double_t FinalMax = 2,
                                        Bool_t logY = false);

  private:

    UInt_t                     fNumPlots;           // Number of  plots that will be overlayed on the canvas
    TString                    fCanvasName;         // The name of the output canvas
    TTree*                     fDefaultTree;        // Default Tree if needed
    TString                    fDefaultCut;         // Default cut if needed
    TString                    fDefaultExprRes;     // Default resolution expression if needed

    TString                    fInExprX;            // X Expression should be constant

    Double_t                   l1;
    Double_t                   l2;
    Double_t                   l3;
    Double_t                   l4;

    std::vector<TTree*>        fInTrees;            // Holds all the trees for each line if needed
    std::vector<TString>       fInCuts;             // Holds the cuts for the trees if needed
    std::vector<TString>       fInExprRes;          // Holds multiple resolution expressions if needed

    ClassDef(PlotResolution,1)
  };
}

#endif
