//--------------------------------------------------------------------------------------------------
// PlotResolution
//
// This class Plots the resolution of some variable as a function of some other variable
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_PLOTRESOLUTION_H
#define MITPLOTS_PLOT_PLOTRESOLUTION_H

#include "TGraphErrors.h"
#include "TCanvas.h"

#include "MitPlots/Plot/interface/PlotBase.h"

namespace mithep
{
  class PlotResolution : public PlotBase
  {
  public:
    PlotResolution();
    virtual ~PlotResolution();

    void                         SetExprX                ( TString expr )                                 { fInExprX = expr;             }
    void                         SetParameterLimits      ( Int_t param, Double_t low, Double_t high );

    // These were used to get response corrected plots
    // Can probably use them for ratio plots in the future
    // These tools should also be moved to a utils or something. They don't require an object.
    std::vector<TGraphErrors*>   GetRatioToPoint         ( std::vector<TGraphErrors*> InGraphs, Double_t RatioPoint, Double_t PointError = 0 );
    std::vector<TGraphErrors*>   GetRatioToLine          ( std::vector<TGraphErrors*> InGraphs, TGraphErrors *RatioGraph );
    std::vector<TGraphErrors*>   GetRatioToLines         ( std::vector<TGraphErrors*> InGraphs, std::vector<TGraphErrors*> RatioGraphs );

    std::vector<TGraphErrors*>   MakeFitGraphs           ( Int_t NumXBins, Double_t MinX, Double_t MaxX,  // This does the fitting
                                                           Int_t NumYBins, Double_t MinY, Double_t MaxY,  // Specify which parameter of a Gaussian
                                                           Int_t ParamNumber = 1 );                       //   that you want to plot

    // The defaults are set up for resolution, but response can be gotten too
    TCanvas*                     MakeCanvas              ( std::vector<TGraphErrors*> theGraphs,
                                                           TString CanvasTitle, TString XLabel, TString YLabel,
                                                           Double_t YMin, Double_t YMax, Bool_t logY = false);

    void                         MakeCanvas              ( TString FileBase, std::vector<TGraphErrors*> theGraphs,
                                                           TString CanvasTitle, TString XLabel, TString YLabel,
                                                           Double_t YMin, Double_t YMax, Bool_t logY = false);

    void                         SetDumpingFits           ( Bool_t dump )                                 { fDumpingFits = dump;        }

  private:

    std::vector<Int_t>         fParams;             // This is vector used for setting parameter limits for fits
    std::vector<Double_t>      fParamLows;          // Low values of these parameters
    std::vector<Double_t>      fParamHighs;         // High values of these parameters

    TString                    fInExprX;            // X Expression should be constant

    Bool_t                     fDumpingFits;        // Bool used to dump .png files if you want to check fits
    Int_t                      fNumFitDumps;        // int to keep track of different number of fits

    ClassDef(PlotResolution,1)
  };
}

#endif
