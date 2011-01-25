//--------------------------------------------------------------------------------------------------
// $Id: HistStyle.h,v 1.1.2.2 2010/10/12 21:25:04 paus Exp $
//
// HistStyle
//
// This class implements HistStyle which defines a set of style features to be used to
// create a nicely fitting plot of a histogram.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_STYLE_HISTSTYLE_H
#define MITPLOTS_STYLE_HISTSTYLE_H

#include <TString.h>

namespace mithep 
{
  class HistStyle
  {
  public:
    HistStyle();
    ~HistStyle() {}
    // return the attribute
    int             Color()       const { return fColor; }
    float           LineWidth()   const { return fLineWidth; }
    int             FillStyle()   const { return fFillStyle; }
    int             MarkerStyle() const { return fMarkerStyle; }
    float           MarkerSize()  const { return fMarkerSize; }
    // set the attribute
    void            SetColor      (int   i) { fColor       = i; }
    void            SetLineWidth  (float f) { fLineWidth   = f; }
    void            SetFillStyle  (int   i) { fFillStyle   = i; }
    void            SetMarkerStyle(int   i) { fMarkerStyle = i; }
    void            SetMarkerSize (float f) { fMarkerSize  = f; }
    // helpers
    void            Show()       const; // show sample properties
    
  private:
    // contents of the style
    int             fColor;
    float           fLineWidth;
    int             fFillStyle;
    int             fMarkerStyle;
    float           fMarkerSize;
    
    ClassDef(HistStyle, 0) // Interface to HistStyle
  };
}
#endif
