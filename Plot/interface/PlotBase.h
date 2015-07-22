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

    void                   SetCanvasName            ( TString name )                                { fCanvasName = name;         }
    void                   SetLineWidth             ( Int_t width )                                 { fLineWidth = width;         }

    void                   AddLine                  ( TTree *tree, TString cut, TString expr );

    void                   SetExprX                 ( TString expr )                                { fInExprX = expr;            }
    void                   SetDefaultTree           ( TTree *tree )                                 { fDefaultTree = tree;        }
    void                   SetDefaultWeight         ( TString cut )                                 { fDefaultCut = cut;          }
    void                   SetDefaultExprY          ( TString expr )                                { fDefaultExprY = expr;       }

    void                   SetTreeList              ( std::vector<TTree*> treelist )                { fInTrees = treelist;        }
    void                   AddTree                  ( TTree *tree )                                 { fInTrees.push_back(tree);   }
    void                   AddWeight                ( TString cut )                                 { fInCuts.push_back(cut);     }
    void                   AddExprY                 ( TString expr )                                { fInExprY.push_back(expr);   }
    void                   ResetExprY               ()                                              { fInExprY.resize(0);         }
    void                   AddTreeWeight            ( TTree *tree, TString cut );
    void                   AddTreeExprY             ( TTree *tree, TString expr );
    void                   AddWeightExprY           ( TString cut, TString expr );

    void                   SetLegendLimits          ( Double_t lim1, Double_t lim2, Double_t lim3, Double_t lim4 );
    void                   AddLegendEntry           ( TString LegendEntry, Color_t ColorEntry );

  protected:

    TString                    fCanvasName;         // The name of the output canvas
    Int_t                      fLineWidth;

    TTree*                     fDefaultTree;        // Default Tree if needed
    TString                    fDefaultCut;         // Default cut if needed
    TString                    fDefaultExprY;       // Default resolution expression if needed

    TString                    fInExprX;            // X Expression should be constant

    Double_t                   l1;
    Double_t                   l2;
    Double_t                   l3;
    Double_t                   l4;

    std::vector<TTree*>        fInTrees;            // Holds all the trees for each line if needed
    std::vector<TString>       fInCuts;             // Holds the cuts for the trees if needed
    std::vector<TString>       fInExprY;            // Holds multiple resolution expressions if needed

    std::vector<TString>       fLegendEntries;
    std::vector<Color_t>       fLineColors;

    ClassDef(PlotBase,1)
  };
}

#endif
