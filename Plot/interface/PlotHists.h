//--------------------------------------------------------------------------------------------------
// PlotHists
//
// This class plots various configurations of histograms
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_PLOTHISTS_H
#define MITPLOTS_PLOT_PLOTHISTS_H

#include "TH1D.h"
#include "TCanvas.h"

#include "MitPlots/Plot/interface/PlotBase.h"

namespace mithep
{
  class PlotHists : public PlotBase
  {
  public:
    PlotHists();
    virtual ~PlotHists();

    void                   SetNormalizedHists       ( Bool_t b )        { fNormalizedHists = b;  }
    void                   SetFilledHistColors      ( Bool_t b )        { fFilledHistColors = b; }
    void                   SetStackHists            ( Bool_t b )        { fStackHists = b;       }

    std::vector<TH1D*>     MakeHists                ( Int_t NumXBins, Double_t *XBinsK);
    /* std::vector<TH1D*>     MakeHists                ( Int_t NumXBins, Double_t MinX, Double_t MaxX); */

    // The defaults are set up for hists, but response can be gotten too
    TCanvas*               MakeCanvas               ( std::vector<TH1D*> theHists,
                                                      TString CanvasTitle, TString XLabel, TString YLabel,
                                                      Bool_t logY = false);

  private:

    Bool_t    fNormalizedHists;
    Bool_t    fFilledHistColors;
    Bool_t    fStackHists;

    ClassDef(PlotHists,1)
  };
}

#endif
