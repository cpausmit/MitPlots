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

    void                   SetParameterLimits       ( Int_t param, Double_t low, Double_t high );

    std::vector<TGraphErrors*>   GetRatioToPoint    ( std::vector<TGraphErrors*> InGraphs, Double_t RatioPoint, Double_t PointError = 0 );
    std::vector<TGraphErrors*>   GetRatioToLine     ( std::vector<TGraphErrors*> InGraphs, TGraphErrors *RatioGraph );
    std::vector<TGraphErrors*>   GetRatioToLines    ( std::vector<TGraphErrors*> InGraphs, std::vector<TGraphErrors*> RatioGraphs );

    std::vector<TGraphErrors*>   MakeFitGraphs      ( Int_t NumXBins, Double_t MinX, Double_t MaxX,
                                                      Int_t NumYBins, Double_t MinY, Double_t MaxY,
                                                      Int_t ParamNumber = 1 );

    // The defaults are set up for resolution, but response can be gotten too
    TCanvas*               MakeCanvas               ( std::vector<TGraphErrors*> theGraphs,
                                                      TString CanvasTitle, TString XLabel, TString YLabel,
                                                      Double_t YMin, Double_t YMax, Bool_t logY = false);

    void                   SetDumpingFits           ( Bool_t dump )                                 { fDumpingFits = dump;        }

  private:

    std::vector<Int_t>         fParams;
    std::vector<Double_t>      fParamLows;
    std::vector<Double_t>      fParamHighs;

    Bool_t                     fDumpingFits;
    Int_t                      fNumFitDumps;

    ClassDef(PlotResolution,1)
  };
}

#endif
