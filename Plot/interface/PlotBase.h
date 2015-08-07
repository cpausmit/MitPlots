//--------------------------------------------------------------------------------------------------
// PlotBase
//
// This class holds the trees, expressions, and legend that will be used in plots
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_PLOT_PLOTBASE_H
#define MITPLOTS_PLOT_PLOTBASE_H

#include <vector>

#include "TTree.h"
#include "TString.h"

namespace mithep
{
  class PlotBase
  {
  public:
    PlotBase();
    virtual ~PlotBase();

    void                   SetCanvasName            ( TString name )                                { fCanvasName = name;          }
    void                   SetDefaultLineWidth      ( Int_t width )                                 { fDefaultLineWidth = width;   }
    void                   SetDefaultLineStyle      ( Int_t style )                                 { fDefaultLineStyle = style;   }
    void                   SetIncludeErrorBars      ( Bool_t include )                              { fIncludeErrorBars = include; }

    void                   AddLine                  ( TTree *tree, TString cut, TString expr );

    void                   SetExprX                 ( TString expr )                                { fInExprX = expr;             }
    void                   SetDefaultTree           ( TTree *tree )                                 { fDefaultTree = tree;         }
    void                   SetDefaultWeight         ( TString cut )                                 { fDefaultCut = cut;           }
    void                   SetDefaultExpr           ( TString expr )                                { fDefaultExpr = expr;         }

    void                   SetTreeList              ( std::vector<TTree*> treelist )                { fInTrees = treelist;         }
    void                   AddTree                  ( TTree *tree )                                 { fInTrees.push_back(tree);    }
    void                   AddWeight                ( TString cut )                                 { fInCuts.push_back(cut);      }
    void                   AddExpr                  ( TString expr )                                { fInExpr.push_back(expr);     }
    void                   ResetExpr                ()                                              { fInExpr.resize(0);           }
    void                   AddTreeWeight            ( TTree *tree, TString cut );
    void                   AddTreeExpr              ( TTree *tree, TString expr );
    void                   AddWeightExpr            ( TString cut, TString expr );

    void                   SetLegendLimits          ( Double_t lim1, Double_t lim2, Double_t lim3, Double_t lim4 );
    void                   AddLegendEntry           ( TString LegendEntry, Color_t ColorEntry );
    void                   AddLegendEntry           ( TString LegendEntry, Color_t ColorEntry, Int_t LineWidth, Int_t LineStyle );
    void                   SetLegendBorderSize      ( Int_t size )                                  { fLegendBorderSize = size;    }

  protected:

    UInt_t                     fPlotCounter;

    TString                    fCanvasName;         // The name of the output canvas
    Int_t                      fDefaultLineWidth;
    Int_t                      fDefaultLineStyle;
    Bool_t                     fIncludeErrorBars;

    TTree*                     fDefaultTree;        // Default Tree if needed
    TString                    fDefaultCut;         // Default cut if needed
    TString                    fDefaultExpr;        // Default resolution expression if needed

    TString                    fInExprX;            // X Expression should be constant

    Double_t                   l1;
    Double_t                   l2;
    Double_t                   l3;
    Double_t                   l4;
    Int_t                      fLegendBorderSize;

    std::vector<TTree*>        fInTrees;            // Holds all the trees for each line if needed
    std::vector<TString>       fInCuts;             // Holds the cuts for the trees if needed
    std::vector<TString>       fInExpr;             // Holds multiple resolution expressions if needed

    std::vector<TString>       fLegendEntries;
    std::vector<Color_t>       fLineColors;
    std::vector<Int_t>         fLineWidths;
    std::vector<Int_t>         fLineStyles;

    ClassDef(PlotBase,1)
  };
}

#endif
