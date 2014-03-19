#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TStyle.h>
#include "MitPlots/Style/interface/MitStyle.h"

using namespace mithep;

void MitStyle::Init()
{
  // Initialization with proper defaults is the start

  const char* author   = "$Author: paus $$";
  const char* modified = "$Modified: Wed Mar 19 00:19:30 2014 by paus $$";
  printf(" MIT root style (%s,%s).\n",author,modified);
  printf("\n");
  printf(" Use: MitStyle::MakeCanvas(name,title)\n");
  printf("      MitStyle::InitSubPad(pad,nPad)\n");
  printf("      MitStyle::InitHist(hist,xTitle,yTitle,color)\n");
  printf("\n");
  SetStyle();
}

TCanvas* MitStyle::MakeCanvas(const char* name, const char *title)
{
  // Make a canvas with good initial settings

  TCanvas *canvas = new TCanvas(name,title);

  // the default should be taken from MitStyle::Init()

  //// General overall stuff
  //canvas->SetFillColor      (0);
  //canvas->SetBorderMode     (0);
  //canvas->SetBorderSize     (10);
  //// Set margins to reasonable defaults
  //canvas->SetLeftMargin     (0.20);
  //canvas->SetRightMargin    (0.05);
  //canvas->SetTopMargin      (0.08);
  //canvas->SetBottomMargin   (0.15);
  //// Setup a frame which makes sense
  //canvas->SetFrameFillStyle (0);
  //canvas->SetFrameLineStyle (0);
  //canvas->SetFrameBorderMode(0);
  //canvas->SetFrameBorderSize(10);
  //canvas->SetFrameFillStyle (0);
  //canvas->SetFrameLineStyle (0);
  //canvas->SetFrameBorderMode(0);
  //canvas->SetFrameBorderSize(10);

  return canvas;
}

void MitStyle::InitSubPad(TPad* pad, int i)
{
  // Initializing a sub pad

  pad->cd(i);
  TPad *tmpPad = (TPad*) pad->GetPad(i);
  tmpPad->SetLeftMargin  (0.20);
  tmpPad->SetTopMargin   (0.05);
  tmpPad->SetRightMargin (0.07);
  tmpPad->SetBottomMargin(0.15);
  return;
}

void MitStyle::InitHistWide(TH1 *hist, const char *xtit, const char *ytit, EColor color)
{
  InitHist(hist,xtit,ytit,color);
  hist->SetTitleOffset(1.100,"Y");
}

void MitStyle::InitHist(TH1 *hist, const char *xtit, const char *ytit, EColor color)
{
  // Initializing a histogram

  hist->SetTitle      ("");  
  hist->SetXTitle     (xtit);
  hist->SetYTitle     (ytit);

  hist->SetLineColor  (color);
  hist->SetLineWidth  (2.0);

  hist->SetMarkerStyle(20);
  hist->SetMarkerColor(color);
  hist->SetMarkerSize (0.6);

  hist->SetTitleFont  (42   ,"X");
  hist->SetTitleSize  (0.055,"X");
  hist->SetTitleOffset(1.100,"X");
  hist->SetLabelOffset(0.010,"X");
  hist->SetLabelSize  (0.050,"X");
  hist->SetLabelFont  (42   ,"X");
  hist->SetTickLength (-0.01,"X");

  hist->SetTitleFont  (42   ,"Y");
  hist->SetTitleSize  (0.055,"Y");
  hist->SetTitleOffset(1.700,"Y");
  hist->SetLabelOffset(0.010,"Y");
  hist->SetLabelSize  (0.050,"Y");
  hist->SetLabelFont  (42   ,"Y");
  hist->SetTickLength (-0.01,"Y");

  return;
}

void MitStyle::SetStyleWide()
{
  SetStyle();
  TStyle *MitStyle = gStyle;// new TStyle("MIT-Style","The Perfect Style for Plots ;-)");
  MitStyle->SetCanvasDefW (1100);
  MitStyle->SetPadLeftMargin(0.12);

  //MitStyle->SetTitleOffset(1.200,"Y");

  //MitStyle->SetPadRightMargin(0.20);
  //MitStyle->SetPadLeftMargin (0.05);
}

void MitStyle::SetStyle()
{
  // Setting style parameters

  TStyle *MitStyle = gStyle;// new TStyle("MIT-Style","The Perfect Style for Plots ;-)");
  //gStyle = MitStyle;

  // Canvas
  MitStyle->SetCanvasColor     (0);
  MitStyle->SetCanvasBorderSize(10);
  MitStyle->SetCanvasBorderMode(0);
  MitStyle->SetCanvasDefH      (700);
  MitStyle->SetCanvasDefW      (700);
  MitStyle->SetCanvasDefX      (100);
  MitStyle->SetCanvasDefY      (100);

  // Pads
  MitStyle->SetPadColor       (0);
  MitStyle->SetPadBorderSize  (10);
  MitStyle->SetPadBorderMode  (0);
  MitStyle->SetPadBottomMargin(0.13);
  MitStyle->SetPadTopMargin   (0.04);
  MitStyle->SetPadLeftMargin  (0.18);
  MitStyle->SetPadRightMargin (0.04);
  MitStyle->SetPadGridX       (0);
  MitStyle->SetPadGridY       (0);
  MitStyle->SetPadTickX       (0);
  MitStyle->SetPadTickY       (0);

  // Frames
  MitStyle->SetFrameFillStyle ( 0);
  MitStyle->SetFrameFillColor ( 0);
  MitStyle->SetFrameLineColor ( 1);
  MitStyle->SetFrameLineStyle ( 0);
  MitStyle->SetFrameLineWidth ( 1);
  MitStyle->SetFrameBorderSize(10);
  MitStyle->SetFrameBorderMode( 0);

  // Histograms
  MitStyle->SetHistFillColor(2);
  MitStyle->SetHistFillStyle(0);
  MitStyle->SetHistLineColor(1);
  MitStyle->SetHistLineStyle(0);
  MitStyle->SetHistLineWidth(2);
  MitStyle->SetNdivisions(505);

  // Functions
  MitStyle->SetFuncColor(1);
  MitStyle->SetFuncStyle(0);
  MitStyle->SetFuncWidth(2);

  // Various
  MitStyle->SetMarkerStyle(20);
  MitStyle->SetMarkerColor(kBlack);
  MitStyle->SetMarkerSize (1.2);

  MitStyle->SetTitleSize  (0.055,"X");
  MitStyle->SetTitleOffset(1.200,"X");
  MitStyle->SetLabelOffset(0.005,"X");
  MitStyle->SetLabelSize  (0.050,"X");
  MitStyle->SetLabelFont  (42   ,"X");
  MitStyle->SetTickLength (-0.03,"X");

  MitStyle->SetStripDecimals(kFALSE);

  MitStyle->SetTitleSize  (0.055,"Y");
  MitStyle->SetTitleOffset(1.800,"Y");
  MitStyle->SetLabelOffset(0.010,"Y");
  MitStyle->SetLabelSize  (0.050,"Y");
  MitStyle->SetLabelFont  (42   ,"Y");
  MitStyle->SetTickLength (-0.03,"Y");

  MitStyle->SetTextSize   (0.055);
  MitStyle->SetTextFont   (42);

  MitStyle->SetStatFont   (42);
  MitStyle->SetTitleFont  (42);
  MitStyle->SetTitleFont  (42,"X");
  MitStyle->SetTitleFont  (42,"Y");

  MitStyle->SetOptStat    (0);
  return;
}
