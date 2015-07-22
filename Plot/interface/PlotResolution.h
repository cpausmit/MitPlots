//--------------------------------------------------------------------------------------------------
// PlotResolution
//
// This class Plots the resolution of some variable as a function of some other variable
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_PLOTRESOLUTION_H
#define MITPLOTS_PLOT_PLOTRESOLUTION_H

#include "TGraph.h"
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

    std::vector<TGraph*>   GetRatioToPoint          ( std::vector<TGraph*> InGraphs, Double_t RatioPoint );
    std::vector<TGraph*>   GetRatioToLine           ( std::vector<TGraph*> InGraphs, TGraph *RatioGraph );
    std::vector<TGraph*>   GetRatioToLines          ( std::vector<TGraph*> InGraphs, std::vector<TGraph*> RatioGraphs );

    std::vector<TGraph*>   MakeFitGraphs            ( Int_t NumXBins, Double_t MinX, Double_t MaxX,
                                                      Int_t NumYBins, Double_t MinY, Double_t MaxY,
                                                      Int_t ParamNumber = 1 );

    // The defaults are set up for resolution, but response can be gotten too
    TCanvas*               MakeCanvas               ( std::vector<TGraph*> theGraphs,
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
