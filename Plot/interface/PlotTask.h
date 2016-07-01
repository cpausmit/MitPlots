//--------------------------------------------------------------------------------------------------
// PlotTask
//
// This class implements PlotTask which allows to plot the samples with various options.
//
// Authors: C.Paus, J.Bendavid
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_PLOTTASK_H
#define MITPLOTS_PLOT_PLOTTASK_H

#include <TH1D.h>
#include <TCanvas.h>
#include "MitPlots/Input/interface/TaskSamples.h"
#include "MitPlots/Style/interface/HistStyles.h"

namespace mithep 
{
  enum PlotType {
    Stacked,          // plot stacked results
    Contributions,    // plot contributions
    Normalized        // plot normalized contributiuons
  };
  
  class PlotTask
  {
  public:
    PlotTask(TaskSamples *taskSamples, const double lumi);
    virtual ~PlotTask();

    // Define histogram ranges
    void                 SetHistRanges    (double xmin,   double xmax,
					   double ymin=0, double ymax=0) {
                                           fHistXMinimum = xmin; fHistXMaximum = xmax;
                                           fHistMinimum  = ymin; fHistMaximum  = ymax; }
    void                 SetHistMinimum   (double min)     { fHistMinimum = min; }
    void                 SetHistMaximum   (double max)     { fHistMaximum = max; }
    void                 SetHistXMinimum  (double min)     { fHistXMinimum = min; }
    void                 SetHistXMaximum  (double max)     { fHistXMaximum = max; }
    void                 SetPngFileName   (const char *n)  { fImageFileName = n; }
    void                 SetImageFileName (const char *n)  { fImageFileName = n; }
    // Other plot parameters
    void                 SetHistStyles    (HistStyles *hS) { fHistStyles = hS; }
    void                 SetAxisTitles    (const char* xtit, const char* ytit = "Number of Events", const char* xunit = "");
    void                 SetLogy          (bool b)         { fLogy = b; }
    void                 SetXLegend       (double x)       { fXLegend = x; }
    void                 SetYLegend       (double y)       { fYLegend = y; }
    void                 SetNRebin        (UInt_t n)       { fNRebin = n; }
    void                 SetNBins         (UInt_t n)       { fNBins = n;  }
    void                 SetDrawExp       (const char* draw, const char* sel);
    
    void                 SetPuTarget      (const TH1D *h)  { fPuTarget = h; }
    
    static float         PuWeight         (Int_t npu);
    
    
    // Overlay the contribution in a single histogram (no adding/stacking)
    void                 Plot                (PlotType pType, const char* obj,
                                              const char* draw = "", const char* cuts = "",
                                              const char* samp = "");
                                              // last argument to specify sample name for saving histograms to rootfile
                                              // if you don't want to save, put "" for this argument

    // Make an additional image. Use name for the file name if specified. Otherwise use fImageFileName
    void                 SavePlot(char const* name = 0);

    // Overlay the contribution in a single histogram (no adding/stacking)
    void                 PlotRatio           (const char* obj,
                                              const char* draw = "", const char* cuts = "",
                                              const char* samp = "");

  private:
    void                 CollectNormalized   (const char* hist);
    void                 CollectContributions(const char* hist);
    void                 DrawFrame           ();
    void                 DrawHistograms      ();
    void                 PlotStack           (const char* hist, bool rescale = kFALSE);
    
    // Basic function to perfrom all reading and scaling operations
    void                 ScaleHistograms     (const char* hist);

    //Save temporary histograms from Plot to Rootfile
    void                 SaveHistos          (const char* obj, const char* out, const char* obs);

    // Helper to set scale for a histogram
    void                 FindHistMaximum     ();
    void                 FindStackHistMaximum();
    void                 OverlayFrame        () const;
    void                 OverlayStackFrame   () const;
    void                 OverlayEmptyHist    () const;

    TaskSamples         *fTask;         // analysis task to be plotted
    HistStyles          *fHistStyles;   // styles for plotting
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
    TString              fAxisUnitX;    // x axis unit
    bool                 fLogy;         // use log scale on y axis?
    double               fXLegend;      // x position of upper left legend box
    double               fYLegend;      // y position of upper left legend box
    UInt_t               fNBins;        // number of bins for TTree-derived histograms
    TString              fDrawExp;      // draw expression for TTree::Draw
    TString              fSelExp;       // selection expression for TTree::Draw
    TString              fImageFileName;// name of the image file for the plots
    std::vector<TH1D*>   fHists;        // list of scaled histograms
    std::vector<TH1D*>   fStackedHists; // list of scaled histograms

    std::vector<TH1D*>   fHistsToPlot;  // list histograms ready to plot

    TCanvas             *fCanvas;       // canvas

    const TH1D          *fPuTarget;
    static const TH1D   *sPuWeights;

    ClassDef(PlotTask, 0) // PlotTask plots analysis task with various options
  };
}
#endif
