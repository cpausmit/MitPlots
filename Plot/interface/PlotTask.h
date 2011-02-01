//--------------------------------------------------------------------------------------------------
// $Id: PlotTask.h,v 1.2 2011/01/25 11:30:30 paus Exp $
//
// PlotTask
//
// This class implements PlotTask which allows to plot the samples with various options.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_PLOT_PLOTTASK_H
#define MITPLOTS_PLOT_PLOTTASK_H

#include <TH1D.h>
#include "MitPlots/Input/interface/TaskSamples.h"
#include "MitPlots/Style/interface/HistStyles.h"

namespace mithep 
{
  class PlotTask
  {
  public:
    PlotTask(const TaskSamples *taskSamples, const double lumi);
    ~PlotTask();

    // Define histogram ranges
    void                 SetHistMinimum   (double min) { fHistMinimum = min; }
    void                 SetHistMaximum   (double max) { fHistMaximum = max; }
    void                 SetHistXMinimum  (double min) { fHistXMinimum = min; }
    void                 SetHistXMaximum  (double max) { fHistXMaximum = max; }
    // Other plot parameters
    void                 SetHistStyles    (HistStyles *hS) { fHistStyles = hS; }
    void                 SetAxisTitles    (const char* xtit, const char* ytit = "Number of Events");
    void                 SetXLegend       (double x)   { fXLegend = x; }
    void                 SetYLegend       (double y)   { fYLegend = y; }
    void                 SetNRebin        (UInt_t n)   { fNRebin = n; }
    void                 SetNBins         (UInt_t n)   { fNBins = n;  }
    void                 SetDrawExp       (const char* draw, const char* sel);
    
  private:
    // Overlay the contribution in a single histogram (no adding/stacking)
    void                 PlotContributions(const char* dir, const char* hist);
    void                 PlotStack        (const char* dir, const char* hist);
    
    // Basic function to perfrom all reading and scaling operations
    void                 ScaleHistograms  (const char* dir, const char* hist);

    // Helper to set scale for a histogram
    void                 FindHistMaximum  ();
    void                 OverlayFrame     () const;
    void                 OverlayEmptyHist () const;

    const TaskSamples   *fTask;         // analysis task to be plotted
    HistStyles          *fHistStyles;   // style for plotting
    const double         fTargetLumi;   // target luminosity for task
    
    UInt_t               fIdxHistMax;   // index of histogram with maximum entry
    UInt_t               fNRebin;       // rebin parameter (default is 1)
    TH1D*                fEmptyHist;    // empty identical histogram
    TH1D*                fDataHist;     // data histogram if it exists
    double               fHistMinimum;  // histogram maximum to be displayed
    double               fHistMaximum;  // histogram minimum to be displayed
    double               fHistXMinimum; // histogram x-axis maximum to be displayed
    double               fHistXMaximum; // histogram x-axis minimum to be displayed
    TString              fAxisTitleX;   // x axis title
    TString              fAxisTitleY;   // y axis title
    double               fXLegend;      // x position of upper left legend box
    double               fYLegend;      // y position of upper left legend box
    UInt_t               fNBins;        // number of bins for TTree-derived histograms
    TString              fDrawExp;      // draw expression for TTree::Draw
    TString              fSelExp;       // selection expression for TTree::Draw
    std::vector<TH1D*>   fHists;        // list of scaled histograms
    std::vector<TH1D*>   fStackedHists; // list of scaled histograms
    
    ClassDef(PlotTask, 0) // PlotTask plots analysis task with various options
  };
}
#endif
