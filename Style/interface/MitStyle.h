//--------------------------------------------------------------------------------------------------
// $Id: MitStyle.h,v 1.1.2.1 2010/10/03 04:08:49 paus Exp $
//
// MitStyle
//
// This class implements MitStyle which defines most relevant plot properties to give a reasonable
// plot. Of course every plot needs fine tuning, which has to be done by hand, as needed.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_STYLE_MITSTYLE_H
#define MITPLOTS_STYLE_MITSTYLE_H

#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>

namespace mithep 
{
  class MitStyle
  {
  public:
    MitStyle() { Init(); }
    virtual ~MitStyle() {}
    
    static void     Init();

    static TCanvas* MakeCanvas  (const char* name, const char *title);
    static void     InitSubPad  (TPad *pad, int i);
    static void     InitHistWide(TH1  *hist,
				 const char *xtit,
				 const char *ytit  = "Number of Entries",
				 EColor color = kBlack);
    static void     InitHist    (TH1  *hist,
				 const char *xtit,
				 const char *ytit  = "Number of Entries",
				 EColor color = kBlack);
    static void     SetStyleWide();
    static void     SetStyle    ();

    ClassDef(MitStyle, 0) // Interface to MitStyle
  };
}
#endif
