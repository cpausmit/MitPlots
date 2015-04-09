//--------------------------------------------------------------------------------------------------
// $Id: HistStyles.h,v 1.1.2.2 2010/10/12 21:25:04 paus Exp $
//
// HistStyles
//
// This class implements HistStyles which is just a list of histogram and text styles needed to
// style a plot in PlotTask. There is a predefined default set of styles and there is a series of
// styles which can be defined by the user.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_STYLE_HISTSTYLES_H
#define MITPLOTS_STYLE_HISTSTYLES_H

#include <TH1.h>
#include <vector>
#include "MitPlots/Style/interface/HistStyle.h"

namespace mithep 
{
  class HistStyles
  {
  public:
    HistStyles();
    virtual ~HistStyles() {}
    // access to the the style contents
    const UInt_t            *NStyles ()         const { return &fNStyles; }
    const HistStyle         *GetStyle(UInt_t i) const; // return 'i'th Monte Carlo style
    const HistStyle         *GetDataStyle()     const; // return the data style
    // add styles
    void                     Clear();                  // clear Monte Carlo histogram style
    HistStyle               *AddStyle();               // add another Monte Carlo histogram style
    HistStyle               *SetDataStyle();           // add the data histogram style
    // helpers
    void                     Show()             const; // show style list properties

    // for looping
    const HistStyle         *CurrentStyle()     const; // return the present Monte Carlo style
    void                     NextStyle();              // return the next Monte Carlo style
    void                     PreviousStyle();          // return the previous Monte Carlo style
    void                     ResetStyle();             // return the first Monte Carlo style
    
    void                     ApplyCurrentStyle(TH1 *h) const; // apply present Monte Carlo style
    void                     ApplyDataStyle   (TH1 *h) const; // apply present data style

  private:
    // contents of the style
    UInt_t                   fNStyles;    // number of stored styles
    UInt_t                   fIStyle;     // index of present style
    std::vector<HistStyle>   fStyles;     // list of styles
    HistStyle               *fDataStyle;  // data sample style
    
    ClassDef(HistStyles, 0) // Interface to HistStyles
  };
}
#endif
